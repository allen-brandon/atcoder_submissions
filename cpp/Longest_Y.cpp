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
#define ordered_set tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> // find_by_order(), order_by_key()
#define ordered_multiset tree<pair<ll,ll>, null_type, less<pair<ll,ll>>, rb_tree_tag, tree_order_statistics_node_update>
#define fio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
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
array<ll,200001> lpref; //sum of dist to all yj<i
array<ll,200001> rpref; //sum of dist to all yj>i
array<ll,200001> lpop; //count of all yj<i
array<ll,200001> rpop; //count of all yj>i

ll cost (int l, int r, const vi& a) {
    int m = l+(r-l)/2;
    ll l_pop = m-l, r_pop = r-m;
    l = a[l]; m = a[m]; r = a[r]; //use coordinates of each Y
    ll res = 0;
    //cost to move all l to m
    res += lpref[m];
    res -= lpref[l];
    res -= lpop[l]*ll(m-l);
    res -= (l_pop*(l_pop+1))/2;
    //cost to more all r to m
    res += rpref[m];
    res -= rpref[r];
    res -= rpop[r]*ll(r-m);
    res -= (r_pop*(r_pop+1))/2;
    return res;
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    si(s);
    lli(k);
    int n = s.size();
    vi a;
    ll cur = 0;
    ll curpop = 0;
    for (int i=0; i<n; ++i) {
        lpop[i]=curpop;
        cur+=curpop;
        lpref[i]=cur;
        if (s[i]=='Y') {
            a.push_back(i);
            curpop+=1;
        }
    }
    cur = 0;
    curpop = 0;
    for (int i=n-1; i>=0; --i) {
        rpop[i]=curpop;
        cur+=curpop;
        rpref[i]=cur;
        curpop+=(s[i]=='Y');
    }
    int l = 0, msf = 0;
    for (int r=0; r<a.size(); ++r) {
        while (cost(l,r,a)>k) ++l;
        msf = max(msf, r+1-l);
    }
    print(msf);
}