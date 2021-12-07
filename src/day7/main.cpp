#include <fstream>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <sstream>
#include <vector>

using namespace std;

vector<int> readInput(ifstream &fin)
{
    string line;
    getline(fin, line);

    istringstream ss(line);
    string token;

    vector<int> positions;

    while (getline(ss, token, ','))
    {
        positions.push_back(stoi(token));
    }

    return positions;
}

void part1(const vector<int> &positions)
{
    int ans = INT32_MAX;
    for (const auto pos : positions)
    {
        vector<int> v;
        transform(positions.begin(), positions.end(), back_inserter(v), [pos](int x) { return abs(x - pos); });

        ans = min(ans, accumulate(v.begin(), v.end(), 0));
    }

    cout << ans << '\n';
}

void part2(const vector<int> &positions)
{
    int ans = INT32_MAX;
    set<int> s(positions.begin(), positions.end());
    for (int pos = *s.begin(); pos <= *s.end(); ++pos)
    {
        vector<int> v;
        transform(positions.begin(), positions.end(), back_inserter(v), [pos](int x) {
            auto val = abs(x - pos);

            return (val + 1) * val / 2;
        });

        int res = accumulate(v.begin(), v.end(), 0);
        ans = min(ans, res);
    }

    cout << ans << '\n';
}

int main()
{
    ifstream fin("d7input");

    auto positions = readInput(fin);

    part1(positions);
    part2(positions);
}