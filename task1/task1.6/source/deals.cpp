#include <deals.hpp>

float Deal::GetProfitMultiplicator() const {
    if (type == DealType::long_deal) {
        return 1;
    } else if (type == DealType::short_deal) {
        return -1;
    }
    return numeric_limits<float>::quiet_NaN();
}

float Deal::GetProfit() const {
    return stock_count * (stock_price_close - stock_price_open) * GetProfitMultiplicator();
}

bool operator<(const Deal& lhs, const Deal& rhs) {
    if (lhs.stock_id != rhs.stock_id) {
        return lhs.stock_id < rhs.stock_id;
    }
    
    if (lhs.residual != rhs.residual) {
        return rhs.residual;
    }

    if (lhs.residual) {
        return lhs.operation_id_open < rhs.operation_id_open;
    }

    if (lhs.operation_id_close != rhs.operation_id_close) {
        return lhs.operation_id_close < rhs.operation_id_close;
    }
    return lhs.operation_id_open < rhs.operation_id_open;
}

ostream& operator<< (ostream& stream, Deal const& deal) {
    stream << deal.stock_id << " ";
    stream << deal.stock_count << " ";
    stream << deal.stock_price_open << " ";

    if (deal.residual) {
        stream << "- - ";
    } else {
        stream << deal.stock_price_close << " " << deal.GetProfit() << " ";
    }
    stream << DEAL_NAMES[static_cast<int>(deal.type)] << " "
           << deal.operation_id_open;
    
    if (!deal.residual) {
        stream << " " << deal.operation_id_close;
    }

    return stream;
}

istream& operator>> (istream& stream, Deal& deal);