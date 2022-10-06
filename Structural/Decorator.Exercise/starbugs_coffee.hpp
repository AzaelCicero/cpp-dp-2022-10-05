#ifndef COFFEEHELL_HPP_
#define COFFEEHELL_HPP_

#include <iostream>
#include <string>
#include <memory>

class Coffee
{
public:
    virtual ~Coffee() = default;

    virtual float get_total_price() const = 0;
    virtual std::string get_description() const = 0;
    virtual void prepare() = 0;
};

class CoffeeBase : public Coffee
{
    float price_;
    std::string description_;

public:
    CoffeeBase(float price, const std::string& description) : price_{price}, description_{description}
    {
    }

    float get_total_price() const override
    {
        return price_;
    }

    std::string get_description() const override
    {
        return description_;
    }
};

class Espresso : public CoffeeBase
{
public:
    Espresso(float price = 4.0, const std::string& description = "Espresso")
        : CoffeeBase{price, description}
    {
    }

    void prepare() override
    {
        std::cout << "Making a perfect espresso: 7 g, 15 bar and 24 sec.\n";
    }
};

class Cappuccino : public CoffeeBase
{
public:
    Cappuccino(float price = 6.0, const std::string& description = "Cappuccino")
        : CoffeeBase{price, description}
    {
    }

    void prepare() override
    {
        std::cout << "Making a perfect cappuccino.\n";
    }
};

class Latte : public CoffeeBase
{
public:
    Latte(float price = 8.0, const std::string& description = "Latte")
        : CoffeeBase{price, description}
    {
    }

    void prepare() override
    {
        std::cout << "Making a perfect latte.\n";
    }
};

// TO DO: Condiments: Whipped: 2.5$, Whisky: 6.0$, ExtraEspresso: 4.0$

class CoffeDecorator : public Coffee{
public:
    CoffeDecorator(std::unique_ptr<Coffee> decorated) : decorated_(std::move(decorated))
    {
    }

    float get_total_price() const override
    {
        return decorated_->get_total_price();
    }

    std::string get_description() const override{
        return decorated_->get_description();
    }

    void prepare() override
    {
        return decorated_->prepare();
    }

private:
    std::unique_ptr<Coffee> decorated_;
};

class WhippedCoffeDecorator : public CoffeDecorator
{
public:
using CoffeDecorator::CoffeDecorator;


float get_total_price() const override
{
    return 2.5f + CoffeDecorator::get_total_price();
}

std::string get_description() const override{
    return CoffeDecorator::get_description() + " with cream";
}

void prepare() override
{
    CoffeDecorator::prepare();
    std::cout << "Adding cream. \n";
}
};


class WhiskyCoffeDecorator : public CoffeDecorator
{
public:
using CoffeDecorator::CoffeDecorator;


float get_total_price() const override
{
    return 6.f + CoffeDecorator::get_total_price();
}

std::string get_description() const override{
    return CoffeDecorator::get_description() + " with whisky";
}

void prepare() override
{
    CoffeDecorator::prepare();
    std::cout << "Adding whisky. \n";
}
};

class ExtraExpressoCoffeDecorator : public CoffeDecorator
{
public:
using CoffeDecorator::CoffeDecorator;


float get_total_price() const override
{
    return 4.f + CoffeDecorator::get_total_price();
}

std::string get_description() const override{
    return CoffeDecorator::get_description() + " and extra expresso";
}

void prepare() override
{
    CoffeDecorator::prepare();
    std::cout << "Adding expresso. \n";
}
};

#endif /*COFFEEHELL_HPP_*/
