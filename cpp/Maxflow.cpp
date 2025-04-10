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
ll mod = 1000000007;

pair<int,int> didj[4] = {{-1,0},{0,1},{1,0},{0,-1}};
string urdl = "^>v<";
int arr[10003];
array<map<int,int>,10001> adj;
array<int,10003> seen;
array<array<char,101>,101> board;

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(n); ii(m);
    int s = n*m, t = n*m+1;
    fill(adj.begin(), adj.begin()+t+1, map<int,int>());
    auto enc = [m](int i, int j) { return i*m+j; };
    auto dec = [m](int idx) { return pair<int,int>({idx/m, idx%m}); };
    for (int i=0; i<n; ++i) {
        si(row);
        for (int j=0; j<m; ++j) {
            arr[enc(i,j)]=row[j]=='.';
            board[i][j]=row[j];
        }
    }
    for (int idx=0; idx<s; ++idx) {
        if (arr[idx]==0) continue;
        auto [i, j] = dec(idx);
        if (idx&1) {
            adj[idx][t]=1;
            adj[t][idx]=0;
        } else {
            adj[idx][s]=0;
            adj[s][idx]=1;
        }
        for (auto [di, dj] : didj) {
            int x=i+di,y=j+dj;
            int jdx=enc(x,y);
            if (x<0 || y<0 || x==n || y==m || arr[jdx]==0) continue;
            adj[idx][jdx]=1;
        }
    }
    int found, u, v, res=0;
    while (1) {
        fill(seen.begin(), seen.begin()+t+1, -1);
        queue<int> q({s});
        found = 0;
        while (!found && q.size()!=0) {
            u = q.front();
            q.pop();
            for (auto [v, w] : adj[u]) {
                if (!w or seen[v]!=-1) continue;
                seen[v]=u;
                if (v==t) {
                    found=1;
                    break;
                }
                q.push(v);
            }
        }
        if (!found) break;
        v = t;
        while (v!=s) {
            u=seen[v];
            adj[v][u]--;
            adj[u][v]++;
            auto [i,j] = dec(v);
            auto [x,y] = dec(u);
            if (v==t || board[x][y]!='.') {
                board[i][j]='.';
            } else if (u!=s) {
                for (int k=0; i<4; ++k) {
                    auto [di,dj] = didj[k];
                    if (x==i+di && y==j+dj) {
                        board[i][j]=urdl[k];
                        board[x][y]=urdl[(k+2)%4];
                    }
                }
            }
            v=u;
        }
        res+=1;
    }
    print(res);
    string row;
    for (int i=0; i<n; ++i) {
        string row(board[i].begin(), board[i].begin()+m);
        print(row);
    }
}