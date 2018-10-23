#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;

int n;
long long a, d, b, v[50];
vector< pair< pair<long long,long long>, int>  > points;
map<long long, long long> inner;

void set_generator(int type, int i){
	if(type == 1 && i == n/2){
		//printf("%lld %lld %lld -> %d -> (%lld,%lld)\n", a, d, b, type, a-d, d-b);
		points.push_back({{d-b, a-d}, type}); // inverted
		return;
	}
	if(type == 0 && i == n){
		//printf("%lld %lld %lld -> %d -> (%lld,%lld)\n", a, d, b, type, d-a, b-d);
		points.push_back({{b-d, d-a}, type}); // inverted
		return;
	}

	a += v[i]; set_generator(type, i+1); a -= v[i];
	d += v[i]; set_generator(type, i+1); d -= v[i];
	b += v[i]; set_generator(type, i+1); b -= v[i];
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) scanf("%lld", &v[i]);
	set_generator(1,0); set_generator(0,(n/2));
	//printf("----------------------------------------\n");
	sort(points.begin(), points.end());
	long long res = 0x3f3f3f3f3f3f3f3f;
	for(auto & obj : points){
		long long x = obj.x.y, y = obj.x.x;
		//printf("%lld,%lld -> %d\n", x, y, obj.y);
		if(obj.y == 0) {
			auto it = inner.find(x);
			if(it == inner.end()) inner[x] = x+y;
			it->y = min(it->y, x+y); 
			auto val = it->y; ++it;
			while(it != inner.end()){
				if(it->y <= val) it = inner.erase(it);
				else ++it;
			}
		} else {
			auto it = inner.upper_bound(x);
			if(it == inner.begin()) continue;
			--it; 
			//printf("Query : %lld val : %lld\n", it->y, x + y - it->y);
			res = min(res, x + y - it->y);
		}
	}
	cout << res << endl;
	return 0;
}
