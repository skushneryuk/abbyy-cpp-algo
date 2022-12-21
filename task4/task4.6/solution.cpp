#include <ranges>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;


template<typename T>
concept IF2StringConvertible = requires(T number) { 
    to_string(number);
} && (
    is_floating_point_v<T> || is_integral_v<T>
);


template<IF2StringConvertible Number1, IF2StringConvertible Number2>
string concat(Number1 n1, Number2 n2) {
    return to_string(n1) + to_string(n2);
}


int main() {
    static_assert(IF2StringConvertible<int>);
    static_assert(IF2StringConvertible<long long>);
    static_assert(IF2StringConvertible<float>);
    static_assert(IF2StringConvertible<double>);
    static_assert(!IF2StringConvertible<string>);
    static_assert(!IF2StringConvertible<vector<int>>);

    cout << concat(50, 55) << endl;
    cout << concat(5.0, 55) << endl;
    cout << concat(50, 5.5) << endl;
    cout << concat(5.0, 5.5) << endl;
}