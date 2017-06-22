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
#include <climits>

inline int getRand(int l, int r)
{
	        return l + (int)((double)rand() / RAND_MAX * INT_MAX) % (r - l + 1);
}

int main()
{
	freopen("../data.in", "w", stdout);
	srand(time(0));
	int N = 100000;
	printf("%d\n", N);
	for (int i = 1; i <= 50000; i++) {
		printf("1 %d\n", i);
	}
	for (int i = 50001; i <= N; i++) {
		int op = getRand(3, 6);
		printf("%d %d\n", op, getRand(1, 50000));
	}
	return 0;
}

