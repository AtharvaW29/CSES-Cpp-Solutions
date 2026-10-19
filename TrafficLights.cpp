	#include <bits/stdc++.h>
	using namespace std;

	void solve() {
	    int x, n;
	    cin >> x >> n;
	    set<int> lights;
	    
	    lights.insert(0);
	    lights.insert(x);

	    multiset<int> gaps;
	    gaps.insert(x);

	    for(int j = 0; j < n; j++)
	    {
	    	int value;
	    	cin >> value;
	    	auto it = lights.upper_bound(value);
	    	int right = *it;
	    	cout << "right: ->" << right << "\n";
	    	int left = *prev(it);
	    	cout << "left ->" << left << "\n";

	    	gaps.erase(gaps.find(right - left));
	    	gaps.insert(value - left);
	    	gaps.insert(right - value);

	    	lights.insert(value);
	    	cout << *gaps.rbegin() << "\n";	
	    }
	}

	int main() {
	    ios_base::sync_with_stdio(false);
	    cin.tie(nullptr);

	    #ifndef ONLINE_JUDGE
	    freopen("input.txt", "r", stdin);
	    freopen("output.txt", "w", stdout);
	    #endif

	    solve();
	    return 0;
	}
