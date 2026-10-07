#include <vector>
#include <set>
#include <iostream>

using namespace std;

void solve()
{
	int n;
	std::cin >> n;
	vector<int> nums(n);
	for(int &value: nums)
	{
		std::cin >> value;
	}
	set<int> a;
	for(int i : nums)
	{
		if(a.contains(i))
		{
			continue;
		}
		else
		{
			a.insert(i);
		}
	}
	std::cout << a.size() << "\n";
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	solve();
	return 0;
}