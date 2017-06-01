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

int N, R, cur = 1, ind;
int C[700050];

#define LOWBIT(x) ((x) & (-(x)))

void init()
{
	int x = 1;
	for (int i = 1; i <= N; x = ++i) {
		while (x <= N) {
			C[x]++;
			x += LOWBIT(x);
		}
	}
}

int find(int sum)
{
	int ind = 0,now = 0;
	for (int i = (1 << 20); i; i >>= 1) {
		if (ind + i <= N && now + C[ind + i] <= sum) {
			ind += i;
			now += C[ind];
		}
	}
	return ind;
}

void add(int ind, int x)
{
	while (ind <= N) {
		C[ind] += x;
		ind += LOWBIT(ind);
	}
}

void debug()
{
	for (int i = 1; i <= N; i++) {
		printf("C[%d]=%d\n", i, C[i]);
	}
}

int main()
{
	N = getInt();
	init();
	for (int i = N; i >= 1; i--) {
		//debug();
		R = getInt();
		cur += R;
		cur %= i;
		if (cur == 0) cur = i;
		ind = find(cur - 1) + 1;
		add(ind, -1);
		printf("%d\n", ind);
		//debug();
	}
	return 0;
}

