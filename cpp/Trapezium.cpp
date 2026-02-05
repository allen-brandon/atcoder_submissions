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
int a[2001][2];

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(n);
    ll res = 0;
    ll parallelograms = 0;
    map<pair<int,int>,int> slopes;
    map<pair<int,int>,map<ll,int>> lengths;
    fr(i,0,n) {
        ii(x1); ii(y1);
        fr(j,0,i) {
            auto [x2,y2] = a[j];
            int dx = x1-x2;
            int dy = y1-y2;
            int neg = 0;
            if (dx<0) {
                dx*=-1;
                neg^=1;
            }
            if (dy<0) {
                dy*=-1;
                neg^=1;
            }
            ll dist = ll(dx)*ll(dx)+ll(dy)*ll(dy);
            int g = gcd(dx,dy);
            dx/=g;
            dy/=g;
            if (dx==0) {
                neg = 0;
                dy = 1;
            }
            if (dy==0) {
                neg = 0;
                dx = 1;
            }
            if (neg) {
                dx*=-1;
            }
            pair<int,int> slope = make_pair(dx,dy);
            res+=ll(slopes[slope]);
            parallelograms += lengths[slope][dist];
            slopes[slope]++;
            lengths[slope][dist]++;
        }
        a[i][0] = x1;
        a[i][1] = y1;
    }
    res-=parallelograms>>1;
    print(res);
}