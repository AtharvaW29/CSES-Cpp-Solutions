#include <vector>
#include <iostream>
#include <unordered_map>
#include <chrono>

using namespace std;

struct custom_hash {
	static uint64_t splitmix(uint64_t x)
	{
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}
	size_t operator()(uint64_t x) const {
		static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
		return splitmix(x + FIXED_RANDOM);
	}
};

void solve()
{
	int size;
	long long target;
	cin >> size >> target;
	vector<long long> nums(size);
	for(long long& value: nums)
	{
		cin >> value;
	}
	unordered_map<long long, int, custom_hash> lookup;
	lookup.reserve(size);
	long long prefix = 0;
	long long ans = 0;
	lookup[0] = 1;
	for(long long value: nums)
	{
		prefix += value;
		auto it = lookup.find(prefix - target);
		if(it != lookup.end())
		{
			ans += it->second;
		}
		++lookup[prefix];
	}
	cout << ans << "\n";
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	solve();
	return 0;
}