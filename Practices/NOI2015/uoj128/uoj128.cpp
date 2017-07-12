#include <cstdio>
#include <vector>

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

int n, q, v;
char cmd[50];

struct TreeNode {
	vector<int> sons;
	int pos;
	int size;
	int chainTop;
	int ste;
	int father;
	int depth;
} tree[100050];
typedef vector<int>::iterator P;
int posn = 0, depn = 0;

void dfs(int now)
{
	tree[now].depth = ++depn;
	tree[now].size = 1;
	for (P p = tree[now].sons.begin(); p != tree[now].sons.end(); p++) {
		dfs(*p);
		tree[now].size += tree[(*p)].size;
	}
	--depn;
}

void hld(int now)
{
	tree[now].pos = ++posn;
	int maxSize = -1, hson = -1;
	for (P p = tree[now].sons.begin(); p != tree[now].sons.end(); p++) {
		if (tree[(*p)].size > maxSize) {
			hson = (*p);
			maxSize = tree[hson].size;
		}
	}
	if (hson != -1) {
		tree[hson].chainTop = tree[now].chainTop;
		hld(hson);
	}
	for (P p = tree[now].sons.begin(); p != tree[now].sons.end(); p++) {
		if ((*p) != hson) {
			tree[(*p)].chainTop = (*p);
			hld(*p);
		}
	}
	tree[now].ste = posn;
}

struct SegTreeNode {
	int l, r;
	int v;
	int lazy;
} segTree[400050];

void dbg()
{
	for (int i = 0; i < n; i++) {
		printf("%d:%d ", tree[i].pos, tree[i].ste);
	}
	puts("");
}

#define L(x) ((x) << 1)
#define R(x) (((x) << 1) | 1)
#define F(x) ((x) >> 1)

void build(int now, int le, int ri)
{
	segTree[now].l = le;
	segTree[now].r = ri;
	if (le == ri) return;
	int mid = (le + ri) >> 1;
	build(L(now), le, mid);
	build(R(now), mid + 1, ri);
}

int x, y, z;

void pushDown(int now)
{
	if (segTree[now].lazy == 1) {
		segTree[L(now)].v = (segTree[L(now)].r - segTree[L(now)].l + 1) * segTree[now].lazy;
		segTree[R(now)].v = (segTree[R(now)].r - segTree[R(now)].l + 1) * segTree[now].lazy;
	} else {
		segTree[L(now)].v = segTree[R(now)].v = 0;
	}
	segTree[L(now)].lazy = segTree[now].lazy;
	segTree[R(now)].lazy = segTree[now].lazy;
	segTree[now].lazy = 0;
}

int query(int now)
{
	if (x <= segTree[now].l && segTree[now].r <= y) {
		return segTree[now].v;
	}
	if (segTree[now].r < x || y < segTree[now].l) {
		return 0;
	}
	int ret = 0;
	int mid = (segTree[now].l + segTree[now].r) >> 1;
	if (segTree[now].lazy) pushDown(now);
	if (x <= mid) ret += query(L(now));
	if (y > mid) ret += query(R(now));
	return ret;
}

void pushUp(int now)
{
	segTree[now].v = segTree[L(now)].v + segTree[R(now)].v;
}

void update(int now)
{
	if (x <= segTree[now].l && segTree[now].r <= y) {
		segTree[now].v = (segTree[now].r - segTree[now].l + 1) * z;
		segTree[now].lazy = z ? z : -1;
		return;
	}
	if (segTree[now].r < x || y < segTree[now].l) {
		return;
	}
	int mid = (segTree[now].l + segTree[now].r) >> 1;
	if (segTree[now].lazy) pushDown(now);
	if (x <= mid) update(L(now));
	if (y > mid) update(R(now));
	pushUp(now);
}

int Q(int fr)
{
	int ret = 0;
	while (tree[fr].chainTop != tree[0].chainTop) {
		x = tree[tree[fr].chainTop].pos;
		y = tree[fr].pos;
		ret += query(1);
		fr = tree[tree[fr].chainTop].father;
	}
	x = tree[0].pos;
	y = tree[fr].pos;
	ret += query(1);
	return ret;
}

void U(int fr)
{
	while (tree[fr].chainTop != tree[0].chainTop) {
		x = tree[tree[fr].chainTop].pos;
		y = tree[fr].pos;
		z = 1;
		update(1);
		fr = tree[tree[fr].chainTop].father;
	}
	x = tree[0].pos;
	y = tree[fr].pos;
	z = 1;
	update(1);
}
	
int main()
{
	n = getInt();
	for (int i = 1; i < n; i++) {
		tree[i].father = getInt();
		tree[tree[i].father].sons.push_back(i);
	}
	dfs(0);
	hld(0);
	//dbg();
	build(1, 1, n);
	q = getInt();
	for (int i = 1; i <= q; i++) {
		scanf("%s%d", cmd, &v);
		if (cmd[0] == 'i') {
			x = y = tree[v].pos;
			if (query(1)) {
				printf("0\n");
				continue;
			}
			printf("%d\n", tree[v].depth - Q(v));
			U(v);
		} else {
			x = y = tree[v].pos;
			if (!query(1)) {
				printf("0\n");
				continue;
			}
			x = tree[v].pos;
			y = tree[v].ste;
			printf("%d\n", query(1));
			x = tree[v].pos;
			y = tree[v].ste;
			z = 0;
			update(1);
		}
	}
	return 0;
}

