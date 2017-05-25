//10.33
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

int N, M, x, l, r, sqr;
#include <cmath>
#define LOWBIT(x) ((x) & (-(x)))
int d[100050];
int ne[100050];
long long C[100050];

void add(int a, int b)
{
	while (a <= N) {
		C[a] += b;
		a += LOWBIT(a);
	}
}

long long query(int a)
{
	long long ret = 0;
	while (a > 0) {
		ret += C[a];
		a -= LOWBIT(a);
	}
	return ret;
}

int next(int a)
{
	if (ne[a] == 0 || ne[a] == a) return ne[a] = a;
	else return ne[a] = next(ne[a]);
}

int main()
{
	N = getInt();
	for (int i = 1; i <= N; i++) {
		d[i] = getInt();
		if (d[i] == 0 || d[i] == 1) {
			ne[i] = i + 1;
		}
		add(i, d[i]);
	}
	M = getInt();
	for (int i = 1; i <= M; i++) {
		x = getInt(); l = getInt(); r = getInt();
		if (x == 1) {
			printf("%lld\n", query(r) - query(l - 1));
		} else {
			for (int j = next(l); j <= r; j = next(j + 1)) {
				sqr = sqrt(d[j]);
				add(j, sqr - d[j]);
				d[j] = sqr;
				if (d[j] == 1) {
					ne[j] = j + 1;
				}
			}
		}
	}
	return 0;
}

