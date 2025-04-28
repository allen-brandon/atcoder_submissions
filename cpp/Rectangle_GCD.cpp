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
LL mod = 1000000007;
array<string,2> ny = {"No","Yes"};
array<int, 200001> a;
array<int, 200001> b;
array<array<int,200001>,32> a_pref;
array<array<int,200001>,32> b_pref;
array<int,200001> res;

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(n); ii(q);
    for (int i=0; i<n; ++i) {
        ii(x);
        a[i] = x;
        if (i!=0) a_pref[0][i-1]=a[i]-a[i-1];
    }
    for (int i=0; i<n; ++i) {
        ii(x);
        b[i] = x;
        if (i!=0) b_pref[0][i-1]=b[i]-b[i-1];
    }
    int len = 2, j=1;
    while (len<=n-1) {
        for (int i=0; i<n+1-len; ++i) {
            a_pref[j][i] = gcd(a_pref[j-1][i], a_pref[j-1][i+(len>>1)]);
            b_pref[j][i] = gcd(b_pref[j-1][i], b_pref[j-1][i+(len>>1)]);
        }
        len<<=1;
        j+=1;
    }
    auto query = [&](const auto& pref, int l, int r) { //exclusive
        int sz = r-l;
        int j = 0;
        while ((1<<j)<=sz) j+=1;
        j-=1;
        if (j<0) return 0;
        return gcd(pref[j][l], pref[j][r-(1<<j)]);
    };
    for (int i=0; i<q; ++i) {
        ii(h1); ii(h2); ii(w1); ii(w2);
        int cur = a[h1-1]+b[w1-1];
        cur = gcd(cur, query(a_pref, h1-1, h2-1));
        cur = gcd(cur, query(b_pref, w1-1, w2-1));
        res[i] = cur;
    }
    for (int i=0; i<q; ++i) {
        print(res[i]);
    }
}