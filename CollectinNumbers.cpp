	#include <bits/stdc++.h>
	using namespace std;

	void solve() {
	    int n;
	    cin >> n;
	    if(n == 0)
	    {
	    	cout << "0 \n"; 
	    }
	    vector<int> nums(n+1);
	    
	    for(int i = 1; i < n+1; i++)
	    {
	    	int value;
	    	cin >> value;
	    	nums[value] = i;
	    }
	    int ans = 1;
	    for(int i = 1; i < n; i++)
	    {
	    	if(nums[i] > nums[i+1])
	    	{
	    		ans++;
	    	}
	    }
		cout << ans << "\n";
	    return;
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
