#ifdef DEBUG
#include <cstdio>
#define USE_INPUT_FILE(file) freopen(file, "r", stdin);
#else
#define USE_INPUT_FILE(file)
#endif

using namespace std;
#include <iostream>
#include <vector>
#include <array>
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
int mod = 1000000007;

array<pair<int,int>,4> direc = {{{-1,0},{0,1},{1,0},{0,-1}}};
string urdl = "^>v<";
int arr[10003];
array<map<int,int>,10003> adj;
array<map<int,int>,10003> flow;
array<int,10003> seen;
array<array<char,101>,101> board;

int maxflow(int n, int m) {
    int s = n*m, t = n*m+1;
    auto enc = [m](int i, int j) { return i*m+j; };
    auto dec = [m](int idx) { return pair<int,int>({idx/m, idx%m}); };
    fill(adj.begin(), adj.begin()+t+1, map<int,int>());
    for (int idx=0; idx<s; ++idx) {
        if (!arr[idx]) continue;
        auto [i,j] = dec(idx);
        if ((i&1)==(j&1)) {
            adj[s][idx]=1;
            adj[idx][s]=0;
            flow[idx][s]=0;
            flow[s][idx]=0;
        } else {
            adj[idx][t]=1;
            adj[t][idx]=0;
            flow[idx][t]=0;
            flow[t][idx]=0;
        }
        for (auto [di,dj] : direc) {
            int x=i+di, y=j+dj;
            int jdx = enc(x,y);
            if (x<0 || y<0 || x==n || y==m || !arr[jdx]) continue;
            if ((i&1)==(j&1)) adj[idx][jdx]=1;
            flow[idx][jdx]=0;
        }
    }
    while (1) {
        fill(seen.begin(), seen.begin()+t+1, -1);
        int found = 0;
        queue<int> q({s});
        while (q.size()!=0 && !found) {
            int u = q.front();
            q.pop();
            for (auto [v, w] : flow[u]) {
                int capacity = adj[u][v]-w;
                if (!capacity || seen[v]!=-1) continue;
                seen[v]=u;
                if (v==t) found=1;
                q.push(v);
            }
        }
        if (!found) break;
        int v = t;
        int msf = mod;
        while (v!=s) {
            int u = seen[v];
            msf = min(msf, adj[u][v]-flow[u][v]);
            v = u;
        }
        v = t;
        while (v!=s) {
            int u = seen[v];
            flow[u][v]+=msf;
            flow[v][u]-=msf;
            v = u;
        }
    }
    int res = 0;
    for (auto [v, w] : flow[s]) {
        res+=max(0, w);
    }
    for (int idx=0; idx<s; ++idx) {
        if (!arr[idx]) continue;
        auto [i, j] = dec(idx);
        for (int k=0; k<4; ++k) {
            auto [di, dj] = direc[k];
            int x=i+di, y=j+dj;
            int jdx = enc(x,y);
            if (x<0 || y<0 || x==n || y==m || !arr[jdx]) continue;
            if (flow[idx][jdx]) board[i][j]=urdl[k];
        }
    }
    return res;
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(n); ii(m);
    for (int i=0; i<n; ++i) {
        si(row);
        for (int j=0; j<m; ++j) {
            arr[i*m+j]=row[j]=='.';
            board[i][j]=row[j];
        }
    }
    int res = maxflow(n, m);
    print(res);
    string row;
    for (int i=0; i<n; ++i) {
        string row(board[i].begin(), board[i].begin()+m);
        print(row);
    }
}