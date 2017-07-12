#include <cstdio>
#include <cstring>

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

char str[30050];
int len;

bool chk(int begin, int end)
{
	int mid = (begin + end) >> 1;
	for (int i = 0; i <= mid - begin; i++) {
		if (str[begin + i] != str[mid + 1 + i]) return false;
	}
	return true;
}

int cnt(int begin, int end)
{
	int ret = 0;
	for (int i = begin + 2; i < end; i += 2) {
		if (chk(begin, i - 1) && chk(i, end)) ret++;
	}
	return ret;
}

bool type34()
{
	char c = str[0];
	for (int i = 1; i < len; i++) {
		if (str[i] != c) {
			return false;
		}
	}
	return true;
}

int tmain()
{
	int ans = 0;
	gets(str);
	len = strlen(str);
	if (len < 4) {
		puts("0");
		return 0;
	}
	if (type34()) {
		len--;
		for (int i = 0; i <= len; i++) {
			ans += i * (len - i) / 2;
		}
		printf("%d\n", ans / 2);
		return 0;
	}
	for (int i = 3; i < len; i++) {
		for (int j = 0; j <= i - 3; j++) {
			if ((i - j) % 2 == 0) continue;
			ans += cnt(j, i);
		}
	}
	printf("%d\n", ans);
	return 0;
}

int main()
{
	int T = getInt();
	while (T--) {
		tmain();
	}
	return 0;
}

