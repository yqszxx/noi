#include <cstdio>

using namespace std;

int f[1000]; // f[i]表示i的父节点
int ch[1000][2]; // ch[i][0]表示i的左儿子, ch[i][1]是右儿子
int key[1000]; // key[i]表示i的关键字，就是i节点上存的值
int cnt[1000]; // cnt[i]表示i节点的关键字的出现次数，相当于权值
int size[1000]; // size[i]表示i子树的大小，包括i
int sz; //整棵树的大小
int root; //整棵树的根

void LDR(int now)
{
	if (ch[now][0]) LDR(ch[now][0]);
	for (int i = 1; i <= cnt[now]; i++) {
		printf("%d ", key[now]);
	}
	if (ch[now][1]) LDR(ch[now][1]);
}

void print(int now)
{
	printf("node[%d]:\nfather:\t%d\nlson:\t%d\nrson:\t%d\nkey:\t%d\ncnt:\t%d\nsize:\t%d\n", now, f[now], ch[now][0], ch[now][1], key[now], cnt[now], size[now]);
}

void interDebug()
{
	char c = 0;
	printf("root = %d, treesiez = %d\n", root, sz);
	int now = root;
	while (c != 'q') {
		if (c == '\n') print(now);
		switch (c) {
			case 'l':
				if (!ch[now][0]) {
					printf("no such son\n");
					c = getchar();
					break;
				}
				now = ch[now][0];
				c = getchar();
				break;
			case 'r':
				if (!ch[now][1]) {
					printf("no such son\n");
					c = getchar();
					break;
				}
				now = ch[now][1];
				c = getchar();
				break;
			case 'f':
				if (!f[now]) {
					printf("no father\n");
					c = getchar();
					break;
				}
				now = f[now];
				c = getchar();
				break;
			default:
				c = getchar();
				break;
		}
	}
}

void clear(int x) //将x节点清零，用于删除后
{
	ch[x][0] = ch[x][1] = f[x] = cnt[x] = key[x] = size[x] = 0;
}

int get(int x) //判断x节点是他的父亲的哪一个儿子，0-L;1-R
{
	return ch[f[x]][1] == x;
}

void update(int x) //更新x节点的size值，用于修改后
{
	if (x) {
		size[x] = cnt[x];
		if (ch[x][0]) size[x] += size[ch[x][0]];
		if (ch[x][1]) size[x] += size[ch[x][1]];
	}
}

void rotate(int x)
{
	int fx = f[x], ffx = f[fx];
	int which = get(x); // ->具体实现步骤1
	ch[fx][which] = ch[x][which ^ 1]; f[ch[fx][which]] = fx; // ->具体实现步骤2
	f[fx] = x; ch[x][which ^ 1] = fx; // ->具体实现步骤3
	f[x] = ffx; // ->具体实现步骤4
	if (ffx) {
		ch[ffx][ch[ffx][1] == fx] = x; // ->具体实现步骤5
	}
	update(fx); update(x); // ->具体实现步骤6
}

void splay(int x) // 将x旋转到根
{
	for (int fx; (fx = f[x]); rotate(x)) {
		if (f[fx]) {
			rotate((get(x) == get(fx)) ? fx/*一字型*/ : x/*之字型*/);
		}
	}
	root = x;
}

void splayTo(int x, int y) { // 将x旋转到y的下面
	for (int fx; (fx = f[x]) != y; rotate(x)) {
		if (f[fx]) {
			rotate((get(x) == get(fx)) ? fx : x);
		}
	}
}

void insert(int v) //插入类似普通二叉树
{
	if (root == 0) { //对应步骤详解1
		sz++;
		ch[sz][0] = ch[sz][1] = f[sz] = 0;
		key[sz] = v;
		cnt[sz] = size[sz] = 1;
		root = sz;
		return;
	}
	int now = root, fa = 0;
	while (true) { //不停向下找直到找到一个可以插入的节点或走到空的叶子新建节点
		if (key[now] == v) { //对应步骤详解2
			cnt[now]++;
			update(now);
			update(fa);
			splay(now);
			break;
		}
		fa = now;
		now = ch[now][key[now] < v]; //小于往右走
		if (now == 0) { //对应步骤详解3
			sz++;
			ch[sz][0] = ch[sz][1] = 0;
			key[sz] = v;
			size[sz] = 1;
			cnt[sz] = 1;
			f[sz] = fa;
			ch[fa][key[fa] < v] = sz;
			update(fa);
			splay(sz);
			break;
		}
	}
}

