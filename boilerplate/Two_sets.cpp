struct Two_sets
{
    int n;
    multiset<int> upper, lower; // upper is fixed at size n
    long long upper_sum;
    Two_sets(int _n)
    {
        n = _n;
        upper_sum = 0;
    }
    void upper_to_lower()
    {
        int k = *upper.begin();
        upper.erase(upper.find(k));
        lower.insert(k);
        upper_sum -= k;
    }

    void lower_to_upper()
    {
        if (lower.size())
        {
            int k = *lower.rbegin();
            lower.erase(lower.find(k));
            upper.insert(k);
            upper_sum += k;
        }
    }

    void insert(int k)
    {
        upper.insert(k);
        upper_sum += k;
        if (upper.size() > n)
        {
            upper_to_lower();
        }
    }
    void erase(int k)
    {
        bool done = false;
        if (lower.find(k) != lower.end())
        {
            lower.erase(lower.find(k));
            done = true;
        }
        if (!done)
        {
            upper.erase(upper.find(k));
            upper_sum -= k;
            if (upper.size() < n)
                lower_to_upper();
        }
    }
};