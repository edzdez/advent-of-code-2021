#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Point
{
    int x, y;
};

struct Line
{
    Point ep1, ep2;
};

vector<Line> readInput(ifstream &fin)
{
    auto parsePoint = [](const string &point) -> Point {
        istringstream ss(point);
        string token;

        getline(ss, token, ',');
        int x = stoi(token);

        getline(ss, token, ',');
        int y = stoi(token);

        return {x, y};
    };

    vector<Line> lines;

    string line;
    while (getline(fin, line))
    {
        istringstream ss(line);
        string token;

        getline(ss, token, ' ');
        Point p1 = parsePoint(token);

        getline(ss, token, ' ');
        getline(ss, token, ' ');
        Point p2 = parsePoint(token);

        lines.push_back({p1, p2});
    }

    return lines;
}

Point getGreatestPoint(const vector<Line> &vents)
{
    Point p{0, 0};

    for (const auto &[ep1, ep2] : vents)
    {
        p.x = max(p.x, max(ep1.x, ep2.x));
        p.y = max(p.y, max(ep1.y, ep2.y));
    }

    return p;
}

int countAns(const vector<vector<int>> &board)
{
    int ans = 0;
    for (const auto &r : board)
    {
        for (const auto c : r)
            ans += c >= 2;
    }

    return ans;
}

void part1(const vector<Line> &vents)
{
    auto greatestPoint = getGreatestPoint(vents);

    vector<vector<int>> board(greatestPoint.y + 2, vector<int>(greatestPoint.x + 2, 0));
    for (const auto &[ep1, ep2] : vents)
    {
        if (ep1.x == ep2.x)
        {
            for (int y = min(ep1.y, ep2.y); y <= max(ep1.y, ep2.y); ++y)
                ++board[y][ep1.x];
        }
        else if (ep1.y == ep2.y)
        {
            for (int x = min(ep1.x, ep2.x); x <= max(ep1.x, ep2.x); ++x)
                ++board[ep1.y][x];
        }
    }

    cout << countAns(board) << '\n';
}

void part2(const vector<Line> &vents)
{
    auto greatestPoint = getGreatestPoint(vents);

    vector<vector<int>> board(greatestPoint.y + 2, vector<int>(greatestPoint.x + 2, 0));
    auto markDiagonal = [&board](Point ep1, Point ep2) {
        if (ep1.y <= ep2.y)
            for (int x = ep1.x, y = ep1.y; x <= ep2.x; ++x, ++y)
                ++board[y][x];
        else
            for (int x = ep1.x, y = ep1.y; x <= ep2.x; ++x, --y)
                ++board[y][x];
    };

    for (const auto &[ep1, ep2] : vents)
    {
        if (ep1.x == ep2.x)
        {
            for (int y = min(ep1.y, ep2.y); y <= max(ep1.y, ep2.y); ++y)
                ++board[y][ep1.x];
        }
        else if (ep1.y == ep2.y)
        {
            for (int x = min(ep1.x, ep2.x); x <= max(ep1.x, ep2.x); ++x)
                ++board[ep1.y][x];
        }
        else
        {
            if (ep1.x <= ep2.x)
            {
                markDiagonal(ep1, ep2);
            }
            else
            {
                markDiagonal(ep2, ep1);
            }
        }
    }

    cout << countAns(board) << '\n';
}

int main()
{
    ifstream fin("d5input");

    auto vents = readInput(fin);

    part1(vents);
    part2(vents);
}
