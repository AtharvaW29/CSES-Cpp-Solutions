	#include <bits/stdc++.h>
	using namespace std;

	void solve() {
	    int n;
	    cin >> n;
	    
	    unordered_map<long long, long long> dic;
	    dic.reserve(n);
		long long ans = 0, l = 0;
	    
	    for(int r = 0; r < n; r++)
	    {
	    	long long value;
	    	cin >> value;

	    	auto it = dic.find(value);
	        if (it != dic.end() && it->second >= l) {
	            l = it->second + 1;
        	}
	    	ans = max(ans, r - l + 1);
	    	dic[value] = r;
	    }
	    cout << ans << "\n";
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
