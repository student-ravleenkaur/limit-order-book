#include "OrderBook.h"
#include <iostream>
#include <algorithm>

void OrderBook::addOrder(Order order) {

    if(order.side == "BUY")
        matchBuy(order);
    else
        matchSell(order);
}

void OrderBook::matchBuy(Order order) {

    while(order.quantity > 0 && !asks.empty()) {

        auto bestAsk = asks.begin();
        double askPrice = bestAsk->first;

        if(order.price != 0 && order.price < askPrice)
            break;

        Order &sellOrder = bestAsk->second.front();

        int tradeQty = std::min(order.quantity, sellOrder.quantity);

        std::cout << "TRADE "
                  << order.id << " "
                  << sellOrder.id << " "
                  << askPrice << " "
                  << tradeQty << std::endl;

        order.quantity -= tradeQty;
        sellOrder.quantity -= tradeQty;

        if(sellOrder.quantity == 0) {
            bestAsk->second.pop_front();
            if(bestAsk->second.empty())
                asks.erase(bestAsk);
        }
    }

    if(order.quantity > 0 && order.price != 0) {
        bids[order.price].push_back(order);
        orderIndex[order.id] = {"BUY", order.price};
    }
}

void OrderBook::matchSell(Order order) {

    while(order.quantity > 0 && !bids.empty()) {

        auto bestBid = bids.begin();
        double bidPrice = bestBid->first;

        if(order.price != 0 && order.price > bidPrice)
            break;

        Order &buyOrder = bestBid->second.front();

        int tradeQty = std::min(order.quantity, buyOrder.quantity);

        std::cout << "TRADE "
                  << buyOrder.id << " "
                  << order.id << " "
                  << bidPrice << " "
                  << tradeQty << std::endl;

        order.quantity -= tradeQty;
        buyOrder.quantity -= tradeQty;

        if(buyOrder.quantity == 0) {
            bestBid->second.pop_front();
            if(bestBid->second.empty())
                bids.erase(bestBid);
        }
    }

    if(order.quantity > 0 && order.price != 0) {
        asks[order.price].push_back(order);
        orderIndex[order.id] = {"SELL", order.price};
    }
}

void OrderBook::cancelOrder(std::string id) {

    if(orderIndex.find(id) == orderIndex.end())
        return;

    auto info = orderIndex[id];
    std::string side = info.first;
    double price = info.second;

    if(side == "BUY") {

        auto it = bids.find(price);

        if(it != bids.end()) {

            auto &dq = it->second;

            for(auto iter = dq.begin(); iter != dq.end(); iter++) {

                if(iter->id == id) {
                    dq.erase(iter);
                    break;
                }
            }

            if(dq.empty())
                bids.erase(it);
        }

    } else {

        auto it = asks.find(price);

        if(it != asks.end()) {

            auto &dq = it->second;

            for(auto iter = dq.begin(); iter != dq.end(); iter++) {

                if(iter->id == id) {
                    dq.erase(iter);
                    break;
                }
            }

            if(dq.empty())
                asks.erase(it);
        }
    }

    orderIndex.erase(id);
}

void OrderBook::printBook() {

    std::cout << "--- Book ---" << std::endl;

    int count = 0;

    for(auto &a : asks) {

        int total = 0;

        for(auto &o : a.second)
            total += o.quantity;

        std::cout << "ASK: " << a.first << " x " << total << std::endl;

        if(++count == 5) break;
    }

    count = 0;

    for(auto &b : bids) {

        int total = 0;

        for(auto &o : b.second)
            total += o.quantity;

        std::cout << "BID: " << b.first << " x " << total << std::endl;

        if(++count == 5) break;
    }
}