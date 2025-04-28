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
array<int, 2026> a;
array<int, 2026> ind;
array<array<ll, 2026>, 2026> dp;

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(n); ii(m);
    fill_n(ind.begin(), n+1, 0);
    for (int i=1; i<=n; ++i) {
        fill_n(dp[i].begin()+1, m, 1ll);
        ii(x);
        ind[x]+=1;
        a[i]=x;
    }
    vi st;
    for (int u=1; u<=n; ++u) {
        if (!ind[u]) st.push_back(u);
    }
    while (st.size() != 0) {
        int u = st.back();
        st.pop_back();
        int v = a[u];
        ind[v]-=1;
        ll cur = 0ll;
        for (int j=1; j<=m; ++j) {
            cur+=dp[u][j];
            cur%=mod;
            dp[v][j]*=cur;
            dp[v][j]%=mod;
        }
        if (!ind[v]) st.push_back(v);
    }
    ll res = 1;
    for (int i = 1; i<=n; ++i) {
        int u = i;
        if (!ind[u]) continue;
        ind[u]-=1;
        int v = a[u];
        while (ind[v]) {
            for (int j=1; j<=m; ++j) {
                dp[v][j]*=dp[u][j];
                dp[v][j]%=mod;
            }
            ind[v]-=1;
            u = v;
            v = a[u];
        }
        ll cur = 0ll;
        for (int j=1; j<=m; ++j) cur = (cur + dp[u][j]) % mod;
        res = (res * cur) % mod;

    }
    print(res);
}