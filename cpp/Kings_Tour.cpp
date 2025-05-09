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
#define printm(_) cout<<"{";for (const auto& kvp:_) cout<<kvp.first<<":"<<kvp.second<<","; cout<<"}\n";
#define si(_) string _; cin >> _;
#define ii(_) int _; cin >> _;
#define lli(_) ll _; cin >> _;
array<pair<int,int>,8> didj = {{{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}}};
array<string,2> ny = {"No","Yes"};
ll inf = 151515151515151;
ll mod = 998244353;
array<bitset<102>,102> seen;
array<pair<int,int>,10000> res;

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    // ii(h); ii(w); ii(a); ii(b);
    // //bounding wall
    // for (int i=0; i<=h+1; ++i) {
    //     seen[i][0]=1;
    //     seen[i][w+1]=1;
    // }
    // for (int j=0; j<=h+1; ++j) {
    //     seen[0][j]=1;
    //     seen[h+1][j]=1;
    // }
    // for (int i=1; i<=h; ++i) {
    //     for (int j=1; j<=w; ++j) {
    //         seen[i][j]=0;
    //     }
    // }
    // seen[1][1]=1;
    // int i=1, j=1;
    // for (int step=0; step<h*w; ++step) {
    //     res[step] = {i,j};
    //     priority_queue<tuple<int,int,int,pair<int,int>>> pq;
    //     for (int idx = 0; idx < 8; ++idx) {
    //         auto [di, dj] = didj[idx];
    //         int x=i+di, y=j+dj;
    //         if (seen[x][y]) continue;
    //         int score = 0;
    //         for (auto [dx, dy] : didj) {
    //             int x1=x+dx, y1=y+dy;
    //             score+=seen[x1][y1];
    //             score+=((x1==a)&&(y1==b));
    //         }
    //         pq.emplace(abs(x-a)+abs(y-b), (idx%2)==0, score, make_pair(x,y));
    //     }
    //     while (pq.size()!=0) {
    //         auto [xyd, idx, score, xy] = pq.top();
    //         auto [x, y] = xy;
    //         pq.pop();
    //         if (x==a && y==b && step<h*w-2) continue;
    //         seen[x][y] = 1;
    //         i = x;
    //         j = y;
    //     }
    //     if (res[step] == make_pair(i,j)) {
    //         break;
    //     }
    // }
    // for (int i=0; i<h*w; ++i) {
    //     print(res[i].first << " " << res[i].second);
    //     if (res[i] == make_pair(0,0)) {
    //         for (int i=0; i<=h+1; ++i) {
    //             print(seen[i]);
    //         }
    //         break;
    //     }
    // }
    // set<pair<int,int>> test(res.begin(), res.begin()+h*w);
    // print(ny[test.size()==h*w]);
}