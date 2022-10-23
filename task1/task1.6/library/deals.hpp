#pragma once

#include <string>
#include <sstream>
#include <limits>

// Structures
using std::string;

// IO
using std::ostream;
using std::istream;

// Tools
using std::numeric_limits;

enum class DealType : int {
    long_deal = 0,
    short_deal = 1,
    unknown = 2,
};

constexpr std::string_view DEAL_NAMES[] = { "long", "short", "unknown" };

class Deal {
private:
    string stock_id;
    int stock_count = 0;
    float stock_price_open;
    float stock_price_close;
    // profit
    string operation_id_open;
    string operation_id_close;
    DealType type;
    bool residual;

    float GetProfitMultiplicator() const;

public:
    float GetProfit() const;

    Deal() = default;
    Deal(string stock_id, int stock_count, float stock_price_open, float stock_price_close,
        string operation_id_open, string operation_id_close, DealType type, bool residual = false):
        stock_id(stock_id),
        stock_count(stock_count),
        stock_price_open(stock_price_open),
        stock_price_close(stock_price_close),
        operation_id_open(operation_id_open),
        operation_id_close(operation_id_close),
        type(type),
        residual(residual) {}

    friend ostream& operator<< (ostream& stream, Deal const& deal);
    friend istream& operator>> (istream& stream, Deal& deal);
    friend bool operator<(const Deal& lhs, const Deal& rhs);
};

