#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

// using namespace __gnu_pbds;
using namespace std;

template <class X, class Y>
ostream &operator<<(ostream &os, pair<X, Y> const &p)
{
    return os << "(" << p.first << ", " << p.second << ") ";
}
template <class Ch, class Tr, class Container>
basic_ostream<Ch, Tr> &operator<<(basic_ostream<Ch, Tr> &os, Container const &x)
{
    os << "[ ";
    for (auto &y : x)
        os << y << ", ";
    return os << "]\n";
}

#define int long long
#define len(a) (int)a.size()
#define rep(i, a, n) for (int i = a; i < n; i++)
#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
const long long INF = 1e18;
const double EPS = 1e-9;
int solve_case()
{

    return 0;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    clock_t clk = clock();
    int t = 1;
    cin >> t;
    for (int _ = 1; _ <= t; _++)
    {
        solve_case();
    }
    cerr << fixed << setprecision(6) << "Time: " << ((double)(clock() - clk)) / CLOCKS_PER_SEC << "\n";
    return 0;
}