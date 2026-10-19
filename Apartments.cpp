	#include <bits/stdc++.h>
	using namespace std;

	void solve() {
		long n, m, k;
	    cin >> n >> m >> k;
	    vector<long> applicants(n);
	    vector<long> apartments(m);
	    for(long& value : applicants)
	    {
	    	cin >> value;
	    }
	    for(long& value : apartments)
	    {
	    	cin >> value;
	    }
	    int ans = 0;
	    std::sort(applicants.begin(), applicants.end());
	    std::sort(apartments.begin(), apartments.end());
	    long i, j;
	    i = 0, j = 0;
	    while((i < n) && (j < m))
	    {
	    	if(((applicants[i] - k) <= apartments[j]) && 
	    		(apartments[j] <= (applicants[i] + k)))
	    	{
	    		ans++;
	    		i++;
	    		j++;
	    	}
	    	else if(apartments[j] < (applicants[i] - k))
	    	{
	    		j++;
	    	}
	    	else if((applicants[i] + k) < apartments[j])
	    	{
	    		i++;
	    	}
	    }
	    cout << ans << "\n";
	}

	int main() {
	    ios_base::sync_with_stdio(false);
	    cin.tie(nullptr);

	    solve();
	    return 0;
	}
