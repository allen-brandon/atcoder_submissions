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
LL mod = 998244353;
array<string,2> ny = {"No","Yes"};
// state[eq][mask]: number of numbers that contain 
array<array<array<LL,100001>,1024>,2> dp1;

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    si(n); ii(m);
    int target = 0;
    for (int i=0; i<m; ++i) {
        ii(x);
        target|=1<<x;
    }
    for (int i=0; i<1024; ++i) {
        if ((i&target)==target) {
            dp[0][0][i]=0ll;
            dp[0][1][i]=0ll;
        }
    }
    LL p = 1;
    for (int i=n.size()-1; i>=0; --i) {
        int cur = n[i]-'0';
        for (int mask=0; mask<1024; ++mask) {
            // # of ways to put x here
            for (int x=0; x<=cur; ++x) {
                int mask1 = mask|(1<<x);
                res+=state[x==cur][mask1];
                res+=state[0][mask1]; // for when it's equal or unequal and you put x in this spot
                res%=mod;
                tmp[0][mask]+=state[0][mask1];
                tmp[0][mask]%=mod;
                tmp[1][mask]+=state[x==cur][mask1];
                tmp[1][mask]%=mod;
            }
            for (int x=cur+1; x<10; ++x) {
                int mask1 = mask|(1<<x);
                res+=state[0][mask1]; //only the states where eq=0 and you put x in this spot
                res%=mod;
                tmp[0][mask]+=state[0][mask1];
                tmp[0][mask]%=mod;
            }
        }
        for (int mask=0; mask<1024; ++mask) {
            state[0][mask]=tmp[0][mask];
            state[1][mask]=tmp[1][mask];
        }
        print(res);
        print(p);
        p*=10;
        p%=mod;
    }
    print(res);
}