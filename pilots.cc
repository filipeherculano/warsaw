#include <bits/stdc++.h>
#define maxn 3000001

using namespace std;

long long n,t,a[maxn],p[maxn];
deque<long long> left_max, left_min;

int main(){
	scanf("%lld %lld", &t, &n);
	for(long long i = 0; i < n; ++i) scanf("%lld", &a[i]);

	long long res = 1;
	p[0] = 0;
	left_max.push_back(0);
	left_min.push_back(0);
	for(long long i = 1; i < n; ++i){
		long long candidate = p[i-1];
		while(!left_max.empty() && a[left_max.front()]-t > a[i]) {
			candidate = max(candidate, left_max.front()+1);
			left_max.pop_front();
		}
		while(!left_min.empty() && a[left_min.front()]+t < a[i]){
			candidate = max(candidate, left_min.front()+1);
			left_min.pop_front();
		} 

		while(!left_max.empty() && a[left_max.back()] < a[i]) left_max.pop_back();
		left_max.push_back(i);
		while(!left_min.empty() && a[left_min.back()] > a[i]) left_min.pop_back();
		left_min.push_back(i);

		p[i] = candidate;
		
		if((i-p[i]+1) > res) res = i-p[i]+1;
	}
	cout << res << endl;

	return 0;
}
