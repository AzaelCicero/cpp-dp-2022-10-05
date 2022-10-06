#include <algorithm>
#include <cassert>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include "shape.hpp"
#include "shape_factories.hpp"

using namespace std;
using namespace Drawing;
using namespace Drawing::IO;

class GraphicsDoc
{
    vector<unique_ptr<Shape>> shapes_;
    ShapeFactory& shape_factory_;
    ShapeRWFactory& shape_rw_factory_;

public:
    GraphicsDoc(ShapeFactory& shape_factory, ShapeRWFactory& shape_rw_factory)
        : shape_factory_{shape_factory}
        , shape_rw_factory_{shape_rw_factory}
    {
    }

    GraphicsDoc(const GraphicsDoc & other)
        : shape_factory_{other.shape_factory_}
        , shape_rw_factory_{other.shape_rw_factory_}
    {
        std::transform(other.shapes_.begin(), other.shapes_.end(), std::back_inserter(shapes_), [](const auto & s)
        {
            return s->clone();
        });
    }

    void add(unique_ptr<Shape> shp)
    {
        shapes_.push_back(std::move(shp));
    }

    void render()
    {
        for (const auto& shp : shapes_)
            shp->draw();
    }

    void load(const string& filename)
    {
        ifstream file_in{filename};

        if (!file_in)
        {
            cout << "File not found!" << endl;
            exit(1);
        }

        while (file_in)
        {
            string shape_id;
            file_in >> shape_id;

            if (!file_in)
                return;

            cout << "Loading " << shape_id << "..." << endl;

            auto shape = shape_factory_.create(shape_id);
            auto shape_rw = shape_rw_factory_.create(make_type_index(*shape));

            shape_rw->read(*shape, file_in);

            shapes_.push_back(std::move(shape));
        }
    }

    void save(const string& filename)
    {
        ofstream file_out{filename};

        for (const auto& shp : shapes_)
        {
            auto shape_rw = shape_rw_factory_.create(make_type_index(*shp));
            shape_rw->write(*shp, file_out);
        }
    }

    GraphicsDoc& operator=(const GraphicsDoc & other)
    {

        return *this;
    }
};

int main()
{
    cout << "Start..." << endl;

    GraphicsDoc doc(SingletonShapeFactory::instance(), SingletonShapeRWFactory::instance());

    doc.load("drawing.txt");

    cout << "\n";

    doc.render();

    GraphicsDoc doc2 = doc;

    doc2.save("new_drawing.txt");
}
