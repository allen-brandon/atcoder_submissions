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
#define ll long long
#define ull unsigned ll
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
array<char,300001> buffer;

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    lli(n); lli(a); lli(b);
    lli(p); lli(q); lli(r); lli(s);
    ll offs = a-b;
    ll doffs = a+b;
    for (ll i=p; i<=q; ++i) {
        for (ll j=r; j<=s; ++j) {
            int marked = 0;
            if (i-j==offs) {
                ll k = i-a;
                if (max(1-a,1-b) <= k && k <= min(n-a,n-b)) {
                    marked = 1;
                }
            }
            if (i+j==doffs) {
                ll k = i-a;
                if (max(1-a,b-n) <= k && k <= min(n-a,b-1)) {
                    marked = 1;
                }
            }
            buffer[j-r] = ".#"[marked];
        }
        print(string(buffer.begin(), buffer.begin()+s+1-r));
    }
    
}