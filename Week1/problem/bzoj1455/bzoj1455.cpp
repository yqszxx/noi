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

bool die[1000050];
struct Node {
	int v, l, r, f, d;
} heap[1000050];
int N, M, ii, jj;
char cm;

inline void swap(int &x, int &y)
{
	x ^= y;
	y ^= x;
	x ^= y;
}

int merge(int x, int y)
{
	if (x == 0) return y;
	if (y == 0) return x;
	if (heap[x].v > heap[y].v) swap(x, y);
	heap[x].r = merge(heap[x].r, y);
	heap[heap[x].r].f = x;
	if (heap[heap[x].l].d < heap[heap[x].r].d)
		swap(heap[x].l, heap[x].r);
	if (heap[x].r == 0) heap[x].d = 0;
	else heap[x].d = heap[heap[x].r].d + 1;
	return x;
}

int pop(int x)
{
	heap[heap[x].l].f = heap[x].l;
	heap[heap[x].r].f = heap[x].r;
	heap[x].l = heap[x].r = heap[x].d = 0;
	return merge(heap[x].l, heap[x].r);
}

int find(int x)
{
	if (heap[x].f == x) return x;
	else return find(heap[x].f);
}

int main()
{
	N = getInt();
	for (int i = 1; i <= N; i++) {
		heap[i].v = getInt();
		heap[i].f = i;
		heap[i].d = heap[i].l = heap[i].r = 0;
	}
	M = getInt();
	for (int i = 1; i <= M; i++) {
		cm = getchar();
		if (cm == 'M') {
			ii = getInt();
			jj = getInt();
			if (die[ii] || die[jj]) continue;
			ii = find(ii);
			jj = find(jj);
			if (ii != jj)
				heap[ii].f = heap[jj].f = merge(ii, jj);
		} else {
			ii = getInt();
			if (die[ii]) printf("0\n");
			else {
				ii = find(ii);
				die[ii] = true;
				printf("%d\n", heap[ii].v);
				heap[ii].f = merge(heap[ii].l, heap[ii].r);
				heap[heap[ii].f].f = heap[ii].f;
			}
		}
	}
	return 0;
}

