	#include <bits/stdc++.h>
	using namespace std;

	void solve() {
	    int n,x;
	    cin >> n >> x;
	    vector<int> nums(n);
	    map<int, int> nums_set;
	    for(int& value : nums)
	    {
	    	cin >> value;
	    }
	    for(int i = 0; i < n; i++)
	    {
	    	auto it = nums_set.find(nums[i]);
	    	if(it != nums_set.end() && it->second != i)
	    	{
	    		cout << i+1 << " " << it->second+1 << "\n";
	    		return;
	    	}
	    	nums_set[x-nums[i]] = i;
	    }
	    cout << "IMPOSSIBLE\n";
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
