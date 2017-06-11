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

#include <vector>
#include <algorithm>
#include <cstring>

int N, u, v, l;

struct Edge {
	int to;
	int length;
	Edge(int _x, int _y): to(_x), length(_y) {};
};
typedef vector<Edge>::iterator P;

struct TreeNode {
	vector<Edge> edges;
	int subTreeSize;
	int maxTreeSize; //与本节点相连的其他节点的子树大小的最大值
	bool done;
	int lengthFromRoot;
	int depthFromRoot;
} tree[100050];

int treeSize, root;
long long ans;

void getRoot(int now, int from)
{
	tree[now].subTreeSize = 1;
	tree[now].maxTreeSize = 0;
	for (P p = tree[now].edges.begin(); p != tree[now].edges.end(); p++) {
		if ((*p).to != from && !tree[(*p).to].done) {
			getRoot((*p).to, now);
			tree[now].subTreeSize += tree[(*p).to].subTreeSize;
			tree[now].maxTreeSize = max(tree[now].maxTreeSize, tree[(*p).to].subTreeSize);
		}
	}
	tree[now].maxTreeSize = max(tree[now].maxTreeSize, treeSize - tree[now].subTreeSize);
	if (tree[now].maxTreeSize < tree[root].maxTreeSize) {
		root = now;
	}
}

int f[200050][2], g[200050][2];
const int zero = 100000;
int appearedTime[200050];
int maxDepth;

void dfs(int now, int from)
{
	maxDepth = max(maxDepth, tree[now].depthFromRoot);
	if (appearedTime[tree[now].lengthFromRoot] > 0) {
		f[zero + tree[now].lengthFromRoot][1]++;
	} else {
		f[zero + tree[now].lengthFromRoot][0]++;
	}
	appearedTime[tree[now].lengthFromRoot]++;
	for (P p = tree[now].edges.begin(); p != tree[now].edges.end(); p++) {
		if ((*p).to != from && !tree[(*p).to].done) {
			tree[(*p).to].depthFromRoot = tree[now].depthFromRoot + 1;
			tree[(*p).to].lengthFromRoot = tree[now].lengthFromRoot + (*p).length;
			dfs((*p).to, now);
		}
	}
	appearedTime[tree[now].lengthFromRoot]--;
}

void calc(int now)
{
	int usedSize = 0;
	g[zero][0] = 1;
	for (P p = tree[now].edges.begin(); p != tree[now].edges.end(); p++) {
		if (!tree[(*p).to].done) {
			tree[(*p).to].lengthFromRoot = (*p).length;
			tree[(*p).to].depthFromRoot = 1;
			maxDepth = 1;
			dfs((*p).to, (*p).to);
			usedSize = max(usedSize, maxDepth);
			ans += (long long)(g[zero][0] - 1) * f[zero][0];
			for (int i = -maxDepth; i <= maxDepth; i++) {
				ans += (long long)f[zero + i][0] * g[zero - i][1];
				ans += (long long)f[zero + i][1] * g[zero - i][0];
				ans += (long long)f[zero + i][1] * g[zero - i][1];
			}
			for (int i = -maxDepth; i <= maxDepth; i++) {
				g[zero + i][0] += f[zero + i][0];
				g[zero + i][1] += f[zero + i][1];
				f[zero + i][0] = f[zero + i][1] = 0;
			}
		}
	}
	for (int i = -usedSize; i <= usedSize; i++) {
		g[zero + usedSize][0] = g[zero + usedSize][1] = 0;
	}
}

void solve(int now)
{
	tree[now].done = true;
	calc(now);
	for (P p = tree[now].edges.begin(); p != tree[now].edges.end(); p++) {
		if (!tree[(*p).to].done) {
			tree[0].maxTreeSize = treeSize = tree[(*p).to].subTreeSize;
			root = 0;
			getRoot((*p).to, 0);
			solve(root);
		}
	}
}

int main()
{
	N = getInt();
	for (int i = 1; i < N; i++) {
		u = getInt();
		v = getInt();
		l = getInt();
		if (l == 0) l = -1;
		tree[u].edges.push_back(Edge(v, l));
		tree[v].edges.push_back(Edge(u, l));
	}
	tree[0].maxTreeSize = treeSize = N;
	root = 0;
	getRoot(1, 1);
	solve(root);
	printf("%lld\n", ans);
	return 0;
}

