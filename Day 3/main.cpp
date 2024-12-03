#include <cassert>
#include <cstdbool>
#include <cstdio>
#include <regex>
#include <fstream>
#include <iostream>
#include <string>
#include <streambuf>

using namespace std;

constexpr auto INPUT_FILENAME = "inputs.txt";

int main(void) {
    auto reg = regex{ R"(mul\((\d+),(\d+)\))" };

    auto ifs = ifstream(INPUT_FILENAME);
    auto str = string((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());

    auto rit = sregex_iterator (str.begin(), str.end(), reg);
    auto rit_end = sregex_iterator();

    int sum = 0;
    for (; rit != rit_end; rit++) {
        auto match = *rit;

        int a = stoi(match[1].str());
        int b = stoi(match[2].str());

        sum += a * b;
    }

    cout << "Sum: " << sum << endl;

    return 0;
}