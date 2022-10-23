#include <operations.hpp>

ostream& operator<< (ostream& stream, Operation const& op) {
    stream << op.operation_id << " ";
    stream << op.stock_id << " ";
    stream << OPERATION_NAMES[static_cast<int>(op.type)] << " ";
    stream << op.stock_count << " ";
    stream << op.stock_price;

    return stream;
}

istream& operator>> (istream& stream, Operation& op) {
    stream >> op.operation_id;

    string type;
    stream >> type;
    if (type == "buy") {
        op.type = OperationType::buy;
    } else if (type == "sell") {
        op.type = OperationType::sell;
    } else {
        op.type = OperationType::unknown;
    }

    stream >> op.stock_id;
    stream >> op.stock_count;
    stream >> op.stock_price;

    return stream;
}