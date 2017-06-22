#include <cstdio>
#include <cstring>
using namespace std;

const int INF = 0x3f3f3f3f;

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

struct Edge {
	int to;
	int cap;
	int rev; //反向边
};
vector<Edge> G[250];
bool vis[250];

void addEdge(int from, int to, int cap)
{
	G[from].push_back((Edge){to, cap, G[to].size()});
	G[to].push_back((Edge){from, 0, G[from].size() - 1});
}

int dfs(int v, int t, int f)
{
	if (v == t) return f;
	vis[v] = true;
	for (int i = 0; i < G[v].size(); i++) {
		Edge &e = G[v][i];
		if (!vis[e.to] && e.cap > 0) {
			int d = dfs(e.to, t, min(f, e.cap));
			if (d > 0) {
				e.cap -= d;
				G[e.to][e.rev].cap += d;
				return d;
			}
		}
	}
	return 0;
}

int maxFlow(int s, int t)
{
	int flow = 0;
	while (true) {
		memset(vis, 0, sizeof(vis));
		int f = dfs(s, t, INF);
		if (f == 0) return flow;
		flow += f;
	}
}

int N, M, S, E, C;

int main()
{
	freopen("data.in", "r", stdin);
	while (scanf("%d%d", &N, &M) == 2) {
		for (int i = 1; i <= 200; i++) {
			G[i].clear();
		}
		for (int i = 1; i <= N; i++) {
			scanf("%d%d%d", &S, &E, &C);
			addEdge(S, E, C);
		}
		printf("%d\n", maxFlow(1, M));
	}
	return 0;
}

