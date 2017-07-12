#include <iostream>
#include <cstdio>
#include <cstring>
#define _(d)while(d((c=B[M++]-48)>=0))
#define N 200005
using namespace std;

int M;char B[14516245];
void re(int&v){int c;_(!);v=c;_()v=v*10+c;}
int p[N],k,h[N];
pair<int,int> a[N];
const int HS=131072/2;
struct hash {
		int fs[HS],sz,nx[N],S[N],v[N];
			void clr()
					{sz=0;memset(fs,-1,sizeof(fs));}
						void push(int&s) {
									int x=s&(HS-1);
											for (int i=fs[x];~i;i=nx[i]) if(S[i]==s)
															{s=v[i];return;}
																	S[sz]=s;s=v[sz]=++k;nx[sz]=fs[x];fs[x]=sz++;
																		}
} ha;
int fd(int x) {return p[x]?p[x]=fd(p[x]):x;}
int main() {
	    fread(B,1,14516240,stdin);
			int T,fl,n,m,x,y,z,u,v;
				re(T);
					while (T--) {
								re(n);m=0;fl=0;k=0;
										memset(p,0,sizeof(p));
												ha.clr();
														for (int i=1;i<=n;i++) {
																		re(x),re(y),re(z);ha.push(x);ha.push(y);
																					if (!z) a[m++]=make_pair(x,y);
																								else if ((u=fd(x))!=(v=fd(y)))
																													h[u]>=h[v]?p[v]=u,h[u]+=h[u]==h[v]:p[u]=v;
																															}
																																	while (m--)
																																					if (fd(a[m].first)==fd(a[m].second))
																																										{fl=1;break;}
																																												puts(fl?"NO":"YES");
																																													}
																																														return 0;
}
