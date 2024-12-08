#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <streambuf>
#include <set>

using namespace std;

constexpr auto INPUT_FILENAME = "inputs.txt";

class point {
public:
    unsigned short X;
    unsigned short Y;

    point(unsigned short x, unsigned short y) {
        X = x;
        Y = y;
    }

    bool operator <(const point& rhs) const {
        if (X != rhs.X) {
            return X < rhs.X;
        }

        return Y < rhs.Y;
    }
};

static vector<string> get_lines(string& str) {
    auto res = vector<string>();
    auto iss = istringstream(str);

    string token;
    while (getline(iss, token, '\n')) {
        res.push_back(token);
    }

    return res;
}

static point find_start(vector<string>& lines) {
    for (auto y = 0; y < lines.size(); y++) {
        auto& line = lines[y];
        for (auto x = 0; x < line.size(); x++) {
            if (line[x] == '^') {
                return point(x, y);
            }
        }
    }

    return point(0, 0);
}

static bool up(vector<string>& lines, point& pos) {
    for (int y = pos.Y; y >= 0; y--) {
        if (lines[y][pos.X] == '#') {
            return true;
        }

        pos.Y = y;
    }

    return false;
}

static bool right(vector<string>& lines, point& pos) {
    for (int x = pos.X; x < lines[pos.Y].size(); x++) {
        if (lines[pos.Y][x] == '#') {
            return true;
        }

        pos.X = x;
    }

    return false;
}

static bool down(vector<string>& lines, point& pos) {
    for (int y = pos.Y; y < lines.size(); y++) {
        if (lines[y][pos.X] == '#') {
            return true;
        }

        pos.Y = y;
    }

    return false;
}

static bool left(vector<string>& lines, point& pos) {
    for (int x = pos.X; x >= 0; x--) {
        if (lines[pos.Y][x] == '#') {
            return true;
        }

        pos.X = x;
    }

    return false;
}

static bool detect_loop(vector<string>& lines, point start) {
    auto uPos = set<point>();
    auto rPos = set<point>();
    auto dPos = set<point>();
    auto lPos = set<point>();
    auto pos = start;
    while (true) {
        if (!up(lines, pos)) {
            break;
        }

        if (!uPos.insert(pos).second) {
            return true;
        }

        if (!right(lines, pos)) {
            break;
        }

        if (!rPos.insert(pos).second) {
            return true;
        }

        if (!down(lines, pos)) {
            break;
        }

        if (!dPos.insert(pos).second) {
            return true;
        }

        if (!left(lines, pos)) {
            break;
        }

        if (!lPos.insert(pos).second) {
            return true;
        }
    }

    return false;
}

int main(void) {
    auto ifs = ifstream(INPUT_FILENAME);
    auto input = string(istreambuf_iterator<char>(ifs), istreambuf_iterator<char>());
    auto lines = get_lines(input);

    auto start = find_start(lines);
    if (start.X == 0 && start.Y == 0) {
        cout << "Failed to find starting pos." << endl;
        return 1;
    }

    auto loops = 0;
    for (auto y = 0; y < lines.size(); y++) {
        for (auto x = 0; x < lines[y].size(); x++) {
            if (lines[y][x] != '.') {
                continue;
            }

            lines[y][x] = '#';
            if (detect_loop(lines, start)) {
                loops++;
            }

            lines[y][x] = '.';
        }
    }

    cout << loops << endl;

    return 0;
}