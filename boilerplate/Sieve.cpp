vector<int> spf;
//vector<int> primes;
void sieve(int n)
{
    spf.resize(n + 1);
    for (int i = 1; i <= n; i++)
        spf[i] = i;
    for (int i = 2; i <= n; i++)
    {
        if (spf[i] == i)
        {
            //primes.push_back(i);
            for (int j = i * i; j <= n; j += i)
            {
                if (spf[j] == j)
                    spf[j] = i;
            }
        }
    }
}