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

const int MAXN = 50000;

int A[MAXN + 50];
int segTree[MAXN * 4 + 50];

#define LEFT(x) ((x) << 1)
#define RIGHT(x) (((x) << 1) | 1)
#define FATHER(x) ((x) >> 1)

void build(int root, int begin, int end) //以root为根建立覆盖区间[begin, end]的线段树
{
	if (begin == end) {
		segTree[root] = A[begin];
	} else {
		int mid = (begin + end) >> 1;
		build(LEFT(root), begin, mid); //在root左子树建立覆盖区间[begin, mid]的线段树
		build(RIGHT(root), mid + 1, end); //在root右子树...
		//计算自己的值（回溯）
		segTree[root] = segTree[LEFT(root)] + segTree[RIGHT(root)];
	}
}

int x, y;
void modify(int root, int begin, int end)
{
	if (begin == end) {
		segTree[root] += y;
		return;
	}
	int mid = (begin + end) >> 1;
	if (x <= mid) { //要更新的节点在左子树上
		modify(LEFT(root), begin, mid);
	} else { //在右子树上
		modify(RIGHT(root), mid + 1, end);
	}
	//更新自身（回溯）
	segTree[root] = segTree[LEFT(root)] + segTree[RIGHT(root)];
}

int query(int root, int begin, int end) //以root为根的子树覆盖了[begin, end]这一区间
{
	if (begin > y || end < x) return 0;
	int ret = 0;
	if (x <= begin && end <= y) return segTree[root];
	int mid = (begin + end) >> 1;
	ret += query(LEFT(root), begin, mid);
	ret += query(RIGHT(root), mid + 1, end);
	return ret;
}

char cmd[10];
int T, N;
int main()
{
	//freopen("data.in", "r", stdin);
	T = getInt();
	for (int t = 1; t <= T; t++) {
		printf("Case %d:\n", t);
		N = getInt();
		for (int i = 1; i <= N; i++) {
			A[i] = getInt();
		}
		build(1, 1, N);
		while (true) {
			scanf("%s", cmd);
			if (cmd[0] == 'A') {
				x = getInt(); y = getInt();
				modify(1, 1, N);
			} else if (cmd[0] == 'S') {
				x = getInt(); y = -getInt();
				modify(1, 1, N);
			} else if (cmd[0] == 'Q') {
				x = getInt(); y = getInt();
				printf("%d\n", query(1, 1, N));
			} else {
				break;
			}
		}
	}
	return 0;
}

