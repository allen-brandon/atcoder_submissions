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
array<ll,3> pf = {2,7,17};

ll powmod(ll x, ll n, ll mod) {
    ll res = 1;
    while (n!=0) {
        if (n&1) {
            res = res*x % mod;
        }
        x = x*x % mod;
        n>>=1;
    }
    return res;
}

ll order(ll x, ll mod) {
    ll k = mod-1;
    for (auto f : pf) {
        while (k%f==0 and powmod(x,k/f,mod)==1) {
            k/=f;
        }
    }
    return k;
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    lli(n); lli(k); lli(m);
    m%=mod;
    ll mod1 = order(m,mod);
    k%=mod1;
    ll res = powmod(k,n,mod1);
    if (res==0) res+=mod1;
    res = powmod(m,res,mod);
    print(res);
}