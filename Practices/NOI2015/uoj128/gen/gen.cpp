#include <cstdio>
#include <climits>
#include <cstdlib>
#include <ctime>

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

int getRand(int l, int r)
{
	return l + (int)((double)rand() / RAND_MAX * INT_MAX) % (r - l + 1);
}

int main()
{
	srand(time(0));
	int N = 100000;
	int Q = 100000;
	printf("%d\n", N);
	for (int i = 1; i < N; i++) {
		printf("%d ", 0);//getRand(0, i - 1));
	}
	printf("\n");
	printf("%d\n", Q);
	for (int i = 1; i <= Q; i++) {
		if (getRand(0, 1)) {
			printf("install ");
		} else {
			printf("uninstall ");
		}
		printf("%d\n", getRand(0, N - 1));
	}
	return 0;
}

