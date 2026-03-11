# Order Book Matching Engine

This project implements a simple Order Book Matching Engine in C++.

Features:
- Add BUY and SELL orders
- Automatic order matching
- Cancel orders
- Displays remaining order book

Technologies Used:
- C++
- STL (map, deque, unordered_map)

How to Run:

1. Compile
g++ main.cpp OrderBook.cpp -o orderbook

2. Run
./orderbook

Sample Input:
O1 BUY 100.50 10
O2 BUY 100.50 5
O3 SELL 100.50 8
O4 SELL 99.00 20
CANCEL O2

Sample Output:
TRADE O1 O3 100.50 8
TRADE O1 O4 99.00 2
