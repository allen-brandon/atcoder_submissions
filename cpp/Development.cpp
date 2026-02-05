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
// ll inf = 151515151515151;
ll inf = 1ll<<59ll;
ll mod = 998244353;
ll a[501][501];


int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    // print(inf);
    ii(n); ii(m);
    fr(i,0,n+1) {
        fill_n(a[i],n+1,inf);
        a[i][i]=0ll;
    }
    fr(i,0,m) {
        ii(u); ii(v); lli(w);
        --u; --v;
        // a[u][v] = w;
        // a[v][u] = w;
        a[u][v] = min(a[u][v], w);
        a[v][u] = min(a[u][v], w);
    }
    ii(k); lli(t);
    fr(i,0,k) {
        ii(u);
        --u;
        a[u][n] = t;
        a[n][u] = 0;
    }
    fr(k,0,n+1) { //node added
        fr(i,0,n+1) { //source
            fr(j,0,i) { //destination
                a[i][j] = min(a[i][j],a[i][k]+a[k][j]);
                a[j][i] = min(a[j][i],a[j][k]+a[k][i]);
            }
        }
    }
    ii(q);
    vll res;
    // fr(i,0,n+1) {
    //     vll test(a[i],a[i]+n+1);
    //     fr(j,0,n+1) {
    //         if (test[j] == inf) test[j] = 0;
    //     }
    //     printv(test);
    // }
    // print("____________________________");
    fr(query,0,q) {
        ii(q_t);
        if (q_t==3) {
            ll cur = 0;
            fr(i,0,n) {
                fr(j,0,i) {
                    if (a[i][j]!=inf) {
                        cur+=a[i][j];
                        cur+=a[j][i];
                    }
                }
            }
            res.push_back(cur);
            continue;
        }
        if (q_t==1) {
            ii(u); ii(v); lli(w);
            --u; --v;
            if (a[u][v]<=w) continue;
            a[u][v] = w;
            a[v][u] = w;
            fr(i,0,n+1) {
                fr(j,0,i) {
                    a[i][j] = min(a[i][j],a[i][u]+w+a[v][j]);
                    a[i][j] = min(a[i][j],a[i][v]+w+a[u][j]);
                    a[j][i] = min(a[j][i],a[j][u]+w+a[v][i]);
                    a[j][i] = min(a[j][i],a[j][v]+w+a[u][i]);
                }
            }
        } else {
            ii(u);
            --u;
            if (a[u][n]==t) continue;
            a[u][n] = t;
            a[n][u] = 0;
            fr(i,0,n+1) {
                fr(j,0,i) {
                    a[i][j] = min(a[i][j],a[i][u]+t+a[n][j]);
                    a[i][j] = min(a[i][j],a[i][n]+a[u][j]);
                    a[j][i] = min(a[j][i],a[j][u]+t+a[n][i]);
                    a[j][i] = min(a[j][i],a[j][n]+a[u][i]);
                }
            }
        }
        // fr(i,0,n+1) {
        //     vll test(a[i],a[i]+n+1);
        //     fr(j,0,n+1) {
        //         if (test[j] == inf) test[j] = 0;
        //     }
        //     printv(test);
        // }
        // print("____________________________");
    }
    for (auto x : res) {
        print(x);
    }
}