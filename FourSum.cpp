#include <vector>
#include <algorithm>
#include <iostream>

using std::vector;

class FourSum
{
public:
	int size = 0;
	int target = 0;
	vector<int>& arr;
	vector<int> result = {};
	vector<vector<int>> pairs = {};

	FourSum(int size_, int target_, vector<int>& arr_)
		: size(size_), target(target_), arr(arr_)
	{
		Solve();
		if (result.empty())
		{
			std::cout << "IMPOSSIBLE" << std::endl;
		}
		else
		{
			for (int i = 0; i < result.size(); i++)
			{
				std::cout << result[i] + 1 << (i == result.size() - 1 ? "" : " ");
			}
		}
	}

	void Solve()
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = i + 1; j < size; j++)
			{
				pairs.push_back({ arr[i] + arr[j], i , j });
			}
		}
		std::sort(pairs.begin(), pairs.end());

		int left = 0;
		int right = pairs.size() - 1;
		while (left < right)
		{
			int crr_sum = pairs[left][0] + pairs[right][0];
			if (crr_sum == target)
			{
				int p = pairs[left][1], q = pairs[left][2];
				int r = pairs[right][1], s = pairs[right][2];
				if (p != r && q != s && p != s && q != r)
				{
					result = { p, q, r, s };
					return;
				}
				result.erase(
					std::unique(result.begin(), result.end()), result.end());
				if(pairs[left + 1][0] == pairs[left][0])
				{
					left++;
				}
				else
				{
					right--;
				}
			}
			else if (crr_sum < target)
			{
				left++;
			}
			else
			{
				right--;
			}
		}
		return;
	};
};

//int main() {
//	std::vector<int> nums = { 1, 0, -1, 0, -2, 2 };
//	int target = 0;
//
//	FourSum solver(nums.size(), target, nums);
//
//	return 0;
//}
