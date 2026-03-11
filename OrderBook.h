#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <map>
#include <deque>
#include <unordered_map>
#include <functional>
#include "Order.h"

class OrderBook {

private:

    std::map<double, std::deque<Order>, std::greater<double>> bids;
    std::map<double, std::deque<Order>> asks;

    std::unordered_map<std::string, std::pair<std::string,double>> orderIndex;

public:

    void addOrder(Order order);
    void matchBuy(Order order);
    void matchSell(Order order);
    void cancelOrder(std::string id);
    void printBook();
};

#endif