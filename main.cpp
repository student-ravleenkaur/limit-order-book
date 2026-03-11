#include <iostream>
#include <sstream>
#include "OrderBook.h"

int main() {

    OrderBook book;
    std::string line;

    while(std::getline(std::cin, line)) {

        std::stringstream ss(line);

        if(line.find("CANCEL") == 0) {

            std::string cmd, id;
            ss >> cmd >> id;

            book.cancelOrder(id);
        }

        else {

            std::string id, side;
            double price;
            int qty;

            ss >> id >> side >> price >> qty;

            Order order(id, side, price, qty);

            book.addOrder(order);
        }
    }

    book.printBook();
}
