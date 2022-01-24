class STable
{
public:
    int LOG = 0;
    int n;
    vector<vector<int>> T;
    STable(vector<int> &a)
    {
        n = (int)a.size();
        while (1 << (LOG + 1) <= n)
            LOG++;
        T.resize(LOG + 1);
        for (int i = 0; i <= LOG; i++)
            T[i].resize(n);
        for (int i = 0; i < n; i++)
            T[0][i] = a[i];
        for (int i = 1; i <= LOG; i++)
        {
            for (int j = 0; j < n - (1 << i) + 1; j++)
            {
                T[i][j] = combine(T[i - 1][j], T[i - 1][j + (1 << (i - 1))]);
            }
        }
    }
    int combine(int a, int b)
    {
        return __gcd(a, b);
    }
    int qry(int l, int r)
    {
        int exp = 0;
        while (1 << (exp + 1) <= r - l + 1)
            exp++;
        return combine(T[exp][l], T[exp][r - (1 << exp) + 1]);
    }
};
