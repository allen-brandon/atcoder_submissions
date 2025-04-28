#ifdef DEBUG
#include <cstdio>
#define USE_INPUT_FILE(file) freopen(file, "r", stdin);
#else
#define USE_INPUT_FILE(file)
#endif

using namespace std;
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <deque>
#include <queue>
#include <numeric>
#include <bitset>
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
ll mod = 1000000007;

array<int,200005> root;
array<int,200005> sz;
// array<int,200001> ind;

int find(int a) {
    while (root[a]!=root[root[a]]) {
        root[a] = root[root[a]];
    }
    return root[a];
}

int join(int a, int b) {
    a = find(a);
    b = find(b);
    if (a==b) return 0;
    if (sz[b]>sz[a]) {
        root[a]=b;
        sz[b]+=sz[a];
    } else {
        root[b]=a;
        sz[a]+=sz[b];
    }
    return 1;
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(n); ii(m);
    fill_n(sz.begin(), n+1, 1);
    for (int i=0; i<=n; ++i) root[i]=i;
    for (int i=0; i<m; ++i) {
        ii(u); ii(v);
        join(u,v);
    }
    ll res = 0;
    for (int a=1; a<=n; ++a) {
        if (root[a] == a) {
            ll x = sz[a];
            res+=(x*(x-1))/2;
        }
    }
    ll m_neg = m;
    res -= m_neg;
    print(res);
}