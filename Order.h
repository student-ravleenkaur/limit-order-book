#ifndef ORDER_H
#define ORDER_H

#include <string>

struct Order {
    std::string id;
    std::string side;
    double price;
    int quantity;

    Order(std::string id, std::string side, double price, int quantity)
        : id(id), side(side), price(price), quantity(quantity) {}
};

#endif