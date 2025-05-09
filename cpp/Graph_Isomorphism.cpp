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
array<int,10> fact = {1, 1, 2, 6, 24, 120, 720, 5040, 40320};
array<set<int>,9> g1;
array<set<int>,9> g2;

bool check (const auto& v) {
    int n = v.size();
    for (int a=1; a<=n; ++a) {
        if (g1[a].size()==0) continue;
        int a1 = v[a];
        for (auto b : g1[a]) {
            int b1 = v[b];
            if (g2[a1].find(b1) == g2[a1].end()) return false;
        }
    }
    return true;
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(n); ii(m);
    fill_n(g1.begin(), n+1, set<int>());
    fill_n(g2.begin(), n+1, set<int>());
    vi v(n+1);
    for (int i=1; i<=n; ++i) {
        v[i]=i;
    }
    for (int i=0; i<m; ++i) {
        ii(u); ii(v);
        g1[u].insert(v);
        g1[v].insert(u);
    }
    for (int i=0; i<m; ++i) {
        ii(u); ii(v);
        g2[u].insert(v);
        g2[v].insert(u);
    }
    bool cur;
    for (int i=1; i<fact[n]; ++i) {
        cur = check(v);
        if (cur) {
            print(ny[1]);
            exit(0);
        }
        next_permutation(v.begin(), v.end());
    }
    cur = check(v);
    print(ny[cur]);
}