int find(int v) //查询v的排名
{
	int ans = 0, now = root; //详解步骤1，初始化
	while (true) {
		if (v < key[now]) { //详解步骤2
			now = ch[now][0];
		} else { //详解步骤3
			ans += (ch[now][0] ? size[ch[now][0]] : 0);
			if (v == key[now]) {
				splay(now);
				return ans + 1;
			}
			ans += cnt[now];
			now = ch[now][1];
		}
	}
}

int findx(int x) //查询排名为x的值
{
	int now = root;
	while (true) {
		if (ch[now][0] && x <= size[ch[now][0]]) {
			now = ch[now][0];
		} else {
			int tmp = (ch[now][0] ? size[ch[now][0]] : 0) + cnt[now];
			if (x <= tmp) {
				return key[now];
			}
			x -= tmp;
			now = ch[now][1];
		}
	}
}

int pre() //求根左子树最右边的节点
{
	int now = ch[root][0];
	while (ch[now][1]) {
		now = ch[now][1];
	}
	return now;
}

int nxt() //求根右子树最左边的节点
{
	int now = ch[root][1];
	while (ch[now][0]) {
		now = ch[now][0];
	}
	return now;
}

void del(int x) //删除一个值为x的节点
{
	find(x); //将值为x的节点旋转到根，下来的操作都是要删除根
	if (cnt[root] > 1) { //根节点上有多个值
		cnt[root]--; //直接去掉其中的一个值
		return; //返回
	}
	if (!ch[root][0] && !ch[root][1]) { //树上只有根节点一个节点
		clear(root); //删除根节点
		return; //返回
	}
	//根节点只有一个儿子的情况：将树根设成根节点唯一的儿子，删除旧的根节点
	if (!ch[root][0]) {
		int oldRoot = root;
		root = ch[root][1];
		f[root] = 0;
		clear(oldRoot);
		return;
	} else if (!ch[root][1]) {
		int oldRoot = root;
		root = ch[root][0];
		clear(oldRoot);
		return;
	}
	//如果运行到这里说明根节点有两个儿子
	int leftBig = pre(); //找到新根（根节点左子树最大的一个节点）
	int oldRoot = root;
	splay(leftBig); //把新根旋转到根的位置
	f[ch[oldRoot][1]] = root; //这一行和下一行是把原先x所在节点（旧根）的右子树接在新根右子树的位置上，事实上这两步完成后整棵树和旧根就已经没关系了
	ch[root][1] = ch[oldRoot][1];
	clear(oldRoot); //清空旧根
	update(root); //更新新根大小数据
}



int main()
{
	int v, w;
	char c = getchar();
	while (c != 'Q') {
		switch (c) {
			case 't':
				scanf("%d%d", &v, &w);
				splayTo(v, w);
				printf("%d is now just under %d\n", v, w);
				c = getchar();
			case 'd':
				printf("entering debug mode\n");
				interDebug();
				c = getchar();
				break;
			case 'i':
				scanf("%d", &v);
				insert(v);
				printf("insert(%d) done\n", v);
				c = getchar();
				break;
			case 'f':
				scanf("%d", &v);
				printf("find(%d) = %d\n", v, find(v));
				c = getchar();
				break;
			case 'x':
				scanf("%d", &v);
				printf("findx(%d) = %d\n", v, findx(v));
				c = getchar();
				break;
			case 's':
				scanf("%d", &v);
				splay(v);
				printf("splay(%d) done\n", v);
				c = getchar();
				break;
			case 'p':
				LDR(root);
				printf("\n");
				c = getchar();
				break;
			case 'r':
				scanf("%d", &v);
				del(v);
				printf("del(%d) done\n", v);
				c = getchar();
				break;
			default:
				c = getchar();
				break;
		}
	}
	return 0;
}
