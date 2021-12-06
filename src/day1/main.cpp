#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

void part1(const vector<int> &depths)
{
    vector<int> v(depths.size());
    adjacent_difference(depths.begin(), depths.end(), v.begin());

    int ans = 0;
    for (auto it = v.begin() + 1; it != v.end(); ++it)
        ans += *it > 0;

    cout << ans << '\n';
}

void part2(const vector<int> &depths)
{
    auto it = depths.begin();
    auto it1 = depths.begin() + 3;

    int ans = 0;
    while (it1 != depths.end())
    {
        ans += *it1 > *it;
        ++it;
        ++it1;
    }

    cout << ans << '\n';
}

int main()
{
    fstream fin("d1input");
    vector<int> depths;

    int val = 0;
    while (fin >> val)
        depths.push_back(val);

    part1(depths);
    part2(depths);
}
