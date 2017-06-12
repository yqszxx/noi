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

int N, Q, il, ir, iz, f;

#include <algorithm>
#include <vector>
struct TreeNode {
	vector<int> sons;
	int father;
	int subTreeSize;
	int chainTop;
	int posInSegTree;
} tree[50050];
typedef vector<int>::iterator SP;

void dfs(int now, int from)
{
	tree[now].father = from;
	tree[now].subTreeSize = 1;
	for (SP p = tree[now].sons.begin(); p != tree[now].sons.end(); p++) {
		dfs((*p), now);
		tree[now].subTreeSize += tree[(*p)].subTreeSize;
	}
}

int posNow;
void hld(int now)
{
	tree[now].posInSegTree = ++posNow;
	int heaviestSon = -1, heaviestSonSize = -1;
	for (SP p = tree[now].sons.begin(); p != tree[now].sons.end(); p++) {
		if (tree[(*p)].subTreeSize > heaviestSonSize) {
			heaviestSonSize = tree[(*p)].subTreeSize;
			heaviestSon = (*p);
		}
	}
	if (heaviestSon != -1) {
		tree[heaviestSon].chainTop = tree[now].chainTop;
		hld(heaviestSon);
	}
	for (SP p = tree[now].sons.begin(); p != tree[now].sons.end(); p++) {
		if ((*p) != heaviestSon) {
			tree[(*p)].chainTop = (*p);
			hld((*p));
		}
	}
}

struct Query {
	int ansId;
	int v;
	bool isLeft;
	Query(int _ansId, int _v, bool _isLeft): ansId(_ansId), v(_v), isLeft(_isLeft) {};
	bool operator < (const Query& q) const
	{
		return v < q.v;
	}
};
vector<Query> queries;
typedef vector<Query>::iterator QP;

struct Answer {
	int lAns;
	int rAns;
	int z;
} answers[50050];

struct SegTreeNode {
	int v;
	int lazy;
	int l, r, size;
} segTree[200050];

#define LEFT(x) ((x) << 1)
#define RIGHT(x) (((x) << 1) | 1)

const int MOD = 201314;

void build(int now, int l, int r)
{
	segTree[now].l = l;
	segTree[now].r = r;
	segTree[now].size = r - l + 1;
	if (l == r) return;
	int mid = (l + r) >> 1;
	build(LEFT(now), l, mid);
	build(RIGHT(now), mid + 1, r);
}

void pushDown(int node)
{
	if (segTree[node].lazy == 0) {
		return;
	}
	segTree[LEFT(node)].v += segTree[LEFT(node)].size * segTree[node].lazy;
	segTree[RIGHT(node)].v += segTree[RIGHT(node)].size * segTree[node].lazy ;
	segTree[LEFT(node)].lazy += segTree[node].lazy;
	segTree[RIGHT(node)].lazy += segTree[node].lazy;
	segTree[node].lazy = 0;
}

int x, y, z;

int query(int now)
{
	if (x > y) swap(x, y);
	int l = segTree[now].l, r = segTree[now].r;
	if (x <= l && r <= y) {
		return segTree[now].v;
	}
	if (y < l || x > r) {
		return 0;
	}
	pushDown(now);
	int ret = 0;
	int mid = (l + r) >> 1;
	if (x <= mid) ret += query(LEFT(now));
	if (y > mid) ret += query(RIGHT(now));
	return ret;
}

void update(int now)
{
	if (x > y) swap(x, y);
	int l = segTree[now].l, r = segTree[now].r;
	if (y < l || x > r) return;
	if (x <= l && r <= y) {
		segTree[now].v += segTree[now].size * z;
		segTree[now].lazy += z;
		return;
	}
	pushDown(now);
	int mid = (l + r) >> 1;
	if (x <= mid) update(LEFT(now));
	if (y > mid) update(RIGHT(now));
	segTree[now].v = segTree[LEFT(now)].v + segTree[RIGHT(now)].v;
}

int solveQuery(int u, int v)
{
	int ret = 0;
	while (tree[u].chainTop != tree[v].chainTop) {
		x = tree[u].posInSegTree;
		y = tree[tree[u].chainTop].posInSegTree;
		ret += query(1);
		ret %= MOD;
		u = tree[tree[u].chainTop].father;
	}
	x = tree[u].posInSegTree;
	y = tree[v].posInSegTree;
	ret += query(1);
	ret %= MOD;
	return ret;
}

void solveUpdate(int u, int v)
{
	while (tree[u].chainTop != tree[v].chainTop) {
		x = tree[u].posInSegTree;
		y = tree[tree[u].chainTop].posInSegTree;
		z = 1;
		update(1);
		u = tree[tree[u].chainTop].father;
	}
	x = tree[u].posInSegTree;
	y = tree[v].posInSegTree;
	z = 1;
	update(1);
}

int main()
{
	freopen("data.in", "r", stdin);
	N = getInt(); 
	Q = getInt();
	for (int i = 1; i < N; i++) {
		f = getInt();
		tree[f].sons.push_back(i);
	}
	dfs(0, 0);
	hld(0);
	build(1, 1, N);
	for (int i = 1; i <= Q; i++) {
		il = getInt();
		ir = getInt();
		iz = getInt();
		queries.push_back(Query(i, il - 1, true));
		queries.push_back(Query(i, ir, false));
		answers[i].z = iz;
	}
	sort(queries.begin(), queries.end());
	int nowPos = -1;
	for (QP p = queries.begin(); p != queries.end(); p++) {
		while (nowPos < (*p).v) {
			nowPos++;
			solveUpdate(nowPos, 0);
		}
		if ((*p).isLeft) {
			answers[(*p).ansId].lAns = solveQuery(answers[(*p).ansId].z, 0);
		} else {
			answers[(*p).ansId].rAns = solveQuery(answers[(*p).ansId].z, 0);
		}
	}
	for (int i = 1; i <= Q; i++) {
		printf("%d\n", (answers[i].rAns - answers[i].lAns + MOD) % MOD);
	}
	return 0;
}

