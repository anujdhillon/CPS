template <typename T>
vector<int> kmp(const T &s)
{
    int n = (int)s.size();
    vector<int> pref(n);
    for (int i = 1; i < n; i++)
    {
        int j = pref[i - 1];
        while (j && s[j] != s[i])
            j = pref[j - 1];
        pref[i] = j + (s[i] == s[j]);
    }
    return pref;
}
