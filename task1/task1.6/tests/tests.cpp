#include <algorithm>
#include <iterator>
#include <string>
#include <fstream>

#include <market.hpp>

// https://stackoverflow.com/questions/15118661/in-c-whats-the-fastest-way-to-tell-whether-two-string-or-binary-files-are-di
template<typename InputIterator1, typename InputIterator2>
bool
range_equal(InputIterator1 first1, InputIterator1 last1,
        InputIterator2 first2, InputIterator2 last2) {
    while(first1 != last1 && first2 != last2)
    {
        if(*first1 != *first2) return false;
        ++first1;
        ++first2;
    }
    return (first1 == last1) && (first2 == last2);
}

bool compare_files(const std::string& filename1, const std::string& filename2)
{
    std::ifstream file1(filename1);
    std::ifstream file2(filename2);

    std::istreambuf_iterator<char> begin1(file1);
    std::istreambuf_iterator<char> begin2(file2);

    std::istreambuf_iterator<char> end;

    return range_equal(begin1, end, begin2, end);
}

bool run_test(const std::string& input_path, const std::string& answer_path, MarketStrategyType strategy) {
    std::string output_path = "/tmp/tmp123";
    std::ifstream input = std::ifstream(input_path, std::ifstream::in);
    std::ofstream output = std::ofstream(output_path, std::ofstream::out);

    Market market(strategy, input, output);
    market.ProcessMarket();
    
    input.close();
    output.close();
    return compare_files(output_path, answer_path);
}

int main() {
	assert(("Incorrect behaviour in test 1", run_test("tests/in1.txt", "tests/out1.txt", MarketStrategyType::sell_first)));
    assert(("Incorrect behaviour in test 2", run_test("tests/in2.txt", "tests/out2.txt", MarketStrategyType::sell_last)));
    // add tests here
    std::cout << "All tests passed\n";
}