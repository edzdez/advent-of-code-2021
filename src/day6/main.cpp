#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class LanternFish
{
  public:
    LanternFish() : m_timer(8)
    {
    }

    explicit LanternFish(int time) : m_timer(time)
    {
    }

    bool tick()
    {
        if (m_timer == 0)
        {
            m_timer = 6;
            return true;
        }
        else
        {
            --m_timer;
            return false;
        }
    }

    [[nodiscard]] int getTimer() const
    {
        return m_timer;
    }

  private:
    int m_timer;
};

vector<LanternFish> readInput(ifstream &fin)
{
    vector<LanternFish> v;
    string line;
    getline(fin, line);

    istringstream ss(line);
    string token;
    while (getline(ss, token, ','))
        v.emplace_back(stoi(token));

    return v;
}

void simulate(vector<LanternFish> &v, int days)
{
    while (days--)
    {
        int fishToAdd = 0;
        for (auto &fish : v)
        {
            if (fish.tick())
                ++fishToAdd;
        }

        while (fishToAdd--)
        {
            v.emplace_back();
        }
    }
}

void part1(vector<LanternFish> v)
{
    simulate(v, 80);
    cout << v.size() << '\n';
}

void part2(const vector<LanternFish> &v)
{
    vector<size_t> fishAtAge(9, 0);
    for (const auto &fish : v)
        ++fishAtAge[fish.getTimer()];

    for (int i = 0; i < 256; ++i)
    {
        vector<size_t> fishToAdd(9, 0);
        fishToAdd[8] = fishAtAge[0];
        fishToAdd[6] = fishAtAge[0];

        rotate(fishAtAge.begin(), fishAtAge.begin() + 1, fishAtAge.end());
        fishAtAge[8] = 0;

        for (int idx = 0; idx < 9; ++idx)
            fishAtAge[idx] += fishToAdd[idx];
    }

    cout << accumulate(fishAtAge.begin(), fishAtAge.end(), 0ul);
}

int main()
{
    ifstream fin("d6input");
    auto fishes = readInput(fin);

    part1(fishes);
    part2(fishes);
}