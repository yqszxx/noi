#include <cstdio>
#include <cstdlib>
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

#include <cstring>

struct TrieNode {
	int next[26];
	int cnt;
} trie[10000000];

int trieSz = 0;

char str[200];

void trieInsert(char* str) {
	int len = strlen(str);
	int p = 0;
	for (int i = 0; i < len; i++) {
		int id = str[i] - 'a';
		if (trie[p].next[id] == 0) {
			trie[p].next[id] = ++trieSz;
			p = trieSz;
			trie[p].cnt = 1;
		} else {
			p = trie[p].next[id];
			trie[p].cnt++;
		}
	}
}

int trieFind(char* str)
{
	int len = strlen(str);
	int p = 0;
	for (int i = 0; i < len; i++) {
		int id = str[i] - 'a';
		p = trie[p].next[id];
		if (p == 0) {
			return 0;
		}
	}
	return trie[p].cnt;
}

int main()
{
	freopen("data.in", "r", stdin);
	while (gets(str) && str[0] != '\0') {
		trieInsert(str);
	}
	while (scanf("%s", str) != EOF) {
		printf("%d\n", trieFind(str));
	}
	return 0;
}

