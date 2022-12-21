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

std::ostream& operator<<(std::ostream& out, const Person& person) {
    return out << person.first_name << " " << person.second_name;
}

template <typename InputIter, typename OutputIter>
void MyCopy(InputIter begin, InputIter end, OutputIter target) {
    for (auto iter{ begin }; iter != end; ++iter, ++target) {
        *target = *iter;
    }
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

    auto without_age = people
                       | ranges::views::transform(
                           [](const std::pair<Person, Age>& person) {
                               return person.first;
                           }
                       )
                       | ranges::views::take(4);

    MyCopy(without_age.begin(), without_age.end(), std::ostream_iterator<Person>(std::cout, "\n"));
    
    auto only_second_name = without_age | ranges::views::transform(
        [](const Person& person) {
            return person.second_name;
        }    
    );

    MyCopy(only_second_name.begin(), only_second_name.end(), std::ostream_iterator<string>(std::cout, "\n"));
}