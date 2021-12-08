#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<string> parsePattern(const string &input)
{
    vector<string> v;

    istringstream ss(input);
    string token;
    while (ss >> token)
    {
        sort(token.begin(), token.end());
        v.push_back(token);
    }

    return v;
}

void part1(const vector<vector<string>> &patterns, const vector<vector<string>> &outputs)
{
    int ans = 0;

    for (const auto &output : outputs)
    {
        for (const auto &digit : output)
        {
            ans += (digit.size() == 2 || digit.size() == 4 || digit.size() == 3 || digit.size() == 7);
        }
    }

    cout << ans << '\n';
}

bool findPerfectIntersection(const vector<string> &v, int checkIdx, int searchIdx)
{
    vector<char> temp;
    set<char> checkRange(v[checkIdx].begin(), v[checkIdx].end());
    set<char> searchRange(v[searchIdx].begin(), v[searchIdx].end());
    set_intersection(checkRange.begin(), checkRange.end(), searchRange.begin(), searchRange.end(), back_inserter(temp));

    if (temp.size() == min(v[checkIdx].size(), v[searchIdx].size()))
        return true;

    return false;
}

void fillInRest(const vector<string> &v, map<string, int> &table)
{
    auto nineIndex = 0;
    for (int i = 6; i < 9; ++i)
        if (findPerfectIntersection(v, i, 2))
            nineIndex = i;
    table[v[nineIndex]] = 9;

    auto zeroIndex = 0;
    for (int i = 6; i < 9; ++i)
    {
        if (i == nineIndex)
            continue;

        if (findPerfectIntersection(v, i, 1))
            zeroIndex = i;
    }
    table[v[zeroIndex]] = 0;

    for (int i = 6; i < 9; ++i)
    {
        if (i != nineIndex && i != zeroIndex)
            table[v[i]] = 6;
    }

    auto threeIndex = 0;
    for (int i = 3; i < 6; ++i)
        if (findPerfectIntersection(v, i, 1))
            threeIndex = i;
    table[v[threeIndex]] = 3;

    auto fiveIndex = 0;
    for (int i = 3; i < 6; ++i)
    {
        if (i == threeIndex)
            continue;

        if (findPerfectIntersection(v, i, nineIndex))
            fiveIndex = i;
    }
    table[v[fiveIndex]] = 5;

    for (int i = 3; i < 6; ++i)
    {
        if (i != threeIndex && i != fiveIndex)
            table[v[i]] = 2;
    }
}

void part2(const vector<vector<string>> &patterns, const vector<vector<string>> &outputs)
{
    int64_t ans = 0;

    for (auto i = 0ul; i < patterns.size(); ++i)
    {
        auto v = patterns[i];
        sort(v.begin(), v.end(),
             [](const string &first, const string &second) { return first.size() < second.size(); });

        // this is pretty nasty, but I can't think of another way to do it right now
        map<string, int> table;
        table[v[0]] = 1;
        table[v[1]] = 7;
        table[v[2]] = 4;
        table[v[9]] = 8;

        fillInRest(v, table);

        int temp = 0;
        int scale = 1000;
        for (const auto &digit : outputs[i])
        {
            temp += table[digit] * scale;
            scale /= 10;
        }

        ans += temp;
    }

    cout << ans << '\n';
}

int main()
{
    ifstream fin("d8input");

    vector<vector<string>> patterns;
    vector<vector<string>> outputs;

    string line;
    while (getline(fin, line))
    {
        istringstream ss(line);
        string token;

        getline(ss, token, '|');
        patterns.push_back(parsePattern(token));

        getline(ss, token);
        outputs.push_back(parsePattern(token));
    }

    part1(patterns, outputs);
    part2(patterns, outputs);
}