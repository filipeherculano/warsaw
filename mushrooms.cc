#include <bits/stdc++.h>
#define maxn 1000001
using namespace std;

long long n,t,v[maxn];

long long solve(){
	if(n == 1) return v[0] * ((t+1)/2);
	
	long long res = 0, sum = 0;
	for(long long i = 0; i < n-1 && t; ++i){
		res = max(res, sum + (v[i] * ((t+1)/2)) + (v[i+1] * (t/2)));
		sum += v[i];
		--t;
	}

	return res;
}

int main(){
	scanf("%lld %lld", &n, &t); ++t;
	for(int i = 0; i < n; ++i) scanf("%lld", &v[i]);
	cout << solve() << endl;
	return 0;
}
