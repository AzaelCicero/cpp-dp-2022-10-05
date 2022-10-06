#include "starbugs_coffee.hpp"
#include <memory>
#include <functional>

void client(std::unique_ptr<Coffee> coffee)
{
    std::cout << "Description: " << coffee->get_description() << "; Price: " << coffee->get_total_price() << std::endl;
    coffee->prepare();
}

class CoffeBuilder
{
public:
    CoffeBuilder(std::function<std::unique_ptr<Coffee>()> base) : current_(std::move(base))
    {}

    CoffeBuilder & with_cream()
    {
        current_ = [prev = std::move(current_)](){
            return std::make_unique<WhippedCoffeDecorator>(prev());
        };
        return *this;
    }
    
    CoffeBuilder & with_whisky()
    {
        current_ = [prev = std::move(current_)](){
            return std::make_unique<WhiskyCoffeDecorator>(prev());
        };
        return *this;
    }
    
    CoffeBuilder & with_extra_expresso()
    {
        current_ = [prev = std::move(current_)](){
            return std::make_unique<ExtraExpressoCoffeDecorator>(prev());
        };
        return *this;
    }

    std::unique_ptr<Coffee> create()
    {
        return current_();
    }
private:
    std::function<std::unique_ptr<Coffee>()> current_;
};

int main()
{
    CoffeBuilder maker {std::make_unique<Espresso>};
    maker.with_cream().with_extra_expresso().with_whisky();
    
    std::unique_ptr<Coffee> cf = maker.create();
    
    client(std::move(cf));
}
