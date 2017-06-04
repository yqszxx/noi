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

int N, M, cmd;

inline int getRand(int l, int r)
{
	if (l == r) return l;
	int c = rand() % (r - l) + l;
	if (c == r - l && rand() % 2) c++;
	return c;
}

int main()
{
	srand(time(NULL));
	N = 10;
	M = 100;
	printf("%d %d\n", N, M);
	printf("%d %d\n", 0, getRand(1, 100));
	for (int i = 2; i <= N; i++) {
		printf("%d %d\n", getRand(1, i - 1), getRand(1, 100));
	}
	for (int i = 1; i <= M; i++) {
		cmd = getRand(1, 3);
		if (cmd == 1) {
			printf("V %d %d\n", getRand(1, N), getRand(1, 100));
		} else if (cmd == 2) {
			printf("E %d\n", getRand(1, N));
		} else {
			printf("Q %d\n", getRand(1, N));
		}
	}
	return 0;
}

