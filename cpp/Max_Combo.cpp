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
int arr[500001];
int res[500001];

class SegmentTree {
    private:
    int n;
    vi a;
    vector<pair<int,int>> p; //len and val of prefix
    vector<pair<int,int>> s; //len and val of suffix

    public:
    SegmentTree(int m) {
        n = 1;
        while (n<m) n<<=1;
        a.assign(n<<1,1);
        p.assign(n<<1,make_pair(1,-1));
        s.assign(n<<1,make_pair(1,-1));
        fr(i,0,m) {
            p[i+n] = make_pair(1,arr[i]);
            s[i+n] = make_pair(1,arr[i]);
        }
        int pop = 1;
        for (int i=n-1; i>0; --i) {
            a[i] = max(a[i<<1],a[i<<1|1]);
            if (s[i<<1].second == p[i<<1|1].second && s[i<<1].second!=-1) {
                a[i] = max(a[i], s[i<<1].first+p[i<<1|1].first);
            }
            if (p[i<<1].first==pop && p[i<<1].second==p[i<<1|1].second && p[i<<1].second != -1) {
                p[i] = make_pair(pop+p[i<<1|1].first,p[i<<1|1].second);
            } else {
                p[i] = p[i<<1];
            }
            if (s[i<<1|1].first==pop && s[i<<1|1].second==s[i<<1].second && s[i<<1|1].second != -1) {
                s[i] = make_pair(pop+s[i<<1].first,s[i<<1].second);
            } else {
                s[i] = s[i<<1|1];
            }
            if (__builtin_popcount(i)==1) pop<<=1;
        }
    }

    void update(int i, int x) {
        i+=n;
        p[i] = make_pair(1,x);
        s[i] = make_pair(1,x);
        i>>=1;
        int pop = 1;
        while (i) {
            a[i] = max(a[i<<1],a[i<<1|1]);
            if (s[i<<1].second == p[i<<1|1].second && s[i<<1].second!=-1) {
                a[i] = max(a[i], s[i<<1].first+p[i<<1|1].first);
            }
            s[i] = s[i<<1|1];
            if (p[i<<1].first==pop && p[i<<1].second==p[i<<1|1].second) {
                p[i] = make_pair(pop+p[i<<1|1].first,p[i<<1|1].second);
            } else {
                p[i] = p[i<<1];
            }
            if (s[i<<1|1].first==pop && s[i<<1|1].second==s[i<<1].second) {
                s[i] = make_pair(pop+s[i<<1].first,s[i<<1].second);
            } else {
                s[i] = s[i<<1|1];
            }
            i>>=1;
            pop<<=1;
        }
        }
        
        int query(int l, int r) {
            // print("(" << l << ", " << r << ")");
            l+=n;
            r+=n;
            int res = 0;
            int pop = 1;
            pair<int,int> pref = make_pair(1,-1), suf = make_pair(1,-1);
            while (l<r) {
                if (l&1) {
                    res = max(res, a[l]);
                    if (p[l].second==pref.second) {
                        res = max(res, p[l].first+pref.first);
                        if (p[l].first==pop) {
                            pref = make_pair(pref.first+pop, pref.second);
                        } else {
                            pref = s[l];
                        }
                    } else {
                        pref = s[l];
                    }
                    ++l;
                }
            if (r&1) {
                --r;
                res = max(res, a[r]);
                if (s[r].second==suf.second) {
                    res = max(res, s[r].first+suf.first);
                    if (s[r].first==pop) {
                        suf = make_pair(suf.first+pop,suf.second);
                    } else {
                        suf = p[r];
                    }
                } else {
                    suf = p[r];
                }
            }
            l>>=1;
            r>>=1;
            pop<<=1;
            // print(pref.first << ", " << pref.second);
            // print(suf.first << ", " << suf.second);
            // print("");
        }
        if (pref.second==suf.second) {
            res = max(res, pref.first+suf.first);
        }
        return res;
    }
};

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(n); ii(q);
    si(s);
    fr(i,0,n) {
        int x = s[i] - 'a';
        arr[i] = x;
    }
    SegmentTree st = SegmentTree(n);
    int res_idx = 0;
    fr(i,0,q) {
        ii(t);
        if (t==1) {
            ii(idx); si(c);
            --idx;
            int x = c[0] - 'a';
            st.update(idx,x); 
        } else {
            ii(l); ii(r);
            --l;
            res[res_idx++] = st.query(l,r);
        }
    }
    fr(i,0,res_idx) print(res[i]);
}