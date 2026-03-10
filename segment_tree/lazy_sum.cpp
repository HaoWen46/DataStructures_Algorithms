#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

void apply(int st[], int tag[], int n, int p, int v) {
    st[p] = (st[p] + v) % mod;
    if (p < n) tag[p] = (tag[p] + v) % mod;
}

void push(int st[], int tag[], int n, int p) {
    for (int h = __lg(p); h >= 0; h--) {
        int i = p >> h;
        if (!tag[i >> 1]) continue;
        apply(st, tag, n, i, tag[i >> 1]);
        apply(st, tag, n, i ^ 1, tag[i >> 1]);
        tag[i >> 1] = 0;
    }
}

void pull(int st[], int p) {
    while (p >>= 1) {
        st[p] = (st[p << 1] + st[p << 1 | 1]) % mod;
    }
}

// add v to the range [l, r)
void update(int st[], int tag[], int n, int l, int r, int v) {
    if (l >= r) return;
    int ll = l += n, rr = r += n;
    push(st, tag, n, ll);
    push(st, tag, n, rr - 1);
    for (; l < r; l >>= 1, r >>= 1) {
        if (l & 1) apply(st, tag, n, l++, v);
        if (r & 1) apply(st, tag, n, --r, v);
    }
    pull(st, ll);
    pull(st, rr - 1);
}

// query the range sum [l, r)
int query(int st[], int tag[], int n, int l, int r) {
    int res = 0;
    l += n; r += n;
    push(st, tag, n, l);
    push(st, tag, n, r - 1);
    for (; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res = (res + st[l++]) % mod;
        if (r & 1) res = (res + st[--r]) % mod;
    }
    return res;
}

int main() {
    int n, st[200005]{}, tag[100005]{};
    cin >> n;
    update(st, tag, n, 0, n, 1);
    return 0;
}
