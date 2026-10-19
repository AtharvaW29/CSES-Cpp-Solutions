	#include <bits/stdc++.h>
	using namespace std;

	void solve() {
	    int s;
	    cin >> s;
	    vector<pair<int, int>> intervals;
	    for(int i = 0; i < s; i++)
	    {
	    	int start, end;
	    	cin >> start >> end;
	    	intervals.push_back({start, end});
	    }
	    sort(intervals.begin(), intervals.end(), 
	    	[](const pair<int, int>& a, const pair<int, int>& b){
	    	return a.second < b.second;
	    });
	    int last_end_time = -2e9;
	    int ans = 0;
	    for(pair<int, int>& muvie: intervals)
	    {
	    	if(muvie.first >= last_end_time)
	    	{
	    		ans++;
	    		last_end_time = muvie.second;
	    	}	
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
	    // correct ans = 200000
	    solve();
	    return 0;
	}




