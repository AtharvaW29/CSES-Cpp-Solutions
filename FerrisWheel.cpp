	#include <bits/stdc++.h>
	using namespace std;

	void solve() {
	    long n, x;
	    cin >> n >> x;
	    vector<long> children(n);
	    for(long& value : children)
	    {
	    	cin >> value;
	    }
	    std::sort(children.begin(), children.end());
	    int ans = 0;
	    long i, j;
	    i = 0, j = n-1;
	    while(i <= j)
	    {
	    	if(children[i] + children[j] <= x)
	    	{
	    		i++;
	    		j--;
	    	}
	    	else
	    	{
	    		j--;
	    	}
	    	ans++;
	    }
	    std::cout << ans << "\n";
	}

	int main() {
	    ios_base::sync_with_stdio(false);
	    cin.tie(nullptr);

	    solve();
	    return 0;
	}
