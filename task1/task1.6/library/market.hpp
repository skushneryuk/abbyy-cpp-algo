#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <assert.h>


#include <deals.hpp>
#include <operations.hpp>

// Structures
using std::deque;
using std::vector;
using std::string;
using std::unordered_map;

// IO
using std::ostream;
using std::istream;

enum class MarketStrategyType { sell_last, sell_first };
enum class StockStateType { shorts, longs, empty };

class Market {
private:
    unordered_map<string, deque<Operation>> operations;
    unordered_map<string, StockStateType> stock_states;
    vector<Deal> deals;

    MarketStrategyType strategy = MarketStrategyType::sell_last;
    istream& input;
    ostream& output;

    void ProcessOperation(const Operation& op);
    void FinalizeDeals();
    void SortDeals();
    void OutputDeals();

public:
    Market(MarketStrategyType strategy = MarketStrategyType::sell_first,
           istream& input = std::cin, ostream& output = std::cout):
           strategy(strategy),
           input(input),
           output(output) {}

    void ProcessMarket();
};