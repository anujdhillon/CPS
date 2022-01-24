struct Node
{
    int max_len, left, right;
    Node()
    {
        max_len = 0;
        left = 0;
        right = 0;
    }
    Node(char ch)
    {
        max_len = 0;
        left = (ch == '(');
        right = (ch == ')');
    }
    friend Node combine(Node &a, Node &b)
    {
        Node res;
        int k = min(a.left, b.right);
        res.max_len = a.max_len + b.max_len + 2 * k;
        res.left = a.left - k + b.left;
        res.right = b.right - k + a.right;
        return res;
    }
};

template <class T>
struct SGT
{
    int n;
    vector<T> t;
    SGT(vector<T> &a)
    {
        n = (int)a.size();
        t.resize(4 * n);
        build(a, 1, 0, n - 1);
    }

    void build(vector<T> &a, int v, int tl, int tr)
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

    void update(int v, int tl, int tr, int pos, T new_val)
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
    T query(int l, int r)
    {
        return query(1, 0, n - 1, l, r);
    }
    void update(int pos, T new_val)
    {
        update(1, 0, n - 1, pos, new_val);
    }
    T query(int v, int tl, int tr, int l, int r)
    {
        if (l > r)
            return T();
        if (l == tl && r == tr)
        {
            return t[v];
        }
        int tm = (tl + tr) / 2;
        Node left_child = query(v * 2, tl, tm, l, min(r, tm));
        Node right_child = query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
        return combine(left_child, right_child);
    }
};
