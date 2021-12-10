#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

void part1(const vector<string> &chunks)
{
    unordered_map<char, int> scoreLUT{{')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};

    int score = 0;
    for (const auto &chunk : chunks)
    {
        stack<char> s;
        for (const auto c : chunk)
        {
            if (c == '(' || c == '[' || c == '{' || c == '<')
                s.push(c);

            else
            {
                if ((c == ')' && s.top() == '(') || (c == ']' && s.top() == '[') || (c == '}' && s.top() == '{') ||
                    (c == '>' && s.top() == '<'))
                    s.pop();
                else
                {
                    score += scoreLUT[c];
                    break;
                }
            }
        }
    }

    cout << score << '\n';
}

void part2(const vector<string> &chunks)
{
    unordered_map<char, int> scoreLUT{{'(', 1}, {'[', 2}, {'{', 3}, {'<', 4}};

    vector<int64_t> scores;
    for (const auto &chunk : chunks)
    {
        stack<char> s;
        int64_t score = 0;
        bool flag = false;

        for (const auto c : chunk)
        {
            if (c == '(' || c == '[' || c == '{' || c == '<')
                s.push(c);
            else
            {
                if ((c == ')' && s.top() == '(') || (c == ']' && s.top() == '[') || (c == '}' && s.top() == '{') ||
                    (c == '>' && s.top() == '<'))
                    s.pop();
                else
                {
                    flag = true;
                    break;
                }
            }
        }

        if (!flag)
        {
            while (!s.empty())
            {
                auto c = s.top();
                s.pop();

                score *= 5;
                score += scoreLUT[c];
            }

            scores.push_back(score);
        }
    }

    sort(scores.begin(), scores.end());
    cout << scores[scores.size() / 2] << '\n';
}

int main()
{
    ifstream fin("d10input");

    vector<string> chunks;
    string line;

    while (getline(fin, line))
        chunks.push_back(line);

    part1(chunks);
    part2(chunks);
}