#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve()
{
	int size, target;
	std::cin >> size >> target;
	std::vector<std::pair<int,int>> nums(size);
	for(int i = 0; i < nums.size(); i++)
	{
		std::cin >> nums[i].first;
		nums[i].second = i;
	}
	std::sort(nums.begin(), nums.end());
	int l, r;
	for(int i = 0; i < nums.size(); i++)
	{
		l = i + 1, r = nums.size() - 1;
		while (l < r)
		{
			long long crr_sum = (long long)nums[i].first + nums[l].first + nums[r].first;
			if (crr_sum == target)
			{
				std::cout 
				<< nums[i].second + 1 << " " 
				<< nums[l].second + 1 << " " 
				<< nums[r].second + 1 << " " << "\n";
				return;
			}
			else if (crr_sum > target)
			{
				r--;
			}
			else
			{
				l++;
			}
		}
	}
	std::cout << "IMPOSSIBLE" << "\n";
	return;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	solve();
	return 0;
}