#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <memory>

#include "point.hpp"
#include <memory>

namespace Drawing
{
    class Shape
    {
    public:
        virtual ~Shape() = default;
        virtual void move(int dx, int dy) = 0;
        virtual void draw() const = 0;
        
        virtual std::unique_ptr<Shape> clone() const = 0;
    };
    
    template<class TDerived>
    class CloneableShape : public Shape
    {
        std::unique_ptr<Shape> clone() const override
        {
            return std::make_unique<TDerived>(static_cast<const TDerived &>(*this));
        }
    };

    template<class TDerived>
    class ShapeBase : public CloneableShape<TDerived>
    {
        Point coord_; // composition
    public:
        Point coord() const
        {
            return coord_;
        }

        void set_coord(const Point& pt)
        {
            coord_ = pt;
        }

        ShapeBase(int x = 0, int y = 0)
            : coord_{x, y}
        {
        }

        void move(int dx, int dy) override
        {
            coord_.translate(dx, dy);
        }
    };
}

#endif // SHAPE_HPP
