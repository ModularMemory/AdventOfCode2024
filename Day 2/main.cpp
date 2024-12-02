#define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <cstdbool>
#include <cstdio>
#include <cctype>
#include <vector>

constexpr auto REPORTS_FILENAME = "inputs.txt";

static std::vector<std::vector<int>> getReports(void) {
    std::vector<std::vector<int>> reports;
    FILE* fp;
    fopen_s(&fp, REPORTS_FILENAME, "r");
    assert(fp);

    char buff[256] = { 0 };
    while (true) {
        std::vector<int> current;
        fgets(buff, 256, fp);

        auto str = strtok(buff, " ");
        while (str) {
            current.push_back(atoi(str));
            str = strtok(NULL, " ");
        }

        current.shrink_to_fit();
        reports.push_back(current);

        if (feof(fp)) {
            break;
        }
    }

    fclose(fp);
    reports.shrink_to_fit();
    return reports;
}

static bool isSafe(std::vector<int> levels) {
    if (levels[0] == levels[1]) {
        return false;
    }

    bool increasing = levels[0] < levels[1];
    if (increasing) {
        for (int i = 0; i < levels.size() - 1; i++) {
            if (levels[i + 1] <= levels[i]) {
                return false;
            }

            if (levels[i + 1] - levels[i] > 3) {
                return false;
            }
        }
    }
    else {
        for (int i = 0; i < levels.size() - 1; i++) {
            if (levels[i + 1] >= levels[i]) {
                return false;
            }

            if (levels[i] - levels[i + 1] > 3) {
                return false;
            }
        }
    }

    return true;
}

static int countSafe(std::vector<std::vector<int>> reports) {
    int safe = 0;
    for (const auto& report : reports) {
        if (isSafe(report)) {
            safe++;
        }
    }

    return safe;
}

int main(void) {
    auto reports = getReports();

    int safe = countSafe(reports);

    printf("Safe: %d\n", safe);

    return 0;
}