#include <market.hpp>


void Market::ProcessOperation(const Operation& op) {
    if (stock_states.find(op.stock_id) == stock_states.end() || operations.find(op.stock_id) == operations.end()) {
        stock_states[op.stock_id] = StockStateType::empty;
        operations[op.stock_id] = deque<Operation>();
    }
    auto& current_deq = operations[op.stock_id];
    StockStateType squeeze_type = op.type == OperationType::buy
                                ? StockStateType::shorts
                                : StockStateType::longs;
    
    StockStateType update_type = op.type == OperationType::buy
                                ? StockStateType::longs
                                : StockStateType::shorts;

    DealType deal_type = op.type == OperationType::buy
                        ? DealType::short_deal
                        : DealType::long_deal;

    // if there is no operations for this stock yet
    // or all operations are of the same type
    if (stock_states[op.stock_id] != squeeze_type) {
        current_deq.push_back(op);
        stock_states[op.stock_id] = update_type;
    } else { // if there is shorts in operations
        int stock_to_buy = op.stock_count;
        while (!current_deq.empty() && stock_to_buy > 0) {
            Operation& check = strategy == MarketStrategyType::sell_last
                                ? current_deq.back()
                                : current_deq.front();
            if (check.stock_count <= stock_to_buy) {
                stock_to_buy -= check.stock_count;
                if (strategy == MarketStrategyType::sell_last) {
                    current_deq.pop_back();
                } else {
                    current_deq.pop_front();
                }

                // adding deal to vector
                deals.emplace_back(
                    op.stock_id,
                    check.stock_count,
                    check.stock_price,
                    op.stock_price,
                    check.operation_id,
                    op.operation_id,
                    deal_type
                );
            } else {
                // adding deal to vector
                deals.emplace_back(
                    op.stock_id,
                    stock_to_buy,
                    check.stock_price,
                    op.stock_price,
                    check.operation_id,
                    op.operation_id,
                    deal_type
                );

                check.stock_count -= stock_to_buy;
                stock_to_buy = 0;
            }
        }
        if (stock_to_buy != 0) { // we bought all shorts, but still stocks remain
            Operation new_op = op;
            new_op.stock_count = stock_to_buy;
            current_deq.push_back(new_op);

            stock_states[op.stock_id] = update_type;
        }
        if (current_deq.empty()) {
            stock_states[op.stock_id] = StockStateType::empty;
        }
    }
}

void Market::FinalizeDeals() {
    for (auto& deq_pair : operations) {
        auto& deq = deq_pair.second;
        while (!deq.empty()) {
            auto op = deq.back();
            deals.emplace_back(
                op.stock_id,
                op.stock_count,
                op.stock_price,
                op.stock_price, // useless
                op.operation_id,
                op.operation_id, // useless
                op.type == OperationType::buy ? DealType::long_deal : DealType::short_deal,
                true
            );
            deq.pop_back();
        }
    }
}

void Market::SortDeals() {
    std::sort(deals.begin(), deals.end());
}

void Market::OutputDeals() {
    for (auto& deal : deals) {
        output << deal << "\n";
    }
}

void Market::ProcessMarket() {
    Operation op;
    while (input >> op) {
        ProcessOperation(op);
    }
    FinalizeDeals();
    SortDeals();
    OutputDeals();
}