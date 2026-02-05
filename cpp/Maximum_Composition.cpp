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
typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> ordered_set; // find_by_order(), order_of_key()
typedef tree<pair<ll,ll>, null_type, less<pair<ll,ll>>, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;
#define vll vector<ll>
#define vi vector<int>
#define counter(_) unordered_map<_,size_t>
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
pair<ll,ll> arr[200001];
ll state[11];

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    fill_n(state+1,10,-1ll);
    state[0] = 1ll;
    ii(n); ii(k);
    fr(i,0,n) {
        lli(a); lli(b);
        arr[i] = {a,b};
    }
    sort(arr,arr+n, [](pair<ll,ll> p1, pair<ll,ll> p2) {
        return (p1.first-1)*p2.second < (p2.first-1)*p1.second; // float(p1.first)/float(p1.second) < float(p2.first)/float(p2.second);
    });
    fr(i,0,n) {
        auto [a,b] = arr[i];
        for (int j = k; j>0; j--) {
            if (state[j-1]<0) continue;
            state[j] = max(state[j], a*state[j-1]+b);
        }
    }
    // vll test(state,state+k+1);
    // printv(test);
    print(state[k]);
}