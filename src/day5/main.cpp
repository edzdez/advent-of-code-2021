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

void part1(const vector<Line> &vents)
{
    auto greatestPoint = [&]() -> Point {
        Point p{0, 0};

        for (const auto &[ep1, ep2] : vents)
        {
            p.x = max(p.x, max(ep1.x, ep2.x));
            p.y = max(p.y, max(ep1.y, ep2.y));
        }

        return p;
    }();

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

    int ans = 0;
    for (const auto &r : board)
    {
        for (const auto c : r)
            ans += c >= 2;
    }

    cout << ans << '\n';
}

int main()
{
    ifstream fin("d5input");

    auto vents = readInput(fin);

    part1(vents);
}
