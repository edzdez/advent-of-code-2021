#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

map<pair<int, int>, int> dijkstra(const vector<vector<int>> &dangerLevels, const pair<int, int> &startPoint)
{
    map<pair<int, int>, int> minDistances;
    for (int i = 0; i < dangerLevels.size(); ++i)
        for (int j = 0; j < dangerLevels[i].size(); ++j)
            minDistances[{j, i}] = INT32_MAX;
    minDistances[startPoint] = 0;

    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> pq;
    pq.push({0, startPoint});

    int dx[]{-1, 1, 0, 0}, dy[]{0, 0, -1, 1};
    while (!pq.empty())
    {
        auto [x, y] = pq.top().second;
        pq.pop();

        if (x == dangerLevels[0].size() - 1 && y == dangerLevels.size() - 1)
            break;

        for (int i = 0; i < 4; ++i)
        {
            auto absX = x + dx[i], absY = y + dy[i];

            if (absX < 0 || absX >= dangerLevels[0].size() || absY < 0 || absY >= dangerLevels.size())
                continue;

            auto w = dangerLevels[absY][absX];
            if (minDistances[{absX, absY}] > w + minDistances[{x, y}])
            {
                minDistances[{absX, absY}] = w + minDistances[{x, y}];
                pq.push({minDistances[{absX, absY}], make_pair(absX, absY)});
            }
        }
    }

    return minDistances;
}

void part1(const vector<vector<int>> &dangerLevels)
{
    auto distances = dijkstra(dangerLevels, {0, 0});
    cout << distances[{dangerLevels[0].size() - 1, dangerLevels.size() - 1}] << '\n';
}

vector<vector<int>> expand(const vector<vector<int>> &dangerLevels)
{
    vector<vector<int>> res;

    for (int i = 0; i < 5; ++i)
    {
        for (int y = 0; y < dangerLevels.size(); ++y)
        {
            vector<int> line;
            for (int j = 0; j < 5; ++j)
            {
                for (int x = 0; x < dangerLevels[0].size(); ++x)
                {
                    auto res = dangerLevels[y][x] + i + j;
                    while (res > 9)
                        res -= 9;

                    line.push_back(res);
                }
            }
            res.push_back(line);
        }
    }

    return res;
}

void part2(const vector<vector<int>> &dangerLevels)
{
    auto expandedLevels = expand(dangerLevels);
    auto distances = dijkstra(expandedLevels, {0, 0});
    cout << distances[{expandedLevels[0].size() - 1, expandedLevels.size() - 1}] << '\n';
}

int main()
{
    ifstream fin("d15input");

    string line;
    vector<vector<int>> dangerLevels;
    while (fin >> line)
    {
        vector<int> v;
        for (const auto &c : line)
            v.push_back(c - '0');
        dangerLevels.push_back(v);
    }

    part1(dangerLevels);
    part2(dangerLevels);
}