#include <cstdio>
#include <cmath>

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

int N;
int data[100050];
long long C[100050];
int next[100050];

#define LOWBIT(x) ((x) & (-(x)))

void add(int x, int y)
{
	//printf("ADD(%d, %d)\n", x, y);
	if (x == 0) return;
	while (x <= N) {
		C[x] += y;
		x += LOWBIT(x);
	}
}

long long query(int x)
{
	//printf("QUERY(%d)\n", x);
	if (x <= 0) return 0;
	long long ret = 0;
	while (x > 0) {
		ret += C[x];
		x -= LOWBIT(x);
	}
	return ret;
}

int getNext(int x)
{
	if (next[x] == x) return x;
	return next[x] = getNext(next[x]);
}

int main()
{
	N = getInt();
	for (int i = 1; i <= N; i++) {
		data[i] = getInt();
		add(i, data[i]);
		if (data[i] == 0 || data[i] == 1) {
			next[i] = i + 1;
		} else {
			next[i] = i;
		}
	}
	next[N + 1] = N + 1;
	int M = getInt(), x, l, r;
	while (M--) {
		x = getInt(); l = getInt(); r = getInt();
		if (x & 1) {
			printf("%lld\n", query(r) - query(l - 1));
		} else {
			for (int i = l; i <= r; i++) {
				if (data[i] == 1 || data[i] == 0) i = getNext(i);
				if (i > r) break;
				add(i, ((int)sqrt(data[i])) - data[i]);
				data[i] = sqrt(data[i]);
				if (data[i] == 1) {
					next[i] = i + 1;
				}
			}
		}
	}
	return 0;
}

