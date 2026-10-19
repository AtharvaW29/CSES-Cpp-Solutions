	#include <bits/stdc++.h>
	using namespace std;

	void solve() {
	    int n;
	    cin >> n;
	    vector<long long> sticks(n);
	    for(long long& value : sticks)
	    {
	    	cin >> value;
	    }
	    sort(sticks.begin(), sticks.end());
	    int mid = n / 2;
	    int l = 0;
	    long long ans = 0;
	    while(l < n)
	    {
	    	ans += abs(sticks[l] - sticks[mid]);
	    	l++;
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
