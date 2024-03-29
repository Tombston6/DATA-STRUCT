/*
    首先是递归构造二叉树，跳过数组0是因为后续需要利用数组0来周转
其中使用update函数来更新每个结点现在挂载多少个叶子结点
同时使用pushdown函数来记录结点的父节点，此函数赋值节点左右子树的父节点，使得可以跳过根节点

qur函数，出入根节点，如果根节点就是叶子结点则返回0
否则开始merge


merge函数：如果左子树的叶子节点比右子树的叶子结点少，那么就交换左右子树
左右子树的父节点都取消，通过clac函数计算左右子树


clac函数：如果右子树的左子树存在，就递归左子树和右子树的左子树
如果右子树是叶子结点q添加右子树，如果右子树的右子树存在，就递归clac左子树和右子树的右子树

*/

#include<stdio.h>
#include<iostream>
using namespace std;
#define ForD(i,n) for(int i=n;i;i--)
#define F (100000007)
#define MAXN (2*200000+10)

long long mul(long long a,long long b)
{
    return (a * b) % F;
}

long long add(long long a,long long b)
{
    return (a+b) % F;
}
long long sub(long long a,long long b)
{
    return (a - b + ( a - b ) / F * F + F ) % F;
}

int n,root=0;

//C++的结构体，其中下面是构造函数
struct node
{
    int fa,ch[2],size,c;
    //size是叶子节点的个数
    //c是结点的value
    //ch[0]是左孩子， ch[1]是右孩子
    node():size(0),c(0){ch[0]=ch[1]=fa=0;}
}a[MAXN];


void update(int x)
{
    //更新每个结点上叶子结点的个数
    a[x].size = a[a[x].ch[0]].size + a[a[x].ch[1]].size + (a[x].c>0);
}

int tail=0;

void pushdown(int x)
{
    a[a[x].ch[0]].fa = a[a[x].ch[1]].fa = x; //记住父节点
}

void build(int &x)
{
    if (!x) 
        x=++tail;
    scanf("%d",&a[x].c);
    if (a[x].c==0)
    {
        build(a[x].ch[0]);
        build(a[x].ch[1]);
        update(x);
        pushdown(x);
    }
    else 
        a[x].size=1;
}

void rotate(int x)
{
    int y=a[x].fa,z=a[y].fa;
    bool p=a[y].ch[0]==x;
    if (z)
    {
        if (a[z].ch[0]==y) a[z].ch[0]=x;
        else a[z].ch[1]=x;
    }
    a[x].fa=z,a[y].fa=x;
    if (a[x].ch[p]) a[a[x].ch[p]].fa=y;
    a[y].ch[p^1]=a[x].ch[p];
    a[x].ch[p]=y;
    update(y);
}

void splay(int x)
{
    while (a[x].fa)
    {
        int y=a[x].fa,z=a[y].fa;
        if (z)
            if ((a[y].ch[0]==x)^(a[z].ch[0]==y)) rotate(x);
            else rotate(y);
        rotate(x);
    }
    update(x);
}

void ins(long long &tot,int x,int y)
{
    a[x].size++;
    if (a[y].c<=a[x].c)
    {
        if (a[x].ch[0]) ins(tot,a[x].ch[0],y);
        else a[y].fa=x,splay(a[x].ch[0]=y);
    }
    else
    {
        tot+=a[a[x].ch[0]].size+(a[x].c>0);
        if (a[x].ch[1]) ins(tot,a[x].ch[1],y);
        else a[y].fa=x,splay(a[x].ch[1]=y);
    }
}

int q[MAXN],kong;

void clac(int x,int y)
{
    //核心
    if (a[y].ch[0]) clac(x,a[y].ch[0]);
    if (a[y].c) q[++kong]=y;
    if (a[y].ch[1]) clac(x,a[y].ch[1]);
}

long long merge(bool &lor,int z)
{
    int x=a[z].ch[0],y=a[z].ch[1];
    if (a[x].size<a[y].size) swap(x,y);
 
    a[x].fa=0;a[y].fa=0;q[1]=y;
    kong=0;clac(x,y);
    long long tot=0;
    ForD(i,kong)
    {
        int now=q[i];
        a[now].ch[0]=a[now].ch[1]=a[now].fa=0;a[now].size=1;
        ins(tot,x,now);
        x=now;
    }
    a[x].fa=z;
    a[z].ch[0]=0,a[z].ch[1]=x;
    return tot;
}

long long qur(int &x)
{
    if (a[x].c) return 0;
    else
    {
        long long lson=a[a[x].ch[0]].size,rson=a[a[x].ch[1]].size,ls=qur(a[x].ch[0]),rs=qur(a[x].ch[1]);
        bool lor = 0;
        long long ms=merge(lor,x);
        return ls+rs+min(lson*rson-ms,ms);
    }
}
int main()
{
    scanf("%d",&n);
    build(root);
    cout<<qur(root)<<endl;
    return 0;
}
