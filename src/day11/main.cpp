#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

void tick(vector<vector<uint8_t>> &grid)
{
    for (auto &line : grid)
        for (auto &cell : line)
            ++cell;
}

void flash(vector<vector<uint8_t>> &grid, map<pair<int, int>, bool> &visited, int x, int y)
{
    if (visited[{x, y}])
        return;

    if (grid[y][x] > 9)
    {
        visited[{x, y}] = true;
        for (int relY = -1; relY <= 1; ++relY)
        {
            for (int relX = -1; relX <= 1; ++relX)
            {
                if (relX == 0 && relY == 0)
                    continue;

                auto absX = x + relX, absY = y + relY;
                if (absX < 0 || absX >= grid[y].size() || absY < 0 || absY >= grid.size())
                    continue;

                ++grid[absY][absX];
                flash(grid, visited, absX, absY);
            }
        }
    }
}

void part1(vector<vector<uint8_t>> grid)
{
    uint64_t numFlashes = 0;

    for (int i = 0; i < 100; ++i)
    {
        map<pair<int, int>, bool> visited;

        tick(grid);

        for (int y = 0; y < grid.size(); ++y)
        {
            for (int x = 0; x < grid[y].size(); ++x)
            {
                flash(grid, visited, x, y);
            }
        }

        for (auto &line : grid)
        {
            for (auto &cell : line)
            {
                if (cell > 9)
                {
                    ++numFlashes;
                    cell = 0;
                }
            }
        }
    }

    cout << numFlashes << '\n';
}

void part2(vector<vector<uint8_t>> grid)
{
    int i = 1;
    for (;; ++i)
    {
        uint64_t numFlashes = 0;
        map<pair<int, int>, bool> visited;

        tick(grid);

        for (int y = 0; y < grid.size(); ++y)
        {
            for (int x = 0; x < grid[y].size(); ++x)
            {
                flash(grid, visited, x, y);
            }
        }

        for (auto &line : grid)
        {
            for (auto &cell : line)
            {
                if (cell > 9)
                {
                    ++numFlashes;
                    cell = 0;
                }
            }
        }

        if (numFlashes == grid.size() * grid[0].size())
            break;
    }

    cout << i << '\n';
}

int main()
{
    ifstream fin("d11input");

    vector<vector<uint8_t>> grid;
    string s;
    while (fin >> s)
    {
        vector<uint8_t> line;
        for (const auto c : s)
            line.push_back(c - '0');
        grid.push_back(line);
    }

    part1(grid);
    part2(grid);
}