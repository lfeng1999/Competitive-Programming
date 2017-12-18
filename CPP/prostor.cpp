#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
struct Event{
	ll type, x1, y1, x2, y2, z;
	//type 1 is adding line seg to bit
	//type 2 is checking the instant rectangle
	//type 3 is removing line seg from bit
	Event(ll T, ll _x1, ll _y1, ll _x2, ll _y2, ll _z){
		type = T, x1 = _x1, y1 = _y1, x2 = _x2, y2 = _y2, z = _z;
	};
	bool operator < (const Event &a){
		if (z != a.z)
			return z < a.z;
		return type < a.type;
	}
};

ll N, bithi[1010][1010], bitlo[1010][1010];

ll queryhi(ll a, ll b){
	ll tot = 0;
	for (ll i=a; i>0; i-=i&(-i))
		for (ll j=b; j>0; j-=j&(-j))
			tot += bithi[i][j];
	return tot;
}

void updatehi(ll a, ll b, ll val){
	for (ll i=a; i < 1000; i += i&(-i))
		for (ll j=b; j < 1000; j += j&(-j))
			bithi[i][j] += val;
}

ll querylo(ll a, ll b){
	ll tot = 0;
	for (ll i=a; i>0; i-=i&(-i))
		for (ll j=b; j>0; j-=j&(-j))
			tot += bitlo[i][j];
	return tot;
}

void updatelo(ll a, ll b, ll val){
	for (ll i=a; i < 1000; i += i&(-i))
		for (ll j=b; j < 1000; j += j&(-j))
			bitlo[i][j] += val;
}
vector<Event> XY, YZ, ZX;

ll solve(vector<Event> &V){ //Suppose it was where we're looping through z right now....
//IN OTHER WORDS ZX. Z IS THE GUY NOT CHANGING OMDADMAKDNA
//The vertical lines are where x does not change? ok
	for (ll i=0; i<1010; ++i){
		fill(bitlo[i], bitlo[i] + 1010, 0);
		fill(bithi[i], bithi[i] + 1010, 0);
	}
	sort(V.begin(), V.end());
	ll ret = 0;
	for (Event E : V){
		ll type = E.type, x1 = E.x1, x2 = E.x2, y1 = E.y1, y2 = E.y2;
		if (type == 1){ //X stays the same so whatever
			ret += querylo(y2, x1) - querylo(y2, x1 - 1);
			ret -= queryhi(y1-1, x1) - queryhi(y1-1, x1-1); //Adding a line segment
			updatelo(y1, x1, 1);
			updatehi(y2, x1, 1);
		}
		else if (type == 2){ //Checking rectangle
			ret += querylo(y2, x2) - querylo(y2, x1 - 1);
			ret -= queryhi(y1-1, x2) - queryhi(y1-1, x1 - 1);
		}
		else if (type == 3){ //removing line segment
			updatelo(y1, x1, -1);
			updatehi(y2, x1, -1);
		}
	}
	return ret; //No fucking idea if this is going to work LMFAO
}


int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N;
	for (ll i=0; i<N; ++i){
		ll x1, y1, z1, x2, y2, z2;
		cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
		if (x1 > x2) swap(x1, x2);
		if (y1 > y2) swap(y1, y2);
		if (z1 > z2) swap(z1, z2);
		
		if (x1 == x2){
			ZX.push_back(Event(1, x1, y1, x2, y2, z1));
			ZX.push_back(Event(3, x1, y1, x2, y2, z2));

			XY.push_back(Event(2, y1, z1, y2, z2, x1));
		}
		else if (y1 == y2){
			XY.push_back(Event(1, y1, z1, y2, z2, x1));
			XY.push_back(Event(3, y1, z1, y2, z2, x2));

			YZ.push_back(Event(2, z1, x1, z2, x2, y1));
		}
		else if (z1 == z2){
			YZ.push_back(Event(1, z1, x1, z2, x2, y1));
			YZ.push_back(Event(3, z1, x1, z2, x2, y2));

			ZX.push_back(Event(2, x1, y1, x2, y2, z1));
		}
	}
	cout << solve(XY) + solve(YZ) + solve(ZX); //BLESS

	return 0;
}