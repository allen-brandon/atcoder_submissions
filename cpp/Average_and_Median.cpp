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
#include <iomanip>
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
array<string,2> ny = {"No","Yes"};
array<int,100002> a;
array<int,100003> dp;
array<double,100003> avg_dp;
bool check_med(int n, int m) {
    dp[n]=0;
    dp[n+1]=0;
    for (int i=n-1; i>=0; --i) {
        dp[i]=(a[i]>=m)-(a[i]<m);
        dp[i]+=max(dp[i+1],dp[i+2]);
    }
    return max(dp[0],dp[1])>0;
}
bool check_avg(int n, double m) {
    avg_dp[n]=0;
    avg_dp[n+1]=0;
    for (int i=n-1; i>=0; --i) {
        avg_dp[i]=a[i]-m;
        avg_dp[i]+=max(avg_dp[i+1],avg_dp[i+2]);
    }
    return max(avg_dp[0],avg_dp[1])>=0;
}
int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(n);
    for (int i=0; i<n; ++i) {
        ii(x);
        a[i]=x;
    }
    double lb=1.0, rb=mod, mb;
    while (rb-lb>0.00001) {
        mb = lb+(rb-lb)/2;
        if (check_avg(n, mb)) {
            lb = mb;
        } else {
            rb = mb;
        }
    }
    cout << setprecision (14) << lb << "\n";
    int l=1, r=mod, m;
    while (r-l>1) {
        m = l+(r-l)/2;
        if (check_med(n, m)) {
            l = m;
        } else {
            r = m;
        }
    }
    print(l);
}