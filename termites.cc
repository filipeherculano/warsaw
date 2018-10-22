// NOT PASSED

#include <bits/stdc++.h>
#define maxn 1000001
using namespace std;

void fusion(deque<long long> &d){
	deque<long long> res;
	for(auto & val : d){
		res.push_back(val);
		long long n = res.size();
		while(n >= 3 && res[n-1] <= res[n-2] && res[n-2] >= res[n-3]){
			long long x = res.back(); res.pop_back();
			long long M = res.back(); res.pop_back();
			long long y = res.back(); res.pop_back();
			if(x+y-M) res.push_back(x+y-M);
			n -= 2;
		} 	
	} 
	d = res;
}

long long worthless(vector< deque<long long> > &vdi){
	long long n = 0, res = 0;
	for(auto & d : vdi) n += (long long) d.size();

	for(long long i = 0; i < 2; ++i){
		while(vdi[i].size() >= 2 && vdi[i][vdi[i].size()-1] <= vdi[i][vdi[i].size()-2]){
			long long x = vdi[i].back(); vdi[i].pop_back();
			long long M = vdi[i].back(); vdi[i].pop_back();
			res += (((n-vdi[i].size())&1 ? -1LL:1LL) * (x - M));
			n -= 2;
		}
	}

	return res;
}

long long greedy(vector< deque<long long> >& vdi){
	long long res = 0, turn = 1;
	priority_queue< pair<long long,long long>> pq;
	for(long long i = 0; i < (long long) vdi.size(); ++i){
		if(vdi[i].size() == 0) continue;
		pq.push(make_pair(vdi[i].back(), i));
		if(i >= 2 && vdi[i].size() > 1) pq.push(make_pair(vdi[i].front(), i));
	}
	while(!pq.empty()){
		long long val = pq.top().first, idx = pq.top().second; pq.pop();
		res += val*turn;
		turn *= -1;
		if(vdi[idx].size() < 2) continue;

		if(vdi[idx].back() == val) {
			vdi[idx].pop_back();
			if(idx < 2 || vdi[idx].size() > 1) pq.push(make_pair(vdi[idx].back(), idx));
		} else {
			vdi[idx].pop_front();
			if(vdi[idx].size() > 1) pq.push(make_pair(vdi[idx].front(), idx));
		}
	}

	return res;
}

int main(){
	long long n,res = 0,v[maxn],sum = 0;
	scanf("%lld", &n);
	long long start = 0, end = n-1;
	vector< deque<long long> > vdi(2);
	deque<long long> d;

	for(long long i = 0; i < n; ++i) scanf("%lld", &v[i]), sum += v[i];
	
	for(;start < n && v[start]; ++start) d.push_back(v[start]);
	vdi[0] = (d); d.clear();
	for(;end >= 0 && v[end]; --end) d.push_back(v[end]); 
	vdi[1] = (d); d.clear();
	for(long long i = start+1; i <= end; ++i){
		if(v[i] == 0) {
			fusion(d);
			vdi.push_back(d);
			d.clear();
		} else d.push_back(v[i]);
	}
	res += worthless(vdi);
	res += greedy(vdi);
	
	printf("%lld %lld\n", (res+sum)/2, (sum-res)/2);
	return 0;
}
