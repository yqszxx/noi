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

int MOD = 1000000007;

char str1[1000050];
char* str;

#include <cstring>

bool eq(int a, int b)
{
	for (int i = 1; i <= a; i++) {
		if (str[i] != str[b - a + i]) return false;
	}
	return true;
}

int getNum(int a)
{
	if (a == 1) return 0;
	int ret = 0;
	for (int i = 1; i <= a / 2; i++) {
		if (eq(i, a)) {
			ret = i;
		}
	}
	return ret;
}

int tmain()
{
	int ans = 1;
	gets(str1);
	int len = strlen(str1);
	str = str1 - 1;
	for (int i = 1; i <= len; i++) {
		ans = (1LL * ans * (getNum(i) + 1)) % MOD;
	}
	printf("%d\n", ans);
	return 0;
}

int main()
{
	int T = getInt();
	while (T--) tmain();
	return 0;
}

