#ifdef LOCAL
#include "_pch.hpp"
#define USE_INPUT_FILE(file) freopen(file, "r", stdin);
#else
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define USE_INPUT_FILE(file)
#endif

using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using ull = unsigned long long;
#define vll vector<ll>
#define vi vector<int>
#define counter(_) unordered_map<_,size_t>
#define ordered_set tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> // find_by_order(), order_of_key()
#define ordered_multiset tree<pair<ll,ll>, null_type, less<pair<ll,ll>>, rb_tree_tag, tree_order_statistics_node_update>
#define fio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define fr(i,l,r) for (int i=l; i<r; ++i)
#define print(_) cout << _ << "\n";
#define printv(_) for (const auto& x : _) cout << x << ' '; cout << '\n';
#define printm(_) cout<<"{";for (const auto& kvp:_) cout<<kvp.first<<":"<<kvp.second<<","; cout<<"}\n";
#define si(_) string _; cin >> _;
#define ii(_) int _; cin >> _;
#define lli(_) ll _; cin >> _;
array<pair<int,int>,4> didj = {{{-1,0},{0,1},{1,0},{0,-1}}};
array<string,2> ny = {"No","Yes"};
ll inf = 151515151515151;
ll mod = 998244353;
ll modfac[51];
ll lim[51];
map<int,ll> dp[51]; // number of ways to reach each lcm for each index
ll modcomb[51][51];

ll modpow(ll n, ll k) {
    ll res = 1;
    while (k!=0) {
        if (k&1) {
            res = res*n % mod;
        }
        k>>=1;
        n = n*n % mod;
    }
    return res;
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(n); ii(k);
    if (modfac[0]==0) {
        modfac[0]=1;
        modfac[1]=1;
        fr(i,2,51) modfac[i] = (modfac[i-1] * i) % mod;
        modcomb[0][0] = 1;
        fr(i,1,51) {
            modcomb[i][0] = 1;
            fr(j,1,51) {
                modcomb[i][j] = (modcomb[i-1][j-1] + modcomb[i-1][j]) % mod;
            }
        }
    }
    fr(i,0,n+1) {
        dp[i].clear();
    }
    dp[0][1]=1;
    fr(i,0,n+1) { //for each sequence size
        for (auto [j,f] : dp[i]) {
            fr(l,1,n+1-i) {
                dp[i+l][lcm(j,l)] = (dp[i+l][lcm(j,l)] + (dp[i][j]*((modcomb[n-1-i][l-1]*modfac[l-1])%mod))%mod) % mod; //add all cycles of this size to new lcm
            }
        }
    }
    ll res = 0;
    for (auto [x,f] : dp[n]) {
        res  = (res+((modpow(x,k)*f)%mod)) % mod;
    }
    print(res);
}