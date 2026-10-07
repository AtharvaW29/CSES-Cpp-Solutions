#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
using std::vector;

void solve()
{
	int size, target;
	std::cin >> size >> target;
	vector<int> arr(size);
	for (int& value : arr)
	{
		std::cin >> value;
	}
	vector<vector<int>> pairs = {};

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
				cout << (p + 1) << " "
					<< (q + 1) << " "
					<< (r + 1) << " "
					<< (s + 1) << "\n";
				return;
			}
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
	std::cout << "IMPOSSIBLE\n";
	return;
}

//int main()
//{
//#ifdef LOCAL_TESTING
//	return TestNamed("FourSum", solve, "tests/FourSum") ? 0 : 1;
//#else
//	std::ios_base::sync_with_stdio(false);
//	std::cin.tie(nullptr);
//
//	solve();
//	return 0;
//#endif
//}