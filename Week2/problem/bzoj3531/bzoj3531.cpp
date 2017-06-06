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

int N, Q, x, y, u, v;
char cmd[10];
int lcaOfXY;

#include <vector>
const int INF = 0x3f3f3f3f;
struct TreeNode {
        int w, c;
        vector<int> sons;
        int father;
        int subTreeSize;
        int depth;
        int jmpTo[20];
        int chainTop;
        int posInSegTree;
} tree[100050];
int dfsNow, depthNow, posInSegTreeNow;

int rootOfC[100050];

struct SegTreeNode {
        int maxv;
        long long sumv;
        int leftSon, rightSon;
} segTree[10000050];
int segTreeAllocCnt;

void dfs(int root, int from)
{
        tree[root].depth = ++depthNow;
        tree[root].father = from;
        //LCA
        tree[root].jmpTo[0] = tree[root].father;
        for (int i = 1; i <= 17; i++) {
                tree[root].jmpTo[i] = tree[tree[root].jmpTo[i - 1]].jmpTo[i - 1];
        }
        //END LCA
        tree[root].subTreeSize = dfsNow++;
        int sonCnt = tree[root].sons.size();
        for (int i = 0; i < sonCnt; i++) {
                if (tree[root].sons[i] != tree[root].father) {
                        dfs(tree[root].sons[i], root);
                }
        }
        tree[root].subTreeSize = dfsNow - tree[root].subTreeSize;
        depthNow--;
}

void hld(int root)
{
        tree[root].posInSegTree = ++posInSegTreeNow;
        int sonCnt = tree[root].sons.size();
        int heaviestSon = -1, heaviestSonSize = -1;
        for (int i = 0; i < sonCnt; i++) {
                if (tree[root].sons[i] != tree[root].father) {
                        if (heaviestSonSize < tree[tree[root].sons[i]].subTreeSize) {
                                heaviestSon = tree[root].sons[i];
                                heaviestSonSize = tree[tree[root].sons[i]].subTreeSize;
                        }
                }
        }
        if (heaviestSon != -1) {
                tree[heaviestSon].chainTop = tree[root].chainTop;
                hld(heaviestSon);
                for (int i = 0; i < sonCnt; i++) {
                        if (tree[root].sons[i] != tree[root].father &&
                                tree[root].sons[i] != heaviestSon
                        ) {
                                tree[tree[root].sons[i]].chainTop = tree[root].sons[i];
                                hld(tree[root].sons[i]);
                        }
                }
        } else {
                return;
        }
}

inline void maintain(int node)
{
        segTree[node].maxv = max(segTree[segTree[node].leftSon].maxv, segTree[segTree[node].rightSon].maxv);
        segTree[node].sumv = segTree[segTree[node].leftSon].sumv + segTree[segTree[node].rightSon].sumv;
}

/**
 * Modify the `target` postion in the segTree which roots at `root` and covers the interval [`l`, `r`] to `value`.
 * If the `root` node does not exist, alloc one node for it.
 */
void modify(int &root, int l, int r, int target, int value)
{
        if (!root) root = ++segTreeAllocCnt;
        if (l == r) {
                if (l == target) {
                        segTree[root].maxv = value;
                        segTree[root].sumv = value;
                }
                return;
        }
        int mid = (l + r) >> 1;
        if (target <= mid) modify(segTree[root].leftSon, l, mid, target, value);
        else modify(segTree[root].rightSon, mid + 1, r, target, value);
        maintain(root);
}

inline int max(int a, int b)
{
        return a > b ? a : b;
}

long long querySum(int root, int l, int r, int begin, int end)
{
        if (begin > end) swap(begin, end);
        if (!root) return 0;
        if (begin <= l && r <= end) {
                return segTree[root].sumv;
        }
        if (end < l || r < begin) {
                return 0;
        }
        int mid = (l + r) >> 1;
        long long ret = 0;
        if (begin <= mid) {
                ret += querySum(segTree[root].leftSon, l, mid, begin, end);
        }
        if (end > mid) {
                ret += querySum(segTree[root].rightSon, mid + 1, r, begin, end);
        }
        return ret;
}

