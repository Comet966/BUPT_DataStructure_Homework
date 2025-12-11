using namespace std;
#include <vector>
#include <iostream>

#define N_Max 8//实际值加一
//贪心算法解决地图染色问题
//规定颜色编号为1~4（根据四色定理，最多不超过4种

void color_init(int * c_node)
{
    for(int i=0;i<N_Max;i++)
    {
        c_node[i] = 0;
    }
}

int color_find(int * c_node,int n)
{
    return c_node[n];
}

int find_min(int * arr)
{
    int temp=4;
    for(int i=1;i<=4;i++)
    {
        if(arr[i]<temp)
        {
            temp = arr[i];
        }
    }
    return temp;
}
void reset_all_color(int *arr)
{
    arr[0]=5;
    for(int i=1;i<=4;i++)
    {
        arr[i]=i;
    }
}
int main()
{
//测试数据，以邻接表的形式手动输入
    vector<vector<int>> adj(8);
    adj[1] = {2,3,4,5,6,7};
    adj[2] = {1,3};
    adj[3] = {1,2,4,5};
    adj[4] = {1,3,5};
    adj[5] = {1,3,6};
    adj[6] = {1,5};
    adj[7] = {1};
//结果存放
    int color[N_Max];
    color_init(color);//全部置零
    int all_color[5]={4,1,2,3,4};//颜色全集

//按照编号1~7顺序进行遍历，贪心算法来局部最优
    int temp;
    for(int i=1;i<N_Max;i++)
    {
        for(int j=0;j<adj[i].size();j++)
        {
            temp = color_find(color,adj[i][j]);//查找结果中是否已经包含点i的该邻接点，如果包含返回对应颜色编号
            if(temp)
            {
                all_color[temp] = 4;//该颜色编号置为4
            }
        }
        color[i] = find_min(all_color);
        reset_all_color(all_color);
    }
for(int i=1;i<N_Max;i++)
{
    cout<<i<<"\t"<<color[i]<<endl;
}

    return 0;
}