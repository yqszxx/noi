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
#include <climits>
#include <ctime>

int getRand(int l, int r)
{
	return l + (int)((double)rand() / RAND_MAX * INT_MAX) % (r - l + 1);
}

int main()
{
	srand(time(0));
	freopen("data.in", "w", stdout);
	int T = 10;
	printf("%d\n", T);
	for (int i = 1; i <= T; i++) {
		int N = 50000;
		printf("%d\n", N);
		for (int n = 1; n <= N; n++) {
			printf("%d %d %d\n", getRand(1, 1000000000), getRand(1, 1000000000), getRand(0, 1));
		}
	}
	fclose(stdout);
	return 0;
}

