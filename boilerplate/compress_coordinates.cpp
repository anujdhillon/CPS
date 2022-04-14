pair<vector<int>, map<int, int>> compress_coordinates(const set<int> &keypoints)
{
    vector<int> stb;
    map<int, int> bts;
    for (int x : keypoints)
    {
        stb.push_back(x);
    }
    for (int i = 0; i < (int)stb.size(); i++)
        bts[stb[i]] = i;
    return {stb, bts}; // small to big, big to small
}
