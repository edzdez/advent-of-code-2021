#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

enum Direction
{
    FORWARD,
    DOWN,
    UP,
};

struct Instruction
{
    Direction d;
    int64_t m;
};

Direction getDirection(const string &s)
{
    if (s == "forward")
        return Direction::FORWARD;
    if (s == "down")
        return Direction::DOWN;
    if (s == "up")
        return Direction::UP;

    throw invalid_argument("not a direction");
}

void part1(vector<Instruction> v)
{
    int64_t x = 0, y = 0;

    for (auto &i : v)
    {
        switch (i.d)
        {
        case Direction::UP:
            i.m = -i.m;
        case Direction::DOWN:
            y += i.m;
            break;
        case Direction::FORWARD:
            x += i.m;
            break;
        }
    }

    cout << x * y << '\n';
}

void part2(vector<Instruction> v)
{
    int64_t x = 0, y = 0, aim = 0;

    for (auto &i : v)
    {
        switch (i.d)
        {
        case Direction::UP:
            i.m = -i.m;
        case Direction::DOWN:
            aim += i.m;
            break;
        case Direction::FORWARD:
            x += i.m;
            y += i.m * aim;
            break;
        }
    }

    cout << x * y << '\n';
}

int main()
{
    ifstream fin("d2input");

    string s;
    vector<Instruction> v;
    while (getline(fin, s))
    {
        stringstream ss(s);
        string direction, magnitude;
        ss >> direction >> magnitude;

        Instruction d{getDirection(direction), stoi(magnitude)};
        v.push_back(d);
    }

    part1(v);
    part2(v);
}
