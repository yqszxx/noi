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

char str[30000];
char mode[30000];

int slen, mlen;

int next[30000];
#include <cstring>
int match(int startAt)
{
	int ans = 0;
	int i = startAt; // str pointer
	int j = 0; // mode pointer
	while (i < slen) {
		if (str[i] == mode[j] || j == -1) {
			++i;
			++j;
		} else {
			j = next[j];
		}
		if (j == mlen) {
			ans++;
			j = next[j - 1];
			i--;
		}
	}
	return ans;
}

void genNext()
{
	int i = 0;
	int j = -1;
	next[0] = -1;
	while (i < mlen) {
		if (j == -1|| mode[i] == mode[j]) {
			next[++i] = ++j;
		} else {
			j = next[j];
		}
	}
}

int tmain()
{
	gets(str);
	gets(mode);
	slen = strlen(str);
	mlen = strlen(mode);
	genNext();
	for (int i = 0; i < mlen; i++) {
		printf("%d ", next[i]);
	}
	puts("");
	printf("%d\n", match(0));
	return 0;
}

int main()
{
	freopen("data.in", "r", stdin);
	int T = getInt();
	while (T--) tmain();
	return 0;
}
