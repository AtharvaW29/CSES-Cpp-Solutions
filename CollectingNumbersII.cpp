	#include <bits/stdc++.h>
	using namespace std;

	void solve() {
	    int n, m;
	    
	    cin >> n >> m;
	    vector<int> nums(n+1);
	    vector<int> pos_of_val(n+1);

	    for(int i = 1; i < n+1; i++)
	    {
	    	cin >> nums[i];
	    	pos_of_val[nums[i]] = i;
	    }

	    int ans = 1;
	    
	    for(int i = 1; i < (n + 1); i++)
		{
			if(pos_of_val[i] < pos_of_val[i-1])
			{
				ans++;
			}
		}

	    for(int i = 0; i < m; i++)
	    {
	    	int a, b;
	    	cin >> a >> b;

	    	int ax = nums[a];
			int ay = nums[b];

	        set<pair<int, int>> affected;
	        if (ax > 1) affected.insert({ax - 1, ax});
	        if (ax < n) affected.insert({ax, ax + 1});
	        if (ay > 1) affected.insert({ay - 1, ay});
	        if (ay < n) affected.insert({ay, ay + 1});

	    	for(auto it : affected)
	    	{
	    		if(pos_of_val[it.first] > pos_of_val[it.second])
	    		{
	    			ans--;
	    		}	
	    	}
	    	swap(nums[a], nums[b]);
	    	pos_of_val[ax] = b;
	    	pos_of_val[ay] = a;
	    	for(auto it : affected)
	    	{
	    		if(pos_of_val[it.first] > pos_of_val[it.second])
	    		{
	    			ans++;
	    		}	
	    	}

	    	cout << ans << "\n";
	    }

	    return;
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
