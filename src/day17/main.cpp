#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct Vector2
{
    int x, y;
};
struct Target
{
    int x1, y1, x2, y2;
};

Target parseTarget(const string &input)
{
    string temp, x, y;
    istringstream ss(input);
    ss >> temp >> temp >> x >> y;

    x = x.substr(2, x.size() - 3);
    y = y.substr(2, y.size() - 2);

    string x1, x2, y1, y2;
    istringstream ss1(x);
    istringstream ss2(y);

    getline(ss1, x1, '.');
    getline(ss1, x2, '.');
    getline(ss1, x2, '.');

    getline(ss2, y1, '.');
    getline(ss2, y2, '.');
    getline(ss2, y2, '.');

    return Target{stoi(x1), stoi(y1), stoi(x2), stoi(y2)};
}

void part1(const Target &t)
{
    cout << ((-t.y1) * (-t.y1 - 1)) / 2 << '\n';
}

bool simulate(const Target &t, Vector2 v)
{
    Vector2 pos = {0, 0};
    while (pos.x <= t.x2 && pos.y >= t.y1)
    {
        pos.x += v.x;
        pos.y += v.y;

        if (v.x > 0)
            --v.x;
        else if (v.x < 0)
            ++v.x;
        --v.y;

        if (pos.x >= t.x1 && pos.x <= t.x2 && pos.y <= t.y2 && pos.y >= t.y1)
            return true;
    }

    return false;
}

void part2(const Target &t)
{
    int solutions = 0;
    Vector2 v{0, t.y1};

    for (; v.x <= t.x2; ++v.x)
        for (v.y = t.y1; v.y <= -t.y1; ++v.y)
            solutions += simulate(t, v);

    cout << solutions << '\n';
}

int main()
{
    ifstream fin("d17input");

    string line;
    getline(fin, line);

    auto t = parseTarget(line);
    part1(t);
    part2(t);
}