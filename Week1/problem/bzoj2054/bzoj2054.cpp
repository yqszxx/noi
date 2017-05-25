//14.10
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

int N, M, p, q, x, y, t;
int C[1000050];
int ne[1000050];

int next(int i)
{
	if (ne[i] == 0 || ne[i] == i) return ne[i] = i;
	else return ne[i] = next(ne[i]);
}

int main()
{
	N = getInt(); M = getInt(); p = getInt(); q = getInt();
	for (int i = M; i > 0; i--) {
		x = ((long long)i * p + q) % N + 1;
		y = ((long long)i * q + p) % N + 1;
		if (x > y) {
			t = x;
			x = y;
			y = t;
		}
		for (int j = next(x); j <= y; j = next(j)) {
			C[j] = i;
			ne[j] = j + 1;
		}
	}
	for (int i = 1; i <= N; i++) {
		printf("%d\n", C[i]);
	}
	return 0;
}

