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
	for (int i = 0; i <= 10000; i++) {
		for (int i = 0; i < 10; i++) {
			putchar(getRand('a', 'z'));
		}
		putchar('\n');
	}
	putchar('\n');
	for (int i = 0; i <= 10000; i++) {
		for (int i = 0; i <= 3; i++) {
			putchar(getRand('a', 'z'));
		}
		putchar('\n');
	}
	return 0;
}

