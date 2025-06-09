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
array<ll,200001> mu;
array<int,200001> arr;
array<ll,200001> groups;
array<vi,200001> d;
bitset<200001> used;
vi touched;
vi divisors;

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(n);
    if (d[n].size()==0) {
        fill_n(mu.begin(),n+1,-1);
        fill_n(d.begin(),n+1,vi());
        divisors.clear();
        mu[1]=0;
        for (int i=2; i<=n; ++i) {
            if (mu[i]==0) continue;
            divisors.push_back(i);
            for (int j=i; j<=n; j+=i) {
                d[j].push_back(i);
            }
            if (d[i].size()!=1) continue;
            for (int j=i; j<=n; j+=i) {
                mu[j]*=-1;
            }
            if (i>n/i) continue;
            for (int j=i*i; j<=n; j+=i*i) {
                mu[j] = 0;
            }
        }
    }
    for (int i=1; i<=n; ++i) {
        ii(x);
        arr[i] = x;
    }
    ll res = 0;
    for (auto a : divisors) {
        for (int i=a; i<=n; i+=a) {
            for (int b : d[arr[i]]) {
                if (used[b] != 1) {
                    used[b] = 1;
                    touched.push_back(b);
                }
                ++groups[b];
            }
        }
        for (auto b : touched) {
            res += ( ( groups[b] * ( groups[b]+1 ) ) / 2 ) * mu[a] * mu[b];
            groups[b] = 0;
            used[b] = 0;
        }
        touched.clear();
    }
    print(res);
    // printv(divisors);
    // vi test(20000);
    // iota(test.rbegin(),test.rend(),1);
    // random_shuffle(test.begin(),test.end());
    // printv(test);
}