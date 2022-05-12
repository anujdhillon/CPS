struct Fenwick
{
    int n;
    vector<int> sum;
    Fenwick(int _n)
    {
        n = _n;
        sum.resize(n + 1);
    }
    void add(int i, int x)
    {
        for (; i <= n; i += (i & -i))
            sum[i] += x;
    }
    int get(int i)
    {
        int res = 0;
        for (; i; i -= (i & -i))
            res += sum[i];
        return res;
    }
};