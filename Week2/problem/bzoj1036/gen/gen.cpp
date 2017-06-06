#include <cstdio>
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

inline int getRand(int l, int r)
{
	if (l == r) return l;
	int c = rand() % (r - l) + l;
	if (c == r - 1 && rand() % 2) c++;
	return c;
}

int main()
{
	srand(time(NULL));
	int N, Q, cmd;
	freopen("data.in", "w", stdout);
	N = 30000; //getRand(1, 10);
	Q = 200000; //getRand(1, 100);
	printf("%d\n", N);
	for (int i = 2; i <= N; i++) {
		printf("%d %d\n", i, 1);//getRand(1, i - 1));
	}
	for (int i = 1; i <= N; i++) {
		printf("%d", getRand(-30000, 30000));
		if (i != N) printf(" ");
	}
	printf("\n");
	printf("%d\n", Q);
	for (int i = 1; i <= Q; i++) {
		cmd = getRand(1, 3);
		if (cmd == 1) {
			printf("QMAX %d %d\n", getRand(1, N), getRand(1, N));
		} else if (cmd == 2) {
			printf("QSUM %d %d\n", getRand(1, N), getRand(1, N));
		} else {
			printf("CHANGE %d %d\n", getRand(1, N), getRand(-30000, 30000));
		}
	}
	return 0;
}

