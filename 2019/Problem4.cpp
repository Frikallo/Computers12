#include <bits/stdc++.h>

using namespace std;

typedef __int128 ll; // long long is not enough for this problem, took me a while to figure this out but you need to use __int128
const int N = 1e6 + 5;
const ll INF = 1e15;
const ll LLINF = 1e30;
int n, k;
ll a[N];
vector<int> stk;

struct node {
    ll dp, mx;
    bool operator<(const node& other) const {
        return dp + mx < other.dp + other.mx;
    }
};

struct segtree {
#define lc (rt << 1)
#define rc (rt << 1 | 1)
    node st[N << 2];
    ll mn[N << 2], lazy[N << 2];
    bool flag[N << 2];
    void push_down(int rt) {
        if(flag[rt]) {
            lazy[lc] = lazy[rc] = lazy[rt];
            st[lc].dp = mn[lc];
            st[rc].dp = mn[rc];
            st[lc].mx = st[rc].mx = lazy[rt];
            flag[lc] = flag[rc] = 1;
            flag[rt] = 0;
        }
    }
    void push_up(int rt) {
        st[rt] = max(st[lc], st[rc]);
        mn[rt] = max(mn[lc], mn[rc]);
    }
    void build(int rt, int l, int r) {
        if(l == r) {
            st[rt].dp = st[rt].mx = -LLINF;
            mn[rt] = -LLINF;
            return;
        }
        int mid = l + r >> 1;
        build(lc, l, mid);
        build(rc, mid + 1, r);
        push_up(rt);
    }
    void update(int rt, int l, int r, int pos, ll val) {
        if(l == r) {
            st[rt].dp = mn[rt] = val;
            return;
        }
        int mid = l + r >> 1;
        push_down(rt);
        if(pos <= mid) update(lc, l, mid, pos, val);
        else update(rc, mid + 1, r, pos, val);
        push_up(rt);
    }
    void update(int rt, int l, int r, int x, int y, ll val) {
        if(l == x && y == r) {
            st[rt].dp = mn[rt];
            st[rt].mx = val;
            flag[rt] = 1;
            lazy[rt] = val;
            return;
        }
        int mid = l + r >> 1;
        push_down(rt);
        if(y <= mid) update(lc, l, mid, x, y, val);
        else if(x > mid) update(rc, mid + 1, r, x, y, val);
        else update(lc, l, mid, x, mid, val), update(rc, mid + 1, r, mid + 1, y, val);
        push_up(rt);
    }
    node query(int rt, int l, int r, int x, int y) {
        if(l == x && y == r) return st[rt];
        int mid = l + r >> 1;
        push_down(rt);
        if(y <= mid) return query(lc, l, mid, x, y);
        else if(x > mid) return query(rc, mid + 1, r, x, y);
        else return max(query(lc, l, mid, x, mid), query(rc, mid + 1, r, mid + 1, y));
    }
} st;

ll string_to_ll(const std::string& str) {
    ll result = 0;
    for (char c : str) {
        if (c >= '0' && c <= '9') {
            result = result * 10 + (c - '0');
        }
    }
    return result;
}

std::string ll_to_string(ll value) {
    std::string str;
    bool negative = false;
    if (value < 0) {
        negative = true;
        value = -value;
    }

    do {
        str.push_back('0' + (value % 10));
        value /= 10;
    } while (value != 0);

    if (negative) {
        str.push_back('-');
    }

    std::reverse(str.begin(), str.end());
    return str;
}

int main() {
    cin >> n >> k;
    st.build(1, 0, n);
    st.update(1, 0, n, 0, 0);
    for(int i = 1;i<=n;++i) {
        string x;
        cin >> x;
        ll x_ll = string_to_ll(x);
        a[i] = x_ll - INF;
        while(!stk.empty() && a[stk.back()] < a[i]) stk.pop_back();
        int mx = stk.empty() ? 0 : stk.back();
        st.update(1, 0, n, mx, i - 1, a[i]);
        node dp = st.query(1, 0, n, max(0, i - k), i - 1);
        st.update(1, 0, n, i, dp.dp + dp.mx);
        stk.push_back(i);
    }
    ll day = (n - 1) / k + 1;
    ll ans = st.query(1, 0, n, n, n).dp + day * INF;
    string ans_str = ll_to_string(ans);
    cout << ans_str << endl;
    return 0;
}