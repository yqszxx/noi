#include<bits/stdc++.h>
using namespace std;
#define ps(O) path[O].size()
#define bs b.as.size()
inline int R()
{
		int r=0;char c=getchar();
			while(c<'0'||c>'9') c=getchar();
				while(c>='0'&&c<='9') {r=r*10+c-'0';c=getchar();}
					return r;
}
const int maxn=100005;
vector<int> path[maxn];
struct node
{
		int anc,ad;
			bool ac;
				vector<int> as;
					node(int a=0){anc=a;ac=0;}
}ns[maxn];
int cur,d[maxn],sz[maxn],bl[maxn],fa[maxn];
int dfs(int o)
{
		sz[o]=1;
			for(int i=0;i<ps(o);i++) 
					{
								int to=path[o][i];
										d[to]=d[o]+1;
												sz[o]+=dfs(to);
													}
														return sz[o];
}
void set_l(int o,int c)
{
		bl[o]=c;
			int z=100001,to;
				for(int i=0;i<ps(o);i++) 
						{
									to=path[o][i];
											if(sz[to]>sz[z]) z=to;
												}
													if(z==100001) return;
														set_l(z,c);
															for(int i=0;i<ps(o);i++) 
																	{
																				to=path[o][i];
																						if(to==z) continue;
																								ns[cur]=node(to);cur++;
																										set_l(to,cur-1);
																											}
}
int ins(int o,int f)
{
		node &b=ns[bl[o]];
			if(f>=0) b.as.push_back(f);
				int ans=0;
					if(b.ac)
							{
										if(b.ad>=d[o]) return 0;
												ans=d[o]-b.ad;b.ad=d[o];
													}
														else
																{
																			b.ac=true;
																					ans=d[o]-d[b.anc]+1;
																							b.ad=d[o];
																									if(b.anc!=0) ans+=ins(fa[b.anc],b.anc);
																										}
																											return ans;
}
int uni(int o)
{
		node &b=ns[bl[o]];
			if(!b.ac) return 0;
				int ans=0;
					if(o==b.anc)
							{
										ans=b.ad-d[o]+1;
												for(int i=0;i<bs;i++) ans+=uni(b.as[i]);
														b.ac=false;
																b.as.clear();
																	}
																		else
																				{
																							if(b.ad<d[o]) return 0;
																									ans=b.ad-d[o]+1;
																											for(int i=0;i<bs;i++) if(d[b.as[i]]>d[o]) ans+=uni(b.as[i]);
																													b.ad=d[o]-1;
																														}
																															return ans;
}
char s[20];
int main()
{
		int n=R(),a,q;
			for(int i=1;i<n;i++)
					{
								a=R();
										path[a].push_back(i);
												fa[i]=a;
													}
														dfs(0);
															ns[cur]=node(0);cur++;
																set_l(0,0);
																	q=R();
																		while(q--)
																				{
																							scanf("%s",s);
																									if(s[0]=='i') printf("%d\n",ins(R(),-1));
																											else printf("%d\n",uni(R()));
																												}
																													return 0;
}
