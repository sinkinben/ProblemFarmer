#include<iostream>
#define N 1000
int tree[N]={0};
//含路径压缩优化的并查集
int findRoot(int x)
{
	int tmp;
	if(tree[x]==-1)
		return x;
	else
	{
		tmp = findRoot(tree[x]);
		tree[x] = tmp;
		return tmp;
	}
} 
using namespace std;
int main()
{
	int n;	//点数
	int m;	//边数 
	cin>>n>>m; 
	//开始n个点均是孤立的
	for(int i=1;i<=n;i++) 
		tree[i]=-1;
	
	while(m--)
	{
		int a,b,c;	//c是权值，此处无用 
		scanf("%d %d %d",&a,&b,&c);
		a = findRoot(a);
		b = findRoot(b);
		if(a!=b)
			tree[a]=b;
	}
	
	int ans=0;
	//计算连通分量的个数
	for(int i=1;i<=n;i++)
		if(tree[i]==-1)
			ans++;
	printf("%d\n",ans); 
	
	//输出tree
	for(int i=1;i<=n;i++) 
		cout<<tree[i]<<' ';
	cout<<endl;
	//若图是联通的，则findRoot(i)==findRoot(j)恒为1
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			cout<<(findRoot(i)==findRoot(j))<<endl;
		} 
	 } 
}


