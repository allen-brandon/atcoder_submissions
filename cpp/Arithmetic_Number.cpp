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

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    si(s);
    int n = s.size();
    if (n==1) {
        print(s);
        exit(0);
    }
    vi v;
    for (auto c : s) v.push_back(c-'0');
    vi res;
    bool found = 0;
    for (int dx=-9; dx<10; ++dx) {
        vi cur;
        for (int i=0; i<n; ++i) {
            int d = v[0]+dx*i;
            if (d<0 || d>9) break;
            cur.push_back(d);
        }
        if (cur.size()==n && cur>=v) {
            res = cur;
            found = 1;
            break;
        }
    }
    if (!found) {
        for (int dx=-9; dx<10; ++dx) {
            vi cur;
            for (int i=0; i<n; ++i) {
                int d = v[0]+1+dx*i;
                if (d<0 || d>9) break;
                cur.push_back(d);
            }
            if (cur.size()==n && cur>=v) {
                res = cur;
                found = 1;
                break;
            }
        }

    }
    for (auto x : res) cout << x;
    cout << "\n";
}