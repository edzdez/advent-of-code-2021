#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Board
{
    vector<int> board;
    vector<bool> status;

    Board() : status(vector<bool>(25, false))
    {
    }

    void mark(int num)
    {
        auto it = find(board.begin(), board.end(), num);
        if (it != board.end())
            status[distance(board.begin(), it)] = true;
    }

    bool checkWin()
    {
        // check rows
        for (int r = 0; r < 5; ++r)
        {
            bool flag = true;
            for (int c = 0; c < 5; ++c)
            {
                flag = flag & status[r * 5 + c];
            }

            if (flag)
                return true;
        }

        // check cols
        for (int c = 0; c < 5; ++c)
        {
            bool flag = true;
            for (int r = 0; r < 5; ++r)
            {
                flag = flag & status[r * 5 + c];
            }

            if (flag)
                return true;
        }

        return false;
    }

    [[nodiscard]] int64_t getScore()
    {
        auto score = 0l;

        for (size_t i = 0; i < 25; ++i)
        {
            if (!status[i])
                score += board[i];
        }

        return score;
    }
};

vector<int> parseNumbersDrawn(const string &line)
{
    vector<int> numbersDrawn;
    istringstream ss(line);
    string token;

    while (getline(ss, token, ','))
    {
        numbersDrawn.emplace_back(stoi(token));
    }

    return numbersDrawn;
}

vector<Board> readBoards(ifstream &fin)
{
    auto readBoard = [&]() -> Board {
        Board b;

        for (int i = 0; i < 25; ++i)
        {
            int num;
            fin >> num;

            b.board.push_back(num);
        }

        return b;
    };

    vector<Board> boards;

    string line;
    while (getline(fin, line))
    {
        boards.push_back(readBoard());
    }

    return boards;
}

void part1(const vector<int> &numbersDrawn, vector<Board> boards)
{
    size_t flag = 0;
    int winningNumber = -1;
    for (int i : numbersDrawn)
    {
        for (size_t boardNum = 0; boardNum < boards.size(); ++boardNum)
        {
            boards[boardNum].mark(i);
            if (boards[boardNum].checkWin())
            {
                flag = boardNum + 1;
                break;
            }
        }

        if (flag)
        {
            winningNumber = i;
            break;
        }
    }

    cout << winningNumber * boards[flag - 1].getScore() << '\n';
}

void part2(const vector<int> &numbersDrawn, vector<Board> boards)
{
    vector<int> finishTurn(boards.size(), 0);

    for (int i = 0; i < numbersDrawn.size(); ++i)
    {
        for (size_t boardNum = 0; boardNum < boards.size(); ++boardNum)
        {
            if (finishTurn[boardNum])
                continue;

            boards[boardNum].mark(numbersDrawn[i]);
            if (boards[boardNum].checkWin())
            {
                finishTurn[boardNum] = i;
            }
        }
    }

    auto it = max_element(finishTurn.begin(), finishTurn.end());
    cout << boards[distance(finishTurn.begin(), it)].getScore() * numbersDrawn[*it] << '\n';
}

int main()
{
    ifstream fin("d4input");

    string line;
    getline(fin, line);
    auto numbersDrawn = parseNumbersDrawn(line);

    auto boards = readBoards(fin);

    part1(numbersDrawn, boards);
    part2(numbersDrawn, boards);
}