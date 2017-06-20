#include <cstdio>
#include <algorithm> 

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

int N, M, sz, rt;
int fa[100005], c[100005][2], id[100005];
int size[100005];
bool rev[100005];

void pushUp(int k)
{
	int l = c[k][0], r = c[k][1];
	size[k] = size[l] + size[r] + 1;
}

void pushDown(int k)
{
	int l = c[k][0], r = c[k][1];
	if (rev[k]) {
		swap(c[k][0], c[k][1]);
		rev[l] ^= 1;
		rev[r] ^= 1;
		rev[k] = 0;
	}
}

void rotate(int x, int &k)
{
	int y = fa[x], z = fa[y], l, r;
	if (c[y][0] == x) {
		l = 0;
	} else {
		l = 1;
	}
	r = l ^ 1;
	if (y == k) k = x;
	else {
		if (c[z][0] == y) {
			c[z][0] = x;
		} else {
			c[z][1] = x;
		}
	}
	fa[x] = z;
	fa[y] = x;
	fa[c[x][r]] = y;
	c[y][l] = c[x][r];
	c[x][r] = y;
	pushUp(y);
	pushUp(x);
}

void splay(int x, int &k)
{
	while (x != k) {
		int y = fa[x], z = fa[y];
		if (y != k) {
			if (c[y][0] == x ^ c[z][0] == y) {
				rotate(x, k);
			} else {
				rotate(y, k);
			}
		}
		rotate(x, k);
	}
}

int find(int k, int rank)
{
	pushDown(k);
	int l = c[k][0], r = c[k][1];
	if (size[l] + 1 == rank) return k;
	else if (size[l] >= rank) return find(l, rank);
	else return find(r, rank - size[l] - 1);
}

void rever(int l, int r)
{
	int x = find(rt, l), y = find(rt, r + 2);
	splay(x, rt);
	splay(y, c[x][1]);
	int z = c[y][0];
	rev[z] ^= 1;
}

void build(int l, int r, int f)
{
	if (l > r) return;
	int now = id[l], last = id[f];
	if (l == r) {
		fa[now] = last;
		size[now] = 1;
		if (l < f) c[last][0] = now;
		else c[last][1] = now;
		return;
	}
	int mid = (l + r) >> 1;
	now = id[mid];
	build(l, mid - 1, mid);
	build(mid + 1, r, mid);
	fa[now] = last;
	pushUp(mid);
	if (mid < f) c[last][0] = now;
	else c[last][1] = now;
}

int main()
{
	N = getInt();
	M = getInt();
	for (int i = 1; i <= N + 2; i++) {
		id[i] = ++sz;
	}
	build(1, N + 2, 0);
	rt = (N + 3) >> 1;
	for (int i = 1; i <= M; i++) {
		int l = getInt(), r = getInt();
		rever(l, r);
	}
	for (int i = 2; i <= N + 1; i++) {
		printf("%d ", find(rt, i) - 1);
	}
	return 0;
}

