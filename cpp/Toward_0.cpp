#ifdef DEBUG
#include <cstdio>
#define USE_INPUT_FILE(file) freopen(file, "r", stdin);
#else
#define USE_INPUT_FILE(file)
#endif

using namespace std;
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <deque>
#include <queue>
#include <numeric>
#include <bitset>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <iomanip>
using namespace __gnu_pbds;
#define ll long long
#define ull unsigned ll
#define vll vector<ll>
#define vi vector<int>
#define counter(_) unordered_map<_,size_t>
#define ordered_set tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>
#define ordered_multiset tree<pair<ll,ll>, null_type, less<pair<ll,ll>>, rb_tree_tag, tree_order_statistics_node_update>
#define fio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define print(_) cout << _ << "\n";
#define printv(_) for (const auto& x : _) cout << x << ' '; cout << '\n';
#define printum(_) cout<<"{";for (const auto& kvp:_) cout<<kvp.first<<":"<<kvp.second<<","; cout<<"}\n";
#define si(_) string _; cin >> _;
#define ii(_) int _; cin >> _;
#define lli(_) ll _; cin >> _;
#define ld long double
#define ldi(_) ld _; cin >> _;
ll inf = 151515151515151;
ll mod = 1000000007;

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    lli(n); ldi(a); ldi(x); ldi(y);
    map<ll,ld> seen;
    function<ld(ll)> dfs = [&](ll u) -> ld {
        if (!u) return 0.0;
        if (seen.find(u)!=seen.end()) return seen[u];
        // div by a
        ll v = u/a;
        ld res = dfs(v)+x;

        // roll
        ld aggregate = y;
        for (ld i=2.0; i<=6.0; ++i) {
            v = u/i;
            aggregate+=dfs(v)/6.0;
        }
        aggregate*=6.0/5.0;
        res = min(res, aggregate);
        seen[u] = res;
        return res;
    };
    ld ret = dfs(n);
    cout << setprecision (32) << ret << "\n";
}