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
#define ordered_set tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> // find_by_order(), order_of_key()
#define ordered_multiset tree<pair<ll,ll>, null_type, less<pair<ll,ll>>, rb_tree_tag, tree_order_statistics_node_update>
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
// array<array<array<array<ll,1001>,10>,1001>,10> st;
// array<array<ll,1001>,1001> a;
ll st[10][1001][10][1001];
ll a[1001][1001];

ll rmq(int i1, int j1, int i2, int j2) {
    int h = i2-i1;
    int w = j2-j1;
    int idx = 0, jdx = 0;
    while (1<<idx<=h) ++idx;
    while (1<<jdx<=w) ++jdx;
    --idx; --jdx;
    ll msf = 0;
    auto row1 = st[idx][i1];
    msf = max(msf, row1[jdx][j1]);
    msf = max(msf, row1[jdx][j2-(1<<jdx)]);
    auto row2 = st[idx][i2-(1<<idx)];
    msf = max(msf, row2[jdx][j1]);
    msf = max(msf, row2[jdx][j2-(1<<jdx)]);
    return msf;
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(h); ii(w); ii(h1); ii(w1); ii(h2); ii(w2);
    h2 = min(h2, h1);
    w2 = min(w2, w1);
    int h3 = h+2-h2, w3 = w+2-w2;
    int lim1 = 0;
    while (1<<lim1<=h) ++lim1;
    int lim2 = 0;
    while (1<<lim2<=w) ++lim2;
    fr(i,1,h+1) {
        fr(j,1,w+1) {
            lli(x);
            a[i][j] = x + a[i-1][j] + a[i][j-1] - a[i-1][j-1];
        }
    }
    fr(i,1,h3) { //build st for this row
        auto& row = st[0][i];
        fr(j,1,w3) {
            row[0][j] = a[i+h2-1][j+w2-1] - a[i-1][j+w2-1] - a[i+h2-1][j-1] + a[i-1][j-1];
        }
        fr(jdx,1,lim2) {
            fr(j,1,w3+1-(1<<jdx)) {
                row[jdx][j] = max(row[jdx-1][j],row[jdx-1][j+(1<<(jdx-1))]);
            }
        }
    }
    fr(idx,1,lim1) {
        fr(i,1,h3+1-(1<<idx)) {
            fr(jdx,0,lim2) {
                fr(j,1,w3+1-(1<<jdx)) {
                    st[idx][i][jdx][j] = max(st[idx-1][i][jdx][j], st[idx-1][i+(1<<(idx-1))][jdx][j]);
                }
            }
        }
    }
    ll msf = 0;
    fr(i,h1,h+1) {
        fr(j,w1,w+1) {
            ll cur = a[i][j] - a[i-h1][j] - a[i][j-w1] + a[i-h1][j-w1];
            cur -= rmq(i+1-h1, j+1-w1, i+2-h2, j+2-w2);
            msf = max(msf, cur);
        }
    }
    print(msf);
}   