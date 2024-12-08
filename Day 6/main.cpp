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

static bool up(vector<string>& lines, point& pos, set<point>& positions) {
    for (int y = pos.Y; y >= 0; y--) {
        if (lines[y][pos.X] == '#') {
            return true;
        }

        pos.Y = y;
        positions.insert(pos);
    }

    return false;
}

static bool right(vector<string>& lines, point& pos, set<point>& positions) {
    for (int x = pos.X; x < lines[pos.Y].size(); x++) {
        if (lines[pos.Y][x] == '#') {
            return true;
        }

        pos.X = x;
        positions.insert(pos);
    }

    return false;
}

static bool down(vector<string>& lines, point& pos, set<point>& positions) {
    for (int y = pos.Y; y < lines.size(); y++) {
        if (lines[y][pos.X] == '#') {
            return true;
        }

        pos.Y = y;
        positions.insert(pos);
    }

    return false;
}

static bool left(vector<string>& lines, point& pos, set<point>& positions) {
    for (int x = pos.X; x >= 0; x--) {
        if (lines[pos.Y][x] == '#') {
            return true;
        }

        pos.X = x;
        positions.insert(pos);
    }

    return false;
}

static void print_path(vector<string>& lines, set<point>& positions) {
    for (auto y = 0; y < lines.size(); y++) {
        for (auto x = 0; x < lines[y].size(); x++) {
            if (positions.find(point(x, y)) != positions.end()) {
                cout << '#';
            }
            else {
                cout << '.';
            }
        }

        cout << '\n';
    }
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

    auto positions = set<point>();
    auto pos = start;
    while (true) {
        if (!up(lines, pos, positions)) {
            break;
        }

        if (!right(lines, pos, positions)) {
            break;
        }

        if (!down(lines, pos, positions)) {
            break;
        }

        if (!left(lines, pos, positions)) {
            break;
        }
    }

    cout << positions.size() << endl;

    //print_path(lines, positions);

    return 0;
}