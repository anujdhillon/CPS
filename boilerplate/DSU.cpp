class DSU
{
public:
    vector<int> parent;
    vector<int> sizes;
    DSU(int n)
    {
        parent.resize(n);
        sizes.resize(n);
        for (int i = 0; i < n; i++)
            make_set(i);
    }
    void make_set(int v)
    {
        parent[v] = v;
        sizes[v] = 1;
    }
    int find_set(int v)
    {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }

    void union_sets(int a, int b)
    {
        a = find_set(a);
        b = find_set(b);
        if (a != b)
        {
            if (sizes[a] < sizes[b])
                swap(a, b);
            parent[b] = a;
            sizes[a] += sizes[b];
        }
    }
};