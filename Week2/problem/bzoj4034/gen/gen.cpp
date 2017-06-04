#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <set>

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

inline int getRand(int l, int r)
{
	if (l == r) return l;
	int c = rand() % (r - l) + l;
	if (c == r - 1 && rand() % 2) c++;
	return c;
}

int N, M, v, cmd;
set<int> vs[100050];

int main()
{
	srand(time(NULL));
	N = getRand(10, 50);
	M = getRand(10, 20);
	printf("%d %d\n", N, M);
	for (int i = 1; i <= N; i++) {
		printf("%d", getRand(1, 10));
		if (i != N) printf(" ");
	}
	printf("\n");
	for (int i = 2; i <= N; i++) {
		v = getRand(1, i - 1);
		printf("%d %d\n", i, v);
	}
	for (int i = 1; i <= M; i++) {
		cmd = getRand(1, 3);
		printf("%d ", cmd);
		if (cmd == 1) {
			printf("%d %d\n", getRand(1, N), getRand(1, 10));
		} else if (cmd == 2) {
			printf("%d %d\n", getRand(1, N), getRand(1, 10));
		} else {
			printf("%d\n", getRand(1, N));
		}
	}
	return 0;
}

