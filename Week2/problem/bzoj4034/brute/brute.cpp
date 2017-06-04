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

struct Node {
	vector<int> sons;
	long long v;
	int fa;
} tree[100050];

int N, M;
int a, b, x;

void dfs(int now, int fa)
{
	tree[now].fa = fa;
	for (int i = 0; i < tree[now].sons.size(); i++) {
		if (tree[now].sons[i] != fa) dfs(tree[now].sons[i], now);
	}
}

void dfsAdd(int now, int a)
{
	tree[now].v += a;
	for (int i = 0; i < tree[now].sons.size(); i++) {
		if (tree[now].sons[i] != tree[now].fa) {
			dfsAdd(tree[now].sons[i], a);
		}
	}
}

long long ans;
void dfsFind(int now)
{
	ans += tree[now].v;
	if (now == 1) return;
	dfsFind(tree[now].fa);
}

int main()
{
	N = getInt(); M = getInt();
	for (int i = 1; i <= N; i++) {
		tree[i].v = getInt();
	}
	for (int i = 1; i < N; i++) {
		a = getInt();
		b = getInt();
		tree[a].sons.push_back(b);
		tree[b].sons.push_back(a);
	}
	dfs(1, 1);
	for (int i = 1; i <= M; i++) {
		b = getInt();
		if (b == 1) {
			x = getInt();
			a = getInt();
			tree[x].v += a;
		} else if (b == 2) {
			x = getInt();
			a = getInt();
			dfsAdd(x, a);
		} else {
			x = getInt();
			ans = 0;
			dfsFind(x);
			printf("%lld\n", ans);
		}
	}
	return 0;
}

