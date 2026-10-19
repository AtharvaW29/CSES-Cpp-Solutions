	#include <bits/stdc++.h>
	using namespace std;

	void solve() {
	    int n;
	    cin >> n;
	    multiset<int> dict;
	    int ans = 0;
	    for(int i = 0; i < n; i++)
	    {
	    	int value;
	    	cin >> value;
	    	auto it = dict.upper_bound(value);
	    	if(it != dict.end())
	    	{
	    		dict.erase(it);
	    		dict.insert(value);
	    	}
	    	else
	    	{
	    		dict.insert(value);
	    		ans++;
	    	}
	    }
	    cout << ans << "\n";
	}


	int main() {
	    ios_base::sync_with_stdio(false);
	    cin.tie(nullptr);

	    // #ifndef ONLINE_JUDGE
	    // freopen("input.txt", "r", stdin);
	    // freopen("output.txt", "w", stdout);
	    // #endif

	    solve();
	    return 0;
	}
