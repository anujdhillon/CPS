vector<int> subtree_size;

int dfs(int node, int parent = -INF)
{
    subtree_size[node] = 1;

    for (edge &e : adj[node])
        if (e.node != parent)
            subtree_size[node] += dfs(e.node, node);

    return subtree_size[node];
}

int centroid(int root)
{
    int n = dfs(root);
    bool found;

    // Repeatedly move to the subtree that is at least half of the tree, if such a subtree exists.
    do
    {
        found = false;

        for (edge &e : adj[root])
            if (subtree_size[e.node] < subtree_size[root] && 2 * subtree_size[e.node] >= n)
            {
                root = e.node;
                found = true;
                break;
            }
    } while (found);

    return root;
}