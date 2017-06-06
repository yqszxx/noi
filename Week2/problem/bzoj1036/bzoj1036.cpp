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

int N, a, b, Q;
char cmd[10];
struct TreeNode {
	int v;
	int father;
	vector<int> sons;
	int depth;
	int subTreeSize;
	int chainTop;
	int posInSegTree;
	int jmpTo[20];
} tree[30050];

int dfsNow, depthNow;

void swap(int &a, int &b)
{
	int t = a;
	a = b;
	b = t;
}

void dfs(int root)
{
	//LCA - Doubling Algo
	tree[root].jmpTo[0] = tree[root].father;
	for (int i = 1; i <= 14; i++) {
		tree[root].jmpTo[i] = tree[tree[root].jmpTo[i - 1]].jmpTo[i - 1];
	}
	//End LCA
	depthNow++;
	tree[root].depth = depthNow;
	tree[root].subTreeSize = dfsNow;
	dfsNow++;
	int sonCnt = tree[root].sons.size();
	for (int i = 0; i < sonCnt; i++) {
		if (tree[root].sons[i] != tree[root].father) {
			tree[tree[root].sons[i]].father = root;
			dfs(tree[root].sons[i]);
		}
	}
	tree[root].subTreeSize = dfsNow - tree[root].subTreeSize;
	depthNow--;
}

void hld(int root) {
	dfsNow++;
	tree[root].posInSegTree = dfsNow;
	int sonCnt = tree[root].sons.size();
	if (sonCnt == 1) {
		if (root != 1) return;
		else if (N == 1) return;
	}
	int heaviestSon = -1, heaviestSonSize = -1;
	for (int i = 0; i < sonCnt; i++) {
		if (tree[root].sons[i] != tree[root].father &&
			tree[tree[root].sons[i]].subTreeSize > heaviestSonSize
		) {
			heaviestSonSize = tree[tree[root].sons[i]].subTreeSize;
			heaviestSon = i;
		}
	}
	tree[tree[root].sons[heaviestSon]].chainTop = tree[root].chainTop;
	hld(tree[root].sons[heaviestSon]);
	for (int i = 0; i < sonCnt; i++) {
		if (i == heaviestSon) continue;
		if (tree[root].sons[i] != tree[root].father) {
			tree[tree[root].sons[i]].chainTop = tree[root].sons[i];
			hld(tree[root].sons[i]);
		}
	}
}

int lca(int x, int y)
{
	if (tree[x].depth < tree[y].depth) swap(x, y); //以下x更深
	int t = tree[x].depth - tree[y].depth;
	for (int i = 0; i <= 14; i++) {
		if (t & (1 << i)) {
			x = tree[x].jmpTo[i];
		}
	}
	for (int i = 14; i >= 0; i--) {
		if (tree[x].jmpTo[i] != tree[y].jmpTo[i]) {
			x = tree[x].jmpTo[i];
			y = tree[y].jmpTo[i];
		}
	}
	if (x == y) return x;
	else return tree[x].father;
}

#define LEFT(x) ((x) << 1)
#define RIGHT(x) (((x) << 1) | 1)
struct SegTreeNode {
	int maxv, sumv;
	int l, r;
} segTree[120050];

void build(int root, int begin, int end)
{
	segTree[root].l = begin;
	segTree[root].r = end;
	if (begin == end) return;
	int mid = (begin + end) >> 1;
	build(LEFT(root), begin, mid);
	build(RIGHT(root), mid + 1, end);
}

inline int max(int a, int b)
{
	return a < b ? b : a;
}

inline void maintain(int node)
{
	segTree[node].maxv = max(segTree[LEFT(node)].maxv, segTree[RIGHT(node)].maxv);
	segTree[node].sumv = segTree[LEFT(node)].sumv + segTree[RIGHT(node)].sumv;
}

int x, y;
void modify(int root)
{
	if (segTree[root].l == segTree[root].r && segTree[root].l == x) {
		segTree[root].maxv = segTree[root].sumv = y;
		return;
	}
	if (x < segTree[root].l || x > segTree[root].r) {
		return;
	}
	int mid = (segTree[root].l + segTree[root].r) >> 1;
	if (x <= mid) modify(LEFT(root));
	else modify(RIGHT(root));
	maintain(root);
}

int querySum(int root)
{
	if (x <= segTree[root].l && segTree[root].r <= y) {
		return segTree[root].sumv;
	}
	if (x > segTree[root].r || y < segTree[root].l) {
		return 0;
	}
	int ret = 0;
	int mid = (segTree[root].l + segTree[root].r) >> 1;
	if (x <= mid) {
		ret += querySum(LEFT(root));
	}
	if (y > mid) {
		ret += querySum(RIGHT(root));
	}
	return ret;
}

int queryMax(int root)
{
	if (x <= segTree[root].l && segTree[root].r <= y) {
		return segTree[root].maxv;
	}
	if (x > segTree[root].r || y < segTree[root].l) {
		return -INF;
	}
	int ret = -INF;
	int mid = (segTree[root].l + segTree[root].r) >> 1;
	if (x <= mid) {
		ret = max(ret, queryMax(LEFT(root)));
	}
	if (y > mid) {
		ret = max(ret, queryMax(RIGHT(root)));
	}
	return ret;
}

int solveSum(int u, int v)
{
	int ret = 0;
	while (tree[u].chainTop != tree[v].chainTop) {
		x = tree[tree[u].chainTop].posInSegTree;
		y = tree[u].posInSegTree;
		ret += querySum(1);
		u = tree[tree[u].chainTop].father;
	}
	x = tree[v].posInSegTree;
	y = tree[u].posInSegTree;
	ret += querySum(1);
	return ret;
}

int solveMax(int u, int v)
{
	int ret = -INF;
	while (tree[u].chainTop != tree[v].chainTop) {
		x = tree[tree[u].chainTop].posInSegTree;
		y = tree[u].posInSegTree;
		ret = max(ret, queryMax(1));
		u = tree[tree[u].chainTop].father;
	}
	x = tree[v].posInSegTree;
	y = tree[u].posInSegTree;
	ret = max(ret, queryMax(1));
	return ret;
}

int main()
{
	tree[1].chainTop = 1;
	//freopen("gen/data.in", "r", stdin);
	N = getInt();
	for (int i = 1; i < N; i++) {
		a = getInt();
		b = getInt();
		tree[a].sons.push_back(b);
		tree[b].sons.push_back(a);
	}
	for (int i = 1; i <= N; i++) {
		tree[i].v = getInt();
	}
	dfs(1);
	dfsNow = 0;
	hld(1);
	build(1, 1, N);
	for (int i = 1; i <= N; i++) {
		x = tree[i].posInSegTree;
		y = tree[i].v;
		modify(1);
	}
	Q = getInt();
	for (int i = 1; i <= Q; i++) {
		scanf("%s%d%d", cmd, &a, &b);
		if (cmd[0] == 'C') {
			tree[a].v = b;
			x = tree[a].posInSegTree;
			y = b;
			modify(1);
		} else {
			int l = lca(a, b);
			if (cmd[1] == 'M') {
				printf("%d\n", max(solveMax(a, l), solveMax(b, l)));
			} else {
				printf("%d\n", solveSum(a, l) + solveSum(b, l) - tree[l].v);
			}
		}
	}
	return 0;
}

