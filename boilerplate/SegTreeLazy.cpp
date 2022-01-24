class SegTreeLazy
{
public:
    int n;
    vector<int> t;
    vector<int> lazy;
    SegTreeLazy(vector<int> &a)
    {
        n = a.size();
        t.resize(4 * n);
        lazy.resize(4 * n);
        build(a, 1, 0, n - 1);
    }
    int combine(int a, int b)
    {
        return max(a, b);
    }
    void build(vector<int> &a, int v, int tl, int tr)
    {
        if (tl == tr)
        {
            t[v] = a[tl];
            return;
        }
        int tm = (tl + tr) / 2;
        build(a, 2 * v, tl, tm);
        build(a, 2 * v + 1, tm + 1, tr);
        t[v] = combine(t[2 * v], t[2 * v + 1]);
    }
    void update(int v, int tl, int tr, int l, int r, int add)
    {
        if (l > r)
        {
            return;
        }
        if (tl == l && tr == r)
        {
            t[v] += add;
            lazy[v] += add;
            return;
        }
        int tm = (tl + tr) / 2;
        push(v);
        update(2 * v, tl, tm, l, min(r, tm), add);
        update(2 * v + 1, tm + 1, tr, max(l, tm + 1), r, add);
        t[v] = combine(t[2 * v], t[2 * v + 1]);
    }
    void push(int v)
    {
        t[2 * v] += lazy[v];
        t[2 * v + 1] += lazy[v];
        lazy[2 * v] += lazy[v];
        lazy[2 * v + 1] += lazy[v];
        lazy[v] = 0;
    }
    void update(int l, int r, int add)
    {
        update(1, 0, n - 1, l, r, add);
    }
    int query(int l, int r)
    {
        return query(1, 0, n - 1, l, r);
    }
    int query(int v, int tl, int tr, int l, int r)
    {
        if (l > r)
        {
            return -INF;
        }
        if (l == tl && r == tr)
        {
            return t[v];
        }
        push(v);
        int tm = (tl + tr) / 2;
        return combine(query(v * 2, tl, tm, l, min(r, tm)), query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
    }
};
