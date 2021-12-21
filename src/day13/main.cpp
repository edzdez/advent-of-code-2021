#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void fold(vector<pair<int, int>> &points, const pair<char, int> &fold)
{
    const auto &[dir, loc] = fold;
    for (auto &[x, y] : points)
    {
        if (dir == 'y')
        {
            if (y > loc)
            {
                y = loc - (y - loc);
            }
        }
        else
        {
            if (x > loc)
            {
                x = loc - (x - loc);
            }
        }
    }

    sort(points.begin(), points.end());
    points.erase(unique(points.begin(), points.end()), points.end());
}

void part1(vector<pair<int, int>> points, const vector<pair<char, int>> &folds)
{
    fold(points, folds[0]);

    cout << points.size() << '\n';
}

void part2(vector<pair<int, int>> points, const vector<pair<char, int>> &folds)
{
    int maxX = INT32_MAX, maxY = INT32_MAX;
    for (const auto &step : folds)
    {
        if (step.first == 'x')
        {
            maxX = min(maxX, step.second);
        }
        else
        {
            maxY = min(maxY, step.second);
        }

        fold(points, step);
    }

    for (size_t y = 0; y < maxY; ++y)
    {
        for (size_t x = 0; x < maxX; ++x)
        {
            if (find(points.begin(), points.end(), pair<int, int>{x, y}) != points.end())
                cout << '#';
            else
                cout << ' ';
        }

        cout << '\n';
    }
}

int main()
{
    ifstream fin("d13input");

    string s;
    vector<pair<int, int>> points;
    while (getline(fin, s))
    {
        if (s.empty())
            break;

        istringstream ss(s);
        string x, y;

        getline(ss, x, ',');
        getline(ss, y, ',');

        points.emplace_back(stoi(x), stoi(y));
    }

    vector<pair<char, int>> folds;
    while (getline(fin, s))
    {
        istringstream ss(s);
        string token;

        getline(ss, token, ' ');
        getline(ss, token, ' ');
        getline(ss, token, ' ');

        istringstream ss2(token);
        string dir, loc;
        getline(ss2, dir, '=');
        getline(ss2, loc, '=');

        folds.emplace_back(dir[0], stoi(loc));
    }

    part1(points, folds);
    part2(points, folds);
}