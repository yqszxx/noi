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

int N;

int main()
{
	N = 6;
	printf("%d\n", N);
	for (int i = 2; i <= N; i++) {
		printf("%d %d %d\n", i - 1, i, i % 2);
	}
	return 0;
}

