#include <bits/stdc++.h>
using namespace std;

int N, D, E, M;
vector<int> g[22];

int warehouse[22];
int order[22];
int cost[22];
set<int> l, r;

struct Edge
{
    int u, v, c;
};

vector<Edge> edges;

void bfs(int root);

int main()
{
    ifstream in("order_delivery_input.txt");
    in >> N >> D >> E;
    int x, y, w, c, p;
    for(int i = 0; i < E; ++i)
    {
        in >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    for(int i = 0; i < 22; ++i)
    {
        warehouse[i] = -1;
        order[i] = -1;
        cost[i] = -1;
    }

    for(int i = 0; i < D; ++i)
    {
        in >> w >> c >> p;
        warehouse[p] = w;
        cost[p] = c;
        l.insert(p);
    }

    in >> M;
    for(int i = 0; i < M; ++i)
    {
        int k, g;
        in >> k >> g;
        if(order[g] != -1)
            order[g] += k;
        else
            order[g] = k;
        r.insert(g);
    }

    for(int u: l)
        bfs(u);

    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {return a.c < b.c;});

    int total = 0;
    for(Edge &edge: edges)
    {
        int u = edge.u;
        int v = edge.v;
        int m = min(warehouse[u], order[v]);
        total += m * edge.c;
        warehouse[u] -= m;
        order[v] -= m;
    }

    cout << total << endl;
}

void bfs(int root)
{
    int mask[22];
    int d[22];
    memset(&mask[0], 0, sizeof(mask));
    memset(&d[0], 0, sizeof(d));
    queue<int> q;
    q.push(root);
    mask[root] = 1;
    while (q.size())
    {
        int u = q.front();
        q.pop();
        for(int &v: g[u])        
        {
            if(mask[v])
                continue;
            mask[v] = 1;
            d[v] = d[u] + 1;
            q.push(v);
            if(r.find(v) != r.end())
            {
                Edge e;
                e.u = root;
                e.v = v;
                e.c = d[v] * cost[root];
                edges.push_back(e);
            }
        }
    }
}
