
struct Fenwick2D
{
    int n, m;
    vector<vector<int>> sum;
    Fenwick2D(int _n, int _m)
    {
        n = _n, m = _m;
        sum.resize(n + 1);
        for (int i = 0; i <= n; i++)
            sum[i].resize(m + 1);
    }
    void add(int r, int c, int x)
    {
        for (; r <= n; r += (r & -r))
            for (int j = c; j <= m; j += (j & -j))
                sum[r][j] += x;
    }
    int get(int r, int c)
    {
        int res = 0;
        for (; r; r -= (r & -r))
            for (int j = c; j; j -= (j & -j))
                res += sum[r][j];
        return res;
    }
};
