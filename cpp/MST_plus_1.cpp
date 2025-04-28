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
array<int, 200001> rt;
array<int, 200001> sz;
bitset<200001> res;

int find(int a) {
    while (rt[rt[a]] != rt[a]) {
        rt[a] = rt[rt[a]];
    }
    return rt[a];
}

void join(int a, int b) {
    a = find(a);
    b = find(b);
    if (a==b) return;
    if (sz[b]>sz[a]) {
        rt[a] = b;
        sz[b]+=sz[a];

    } else {
        rt[b] = a;
        sz[a]+=sz[b];
    }
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(n); ii(m); ii(q);
    res = 0;
    fill_n(sz.begin(), n+1, 1);
    for (int i=0; i<=n; ++i) {
        rt[i]=i;
    }
    vector<tuple<int, int, int>> edges;
    for (int i=0; i<m; ++i) {
        ii(u); ii(v); ii(w);
        edges.emplace_back(w, u, v);
    }
    sort(edges.begin(), edges.end());
    // minheap: w, u, v, i
    priority_queue<tuple<int, int, int, int>, vector<tuple<int, int, int, int>>, greater<tuple<int, int, int, int>>> pq;
    for (int i=0; i<q; ++i) {
        ii(u); ii(v); ii(w);
        pq.emplace(w, u, v, i);
    }
    for (auto [w, u, v] : edges) {
        while (pq.size()!=0 && get<0>(pq.top())<w) {
            auto [w1, u1, v1, i] = pq.top();
            pq.pop();
            res[i] = find(u1)!=find(v1);
        }
        join(u, v);
    }
    while (pq.size()!=0) {
        auto [w1, u1, v1, i] = pq.top();
        pq.pop();
        res[i] = find(u1)!=find(v1);
    }
    for (int i=0; i<q; ++i) {
        print(ny[res[i]]);
    }
}