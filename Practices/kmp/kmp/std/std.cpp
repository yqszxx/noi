#include<cstdio>
#include<cstring>
using namespace std;

const int MAXW=1000001,MAXT=1000001;
char W[MAXW],T[MAXT];
int next[MAXW];
int lenW,lenT;

void getnext(int lenW)
{
	int i=0,j=-1;
	next[i]=-1;
	while(i<lenW) {
		if(j==-1||W[i]==W[j]) {
			next[++i]=++j;
		}
		else j=next[j];
	}
}

int kmp(int pos,int lenW,int lenT)
{
	int i=pos,j=0,ans=0;
	while(i<lenT) {
		if(T[i]==W[j]||j==-1) ++i,++j;
		else j=next[j];
		if(j==lenW) {
			ans++;
			j=next[j-1];
			i--;
		}
	}
	return ans;
}


int main()
{
	freopen("../data.in", "r", stdin);
	int n;
	scanf("%d",&n);
	while(n--) {
		scanf("%s%s",T,W);
		lenW=strlen(W);
		lenT=strlen(T);
		getnext(lenW);
		for (int i = 0; i < lenW; i++) {
			printf("%d ", next[i]);
		}
		puts("");
		printf("%d\n",kmp(0,lenW,lenT));
	}
	return 0;
}
