#include <bits/stdc++.h>

#define maxn 3003
#define mini(a,b) ((a) > (b) ? (b):(a))

using namespace std;

short n, q, INF, res[maxn][maxn], sz[maxn];
vector<short> adj[maxn];

void dfs(short v, short p){
	for(auto & u : adj[v]) if(u != p) dfs(u,v);
	if(sz[v] == 1){
		res[v][1] = 0;
		return;
	}

	short turn = 1, pd[2][n+1]; memset(pd,63, sizeof pd);
	pd[0][1] = 0;

	for(short j = 0; j < (short) adj[v].size(); ++j){
		short u = adj[v][j];
		if(u == p) continue;

		for(short i = 1; i <= sz[v]; ++i){
			pd[turn][i] = pd[1-turn][i] + 1;
			for(short a = 1; a < i; ++a){
				short b = i-a;
				pd[turn][i] = mini(pd[turn][i], pd[1-turn][a] + res[u][b]);
			}

			res[v][i] = pd[turn][i];
		}

		turn = 1-turn;
	}
}

short dfs_sz(short v, short p){
	short res = 1;
	for(auto & u : adj[v]) if(u != p) res += dfs_sz(u,v);
	return sz[v] = res;
}

int main(){
	scanf("%hd", &n);
	for(short i = 0; i < n-1; ++i){
		short a,b; scanf("%hd %hd", &a, &b); --a; --b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	dfs_sz(0,-1);
	memset(res, 63, sizeof res);
	INF = res[0][0];
	dfs(0,-1);

	scanf("%hd", &q);
	for(short i = 0; i < q; ++i){
		short val, ans = INF; scanf("%hd", &val);
		for(short j = 0; j < n; ++j) ans = mini(ans, res[j][val] + (j == 0 ? 0:1));
		if(ans >= INF) puts("-1");
		else cout << ans << endl;
	}
	return 0;
}
