#include <ranges>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> v0_numbers;
    cout << "###### With for-loop ######\n";
    for (auto number: ranges::istream_view<int>(std::cin)) {
        if (number == -1) {
            break;
        }
        v0_numbers.push_back(number);
    }

    for (auto number: v0_numbers) {
        cout << number << "\n";
    }

    cout << "##### Without for-loop ####\n";
    auto numbers = ranges::istream_view<int>(std::cin)
                   | views::take_while([](int x){ return x != -1; });

    vector<int> v1_numbers;
    ranges::copy(numbers, back_inserter(v1_numbers));
    ranges::copy(v1_numbers, ostream_iterator<int>(std::cout, "\n"));
}