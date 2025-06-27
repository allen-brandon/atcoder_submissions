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
int a[10][10];
int rows[1024][10];
int cols[1024][10];
ll dp[601][1024];

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(h); ii(w); ii(n);
    int lim = 1<<max(h,w);
    n<<=1;
    fr(i,0,h) {
        si(s);
        fr(j,0,w) {
            int x = s[j]-'0';
            a[i][j]=x;
        }
    }
    fr(mask,1,lim) {
        dp[n][mask]=1;
        fr(j,0,w) {
            if ((mask&(1<<j))==0) continue;
            fr(i,0,h) {
                rows[mask][a[i][j]]|=1<<i;
            }
        }
        fr(i,0,h) {
            if ((mask&(1<<i))==0) continue;
            fr(j,0,w) {
                cols[mask][a[i][j]]|=1<<j;
            }
        }
    }
    for (int t=n-1; t>=0; --t) {
        auto rc = t&1? rows : cols;
        fr(mask,1,lim) {
            fr(x,1,10) {
                int mask1 = rc[mask][x];
                dp[t][mask] += dp[t+1][mask1];
            }
            dp[t][mask]%=mod;
        }
    }
    ll res = dp[0][lim-1];
    print(res);
}