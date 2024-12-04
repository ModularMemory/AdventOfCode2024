#include <vector>
#include <string>
#include <streambuf>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

constexpr auto INPUT_FILENAME = "inputs.txt";

static vector<string> get_lines(string& str) {
    auto res = vector<string>();
    auto iss = istringstream(str);

    string token;
    while (getline(iss, token, '\n')) {
        res.push_back(token);
    }

    return res;
}

static bool is_up(vector<string> lines, size_t x, size_t y) {
    if (y < 3) {
        return false;
    }

    return lines[y][x] == 'X'
        && lines[y - 1][x] == 'M'
        && lines[y - 2][x] == 'A'
        && lines[y - 3][x] == 'S';
}

static bool is_down(vector<string> lines, size_t x, size_t y) {
    if (y + 4 > lines.size()) {
        return false;
    }

    return lines[y][x] == 'X'
        && lines[y + 1][x] == 'M'
        && lines[y + 2][x] == 'A'
        && lines[y + 3][x] == 'S';
}

static bool is_up_left(vector<string> lines, size_t x, size_t y) {
    if (y < 3 || x < 3) {
        return false;
    }

    return lines[y][x] == 'X'
        && lines[y - 1][x - 1] == 'M'
        && lines[y - 2][x - 2] == 'A'
        && lines[y - 3][x - 3] == 'S';
}

static bool is_up_right(vector<string> lines, size_t x, size_t y) {
    if (y < 3 || x + 3 >= lines[y].size()) {
        return false;
    }

    return lines[y][x] == 'X'
        && lines[y - 1][x + 1] == 'M'
        && lines[y - 2][x + 2] == 'A'
        && lines[y - 3][x + 3] == 'S';
}

static bool is_down_left(vector<string> lines, size_t x, size_t y) {
    if (y + 3 >= lines.size() || x < 3) {
        return false;
    }

    return lines[y][x] == 'X'
        && lines[y + 1][x - 1] == 'M'
        && lines[y + 2][x - 2] == 'A'
        && lines[y + 3][x - 3] == 'S';
}

static bool is_down_right(vector<string> lines, size_t x, size_t y) {
    if (y + 3 >= lines.size() || x + 3 > lines[y].size()) {
        return false;
    }

    return lines[y][x] == 'X'
        && lines[y + 1][x + 1] == 'M'
        && lines[y + 2][x + 2] == 'A'
        && lines[y + 3][x + 3] == 'S';
}

int main(void) {
    auto ifs = ifstream(INPUT_FILENAME);
    auto input = string(istreambuf_iterator<char>(ifs), istreambuf_iterator<char>());
    auto lines = get_lines(input);

    auto xmas = 0;
    for (auto y = 0; y < lines.size(); y++) {
        auto& line = lines[y];
        for (auto x = 0; x < line.size(); x++) {
            if (line[x] != 'X') {
                continue;
            }

            if (line.substr(x).find("XMAS", 0) == 0) {
                xmas++;
            }

            if (x >= 3
                && line[x] == 'X'
                && line[x - 1] == 'M'
                && line[x - 2] == 'A'
                && line[x - 3] == 'S') {
                xmas++;
            }

            if (is_up(lines, x, y)) {
                xmas++;
            }

            if (is_down(lines, x, y)) {
                xmas++;
            }

            if (is_up_left(lines, x, y)) {
                xmas++;
            }

            if (is_up_right(lines, x, y)) {
                xmas++;
            }

            if (is_down_left(lines, x, y)) {
                xmas++;
            }

            if (is_down_right(lines, x, y)) {
                xmas++;
            }
        }
    }

    cout << xmas << endl;

    return 0;
}