#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

using u64 = unsigned long long;

static int prase_int(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }

    cerr << "Failed to parse '" << c << "' as int." << endl;
    exit(1);
}

static vector<u64> get_disk() {
    auto ifs = ifstream("inputs.txt");
    auto input = string(istreambuf_iterator<char>(ifs), istreambuf_iterator<char>());

    auto disk = vector<u64>();
    auto id = 0ULL;
    for (auto i = 0ULL; i < input.size(); i++) {
        auto count = prase_int(input[i]);
        if (i % 2 != 0) {
            for (auto j = 0; j < count; j++) {
                disk.push_back(-1);
            }
        }
        else {
            for (auto j = 0; j < count; j++) {
                disk.push_back(id);
            }
            id++;
        }
    }

    return disk;
}

static u64 part1(const vector<u64> disk) {
    auto start = 0ULL;
    auto end = disk.size() - 1;
    auto checksum = 0ULL;
    auto pos = 0ULL;
    while (start <= end) {
        auto i = disk[start];
        if (i != -1) {
            checksum += pos * i;
        }
        else {
            while (disk[end] == -1) {
                end--;
            }

            if (end < start) {
                break;
            }

            checksum += pos * disk[end];
            end--;
        }

        start++;
        pos++;
    }

    return checksum;
}

int main(void) {
    auto disk = get_disk();

    auto sum1 = part1(disk);

    cout << sum1 << endl;

    return 0;
}