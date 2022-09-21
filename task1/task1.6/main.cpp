#include <fstream>
#include <iostream>
#include <assert.h>

#include <market.hpp>


int main(int argc, char *argv[]) {
    assert(("Exactly 3 arguments should be passed", argc == 4));
    assert(("Only two possible strategies", std::string(argv[1]) == "sell_first" || std::string(argv[1]) == "sell_last"));

    MarketStrategyType strategy = std::string(argv[1]) == "sell_first"
                                ? MarketStrategyType::sell_first
                                : MarketStrategyType::sell_last;

    std::ifstream input = std::ifstream(argv[2], std::ifstream::in);
    std::ofstream output = std::ofstream(argv[3], std::ofstream::out);

    Market market(strategy, input, output);
    market.ProcessMarket();
    
    input.close();
    output.close();
}