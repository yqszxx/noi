#include <cstdio>

using namespace std;

int getInt()
{
        int res = 0, pre = 1;
        char ch = getchar();
        while (ch < '0' || ch > '9') {
                if (ch == '-') {
                        pre = -1;
                }
                ch = getchar();
        }
        while (ch >= '0' && ch <= '9') {
                res *= 10;
                res += ch - '0';
                ch = getchar();
        }
        return pre * res;
}

#include <vector>

int N, M, fr, to, cmd, ix, ia;
struct TreeNode {
        int v;
        vector<int> sons;
} tree[100050];

int dfsNow = 0;
int subTreeEnd[100050];
int subTreeBegin[100050];


#define LEFT(x) ((x) << 1)
#define RIGHT(x) (((x) << 1) | 1)
#define FATHER(x) ((x) >> 1)
struct SegTreeNode {
        long long v;
		int flag;
        int l, r;
        long long lazy;
} segTree[800050];

void build(int root, int begin, int end)
{
        segTree[root].l = begin;
        segTree[root].r = end;
        if (begin == end) return;
        int mid = (begin + end) >> 1;
        build(LEFT(root), begin, mid);
        build(RIGHT(root), mid + 1, end);
}

int x, y, z;

void add(int root)
{
	if (segTree[root].l == segTree[root].r && segTree[root].l == x) {
		segTree[root].flag = y;
		return;
	}
	if (segTree[root].r < x || segTree[root].l > x) return;
	int mid = (segTree[root].l + segTree[root].r) >> 1;
	if (x <= mid) add(LEFT(root));
	else add(RIGHT(root));
	segTree[root].flag = segTree[LEFT(root)].flag + segTree[RIGHT(root)].flag;
}

inline void pushDown(int root)
{
        if (segTree[root].lazy != 0) {
                segTree[LEFT(root)].v += (long long)segTree[LEFT(root)].flag * segTree[root].lazy;
                segTree[RIGHT(root)].v += (long long)segTree[RIGHT(root)].flag * segTree[root].lazy;
                segTree[LEFT(root)].lazy += segTree[root].lazy;
                segTree[RIGHT(root)].lazy += segTree[root].lazy;
                segTree[root].lazy = 0;
        }
}

long long query(int root)
{
        if (y < segTree[root].l || x > segTree[root].r) {
                return (long long)0;
        }
        if (x <= segTree[root].l && segTree[root].r <= y) {
                return segTree[root].v;
        }
        pushDown(root);
        long long ret = 0;
        int mid = (segTree[root].l + segTree[root].r) >> 1;
        if (x <= mid) ret += query(LEFT(root));
        if (y >= mid + 1) ret += query(RIGHT(root));
        return ret;
}

void addSeg(int root)
{
        if (y < segTree[root].l || x > segTree[root].r) {
                return;
        }
        if (x <= segTree[root].l && segTree[root].r <= y) {
                segTree[root].v += (long long)segTree[root].flag * z;
                segTree[root].lazy += z;
                return;
        }
        pushDown(root);
        int mid = (segTree[root].l + segTree[root].r) >> 1;
        if (x <= mid) addSeg(LEFT(root));
        if (y >= mid + 1) addSeg(RIGHT(root));
        segTree[root].v = segTree[LEFT(root)].v + segTree[RIGHT(root)].v;
}

void dfs(int root, int from)
{
        dfsNow++;
        subTreeBegin[root] = dfsNow;
        x = dfsNow;
		y = 1;
		add(1);
        x = dfsNow;
        y = dfsNow;
        z = tree[root].v;
        addSeg(1);
        for (unsigned int i = 0; i < tree[root].sons.size(); i++) {
                if (tree[root].sons[i] != from) {
                        dfs(tree[root].sons[i], root);
                }
        }
        dfsNow++;
        x = dfsNow;
		y = -1;
		add(1);
		x = dfsNow;
        y = dfsNow;
        z = tree[root].v;
        addSeg(1);
        subTreeEnd[root] = dfsNow;
}

int main()
{
        N = getInt(); M = getInt();
        for (int i = 1; i <= N; i++) {
                tree[i].v = getInt();
        }
        build(1, 1, N << 1);
        for (int i = 1; i < N; i++) {
                fr = getInt();
                to = getInt();
                tree[fr].sons.push_back(to);
                tree[to].sons.push_back(fr);
        }
        dfs(1, 0);
        for (int i = 1; i <= M; i++) {
                cmd = getInt();
                if (cmd == 1) {
                        ix = getInt();
                        ia = getInt();
                        x = subTreeBegin[ix];
                        y = subTreeBegin[ix];
                        z = ia;
                        addSeg(1);
                        x = subTreeEnd[ix];
                        y = subTreeEnd[ix];
                        z = ia;
                        addSeg(1);
                } else if (cmd == 2) {
                        ix = getInt();
                        ia = getInt();
                        x = subTreeBegin[ix];
                        y = subTreeEnd[ix];
                        z = ia;
                        addSeg(1);
                } else {
                        ix = getInt();
                        x = 1;
                        y = subTreeBegin[ix];
                        printf("%lld\n", query(1));
                }
        }
        return 0;
}
