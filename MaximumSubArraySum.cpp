#include <iostream>
#include <vector>
#include <limits>

using namespace std;

void solve()
{
	int size;
	cin >> size;
	vector<long long> nums(size);
	for(long long& value : nums)
	{
		cin >> value;
	}
	long long max_sum, crr_sum = 0;
	max_sum = std::numeric_limits<long long>::min();
	for(long long value: nums)
	{
		crr_sum += value;
		if(crr_sum > max_sum)
		{
			max_sum = crr_sum;
		}
		if(crr_sum < 0)
		{
			crr_sum = 0;
		}
	}
	
	cout << max_sum << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	solve();
	
	return 0;
}