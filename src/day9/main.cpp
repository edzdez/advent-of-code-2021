#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<pair<int, int>> findLowPoints(const vector<vector<int>> &grid)
{
    vector<pair<int, int>> lowPoints;
    int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
    for (size_t y = 0; y < grid.size(); ++y)
    {
        for (size_t x = 0; x < grid[y].size(); ++x)
        {
            bool flag = true;
            for (size_t i = 0; i < 4; ++i)
            {
                auto absX = x + dx[i], absY = y + dy[i];
                if (absX < 0 || absX >= grid[y].size() || absY < 0 || absY >= grid.size())
                    continue;

                if (grid[absY][absX] <= grid[y][x])
                    flag = false;
            }

            if (flag)
                lowPoints.emplace_back(x, y);
        }
    }

    return lowPoints;
}

void part1(const vector<vector<int>> &grid)
{
    auto lowPoints = findLowPoints(grid);

    int ans = 0;
    for (const auto &[x, y] : lowPoints)
        ans += grid[y][x] + 1;

    cout << ans << '\n';
}

int floodFill(const vector<vector<int>> &grid, map<pair<int, int>, bool> &visited, pair<int, int> startPoint)
{
    int size = 1;
    queue<pair<int, int>> q;
    visited[startPoint] = true;
    q.push(startPoint);

    while (!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();

        int dx[]{1, -1, 0, 0}, dy[]{0, 0, 1, -1};
        for (int i = 0; i < 4; ++i)
        {
            auto absX = x + dx[i], absY = y + dy[i];
            if (absX < 0 || absX >= grid[y].size() || absY < 0 || absY >= grid.size() || visited[{absX, absY}] ||
                grid[absY][absX] == 9)
                continue;

            if (grid[absY][absX] > grid[y][x])
            {
                visited[{absX, absY}] = true;
                q.push({absX, absY});
                ++size;
            }
        }
    }

    return size;
}

void part2(const vector<vector<int>> &grid)
{
    auto lowPoints = findLowPoints(grid);

    vector<int> basinSizes;
    map<pair<int, int>, bool> visited;
    basinSizes.reserve(lowPoints.size());
    for (const auto &lowPoint : lowPoints)
        basinSizes.push_back(floodFill(grid, visited, lowPoint));

    sort(basinSizes.begin(), basinSizes.end(), greater<>());
    cout << basinSizes[0] * basinSizes[1] * basinSizes[2] << '\n';
}

int main()
{
    ifstream fin("d9input");

    vector<vector<int>> grid;
    string line;
    while (fin >> line)
    {
        vector<int> v;
        for (const auto &c : line)
            v.push_back(c - '0');
        grid.push_back(v);
    }

    part1(grid);
    part2(grid);
}