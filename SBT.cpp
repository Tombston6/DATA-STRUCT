#include<cstdio>
#include<algorithm>
using namespace std;
#define MAXN 200005
int n,m;
long long ans;
//SBT,Size Blance Tree
//S是size，Left和Right是左右节点
int S[MAXN],Left[MAXN],Right[MAXN];
unsigned int Key[MAXN];
int Left_Rotate(int rt){
    int k=Right[rt];
    Right[rt]=Left[k];
    Left[k]=rt;
    S[k]=S[rt];
    S[rt]=S[Left[rt]]+S[Right[rt]]+1;
    return rt=k;
}

int Right_Rotate(int rt){
    int k=Left[rt];
    Left[rt]=Right[k];
    Right[k]=rt;
    S[k]=S[rt];
    S[rt]=S[Left[rt]]+S[Right[rt]]+1;
    return rt=k;
}

int Maintain(int rt,bool flag){
    //检查平衡性，不符合的进行左右旋转，并更换rt
    if(flag){
        if(S[Left[Right[rt]]]>S[Left[rt]] || S[Right[Right[rt]]]>S[Left[rt]]){
            if(S[Left[Right[rt]]]>S[Left[rt]])Right[rt]=Right_Rotate(Right[rt]);
            return Left_Rotate(rt);
        }
    }
    else{
        if(S[Right[Left[rt]]]>S[Right[rt]] || S[Left[Left[rt]]]>S[Right[rt]]){
            if(S[Right[Left[rt]]]>S[Right[rt]])Left[rt]=Left_Rotate(Left[rt]);
            return Right_Rotate(rt);
        }
    }
    return rt;
}

int Insert(int rt,int RT){
    S[rt]+=1;
    //先插入后调整平衡性
    //RR和LR是左旋，其他是右旋
    if(Key[RT]>Key[rt]){
        if(Right[rt]>0)Right[rt]=Insert(Right[rt],RT);
        else{
            Right[rt]=RT;
        }
    }
    else{
        if(Left[rt]>0)Left[rt]=Insert(Left[rt],RT);
        else{
            Left[rt]=RT;
        }
    }
    return rt=Maintain(rt,Key[RT]>Key[rt]);
}

int Rank(int rt,int v){
    /*
    *param:rt是一个已经完成了的SBT，v则是要比较的值
    *本函数比较v与二叉树根节点的值来获的SBT上比v小的节点有多少个
    */
    if(v>Key[rt]){
        if(Right[rt]==0)return S[rt];
        return S[rt]-S[Right[rt]]+Rank(Right[rt],v);
    }
    if(Left[rt]==0)return 0;
    return Rank(Left[rt],v);
}

int Merge(int rt,int Start,int End){
    long long lans=0,rans=0;
    for(int i=Start;i<=End;i++){
        lans+=Rank(rt,Key[i]);   //比key[i]小的节点有多少个
        rans+=S[rt]-Rank(rt,Key[i]+1); //比key[i]大的节点有多少个
    }
    for(int i=Start;i<=End;i++){
        //将每个节点插入平衡二叉树
        S[i]=1;
        Left[i]=Right[i]=0;
        rt=Insert(rt,i);
    }
    ans+=min(lans,rans);//最小的则是逆序对数
    return rt;
}

int Init(){
    int v;
    scanf("%d",&v);
    if(v){
        Key[++m]=v;
        S[m]=1;
        Left[m]=Right[m]=0;
        return m;
    }
    int TL,TR,Ls,Le,Rs,Re;
    Ls=m+1;
    TL=Init();
    Le=m;
    Rs=m+1;
    TR=Init();
    Re=m;
    if(S[TL]<S[TR])return Merge(TR,Ls,Le);
    return Merge(TL,Rs,Re);
}
int main()
{
    scanf("%d",&n);
    Init();
    printf("%I64d\n",ans);
    return 0;
}
