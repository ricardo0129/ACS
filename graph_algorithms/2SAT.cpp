#include <bits/stdc++.h>
using namespace std;

int s;
vector<vector<int>> adj, adj_t;
vector<bool> used;
vector<int> order, comp;
vector<bool> assignment;

void dfs1(int v) {
    used[v] = true;
    for (int u : adj[v]) {
        if (!used[u])
            dfs1(u);
    }
    order.push_back(v);
}

void dfs2(int v, int cl) {
    comp[v] = cl;
    for (int u : adj_t[v]) {
        if (comp[u] == -1)
            dfs2(u, cl);
    }
}

bool solve_2SAT() {
    order.clear();
    used.assign(s, false);
    for (int i = 0; i < s; ++i) {
        if (!used[i])
            dfs1(i);
    }

    comp.assign(s, -1);
    for (int i = 0, j = 0; i < s; ++i) {
        int v = order[s - i - 1];
        if (comp[v] == -1)
            dfs2(v, j++);
    }

    assignment.assign(s / 2, false);
    for (int i = 0; i < s; i += 2) {
        if (comp[i] == comp[i + 1])
            return false;
        assignment[i / 2] = comp[i] > comp[i + 1];
    }
    return true;
}

void add_disjunction(int a, bool na, int b, bool nb) {
    // na and nb signify whether a and b are to be negated 
    a = 2*a ^ na;
    b = 2*b ^ nb;
    int neg_a = a ^ 1;
    int neg_b = b ^ 1;
    adj[neg_a].push_back(b);
    adj[neg_b].push_back(a);
    adj_t[b].push_back(neg_a);
    adj_t[a].push_back(neg_b);
}

int main()
{
    cout<<solve_2SAT()<<endl;


    return 0;
}