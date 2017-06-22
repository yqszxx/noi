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

int N, K, u, v, l;

struct Edge {
	int to;
	int length;
	Edge(int _to, int _length): to(_to), length(_length) {};
};
typedef vector<Edge>::iterator P;

struct TreeNode {
	vector<Edge> edges;
	int subTreeSize;
	bool done;
	int maxTreeSize;
	int lengthFromRoot;
} tree[10050];
vector<int> length;
int ans;
int treeSize, root;

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

void getLength(int now, int from)
{
	length.push_back(tree[now].lengthFromRoot);
	for (P p = tree[now].edges.begin(); p != tree[now].edges.end(); p++) {
		if ((*p).to != from && !tree[(*p).to].done) {
			tree[(*p).to].lengthFromRoot = tree[now].lengthFromRoot + (*p).length;
			getLength((*p).to, now);
		}
	}
}

int calc(int now, int init)
{
	length.clear();
	tree[now].lengthFromRoot = init;
	getLength(now, 0);
	sort(length.begin(), length.end());
	int ret = 0;
	int l = 0, r = length.size() - 1;
	while (l < r) {
		if (length[l] + length[r] <= K) {
			ret += r - l;
			l++;
		} else {
			r--;
		}
	}
	return ret;
}

void solve(int now)
{
	ans += calc(now, 0);
	tree[now].done= true;
	for (P p = tree[now].edges.begin(); p != tree[now].edges.end(); p++) {
		if (!tree[(*p).to].done) {
			ans -= calc((*p).to, (*p).length);
			tree[0].maxTreeSize = treeSize = tree[(*p).to].subTreeSize;
			root = 0;
			getRoot((*p).to, 0);
			solve(root);
		}
	}
}

int main()
{
	//freopen("data.in", "r", stdin);
	while (1) {
		N = getInt();
		K = getInt();
		if (N == 0 && K == 0) {
			break;
		}
		//Init
		treeSize = N;
		ans = 0;
		for (int i = 1; i <= N; i++) {
			tree[i].edges.clear();
			tree[i].done = false;
			tree[i].subTreeSize = 0;
			tree[i].maxTreeSize = 0;
			tree[i].lengthFromRoot = 0;
		}
		tree[0].maxTreeSize = N;
		//End Init
		for (int i = 1; i < N; i++) {
			u = getInt();
			v = getInt();
			l = getInt();
			tree[u].edges.push_back(Edge(v, l));
			tree[v].edges.push_back(Edge(u, l));
		}
		root = 0;
		getRoot(1, 1);
		solve(root);
		printf("%d\n", ans);
	}
	return 0;
}

