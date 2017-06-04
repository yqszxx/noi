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

const int INF = 0x3f3f3f3f;

int N, Q, v, ix, iy;
int subTreeBegin[100050], subTreeEnd[100050];
int dfsNow;
int rootNow = 1;
int depth[100050], depthNow, nearest;
char cmd[10];
struct treeNode {
	int v;
	int father;
	vector<int> sons;
} tree[100050];

#define LEFT(x) ((x) << 1)
#define RIGHT(x) (((x) << 1) | 1)
struct segTreeNode {
	int v;
	int l, r;
} segTree[400050];

void build(int root, int begin, int end)
{
	segTree[root].l = begin;
	segTree[root].r = end;
	if (begin == end) return;
	int mid = (begin + end) >> 1;
	build(LEFT(root), begin, mid);
	build(RIGHT(root), mid + 1, end);
}

inline int min(int a, int b)
{
	return a < b ? a : b;
}

int x, y;
void modify(int root)
{
	if (segTree[root].l == segTree[root].r && segTree[root].l == x) {
		segTree[root].v = y;
		return;
	}
	if (x < segTree[root].l || x > segTree[root].r) return;
	int mid = (segTree[root].l + segTree[root].r) >> 1;
	if (x <= mid) modify(LEFT(root));
	else modify(RIGHT(root));
	segTree[root].v = min(segTree[LEFT(root)].v, segTree[RIGHT(root)].v);
}

int query(int root)
{
	if (y < segTree[root].l || x > segTree[root].r) return INF;
	if (x <= segTree[root].l && segTree[root].r <= y) return segTree[root].v;
	int mid = (segTree[root].l + segTree[root].r) >> 1;
	int ret = INF;
	if (x <= mid) ret = min(ret, query(LEFT(root)));
	if (y > mid) ret = min(ret, query(RIGHT(root)));
	return ret;
}

int getNearest(int from, int to)
{
	int i = depth[from] - depth[to] - 1;
	int ret = from;
	while (i--) {
		ret = tree[ret].father;
	}
	return ret;
}

void dfs(int root)
{
	depthNow++;
	depth[root] = depthNow;
	dfsNow++;
	subTreeBegin[root] = dfsNow;
	x = dfsNow;
	y = tree[root].v;
	modify(1);
	int sonCnt = tree[root].sons.size();
	for (int i = 0; i < sonCnt; i++) {
		dfs(tree[root].sons[i]);
	}
	subTreeEnd[root] = dfsNow;
	depthNow--;
}

int main()
{
	freopen("data.in", "r", stdin);
	N = getInt(); Q = getInt();
	build(1, 1, N);
	for (int i = 1; i <= N; i++) {
		tree[i].father = getInt();
		tree[i].v = getInt();
		tree[tree[i].father].sons.push_back(i);
	}
	dfs(1);
	for (int i = 1; i <= Q; i++) {
		scanf("%s", cmd);
		if (cmd[0] == 'V') {
			ix = getInt();
			iy = getInt();
			x = subTreeBegin[ix];
			y = iy;
			modify(1);
		} else if (cmd[0] == 'E') {
			rootNow = getInt();
		} else {
			ix = getInt();
			if (ix == rootNow) {
				x = subTreeBegin[1];
				y = subTreeEnd[1];
				printf("%d\n", query(1));
			} else if (
				subTreeBegin[ix] < subTreeBegin[rootNow] &&
				subTreeEnd[ix] >= subTreeEnd[rootNow]
			) {
				nearest = getNearest(rootNow, ix);
				x = 1;
				y = subTreeBegin[nearest] - 1;
				iy = query(1);
				x = subTreeEnd[nearest] + 1;
				y = N;
				printf("%d\n", min(iy, query(1)));
			} else {
				x = subTreeBegin[ix];
				y = subTreeEnd[ix];
				printf("%d\n", query(1));
			}
		}
	}
	return 0;
}

