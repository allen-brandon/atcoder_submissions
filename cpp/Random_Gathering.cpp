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
ll a[524288];
ll p[524288];
ll pop[524288];

ll inv(ll x) {
    ll res = 1;
    ll pwr = mod-2;
    while (pwr) {
        if (pwr&1)res = (res*x)%mod;
        x = (x*x)%mod;
        pwr>>=1;
    }
    return res;
}

struct SegmentTree {
    int n;
    int bit_len;
    SegmentTree(int n) {
        this -> n = n;
        bit_len = 31-__builtin_clz(n);
        for (int i=n-1; i>0; i--) {
            pop[i] = pop[i<<1] + pop[i<<1|1];
            a[i] = a[i<<1] + a[i<<1|1];
            a[i] -= a[i]>=mod? mod : 0;
        }
    }
    void prop(int i) {
        if (p[i]==-1) return;
        a[i<<1] = (p[i]*pop[i<<1])%mod;
        a[i<<1|1] = (p[i]*pop[i<<1|1])%mod;
        p[i<<1] = p[i];
        p[i<<1|1] = p[i];
        p[i] = -1;
    }
    void flush() {
        fr(i,1,n) prop(i);
    }
    void update(int l, int r, ll x) {
        l+=n; r+=n;
        int r_inc = r-1;
        int lb = l, rb = r_inc;
        //each internal node from 1 to l/r's parents
        for (int i=bit_len; i>0; i--) {
            prop(lb>>i);
            prop(rb>>i);
        }
        rb = r;
        while (lb<rb) {
            if (lb&1) {
                a[lb] = (x*pop[lb])%mod;
                p[lb] = x;
                lb++;
            }
            if (rb&1) {
                rb--;
                a[rb] = (x*pop[rb])%mod;
                p[rb] = x;
            }
            lb>>=1;
            rb>>=1;
        }
        lb = l>>1, rb = r_inc>>1;
        while (lb) {
            a[lb] = (p[lb]==-1? a[lb<<1]+a[lb<<1|1] : p[lb]*pop[lb])%mod;
            a[rb] = (p[rb]==-1? a[rb<<1]+a[rb<<1|1] : p[rb]*pop[rb])%mod;
            lb>>=1;
            rb>>=1;
        }
    }
    ll query(int l, int r) {
        l+=n; r+=n;
        int r_inc = r-1;
        int lb = l, rb = r_inc;
        for (int i=bit_len; i>0; i--) {
            prop(lb>>i);
            prop(rb>>i);
        }
        ll res = 0;
        while (l<r) {
            if (l&1) {
                res += a[l];
                res -= res>=mod? mod : 0;
                l++;
            }
            if (r&1) {
                r--;
                res += a[r];
                res -= res>=mod? mod : 0;
            }
            l>>=1;
            r>>=1;
        }
        return res;
    }
};

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(m); ii(q);
    int n = 1;
    while (n<m) n<<=1;
    fill_n(a, n<<1, 0ll);
    fill_n(p, n<<1, -1ll);
    fill(pop+n, pop+n+m, 1ll);
    fill(pop+n+m, pop+n+n, 0ll);
    fr(i,0,m) {
        lli(x);
        a[i+n] = x;
    }
    SegmentTree st(n);
    fr(j,0,q) {
        ii(l); ii(r);
        l--;
        ll su = st.query(l,r);
        ll po = ll(r-l);
        ll avg = (su*inv(po))%mod;
        st.update(l,r,avg);
    }
    st.flush();
    vll res(a+n, a+n+m);
    printv(res);
}