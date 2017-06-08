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

int T, N, u, v;
struct Edge {
	int to;
	Edge(int _to): to(_to) {};
};
#include <vector>
typedef vector<Edge>::iterator EdgePointer;
struct TreeNode {
	vector<Edge> edges;
	int subTreeSize;
	int father;
} tree[20050];

int minSize, ans;

void dfs(int root, int from)
{
	tree[root].father = from;
	tree[root].subTreeSize = 1;
	int tmp = 0;
	for (EdgePointer p = tree[root].edges.begin(); p != tree[root].edges.end(); p++) {
		if ((*p).to != from) {
			dfs((*p).to, root);
			tree[root].subTreeSize += tree[(*p).to].subTreeSize;
			tmp = max(tmp, tree[(*p).to].subTreeSize);
		}
	}
	tmp = max(tmp, N - tree[root].subTreeSize);
	if (tmp < minSize || (tmp == minSize && root < ans)) {
		ans = root;
		minSize = tmp;
	}
}

const int INF = 0x3f3f3f3f;

int main()
{
	T = getInt();
	while (T--) {
		N = getInt();
		//Init
		for (int i = 1; i <= N; i++) {
			tree[i].edges.clear();
		}
		ans = -1;
		minSize = INF;
		//End Init
		for (int i = 1; i < N; i++) {
			u = getInt();
			v = getInt();
			tree[u].edges.push_back(Edge(v));
			tree[v].edges.push_back(Edge(u));
		}
		dfs(1, 1);
		printf("%d %d\n", ans, minSize);
	}
	return 0;
}

