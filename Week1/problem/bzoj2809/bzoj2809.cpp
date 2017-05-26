//47.38
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

#include <algorithm>

const int INF = 0x3f3f3f3f;

int N, M;
long long ans = -INF;

#include <vector>
struct Node {
	int f;
	int s, p; //salary, power
	int l, r, d;
	int size;
	vector<int> sons;
	long long sum;
	int root;
} heap[100050];

int getD(int x)
{
	if (x == 0) return -1;
	else return heap[x].d;
}

int merge(int x, int y)
{
	if (x == 0) return y;
	if (y == 0) return x;
	if (heap[x].s < heap[y].s) swap(x, y);
	heap[x].r = merge(heap[x].r, y);
	if (getD(heap[x].r) > getD(heap[x].l)) swap(heap[x].r, heap[x].l);
	heap[x].d = getD(heap[x].r) + 1;
	return x;
}

int pop(int x)
{
	int ret = merge(heap[x].l, heap[x].r);
	heap[x].d = heap[x].l = heap[x].r = 0;
	return ret;
}

void dfs(int x)
{
	for (int i = 0; i < heap[x].sons.size(); i++) {
		dfs(heap[x].sons[i]);
		//merge sons
		heap[x].size += heap[heap[x].sons[i]].size;
		heap[x].sum += heap[heap[x].sons[i]].sum;
		heap[x].root = merge(heap[x].root, heap[heap[x].sons[i]].root);
	}
	while (heap[x].sum > M) {
		heap[x].sum -= heap[heap[x].root].s;
		heap[x].root = pop(heap[x].root);
		heap[x].size--;
	}
	ans = max(ans, (long long)heap[x].p * heap[x].size);
}

int main()
{
	N = getInt(); M = getInt();
	for (int i = 1; i <= N; i++) {
		heap[i].f = getInt();
		heap[i].s = heap[i].sum = getInt();
		heap[i].p = getInt();
		heap[i].size = 1;
		heap[heap[i].f].sons.push_back(i);
		heap[i].root = i;
	}
	dfs(1);
	printf("%lld\n", ans);
	return 0;
}

