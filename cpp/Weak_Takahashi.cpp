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
array<bitset<102>,102> grid;
array<array<int,102>,102> dp;

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(h); ii(w);
    for (int i=0; i<h; ++i) {
        si(s);
        for (int j=0; j<w; ++j) {
            grid[i][j] = s[j]=='#';
            dp[i][j]=0;
        }
        grid[i][w] = 1;
        dp[i][w] = 0;
    }
    for (int j=0; j<=w; ++j) dp[h][j] = 0;
    for (int i=h-1; i>=0; --i) {
        for (int j=w-1; j>=0; --j) {
            if (grid[i][j]) continue;
            dp[i][j] = max(dp[i+1][j], dp[i][j+1])+1;
        }
    }
    print(dp[0][0]);
}