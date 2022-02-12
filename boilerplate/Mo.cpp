sort(queries.begin(), queries.end(), [&](pair<int, int> &p1, pair<int, int> &p2) -> bool
     {
        if(p1.first/s != p2.first/s) return p1.first/s < p2.first/s;
        return p1.second < p2.second; });

int currentL = 0, currentR = 0; //[currentL, currentR)

for (auto [L, R] : queries)
{
    while (currentL < L)
    {
        remove(a[currentL]);
        currentL++;
    }
    while (currentL > L)
    {
        add(a[currentL - 1]);
        currentL--;
    }
    while (currentR <= R)
    {
        add(a[currentR]);
        currentR++;
    }
    while (currentR > R + 1)
    {
        remove(a[currentR - 1]);
        currentR--;
    }
}
