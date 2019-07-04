#include <cstring>
#include <iostream>

using namespace std;

struct item
{
    int left1, right1, sum1, longest1;
    int tag;
    bool allis1;
};

const int N = 4e6 + 7;
item a[N];

inline int
max2(int a, int b)
{
    if (a > b)
        b = a;
    return b;
}
inline int
max3(int a, int b, int c)
{
    if (a > b)
        b = a;
    if (b > c)
        c = b;
    return c;
}

inline void
PushUp(int rt)
{
    if (a[rt << 1].allis1)
        a[rt].left1 = a[rt << 1].sum1 + a[rt << 1 | 1].left1;
    else
        a[rt].left1 = a[rt << 1].left1;

    if (a[rt << 1 | 1].allis1)
        a[rt].right1 = a[rt << 1 | 1].sum1 + a[rt << 1].right1;
    else
        a[rt].right1 = a[rt << 1 | 1].right1;

    a[rt].sum1 = a[rt << 1].sum1 + a[rt << 1 | 1].sum1;

    a[rt].longest1 = max3(a[rt << 1].longest1,
                          a[rt << 1 | 1].longest1,
                          a[rt << 1].right1 + a[rt << 1 | 1].left1);

    a[rt].allis1 = a[rt << 1].allis1 && a[rt << 1 | 1].allis1;
}

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1

void
Build(int l, int r, int rt)
{
    a[rt].tag = -1;

    if (l == r) {
        int t;
        cin >> t;
        a[rt].left1 = a[rt].right1 = a[rt].sum1 = a[rt].longest1 = t;
        a[rt].allis1 = t;
        return;
    }
    int m = (l + r) >> 1;

    Build(lson);
    Build(rson);

    PushUp(rt);
}

inline void
PushDown(int rt, int ln, int rn)
{
    // ln,rn为左子树，右子树的数字数量。
    if (a[rt].tag != -1) {
        int tag = a[rt].tag;
        //下推标记
        a[rt << 1].tag = a[rt << 1 | 1].tag = tag;
        //修改子节点
        if (tag == 0) {
            a[rt << 1].allis1 = 0;
            a[rt << 1].left1 = a[rt << 1].right1 = a[rt << 1].sum1 =
              a[rt << 1].longest1 = 0;
            a[rt << 1 | 1].allis1 = 0;
            a[rt << 1 | 1].left1 = a[rt << 1 | 1].right1 = a[rt << 1 | 1].sum1 =
              a[rt << 1 | 1].longest1 = 0;
        } else if (tag == 1) {
            a[rt << 1].allis1 = 1;
            a[rt << 1].left1 = a[rt << 1].right1 = a[rt << 1].sum1 =
              a[rt << 1].longest1 = ln;
            a[rt << 1 | 1].allis1 = 1;
            a[rt << 1 | 1].left1 = a[rt << 1 | 1].right1 = a[rt << 1 | 1].sum1 =
              a[rt << 1 | 1].longest1 = rn;
        }
        //清除本节点标记
        a[rt].tag = -1;
    }
}

void
Update(int L, int R, int C, int l, int r, int rt)
{ // L,R表示操作区间，l,r表示当前节点区间，rt表示当前节点编号
    if (L <= l && r <= R) {
        //向上保持正确
        if (C == 0) {
            a[rt].allis1 = 0;
            a[rt].left1 = a[rt].right1 = a[rt].sum1 = a[rt].longest1 = 0;
        } else if (C == 1) {
            a[rt].allis1 = 1;
            a[rt].left1 = a[rt].right1 = a[rt].sum1 = a[rt].longest1 =
              r - l + 1;
        }

        a[rt].tag = C; //增加标记，表示本区间正确，子区间仍需要根据tag的值来调整
        return;
    }
    int m = (l + r) >> 1;
    PushDown(rt, m - l + 1, r - m); //下推标记
    //这里判断左右子树跟[L,R]有无交集，有交集才递归
    if (L <= m)
        Update(L, R, C, lson);
    if (R > m)
        Update(L, R, C, rson);
    PushUp(rt); //更新本节点信息
}

int
query2(int L, int R, int l, int r, int rt)
{ // L,R表示操作区间，l,r表示当前节点区间，rt表示当前节点编号
    if (L <= l && r <= R) {
        //在区间内，直接返回
        return a[rt].sum1;
    }
    int m = (l + r) >> 1;
    //下推标记，否则rt信息可能不正确
    PushDown(rt, m - l + 1, r - m);

    //累计答案
    int ANS = 0;
    if (L <= m)
        ANS += query2(L, R, lson);
    if (R > m)
        ANS += query2(L, R, rson);
    return ANS;
}

bool
all1(int L, int R, int l, int r, int rt)
{
    if (L <= l && r <= R) {
        return a[rt].allis1;
    }
    int m = (r + l) >> 1;
    PushDown(rt, m - l + 1, r - m);
    return all1(L, m, lson) && all1(m + 1, R, rson);
}

int
longest_left(int L, int R, int l, int r, int rt)
{ // L,R表示操作区间，l,r表示当前节点区间，rt表示当前节点编号
    if (L <= l && r <= R) {
        //在区间内，直接返回
        return a[rt].left1;
    }
    int m = (l + r) >> 1;
    //下推标记，否则rt信息可能不正确
    PushDown(rt, m - l + 1, r - m);

    //累计答案
    int ANS = 0;
    if (L <= m)
        ANS += longest_left(L, R, lson);
    if (R > m && all1(L, m, lson))
        ANS += longest_left(L, R, rson);
    return ANS;
}

int
longest_right(int L, int R, int l, int r, int rt)
{ // L,R表示操作区间，l,r表示当前节点区间，rt表示当前节点编号
    if (L <= l && r <= R) {
        //在区间内，直接返回
        return a[rt].right1;
    }
    int m = (l + r) >> 1;
    //下推标记，否则rt信息可能不正确
    PushDown(rt, m - l + 1, r - m);

    //累计答案
    int ANS = 0;
    if (R > m)
        ANS += longest_right(L, R, rson);
    if (L <= m && all1(m + 1, R, rson))
        ANS += longest_right(L, R, lson);
    return ANS;
}

int
query3(int L, int R, int l, int r, int rt)
{ // L,R表示操作区间，l,r表示当前节点区间，rt表示当前节点编号
    if (L <= l && r <= R) {
        //在区间内，直接返回
        return a[rt].longest1;
    }
    int m = (l + r) >> 1;
    //下推标记，否则rt信息可能不正确
    PushDown(rt, m - l + 1, r - m);

    //累计答案
    int ANS = 0;
    if (L <= m && R <= m)
        ANS = query3(L, R, lson);
    else if (L > m && R > m)
        ANS = query3(L, R, rson);

    else
        ANS = max3(query3(L, m, lson),
                   query3(m + 1, R, rson),
                   longest_right(L, m, lson) + longest_left(m + 1, R, rson));
    return ANS;
}

int
main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    Build(1, n, 1);
    for (int i = 0; i < m; i++) {
        int oper;
        cin >> oper;
        switch (oper) {
            case 1: {
                int l, r, x;
                cin >> l >> r >> x;
                Update(l, r, x, 1, n, 1);
                break;
            }
            case 2: {
                int l, r;
                cin >> l >> r;
                cout << query2(l, r, 1, n, 1) << '\n';
                break;
            }
            case 3: {
                int l, r;
                cin >> l >> r;
                cout << query3(l, r, 1, n, 1) << '\n';
            }
        }
    }

    cout << flush;

    return 0;
}
