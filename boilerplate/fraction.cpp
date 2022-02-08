struct fraction
{
    int num, denom;
    fraction(int _num) : num(_num), denom(1) {}
    fraction(int _num, int _denom) : num(_num), denom(_denom)
    {
        if (denom < 0)
        {
            denom = -denom;
            num = -num;
        }
        int g = __gcd(abs(num), denom);
        num /= g, denom /= g;
    }
    bool operator<(const fraction &other)
    {
        return (__int128_t)num * other.denom < (__int128_t)denom * other.num;
    }
    bool operator<=(const fraction &other)
    {
        return (__int128_t)num * other.denom <= (__int128_t)denom * other.num;
    }
    bool operator>(const fraction &other)
    {
        return (__int128_t)num * other.denom > (__int128_t)denom * other.num;
    }
    bool operator>=(const fraction &other)
    {
        return (__int128_t)num * other.denom >= (__int128_t)denom * other.num;
    }
    bool operator==(const fraction &other)
    {
        return (__int128_t)num * other.denom == (__int128_t)denom * other.num;
    }
    friend ostream &operator<<(ostream &os, const fraction &p)
    {
        return os << "(" << p.num << "/" << p.denom << ") ";
    }
};
