#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

uint64_t dfs(const unordered_map<string, vector<string>> &adj, unordered_map<string, bool> visited, const string &curr)
{
    if (curr == "end")
        return 1;

    if (visited[curr])
        return 0;

    int64_t total = 0;
    if (islower(curr[0]))
        visited[curr] = true;

    for (auto &path : adj.at(curr))
    {
        total += dfs(adj, visited, path);
    }

    return total;
}

void part1(const unordered_map<string, vector<string>> &adj)
{
    unordered_map<string, bool> visited;

    cout << dfs(adj, visited, "start") << '\n';
}

set<vector<string>> dfs2(const unordered_map<string, vector<string>> &adj, unordered_map<string, int> visited,
                         const string &curr, const string &repeat, vector<string> path)
{
    path.push_back(curr);

    if (curr == "end")
        return set<vector<string>>{path};

    if (curr != repeat && visited[curr] == 1)
        return set<vector<string>>();
    else if (curr == repeat && visited[curr] == 2)
        return set<vector<string>>();

    set<vector<string>> paths;
    if (islower(curr[0]))
        ++visited[curr];

    for (auto &next : adj.at(curr))
    {
        auto newPath = path;
        newPath.push_back(next);
        auto s = dfs2(adj, visited, next, repeat, newPath);
        paths.insert(s.begin(), s.end());
    }

    return paths;
}

void part2(const unordered_map<string, vector<string>> &adj)
{
    unordered_map<string, int> visited;

    set<vector<string>> paths;
    for (const auto &[key, _] : adj)
    {
        if (key != "start" && key != "end")
            if (islower(key[0]))
            {
                auto s = dfs2(adj, visited, "start", key, vector<string>{"start"});
                paths.insert(s.begin(), s.end());
            }
    }

    cout << paths.size() << '\n';
}

int main()
{
    ifstream fin("d12input");

    unordered_map<string, vector<string>> adj;
    string line;
    while (getline(fin, line))
    {
        istringstream ss(line);
        string a, b;

        getline(ss, a, '-');
        getline(ss, b, '-');

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // for (const auto &[node, paths] : adj)
    // {
    //     cout << node << ": ";
    //     for (const auto &path : paths)
    //         cout << path << ' ';
    //     cout << '\n';
    // }

    part1(adj);
    part2(adj);
}
