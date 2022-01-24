int n;
vector<vector<int>> p;
vector<vector<int>> g;
vector<int> h;
int LOG = 0;

void dfs(int i)
{
    for (int j = 1; j <= LOG; j++)
    {
        p[i][j] = p[p[i][j - 1]][j - 1];
    }
    h[i] = h[p[i][0]] + 1;
    for (auto j : g[i])
    {
        dfs(j);
    }
}

int kthAncestor(int x, int k)
{
    for (int i = LOG; i >= 0; i--)
    {
        if ((1 << i) <= k)
        {
            k -= (1 << i);
            x = p[x][i];
        }
    }
    return x;
}

int lca(int a, int b)
{
    if (h[a] < h[b])
    {
        b = kthAncestor(b, h[b] - h[a]);
    }
    else if (h[a] > h[b])
    {
        a = kthAncestor(a, h[a] - h[b]);
    }
    for (int i = LOG; i >= 0; i--)
    {
        if (p[a][i] != p[b][i])
        {
            a = p[a][i];
            b = p[b][i];
        }
    }
    if (a == b)
        return a;
    return p[a][0];
}

p.resize(n + 1);
g.resize(n + 1);
h.resize(n + 1);
while (1 << (LOG + 1) <= n)
    LOG++;
for (int i = 0; i < n + 1; i++)
    p[i].resize(LOG + 1);
for (int i = 0; i < LOG + 1; i++)
    p[1][i] = 0;
for (int i = 2; i < LOG + 1; i++)
{
    cin >> p[i][0];
    g[p[i][0]].append(i);
}
dfs(1);