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
// ll inf = 151515151515151;
// ll mod = 998244353;
int inf = 1000000007;
int a[3002][3002];

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(h); ii(w); ii(k);
    fr(i,0,h+2) {
        fill_n(a[i], w+2, inf);
    }
    // val, i, j
    priority_queue<tuple<int,int,int>> pq;
    auto nei = [](int i, int j, int h, int w) -> vector<tuple<int,int,int>> {
        vector<tuple<int,int,int>> res;
        for (auto [di,dj] : didj) {
            int i1=i+di, j1=j+dj;
            if (i1>0 && j1>0 && i1<=h && j1<=w) {
                res.emplace_back(a[i1][j1],i1,j1);
            }
        }
        sort(res.begin(),res.end());
        return res;
    };
    fr(i,0,k) {
        ii(x); ii(y);
        a[x][y] = 0;
        pq.emplace(0,x,y);
    }
    ll res = 0;
    while (!pq.empty()) {
        auto [k,i,j] = pq.top();
        pq.pop();
        k*=-1;
        if (k>a[i][j]) continue;
        res+=ll(k);
        for (auto [k1,i1,j1] : nei(i,j,h,w)) {
            if (k1==inf) {
                a[i1][j1] -= 1;
            } else if (k1>k+1) {
                int d = get<0>(nei(i1,j1,h,w)[1]);
                pq.emplace(-1-d,i1,j1);
                a[i1][j1] = d+1;
            }
        }
    }
    print(res);
}