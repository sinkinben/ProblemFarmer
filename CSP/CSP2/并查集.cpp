#include<iostream>
#define N 1000
int tree[N]={0};
//��·��ѹ���Ż��Ĳ��鼯
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
	int n;	//����
	int m;	//���� 
	cin>>n>>m; 
	//��ʼn������ǹ�����
	for(int i=1;i<=n;i++) 
		tree[i]=-1;
	
	while(m--)
	{
		int a,b,c;	//c��Ȩֵ���˴����� 
		scanf("%d %d %d",&a,&b,&c);
		a = findRoot(a);
		b = findRoot(b);
		if(a!=b)
			tree[a]=b;
	}
	
	int ans=0;
	//������ͨ�����ĸ���
	for(int i=1;i<=n;i++)
		if(tree[i]==-1)
			ans++;
	printf("%d\n",ans); 
	
	//���tree
	for(int i=1;i<=n;i++) 
		cout<<tree[i]<<' ';
	cout<<endl;
	//��ͼ����ͨ�ģ���findRoot(i)==findRoot(j)��Ϊ1
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			cout<<(findRoot(i)==findRoot(j))<<endl;
		} 
	 } 
}


