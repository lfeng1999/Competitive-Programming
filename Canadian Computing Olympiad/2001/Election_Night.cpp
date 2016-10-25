#include <bits/stdc++.h>

using namespace std;

vector<int> graph[205];
int freq[101],mfreq[101], cap[205][205], source = 0, sink = 204, pos[101], cap2[205][205], N, M;
bool past[205];
void remake()
{
    for (int i=0; i!=205; ++i)
        for (int j=0; j!=205; ++j)
        {
            cap2[i][j] = cap[i][j];
        }
}


int augment(int cur, int curflow)
{
    if (cur == sink)
        return curflow;
    past[cur] = true;
    for (int i=0; i!=graph[cur].size(); ++i)
    {
        int v = graph[cur][i];
        if (cap2[cur][v] && !past[v])
        {
            int flow = augment(v,min(cap2[cur][v],curflow));
            if (flow > 0)
            {
                cap2[cur][v]-=flow;
                cap2[v][cur]+=flow;
                return flow;
            }
        }
    }
    return 0;
}


int max_flow()
{
    int mflow = 0, flow = 0;
    do
    {
        memset(past,false,sizeof(past));
        flow = augment(0,N);
        mflow+=flow;
    } while (flow>0);
    return mflow;
}

int main()
{
    //freopen("COCI.txt","r",stdin);
    cin.sync_with_stdio(0);cin.tie(0);
    while(cin >> N >> M && (N!=0 && M!=0))
    {
        memset(pos,-1,sizeof(pos));
        memset(cap,0,sizeof(cap));
        memset(cap2,0,sizeof(cap2));
        memset(freq,0,sizeof(freq));
        memset(mfreq,0,sizeof(mfreq));
        for (int i=0; i!=205; ++i)
            graph[i].clear();
        for (int i=1; i<=N; ++i)
        {
            cap[source][i]=1;
            int a;
            cin >> a;
            for (int j=0; j!=a; ++j)
            {
                int b;
                cin >> b;
                freq[b]++;
                graph[i].push_back(100+b);
                graph[100+b].push_back(i);
                cap[i][100+b] = 1;
            }
            if (a == 1)
                mfreq[graph[i][0]-100]++;
            graph[source].push_back(i);
            graph[i].push_back(source);
        }
        for (int i=1; i<=M; ++i)
        {
            graph[100+i].push_back(sink);
            graph[sink].push_back(100+i);
        }
        for (int i=1; i<=M; ++i)
        {
            int myfreq = mfreq[i];
            bool flag = true;
            for (int j=1; j<=M; ++j)
            {
                if (i!=j)
                {
                    if (freq[j] >= myfreq)
                        flag = false;
                }
            }
            if (flag)
                pos[i] = 2;
        }



        for (int i=1; i<=M; ++i)
        {
            if (pos[i]!=2)
            {
                memset(cap2,0,sizeof(cap2));
                remake();
                for (int j=1; j<=M; ++j)
                    cap2[100+j][sink] = freq[i]-1;
                cap2[100+i][sink] = freq[i];
                if (max_flow() == N)
                    pos[i] = 1;
                else
                    pos[i] = 0;
            }
        }
        for (int i=1; i<=M; ++i)
        {
            if (pos[i] == 0)
                printf("Candidate %d will not become president.\n",i);
            else if (pos[i] == 1)
                printf("Candidate %d may become president.\n",i);
            else
                printf("Candidate %d will become president.\n",i);
        }
        printf("\n");
    }
}
