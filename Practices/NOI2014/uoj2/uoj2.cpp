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
struct opr {
	int type;
	int t;
} ops[100050];
char op[10];

int check(int n)
{
	for (int i = 1; i <= N; i++) {
		if (ops[i].type == 0) {
			n &= ops[i].t;
		} else if (ops[i].type == 1) {
			n |= ops[i].t;
		} else {
			n ^= ops[i].t;
		}
	}
	return n;
}

int main()
{
	N = getInt();
	M = getInt();
	for (int i = 1; i <= N; i++) {
		scanf("%s", op);
		ops[i].t = getInt();
		if (op[0] == 'A') {
			ops[i].type = 0;
		} else if (op[0] == 'O') {
			ops[i].type = 1;
		} else {
			ops[i].type = 2;
		}
	}
	int ans = 0;
	for (int i = 30; i >= 0; i--) {
		if ((check(0) >> i) & 1) continue;
		if (((M >> i) & 1) || (ans + (1 << i) <= M)) {
			if ((check(1 << i) >> i) & 1) {
				ans += (1 << i);
			}
		}
	}
	printf("%d\n", check(ans));
	return 0;
}

