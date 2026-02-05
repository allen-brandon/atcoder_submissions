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
typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> ordered_set; // find_by_order(), order_of_key()
typedef tree<pair<ll,ll>, null_type, less<pair<ll,ll>>, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;
#define vll vector<ll>
#define vi vector<int>
#define counter(_) unordered_map<_,size_t>
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
ll mod = 1000000007;
ll modfac[2000001]; //factorial(i) % mod

//n**p % mod in log(p)
ll f(ll n, ll p) {
    ll res = 1;
    while (p) {
        if (p&1) res = (res*n)%mod;
        p>>=1;
        n = (n*n)%mod;
    }
    return res;
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    lli(k);
    si(s);
    ll n = s.size();
    ll m = k+n;
    modfac[0] = 1;
    fr(i,1,m+1) modfac[i] = (modfac[i-1]*i)%mod;
    ll modfac_n = modfac[n-1], res{};
    fr(i,0,k+1) {
        ll l = f(25,i);
        ll r = f(26,k-i);
        ll num = modfac[i+n-1];
        ll denom = (modfac[i]*modfac_n)%mod;
        //mod inverse of denomenator under mod
        denom = f(denom,mod-2);
        ll comb = (num*denom)%mod; //n-1 choose l
        l = (l*comb)%mod;
        res += (l*r)%mod;
        res -= res>=mod?mod:0;
    }
    print(res);
}