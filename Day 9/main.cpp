#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

using i32 = int;
using u64 = unsigned long long;

static int prase_int(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }

    cerr << "Failed to parse '" << c << "' as int." << endl;
    exit(1);
}

static vector<i32> get_disk() {
    auto ifs = ifstream("inputs.txt");
    auto input = string(istreambuf_iterator<char>(ifs), istreambuf_iterator<char>());

    auto disk = vector<i32>();
    auto id = 0;
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

static u64 part1(const vector<i32> disk) {
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

static u64 compute_checksum(vector<i32> disk) {
    auto checksum = 0ULL;
    for (auto pos = 0ULL; pos < disk.size(); pos++) {
        auto id = disk[pos];
        if (id == -1) {
            continue;
        }

        checksum += pos * id;
    }

    return checksum;
}

static void defragment_files(vector<i32>& disk) {
    auto firstAvailable = 0ULL;
    for (auto end = disk.size() - 1; end >= firstAvailable; end--) {
        auto id = disk[end];
        if (id == -1) {
            continue;
        }

        // Check file size
        auto size = 1;
        while (end - size >= firstAvailable && disk[end - size] == id) {
            size++;
        }

        for (auto start = firstAvailable;; start++) {
            if (start >= end) {
                end -= size - 1;
                break;
            }

            if (disk[start] != -1) {
                continue;
            }

            // Check available space
            auto available = 1;
            while (available < size && start + available <= end && disk[start + available] == -1) {
                available++;
            }

            if (available < size) {
                continue;
            }

            // Move file
            for (auto i = 0; i < size; i++) {
                disk[start + i] = disk[end - i];
                disk[end - i] = -1;
            }
            
            // Find next available
            auto it = find(disk.begin(), disk.end(), -1);
            if (it == disk.end()) {
                cerr << "Failed to find free space." << endl;
                return;
            }

            firstAvailable = distance(disk.begin(), it);
            break;
        }
    }
}

static u64 part2(const vector<i32> original_disk) {
    auto disk = vector<i32>(original_disk);

    defragment_files(disk);

    return compute_checksum(disk);
}

int main(void) {
    auto disk = get_disk();

    //auto sum1 = part1(disk);
    auto sum2 = part2(disk);

    //cout << sum1 << endl;
    cout << sum2 << endl;

    return 0;
}