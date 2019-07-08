#include <iostream>
#define ll long long
using namespace std;
const int N = 1e5 + 7;
int n, m;


ll add[N * 4], sum[N * 4];

void PushUp(int rt) {
    sum[rt] = sum[rt * 2] + sum[rt * 2 + 1];
}

void PushDown(int rt, int m) {
    if (add[rt]) {
        add[rt * 2] += add[rt];
        add[rt * 2 + 1] += add[rt];
        sum[rt * 2] += add[rt] * (m - m / 2);
        sum[rt * 2 + 1] += add[rt] * (m / 2);
        add[rt] = 0;
    }
}

void build(int l=1, int r=n, int rt = 1) {
    add[rt] = 0;//
    if (l == r) {
        cin >> sum[rt];
        return;
    }
    int m = (l + r) / 2;
    build(l, m, rt * 2);
    build(m + 1, r, rt * 2 + 1);
    PushUp(rt);
}

void update(int L, int R, int c, int l=1, int r=n, int rt = 1) {
    if (L <= l && r <= R) {
        add[rt] += c;
        sum[rt] += c * (r - l + 1);
        return;
    }
    PushDown(rt, r - l + 1);
    int m = (l + r) / 2;
    if (L <= m) update(L, R, c, l, m, rt * 2);
    if (m < R) update(L, R, c, m + 1, r, rt * 2 + 1);
    PushUp(rt);
}

ll query(int L, int R, int l=1, int r=n, int rt = 1) {
    if (L <= l && r <= R) {
        return sum[rt];
    }
    PushDown(rt, r - l + 1);
    int m = (l + r) / 2;
    ll ret = 0;
    if (L <= m) ret += query(L, R, l, m, rt * 2);
    if (m < R) ret += query(L, R, m + 1, r, rt * 2 + 1);
    return ret;
}


int main() {
    cin >> n >> m;

    build(1, n);

    for (int i = 0; i < m; i++) {
        char operation;
        cin >> operation;

        if (operation == 'Q') {
            int l, r;
            cin >> l >> r;
            cout << query(l, r) << '\n';
        } else if (operation == 'C') {
            int l, r, c;
            cin >> l >> r >> c;
            update(l, r, c);
        }
    }

    return 0;
}

