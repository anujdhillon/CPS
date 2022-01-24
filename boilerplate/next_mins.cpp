vector<vector<int>> nexts(vector<int> &a, int mul)
{ //use mul = 1 for next_mins, mult = -1 for next_maxs
    int n = (int)a.size();
    vector<vector<int>> res(2, vector<int>(n, n)); // 0 -> left, 1 -> right
    for (int i = 0; i < n; i++)
        res[0][i] = -1;
    vector<int> stack;
    for (int i = 0; i < n; i++)
    {
        while (len(stack) && mul * a[stack.back()] > mul * a[i])
            stack.pop_back();
        if (len(stack))
            res[0][i] = stack.back();
        stack.push_back(i);
    }
    stack.clear();
    for (int i = n - 1; i >= 0; i--)
    {
        while (len(stack) && mul * a[stack.back()] >= mul * a[i])
            stack.pop_back();
        if (len(stack))
            res[1][i] = stack.back();
        stack.push_back(i);
    }
    return res;
}