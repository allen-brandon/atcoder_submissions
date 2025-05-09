#ifdef DEBUG
#include <cstdio>
#define USE_INPUT_FILE(file) freopen(file, "r", stdin);
#else
#define USE_INPUT_FILE(file)
#endif

using namespace std;
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
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
ll inf = 151515151515151;
ll mod = 998244353;
array<string,2> ny = {"No","Yes"};
array<ll,18> a;
array<ll,18> b;
array<array<ull,1<<18>,18> dp;

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(n); lli(llx); lli(lly);
    ull x = (ull)(llx);
    ull y = (ull)(lly);
    for (int i=0; i<n; ++i) {
        cin >> a[i];
    }
    bool same = 1;
    for (int i=0; i<n; ++i) {
        cin >> b[i];
        same &= (a[i]==b[i]);
    }
    if (same) {
        print(0);
        exit(0);
    }
    for (int i=0; i<1<<n; ++i) {
        for (int j=0; j<n; ++j) {
            dp[j][i] = ULLONG_MAX;
        }
    }
    function<ull(int,int)> dfs = [&](int i, int mask) {
        if (i == n) return 0ull;
        if (dp[i][mask] != ULLONG_MAX) return dp[i][mask];
        ull msf = ULLONG_MAX;
        ull cur_y = 0ull;
        bool first = true;
        for (int j=0; j<n; ++j) {
            if (mask&(1<<j)) {
                continue;
            } else {
                cur_y += y;
                if (first) {
                    cur_y -= y;
                    first = false;
                }
                ull cur = dfs(i+1, mask^(1<<j))+cur_y+(x*(max(a[i],b[j])-min(a[i],b[j])));
                if (cur < msf) msf = cur;
            }
        }
        dp[i][mask] = msf;
        return msf;
    };
    ull res = dfs(0,0);
    print(res);
}