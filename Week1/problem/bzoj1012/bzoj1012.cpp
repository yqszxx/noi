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

int M, D, cur, x, t;
char cmd[3];

struct seg {
	int v;
	int l, r;
} segTree[1000050];

#define LEFT(x) ((x) << 1)
#define RIGHT(x) ((x) << 1 | 1)
#define FATHER(x) ((x) >> 1)

inline int max(int a, int b)
{
	if (a > b) return a;
	return b;
}

void build(int root, int l, int r)
{
	segTree[root].l = l;
	segTree[root].r = r;
	if (l == r) {
		return;
	}
	int mid = (l + r) >> 1;
	build(LEFT(root), l, mid);
	build(RIGHT(root), mid + 1, r);
}

int a, b;
int query(int root)
{
	if (segTree[root].r < a || segTree[root].l > b) return -1;
	if (segTree[root].l >= a && segTree[root].r <= b) return segTree[root].v;
	int mid = (segTree[root].l + segTree[root].r) >> 1;
	int ret = -1;
	if (a <= mid) ret = max(ret, query(LEFT(root)));
	if (b > mid) ret = max(ret, query(RIGHT(root)));
	return ret;
}

void add(int root)
{
	if (segTree[root].l == segTree[root].r && segTree[root].l == a) {
		segTree[root].v = b;
		return;
	}
	int mid = (segTree[root].l + segTree[root].r) >> 1;
	if (a <= mid) {
		add(LEFT(root));
	} else {
		add(RIGHT(root));
	}
	segTree[root].v = max(segTree[LEFT(root)].v, segTree[RIGHT(root)].v);
}

int main()
{
	M = getInt();
	D = getInt();
	build(1, 1, M);
	for (int i = 1; i <= M; i++) {
		scanf("%s%d", cmd, &x);
		if (cmd[0] == 'Q') {
			a = cur - x + 1;
			b = cur;
			printf("%d\n", t = query(1));
		} else {
			a = ++cur;
			b = (t + x) % D;
			add(1);
		}
	}
	return 0;
}

