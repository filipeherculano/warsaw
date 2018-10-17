// NOT PASSED

#include <bits/stdc++.h>
#define maxn 1000001
using namespace std;

void fusion(deque<long long> &d){
	deque<long long> res;
	for(auto & val : d){
		res.push_back(val);
		long long n = res.size();
		while(res.size() >= 3 && res[n-1] <= res[n-2] && res[n-2] >= res[n-3]){
			long long a = res.back(); res.pop_back();
			long long b = res.back(); res.pop_back();
			long long c = res.back(); res.pop_back();
			if(a+c-b) res.push_back(a+c-b);
		} 	
	} 
	d = res;
}

long long worthless(vector< deque<long long> > &vdi){
	long long n = 0, res = 0;
	for(auto & d : vdi) n += (long long) d.size();

	for(long long i = 0; i < 2; ++i){
		deque<long long> d;
		for(auto & val : vdi[i]){
			d.push_back(val);
			long long n = d.size();
			while(d.size() >= 2 && d[n-2] >= d[n-1]){
				long long a = d.back(); d.pop_back();
				long long b = d.back(); d.pop_back();
				res += ((n&1 ? -1:1) * (a - b));
				n -= 2;
			}
		}
	}

	return res;
}

long long greedy(vector< deque<long long> >& vdi){
	long long res = 0, turn = 1;
	priority_queue< pair<long long,long long>> pq;
	for(long long i = 0; i < (long long) vdi.size(); ++i){
		if(i < 2) {
			if(vdi[i].size() > 0) pq.push(make_pair(vdi[i].back(), i));
		} else {
			pq.push(make_pair(vdi[i].front(), i));
			if(vdi[0].size() > 1) pq.push(make_pair(vdi[i].back(), i));
		}
	}
	while(!pq.empty()){
		long long val = pq.top().first, idx = pq.top().second; pq.pop();
		res += val*(turn ? 1:-1);
		turn = 1-turn;
		if(vdi[idx].size() == 1) continue;
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
			if(d.size() > 0) vdi.push_back(d);
			d.clear();
		} else d.push_back(v[i]);
	}
	res += worthless(vdi);
	res += greedy(vdi);
	
	printf("%lld %lld\n", res + (sum-res)/2, (sum-res)/2);
	return 0;
}
