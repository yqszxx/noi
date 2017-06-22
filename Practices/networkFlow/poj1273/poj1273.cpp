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

#include <queue>
int N, M, S, E, C, ans, s, t;
int cap[250][250], flow[250][250], a[250], p[250];

const int INF = 0x3f3f3f3f;

#include <cstring>

inline int min(int a, int b)
{
	return a < b ? a : b;
}

void edmondsKarp()
{
	int u, v;
	queue<int> q;
	while (true) {
		memset(a, 0, sizeof(a));
		a[s] = INF;
		q.push(s);
		while (!q.empty()) {
			u = q.front();
			q.pop();
			for (v = 1; v <= t; v++) {
				if (!a[v] && flow[u][v] < cap[u][v]) {
					p[v] = u;
					q.push(v);
					a[v] = min(a[u], cap[u][v] - flow[u][v]);
				}
			}
		}
		if (a[t] == 0) break;
		ans += a[t];
		for (int i = t; i != s; i = p[i]) {
			flow[p[i]][i] += a[t];
			flow[i][p[i]] -= a[t];
		}
	}
}

int main()
{
	while (scanf("%d%d", &N, &M) != EOF) {
		//Init
		s = 1;
		t = M;
		ans = 0;
		memset(flow, 0, sizeof(flow));
		memset(cap, 0, sizeof(cap));
		//End Init
		for (int i = 1; i <= N; i++) {
			scanf("%d%d%d", &S, &E, &C);
			cap[S][E] += C;
		}
		edmondsKarp();
		printf("%d\n", ans);
	}
	return 0;
}

