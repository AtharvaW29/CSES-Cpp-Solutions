	#include <bits/stdc++.h>
	using namespace std;

	void solve() {
	    int n, m;
	    cin >> n >> m;
	    multiset<int> tickets;
	    for(int j = 0; j < n; j++)
	    {
	    	int value;
	    	cin >> value;
	    	tickets.insert(value);
	    }
	    vector<int> customers(m);
	    for(int& value: customers)
	    {
	    	cin >> value;
	    }
	    for(int i = 0; i < m; i++)
	    {
	    	auto it = tickets.upper_bound(customers[i]);
	    	if (it == tickets.begin())
	    	{
	    		cout << "-1 \n";
	    	}
	    	else
	    	{
	    		--it;
	    		cout << *it << "\n";
	    		tickets.erase(it);
	    	}
	    }
	}

	int main() {
	    ios_base::sync_with_stdio(false);
	    cin.tie(nullptr);

	    solve();
	    return 0;
	}
