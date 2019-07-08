#include <iostream>
#include <queue>
#define mx 10001
using namespace std;
 
int n,m,start,end_point;
const int no_edge=999999;
struct edge_node{
    int end_x;
    int weight;
    edge_node *next;
    edge_node(int e,int w,edge_node *nt){end_x=e;weight=w;next=nt;}
};
struct ver_node{
    int ver_point;
    edge_node *head;
    ver_node(edge_node *h=NULL){head=h;}
};
ver_node *elem=new ver_node[mx];
void insert(int x,int y,int w){
    elem[x].head=new edge_node(y,w,elem[x].head);
}
int main(){
    int i;
    queue<int> q;
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m>>start>>end_point;
    int u,v,w;
    int dis[n+2];
    bool in_que[n+2];
    for(i=1;i<=n;++i){
        dis[i]=no_edge;
        in_que[i]=false;
    }
    for(i=1;i<=m;++i){
        cin>>u>>v>>w;
        insert(u,v,w);
    }
    int pre[n+2];
    q.push(start);
    dis[start]=0;
    in_que[start]=true;
    edge_node *p;
    int cur;
    while(!q.empty()){
        cur=q.front();
        q.pop();
        in_que[cur]=false;
        for(p=elem[cur].head;p!=NULL;p=p->next){
            if(dis[p->end_x]>dis[cur]+p->weight){
                dis[p->end_x]=dis[cur]+p->weight;
                pre[p->end_x]=cur;
                if(!in_que[p->end_x]){
                    q.push(p->end_x);
                    in_que[p->end_x]=true;
                }
            }
        }
    }
    cout<<dis[end_point]<<endl;
    int tmp_next[n+1],ct=1;
    for(i=end_point;i!=start;i=pre[i]){
        tmp_next[ct++]=pre[i];
    }
    tmp_next[0]=end_point;
    for(i=ct-1;i>=0;--i) cout<<tmp_next[i]<<" ";
    return 0;
}