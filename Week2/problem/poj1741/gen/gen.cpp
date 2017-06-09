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

#include <cstdlib>
#include <ctime>

inline int getRand(int l, int r)
{
	const int INT_MAX = 0x7fffffff;
	return l + (int)((double)rand() / RAND_MAX * INT_MAX) % (r - l + 1);
}

int T, N, K;

int main()
{
	T = 20;
	while (T--) {
		N = 10000;
		K = 1000;
		printf("%d %d\n", N, K);
		for (int i = 2; i <= N; i++) {
			printf("%d %d %d\n", i - 1, i, getRand(1, 10));
		}
	}
	printf("0 0\n");
	return 0;
}

