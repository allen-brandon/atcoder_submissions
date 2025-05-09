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
#define LL long long
#define uLL unsigned LL
#define vLL vector<LL>
#define vi vector<int>
#define counter(_) unordered_map<_,size_t>
#define ordered_set tree<LL, null_type, less<LL>, rb_tree_tag, tree_order_statistics_node_update>
#define ordered_multiset tree<pair<LL,LL>, null_type, less<pair<LL,LL>>, rb_tree_tag, tree_order_statistics_node_update>
#define fio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define print(_) cout << _ << "\n";
#define printv(_) for (const auto& x : _) cout << x << ' '; cout << '\n';
#define printum(_) cout<<"{";for (const auto& kvp:_) cout<<kvp.first<<":"<<kvp.second<<","; cout<<"}\n";
#define si(_) string _; cin >> _;
#define ii(_) int _; cin >> _;
#define LLi(_) LL _; cin >> _;
LL inf = 151515151515151;
LL mod = 998244353;
array<string,2> ny = {"No","Yes"};
array<LL,300001> dp;
array<LL,300001> a;

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(n);
    stack<LL> mi, ma, mi_sum, ma_sum;
    LL mi_cur=0, ma_cur=0;
    for (int i=1; i<=n; ++i) {
        LLi(x);
        a[i] = x;
    }
    dp[0] = 1;
    for (int i=1; i<=n; ++i) {
        LL x = a[i];
        dp[i] = dp[i-1];
        while (mi.size()!=0 && a[mi.top()]>=x) {
            mi_cur = (mi_cur + mod - mi_sum.top()) % mod;
            mi.pop();
            mi_sum.pop();
        }
        int j = mi.size()==0 ? 0 : mi.top();
        mi_sum.push((x * (dp[i-1] + mod - dp[j-1])) % mod); //sum of dp values from j (inclusive) to i (exclusive)
        mi_cur = (mi_cur + mi_sum.top()) % mod;
        mi.push(i);
        while (ma.size()!=0 && a[ma.top()]<=x) {
            ma_cur = (ma_cur + mod - ma_sum.top()) % mod;
            ma.pop();
            ma_sum.pop();
        }
        j = ma.size()==0 ? 0 : ma.top();
        ma_sum.push((x * (dp[i-1] + mod - dp[j-1])) % mod);
        ma_cur = (ma_cur + ma_sum.top()) % mod;
        ma.push(i);
        dp[i] = (dp[i] + ma_cur + mod - mi_cur) % mod;
    }
    LL res = (ma_cur + mod - mi_cur) % mod;
    print(res);
}