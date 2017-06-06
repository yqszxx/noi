#include <cstdio>
#define INT_MAX 0x7fffffff
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
	return l + (int)((double)rand() / RAND_MAX * INT_MAX) % (r - l + 1);
}

const int MAXW = 10, MAXC = 10000;

int rc[100050];
#include <vector>
#include <algorithm>
vector<int> c[100050];
vector<int>::iterator found;
int x, y;
int N, Q, cmd;
int main()
{
	srand(time(0));
	N = 100000;
	Q = 100000;
	printf("%d %d\n", N, Q);
	for (int i = 1; i <= N; i++) {
		rc[i] = getRand(1, MAXC);
		c[rc[i]].push_back(i);
		printf("%d %d\n", getRand(1, MAXW), rc[i]);
	}
	for (int i = 2; i <= N; i++) {
		printf("%d %d\n", i, getRand(1, i - 1));
	}
	for (int i = 1; i <= Q; i++) {
		cmd = getRand(1, 4);
		switch (cmd) {
			case 1:
				x = getRand(1, N);
				y = c[rc[x]][getRand(1, N) % c[rc[x]].size()];
				printf("QS %d %d\n", x, y);
				break;
			case 2:
				x = getRand(1, N);
				y = c[rc[x]][getRand(1, N) % c[rc[x]].size()];
				printf("QM %d %d\n", x, y);
				break;
			case 3:
				x = getRand(1, N);
				y = getRand(1, N);
				found = find(c[rc[x]].begin(), c[rc[x]].end(), x);
				c[rc[x]].erase(found);
				rc[x] = y;
				c[y].push_back(x);
				printf("CC %d %d\n", x, y);
				break;
			case 4:
				printf("CW %d %d\n", getRand(1, N), getRand(1, 10));
				break;
		}
	}
	return 0;
}

