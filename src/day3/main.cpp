#include <bitset>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

constexpr size_t NUM_BITS = 12;

pair<int, int> countBits(const vector<bitset<NUM_BITS>> &v, size_t idx)
{
    size_t ones = 0, zeros = 0;
    for (const auto &bnum : v)
    {
        if (bnum[idx])
            ++ones;
        else
            ++zeros;
    }

    return {ones, zeros};
}

void part1(const vector<bitset<NUM_BITS>> &v)
{
    bitset<NUM_BITS> gammaRate;
    bitset<NUM_BITS> epsilonRate;

    for (auto i = 0ul; i < NUM_BITS; ++i)
    {
        const auto [ones, zeros] = countBits(v, i);

        if (ones > zeros)
        {
            gammaRate[i] = true;
            epsilonRate[i] = false;
        }
        else
        {
            gammaRate[i] = false;
            epsilonRate[i] = true;
        }
    }

    cout << gammaRate.to_ullong() * epsilonRate.to_ullong() << '\n';
}

void part2(vector<bitset<NUM_BITS>> v)
{
    size_t idx = 1;
    auto O2Vec = v;
    while (O2Vec.size() > 1)
    {
        const auto [ones, zeros] = countBits(O2Vec, NUM_BITS - idx);
        vector<bitset<NUM_BITS>> temp(O2Vec.size());

        if (ones >= zeros)
        {
            auto it = copy_if(O2Vec.begin(), O2Vec.end(), temp.begin(),
                              [&](const bitset<NUM_BITS> &b) { return b[NUM_BITS - idx]; });
            temp.resize(distance(temp.begin(), it));
        }
        else
        {
            auto it = copy_if(O2Vec.begin(), O2Vec.end(), temp.begin(),
                              [&](const bitset<NUM_BITS> &b) { return !b[NUM_BITS - idx]; });
            temp.resize(distance(temp.begin(), it));
        }

        O2Vec = temp;
        ++idx;
    }

    auto CO2Vec = v;
    idx = 1;
    while (CO2Vec.size() > 1)
    {
        const auto [ones, zeros] = countBits(CO2Vec, NUM_BITS - idx);
        vector<bitset<NUM_BITS>> temp(CO2Vec.size());

        if (zeros <= ones)
        {
            auto it = copy_if(CO2Vec.begin(), CO2Vec.end(), temp.begin(),
                              [&](const bitset<NUM_BITS> &b) { return !b[NUM_BITS - idx]; });
            temp.resize(distance(temp.begin(), it));
        }
        else
        {
            auto it = copy_if(CO2Vec.begin(), CO2Vec.end(), temp.begin(),
                              [&](const bitset<NUM_BITS> &b) { return b[NUM_BITS - idx]; });
            temp.resize(distance(temp.begin(), it));
        }

        CO2Vec = temp;
        ++idx;
    }

    cout << O2Vec[0].to_ullong() * CO2Vec[0].to_ullong() << '\n';
}

int main()
{
    ifstream fin("d3input");

    string s;
    vector<bitset<NUM_BITS>> v;
    while (fin >> s)
    {
        v.emplace_back(s);
    }

    part1(v);
    part2(v);
}
