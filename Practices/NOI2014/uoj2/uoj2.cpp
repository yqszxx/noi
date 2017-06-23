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

int N, M;
char cmd[10];
int cmds[100050][2];

inline int solve(int a)
{
	for (int i = 1; i <= N; i++) {
		if (cmds[i][0] == 1) {
			a = a & cmds[i][1];
		} else if (cmds[i][0] == 2) {
			a = a | cmds[i][1];
		} else {
			a = a ^ cmds[i][1];
		}
	}
	return a;
}

int main()
{
	N = getInt();
	M = getInt();
	for (int i = 1; i <= N; i++) {
		scanf("%s%d", cmd, &cmds[i][1]);
		if (cmd[0] == 'A') {
			cmds[i][0] = 1;
		} else if (cmd[0] == 'O') {
			cmds[i][0] = 2;
		} else {
			cmds[i][0] = 3;
		}
	}
	int t, ans = 0;
	for (t = 1; t <= M; t <<= 1);
	for (t >>= 1; t; t >>= 1) {
		if (solve(0) & t) {
			continue;
		} else if ((solve(t) & t) && ((ans + t) <= M)) {
			ans += t;
		}
	}
	printf("%d\n", solve(ans));
	return 0;
}

