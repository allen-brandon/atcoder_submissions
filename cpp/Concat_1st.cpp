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
ll base = 37;
string a[100001];
ll pref[10][10];
int dp[100001][10];
int adj[10][10];

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(n); ii(k);
    string msf = "zzzzzzzzzzz";
    auto cmp = [](string s1, string s2) {
        return (s1+s2)<(s2+s1) || ((s1+s2)==(s2+s1) && s1.size()<s2.size());
    };
    fr(i,0,n) {
        si(s);
        a[i] = s;
        msf = min(msf,s,cmp);
    }
    int m = msf.size();
    // all rotations of msf
    fr(i,0,m) {
        fill_n(adj[i],10,100);
        ll hsh = 0;
        fr(j,0,10) {
            hsh*=base;
            hsh+=msf[(j+i)%m]+1-'a';
            hsh%=mod;
            pref[i][j] = hsh;
        }
    }
    fr(i,0,n) {
        ll hsh = 0;
        int sz = a[i].size();
        fr(j,0,sz) {
            hsh*=base;
            hsh+=a[i][j]+1-'a';
            hsh%=mod;
        }
        fr(j,0,m) {
            if (pref[j][sz-1]==hsh) {
                adj[j][(j+sz)%m]=min(adj[j][(j+sz)%m], sz);
            }
        }
    }
    //at end, cost is 0
    fr(j,0,m) {
        dp[k][j] = 0;
    }
    for (int i=k-1; i>=0; --i) {
        fill_n(dp[i],m,999999999);
        fr(j,0,m) {
            fr(j1,0,m) {
                if (adj[j][j1]!=100) {
                    dp[i][j] = min(dp[i][j], dp[i+1][j1]+adj[j][j1]);
                }
            }
        }
    }
    int res = dp[0][0];
    int lft = res%m;
    fr(i,0,res/m) {
        cout << msf;
    }
    fr(i,0,lft) {
        cout << msf[i];
    }
    cout << "\n";
}