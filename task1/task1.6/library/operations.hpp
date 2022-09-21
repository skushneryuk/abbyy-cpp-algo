#pragma once

#include <string>
#include <sstream>

using std::string;

// IO
using std::ostream;
using std::istream;

enum class OperationType : int {
    buy = 0,
    sell = 1,
    unknown = 2,
};

constexpr std::string_view OPERATION_NAMES[] = { "buy", "sell", "unknown" };

class Operation {
private:
    string operation_id;
    string stock_id;
    OperationType type;
    int stock_count;
    float stock_price;
public:
    Operation() = default;
    Operation(string operation_id, string stock_id, OperationType type, int stock_count, float stock_price):
              operation_id(operation_id), stock_id(stock_id), type(type), stock_count(stock_count), stock_price(stock_price) {}

    friend ostream& operator<< (ostream& stream, Operation const& op);
    friend istream& operator>> (istream& stream, Operation& op);
    friend class Market;
};