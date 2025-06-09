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
array<array<int,103>,103> a;

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(n); ii(m);
    map<char,int> d;
    d['G']=0;
    d['C']=1;
    d['P']=2;
    for (int i=0; i<n<<1; ++i) {
        a[i][0] = 0;
        a[i][1] = i+1;
        si(s);
        for (int j=2; j<m+2; ++j) {
            int x = d[s[j-2]];
            a[i][j] = x;
        }
    }
    for (int j=2; j<m+2; ++j) {
        for (int i=0; i<n; ++i) {
            int x = i<<1;
            int y = x+1;
            int x_move = a[x][j];
            int y_move = a[y][j];
            if (x_move == y_move) continue;
            if ((x_move+1)%3 == y_move) {
                --a[x][0];
            } else {
                --a[y][0];
            }
        }
        sort(a.begin(),a.begin()+(n<<1));
    }
    for (int i=0; i<n<<1; ++i) print(a[i][1]);
}