int queryMax(int root, int l, int r, int begin, int end)
{
        if (begin > end) swap(begin, end);
        if (!root) return -INF;
        if (begin <= l && r <= end) {
                return segTree[root].maxv;
        }
        if (end < l || r < begin) {
                return -INF;
        }
        int mid = (l + r) >> 1;
        int ret = -INF;
        if (begin <= mid) {
                ret = max(ret, queryMax(segTree[root].leftSon, l, mid, begin, end));
        }
        if (end > mid) {
                ret = max(ret, queryMax(segTree[root].rightSon, mid + 1, r, begin, end));
        }
        return ret;
}

inline long long solveSum(int c, int x, int y)
{
        long long ret = 0;
        while (tree[x].chainTop != tree[y].chainTop) {
                ret += querySum(
                        rootOfC[c],
                        1,
                        N,
                        tree[tree[x].chainTop].posInSegTree,
                        tree[x].posInSegTree
                );
                x = tree[tree[x].chainTop].father;
        }
        ret += querySum(
                rootOfC[c],
                1,
                N,
                tree[x].posInSegTree,
                tree[y].posInSegTree
        );
        return ret;
}

inline int solveMax(int c, int x, int y)
{
        int ret = -INF;
        while (tree[x].chainTop != tree[y].chainTop) {
                ret = max(ret, queryMax(
                        rootOfC[c],
                        1,
                        N,
                        tree[tree[x].chainTop].posInSegTree,
                        tree[x].posInSegTree
                ));
                x = tree[tree[x].chainTop].father;
        }
        ret = max(ret, queryMax(
                rootOfC[c],
                1,
                N,
                tree[x].posInSegTree,
                tree[y].posInSegTree
        ));
        return ret;
}

int lca(int x, int y)
{
        if (tree[x].depth < tree[y].depth) swap(x, y);
        int t = tree[x].depth - tree[y].depth;
        for (int i = 0; i <= 17; i++) {
                if (t & (1 << i)) {
                        x = tree[x].jmpTo[i];
                }
        }
        for (int i = 17; i >= 0; i--) {
                if (tree[x].jmpTo[i] != tree[y].jmpTo[i]) {
                        x = tree[x].jmpTo[i];
                        y = tree[y].jmpTo[i];
                }
        }
        if (x == y) return x;
        else return tree[x].father;
}

int main()
{
        freopen("data.in", "r", stdin);
        N = getInt();
        Q = getInt();
        for (int i = 1; i <= N; i++) {
                tree[i].w = getInt();
                tree[i].c = getInt();
        }
        for (int i = 1; i < N; i++) {
                u = getInt();
                v = getInt();
                tree[u].sons.push_back(v);
                tree[v].sons.push_back(u);
        }
        dfs(1, 1);
        tree[1].chainTop = 1;
        hld(1);
        for (int i = 1; i <= N; i++) {
                modify(rootOfC[tree[i].c], 1, N, tree[i].posInSegTree, tree[i].w);
        }
        for (int i = 1; i <= Q; i++) {
                scanf("%s", cmd);
                x = getInt();
                y = getInt();
                if (cmd[0] == 'C') {
                        if (cmd[1] == 'C') {
                                modify(rootOfC[tree[x].c], 1, N, tree[x].posInSegTree, 0); //从旧信仰的线段树里删除节点x
                                tree[x].c = y;
                                modify(rootOfC[tree[x].c], 1, N, tree[x].posInSegTree, tree[x].w);
                        } else {
                                tree[x].w = y;
                                modify(rootOfC[tree[x].c], 1, N, tree[x].posInSegTree, tree[x].w);
                        }
                } else {
                        lcaOfXY = lca(x, y);
                        if (cmd[1] == 'S') {
                                long long t = solveSum(tree[x].c, x, lcaOfXY) + solveSum(tree[x].c, y, lcaOfXY);
                                if (tree[x].c == tree[lcaOfXY].c) {
                                        t -= tree[lcaOfXY].w;
                                }
                                printf("%lld\n", t);
                        } else {
                                printf("%d\n", max(solveMax(tree[x].c, x, lcaOfXY), solveMax(tree[x].c, y, lcaOfXY)));
                        }
                }
        }
        return 0;
}
