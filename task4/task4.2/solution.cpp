#include <ranges>
#include <iostream>
#include <vector>

using namespace std;
namespace rv = std::ranges::views;


using Age = size_t;

struct Person {
    std::string first_name;
    std::string second_name;
    bool sex; // hehe
};

template <typename InputIter>
auto Sum(InputIter begin, InputIter end) {
    auto sum{ *begin };
    for (auto iter{ ++begin }; iter != end; ++iter) {
        sum += *iter;
    }
    return sum;
}


int main() {
    vector<pair<Person, Age>> people = {
        {{"Sergey", "Kushneryuk", true,}, 21},
        {{"Andrew", "Kolmogorov", true,}, 84},
        {{"Michael", "Kutuzov", true,}, 68},
        {{"Ilon", "Mask", true,}, 51},
        {{"Marie", "Curie", false,}, 66},
        {{"Siegfried", "Kircheis", true,}, 21},
    };

    auto my_range = people
                    | ranges::views::transform(
                        [](const std::pair<Person, Age>& person) {
                            return person.second;
                        }
                    )
                    | ranges::views::filter(
                        [](const Age& age) {
                            return 12 <= age && age <= 65;
                        }
                    );

    auto sum_age = Sum(my_range.begin(), my_range.end());
    auto mean_age = sum_age / distance(my_range.begin(), my_range.end());

    cout << mean_age << endl;
}