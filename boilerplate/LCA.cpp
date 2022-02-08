vector<vector<int>> p;
vector<vector<int>> cost;
vector<vector<pair<int, int>>> g;
vector<int> h;
int LOG = 0;

void dfs(int i, int par, int wt)
{
    p[i][0] = par;
    cost[i][0] = wt; // todo
    for (int j = 1; j <= LOG; j++)
    {
        p[i][j] = p[p[i][j - 1]][j - 1];
        cost[i][j] = max(cost[i][j - 1], cost[p[i][j - 1]][j - 1]); // todo
    }
    h[i] = h[p[i][0]] + 1;
    for (auto [j, w] : g[i])
    {
        if (j != par)
            dfs(j, i, w);
    }
}

pair<int, int> kthAncestor(int x, int k)
{
    int path_cost = 0;
    for (int i = LOG; i >= 0; i--)
    {
        if ((1 << i) <= k)
        {
            k -= (1 << i);
            path_cost = max(path_cost, cost[x][i]); // todo
            x = p[x][i];
        }
    }
    return {x, path_cost};
}

pair<int, int> lca(int a, int b)
{
    if (h[a] < h[b])
    {
        swap(a, b);
    }
    auto [anc, path_cost] = kthAncestor(a, h[a] - h[b]);
    a = anc;
    for (int i = LOG; i >= 0; i--)
    {
        if (p[a][i] != p[b][i])
        {
            path_cost = max(path_cost, max(cost[a][i], cost[b][i])); // todo
            a = p[a][i];
            b = p[b][i];
        }
    }
    if (a == b)
        return {a, path_cost};
    return {p[a][0], max(path_cost, max(cost[a][0], cost[b][0]))}; // todo
}

void init_lca(int n)
{
    LOG = 0;
    p.clear();
    g.clear();
    h.clear();
    cost.clear();
    while (1 << (LOG + 1) <= n)
        LOG++;
    p.resize(n + 1);
    g.resize(n + 1);
    h.resize(n + 1);
    cost.resize(n + 1);
    for (int i = 0; i < n + 1; i++)
    {
        p[i].resize(LOG + 1);
        cost[i].resize(LOG + 1);
    }
}
