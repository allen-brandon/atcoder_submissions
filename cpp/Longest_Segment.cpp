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
#define ld long double
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
array<pair<int,int>,101> a;

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(n);
    for (int i=0; i<n; ++i) {
        ii(x); ii(y);
        a[i] = {x,y};
    }
    ld msf = 0;
    auto dist = [&](int i, int j) {
        ld res = 0;
        auto [x1,y1] = a[i];
        auto [x2,y2] = a[j];
        res+=(x2-x1)*(x2-x1);
        res+=(y2-y1)*(y2-y1);
        return sqrt(res);
    };
    for (int i=0; i<n; ++i) {
        for (int j=0; j<i; ++j) {
            msf = max(msf, dist(i,j));
        }
    }
    cout << setprecision (32) << msf << "\n";
}