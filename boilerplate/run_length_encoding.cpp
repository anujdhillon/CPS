template <typename T_iterable>
vector<pair<int, int>> run_length_encoding(T_iterable &iterable)
{
    vector<pair<int, int>> res;
    int n = iterable.size();
    for (int i = 0; i < n; i++)
    {
        if (res.size() && iterable[res.back().first] == iterable[i])
            res.back().second++;
        else
            res.push_back({i, 1});
    }
    return res;
}