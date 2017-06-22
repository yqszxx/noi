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

int N, op, v;

int f[100050], ch[100050][2], key[100050], cnt[100050], size[100050];
int sz, root;

void clear(int x)
{
	ch[x][0] = ch[x][1] = f[x] = key[x] = cnt[x] = size[x] = 0;
}

int get(int x)
{
	return ch[f[x]][1] == x;
}

void update(int x)
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
	int which = get(x);
	ch[fx][which] = ch[x][which ^ 1]; f[ch[fx][which]] = fx;
	f[fx] = x; ch[x][which ^ 1] = fx;
	f[x] = ffx;
	if (ffx) {
		ch[ffx][ch[ffx][1] == fx] = x;
	}
	update(fx);
	update(x);
}

void splay(int x)
{
	for (int fx; (fx = f[x]); rotate(x)) {
		if (f[fx]) {
			rotate((get(x) == get(fx)) ? fx : x);
		}
	}
	root = x;
}

void insert(int v)
{
	if (root == 0) {
		sz++;
		ch[sz][0] = ch[sz][1] = f[sz] = 0;
		key[sz] = v;
		cnt[sz] = size[sz] = 1;
		root = sz;
		return;
	}
	int now = root, fa = 0;
	while (true) {
		if (key[now] == v) {
			cnt[now]++;
			update(now);
			update(fa);
			splay(now);
			break;
		}
		fa = now;
		now = ch[now][key[now] < v];
		if (now == 0) {
			sz++;
			ch[sz][0] = ch[sz][1] = 0;
			ch[fa][key[fa] < v] = sz;
			f[sz] = fa;
			key[sz] = v;
			cnt[sz] = size[sz] = 1;
			update(fa);
			splay(sz);
			break;
		}
	}
}

int find(int v)
{
	int ans = 0, now = root;
	while (true) {
		if (v < key[now]) {
			if (ch[now][0]) {
				now = ch[now][0];
			} else {
				splay(now);
				return ans + 1;
			}
		} else {
			ans += (ch[now][0] ? size[ch[now][0]] : 0);
			if (v == key[now]) {
				splay(now);
				return ans + 1;
			}
			ans += cnt[now];
			now = ch[now][1];
			if (!now) {
				return -1;
			}
		}
	}
}

int findx(int x)
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
			if (!now) {
				return -1;
			}
		}
	}
}

int pre()
{
	int now = ch[root][0];
	while (ch[now][1]) {
		now = ch[now][1];
	}
	return now;
}

int nxt()
{
	int now = ch[root][1];
	while (ch[now][0]) {
		now = ch[now][0];
	}
	return now;
}

void del(int x)
{
	find(x);
	if (cnt[root] > 1) {
		cnt[root]--;
		return;
	}
	if (!ch[root][0] && !ch[root][1]) {
		clear(root);
		return;
	}
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
	int leftBig = pre();
	int oldRoot = root;
	splay(leftBig);
	f[ch[oldRoot][1]] = root;
	ch[root][1] = ch[oldRoot][1];
	clear(oldRoot);
	update(root);
}

int lth(int v)
{
	insert(v);
	int ret = key[pre()];
	del(v);
	return ret;
}

int gth(int v)
{
	insert(v);
	int ret = key[nxt()];
	del(v);
	return ret;
}

int main()
{
	freopen("data/input1.in", "r", stdin);
	N = getInt();
	for (int i = 1; i <= N; i++) {
		op = getInt();
		switch (op) {
			case 1:
				v = getInt();
				insert(v);
				break;
			case 2:
				v = getInt();
				del(v);
				break;
			case 3:
				v = getInt();
				printf("%d\n", find(v));
				break;
			case 4:
				v = getInt();
				printf("%d\n", findx(v));
				break;
			case 5:
				v = getInt();
				printf("%d\n", lth(v));
				break;
			case 6:
				v = getInt();
				printf("%d\n", gth(v));
				break;
		}
	}
	return 0;
}

