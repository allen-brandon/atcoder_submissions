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
array<int,26> c;
array<ll,5001> dp;
array<ll,5001> fac;
array<array<ll,5001>,5001> mc;

ll modfac(int x) {
    if (fac[0]==0) fac[0]=1;
    int y=x;
    while (fac[y]==0) --y;
    while (y!=x) {
        ++y;
        fac[y] = (fac[y-1]*y) % mod;
    }
    return fac[x];
}

ll modcomb(int n, int k) {
    if (mc[5000][5000] == 0) {
        for (int i=0; i<=5000; ++i) {
            mc[i][0]=1ll;
            for (int j=1; j<=i; ++j) {
                mc[i][j]=(mc[i-1][j]+mc[i-1][j-1])%mod;
            }
        }
    }
    return mc[n][k];
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    si(s);
    int n = s.size();
    fill_n(c.begin(),26,0);
    for (auto x : s) {
        c[x-'a']++;
    }
    dp[0]=1ll;
    for (int x=0; x<26; ++x) {
        for (int i=n; i>0; --i) {
            for (int j=1; j<=min(c[x],i); ++j) {
                ll coef = modcomb(i,j);
                dp[i] = (dp[i] + dp[i-j]*coef) % mod;
            }
        }
    }
    ll res = accumulate(dp.begin()+1, dp.begin()+n+1, 0ll) % mod;
    print(res);
}