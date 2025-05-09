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
array<array<ll, 1000002>,4> dp;

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    lli(h); lli(w); ii(k);
    lli(x1); lli(y1); lli(x2); lli(y2);
    fill_n(dp[0].begin(), k+1, 0);
    fill_n(dp[1].begin(), k+1, 0);
    fill_n(dp[2].begin(), k+1, 0);
    fill_n(dp[3].begin(), k+1, 0);
    dp[3][k] = 1;
    for (int i=k-1; i>=0; --i) {
        //neither are same; w-1, h-1 ways to stay at 0; 1 way to move to 1 or 2;
        dp[0][i] = ((dp[0][i+1]*(h+w-4))%mod + dp[1][i+1] + dp[2][i+1]) % mod;
        // same row; h-1 ways to move to 0; w-2 ways to stay at 1; 0 ways to move to 2; 1 way to move to 3;
        dp[1][i] = ((dp[0][i+1]*(h-1))%mod + (dp[1][i+1]*(w-2))%mod + dp[3][i+1]) % mod;
        //same col; w-1 ways to move to 0; h-2 ways to stay at 1; 1 way to move to 3;
        dp[2][i] = ((dp[0][i+1]*(w-1))%mod + (dp[2][i+1]*(h-2))%mod + dp[3][i+1]) % mod;
        //both are same; at x2,y2; no way to move to 0; w-1 to 1, h-1 to 2;
        dp[3][i] = ((dp[1][i+1]*(w-1))%mod + (dp[2][i+1]*(h-1))%mod) % mod;
    }
    int same = (x1==x2) + ((y1==y2)<<1);
    ll res = dp[same][0];
    print(res);
}