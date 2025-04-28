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
array<int,1000001> dist;

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(a); ii(n);
    fill_n(dist.begin(), min(100001, n*10), 0);
    dist[n] = 0;
    queue<int> q;
    q.push(n);
    while (dist[1]==0 && q.size()!=0) {
        int u = q.front();
        q.pop();
        if (u%a==0 && dist[u/a]==0) {
            dist[u/a]=dist[u]+1;
            q.push(u/a);
        }
        if (u>10) {
            string s = to_string(u);
            if (s[1]=='0') continue;
            string t = string(s.begin()+1, s.end());
            t += s[0];
            int v = stoi(t);
            if (dist[v]!=0) continue;
            dist[v] = dist[u]+1;
            q.push(v);
        }
    }
    int res = dist[1];
    res-=(dist[1]==0);
    print(res);
}