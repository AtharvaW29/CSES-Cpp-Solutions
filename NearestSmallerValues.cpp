#include <iostream>
#include <vector>

using namespace std;

void solve()
{
	int size;
	cin >> size;
	vector<int> nums(size);
	vector<int> ans(size, 0);
	for (int& value : nums)
	{
		cin >> value;
	}
	vector<int> stack;
	for (int i = 0; i < size; i++) 
	{
		while(!stack.empty() &&  nums[stack.back()] >= nums[i])
		{
			stack.pop_back();
		}
		if(!stack.empty())
		{
			ans[i] = stack.back() + 1;
			stack.push_back(i);
		}
		else
		{
			stack.push_back(i);
			ans[i] = 0;
		}
	}
	for (int value : ans)
	{
		cout << value << " ";
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	solve();
	return 0;
}