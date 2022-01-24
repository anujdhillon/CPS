class SGT
{
public:
    int n;
    vector<int> t;
    SGT(vector<int> &a)
    {
        n = (int)a.size();
        t.resize(4 * n);
        build(a, 1, 0, n - 1);
    }

    int combine(int a, int b)
    {
        return min(a, b);
    }

    void build(vector<int> &a, int v, int tl, int tr)
    {
        if (tl == tr)
        {
            t[v] = a[tl];
        }
        else
        {
            int tm = (tl + tr) / 2;
            build(a, v * 2, tl, tm);
            build(a, v * 2 + 1, tm + 1, tr);
            t[v] = combine(t[v * 2], t[v * 2 + 1]);
        }
    }

    void update(int v, int tl, int tr, int pos, int new_val)
    {
        if (tl == tr)
        {
            t[v] = new_val;
        }
        else
        {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(v * 2, tl, tm, pos, new_val);
            else
                update(v * 2 + 1, tm + 1, tr, pos, new_val);
            t[v] = combine(t[v * 2], t[v * 2 + 1]);
        }
    }
    int query(int l, int r)
    {
        return query(1, 0, n - 1, l, r);
    }
    void update(int pos, int new_val)
    {
        update(1, 0, n - 1, pos, new_val);
    }
    int query(int v, int tl, int tr, int l, int r)
    {
        if (l > r)
            return INF;
        if (l == tl && r == tr)
        {
            return t[v];
        }
        int tm = (tl + tr) / 2;
        return combine(query(v * 2, tl, tm, l, min(r, tm)), query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
    }
};
