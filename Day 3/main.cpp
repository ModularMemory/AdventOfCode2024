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
    auto reg = regex{ R"((?:mul\((\d+),(\d+)\)|do\(\)|don't\(\)))" };

    auto ifs = ifstream(INPUT_FILENAME);
    auto str = string((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());

    auto rit = sregex_iterator (str.begin(), str.end(), reg);
    auto rit_end = sregex_iterator();

    int sum = 0;
    bool enabled = true;
    for (; rit != rit_end; rit++) {
        auto& match = *rit;

        if (match.str().rfind("don't()") == 0) {
            enabled = false;
            continue;
        }

        if (match.str().rfind("do()") == 0) {
            enabled = true;
            continue;
        }

        if (!enabled) {
            continue;
        }

        int a = stoi(match[1].str());
        int b = stoi(match[2].str());

        sum += a * b;
    }

    cout << "Sum: " << sum << endl;

    return 0;
}