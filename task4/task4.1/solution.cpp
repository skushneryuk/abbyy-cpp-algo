#include <ranges>
#include <iostream>

using namespace std;

int main() {
    auto my_range = std::views::iota(10, 100)
        | std::views::transform([](int x) { return x * x; })
        | std::views::filter([](int x) { return x % 5 != 0; })
        | std::views::transform([](int x) { return std::to_string(x); });

    for (auto elem : my_range) {
        cout << elem << " ";
    }
}