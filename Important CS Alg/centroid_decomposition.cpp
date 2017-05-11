#include <bits/stdc++.h>
using namespace std;

const int N = 200002;

typedef pair<long long, long long> chi;
vector <chi > g[N], qs[N];
vector <long long> me, tot, nodes;
int cnt[N], bc[N], ans[N];
long long h[N];
bool mark[N];

int dfs(int v, bool c = 0, int par = -1, long long di = 0)
{ //One dfs function for multiple purposes
	h[v] = di;
	cnt[v] = 1;
	bc[v] = 0;
	me.push_back(di);
	nodes.push_back(v); //add all nodes in the subtree LMAO
	if(c)
		tot.push_back(di); //Finds distance from a centroid to all nodes in the subtree with a centroid root
	for(int i = 0; i < g[v].size(); i++)
	{
		chi e = g[v][i];
		int u = e.first;
		if(u != par && !mark[u]) //part of this current centroid tree
		{
			cnt[v] += dfs(u, c, v, di + e.second);
			if(!bc[v] || cnt[bc[v]] < cnt[u]) //Generates the tree for the centroid decomp
				bc[v] = u;
		}
	}
	return cnt[v];
}

void solve(int v)
{
	dfs(v);
	int n = cnt[v]; //Default size is n
	while(cnt[bc[v]] * 2 > n) //Finds centroid by walking up old tree
		v = bc[v]; //Walks up old tree to find centroid

	//ok. Found centroid "v"
	tot.clear();
	dfs(v, 1); //stores distance to all nodes where "v" is the centroid 
	mark[v] = 1;
	sort(tot.begin(), tot.end()); //sort the distance haha
	for(int _i = 0; _i < qs[v].size(); _i++)
	{
		chi q = qs[v][_i];
		long long w = q.first;
		int i = q.second;
		ans[i] += upper_bound(tot.begin(), tot.end(), w) - tot.begin() - 1; //Finds the straight line paths of distance less than "w"
		//Only works for shit inside the centroid tree.... O n O
	}
	for(int _i = 0; _i < g[v].size(); _i++)
	{
		chi e = g[v][_i];
		if(!mark[e.first]) //Checks if this node is in this centroid tree OMG "BAE"
		{
			me.clear(); //reset subtree
			nodes.clear();
			dfs(e.first, 0, v, e.second); //Finds "me"
			//The nodes in this subtree of the centroid tree.
			//Distance from the centroid root to this subtree nodes....
			sort(me.begin(), me.end()); //Distance to all subtrees of the centroid not including the previously past centroids
			for(int j = 0; j < nodes.size(); j++)
			{
				int u = nodes[j]; //all nodes that are in this fking subtree
				for(int k = 0; k < qs[u].size(); k++) //We're doing the updates for the nodes in your centroid subtree  #_i....
				{ //THAT'S WHY THERE'S DUPLICATES
					chi q = qs[u][k];
					long long w = q.first;
					int i = q.second; //fix updates for uh... the nodes in the centroid subtree...
					//Add the # of paths starting from the centroid to those nodes
					ans[i] += upper_bound(tot.begin(), tot.end(), w - h[u]) - tot.begin();
					//goes from u -> v then v -> some random node in it's centroid tree
					ans[i] -= upper_bound(me.begin(), me.end(), w - h[u]) - me.begin();
					//but there's the case where u - > v and v -> some node but there's some node -> u or u -> somenode
					//in other words that "some node" is in the same subtree of "v" as "u" and u're dead.

					//The question is the # of d(Start node, some node u)
					// <= then a length that they gave u
					// w is the length
					//Why do I have extra answers?
				}
			}
		}
	}
	for(int i = 0; i < g[v].size(); i++)//Pretty much expanding out from your centroid root. 
		if(!mark[g[v][i].first]) //If you haven't used this point as a centroid yet
			solve(g[v][i].first); //move to next node. Already used the root node with the biggest centroid tree
	mark[v] = 0;
}

 main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	int n, q;
	cin >> n >> q;
	for(int i = 1; i < n; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		g[u].push_back(chi(v, w));
		g[v].push_back(chi(u, w));
	}
	for(int i = 0; i < q; i++)
	{
		long long v, w;
		cin >> v >> w;
		qs[v].push_back(make_pair(w, i)); //offline queries (For simplicity sake)
	}
	solve(1);
	for(int i = 0; i < q; i++) //stored answers
		cout << ans[i] + 1 << endl;
}