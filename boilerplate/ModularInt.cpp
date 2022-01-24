template <int mod>
struct modint
{
    int val;
    modint(int y = 0)
    {
        if (y < 0 || y >= mod)
            y = (y % mod + mod) % mod;
        val = y;
    }
    modint(const modint &y)
    {
        val = y.val;
    }
    void operator=(const modint &y)
    {
        val = y.val;
    }

    modint operator-()
    {
        return modint(-val);
    }
    modint operator+(const modint &y)
    {
        return modint(val) += y;
    }
    modint operator-(const modint &y)
    {
        return modint(val) -= y;
    }
    modint operator*(const modint &y)
    {
        return modint(val) *= y;
    }
    modint operator/(const modint &y)
    {
        return modint(val) /= y;
    }
    modint &operator+=(const modint &y)
    {
        val += y.val;
        if (val >= mod)
            val -= mod;
        return *this;
    }
    modint &operator-=(const modint &y)
    {
        val += mod - y.val;
        if (val >= mod)
            val -= mod;
        return *this;
    }
    modint &operator*=(const modint &y)
    {
        val *= y.val;
        val %= mod;
        return *this;
    }
    modint &operator/=(const modint &y)
    {
        int n = mod - 2;
        modint mul = y;
        while (n)
        {
            if (n & 1)
                *this *= mul;
            mul *= mul;
            n >>= 1;
        }
        return *this;
    }
    operator int() const
    {
        return val;
    }
    friend istream &operator>>(std::istream &is, modint &x)
    {
        int t;
        return is >> t, x = modint(t), is;
    }
    friend ostream &operator<<(std::ostream &os, const modint &x) { return os << x.val; }
};
using mint = modint<1000000007>;
template <typename T>
T power(T x, int y)
{
    T res = 1;
    while (y)
    {
        if (y & 1)
            res = res * x;
        y >>= 1;
        x = x * x;
    }
    return res;
}

vector<mint> fact, invfact;
void initialiseFactorial(int n)
{
    fact.resize(n + 1);
    invfact.resize(n + 1);
    fact[0] = 1;
    invfact[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        fact[i] = fact[i - 1] * mint(i);
        invfact[i] = mint(1) / fact[i];
    }
}

mint c(int n, int r)
{
    if (r > n || n < 0 || r < 0)
        return 0;
    return fact[n] * invfact[r] * invfact[n - r];
}