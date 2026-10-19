#include <bits/stdc++.h>
using namespace std;


// void solve() {
//     auto custom_sort = [](int a, int b){ return a > b; };
//     int n;
//     cin >> n;

//     function<void(vector<int>&, int, int, multiset<int, decltype(custom_sort)>&)> subset_sum = 
//     [&](vector<int> &arr, int sum, int i, multiset<int, decltype(custom_sort)> &s) -> void 
//     {
//         if (i > arr.size())
//         {
//             return;
//         }
//         if (i == arr.size())
//         {
//             s.insert(sum);
//             return;
//         }
//         subset_sum(arr, sum + arr[i], i + 1, s);
//         subset_sum(arr, sum, i + 1, s);
//     };

//     multiset<int, decltype(custom_sort)> coin_set(custom_sort);
//     vector<int> coins(n);
    
//     for (int i = 0; i < n; i++)
//     {
//         int value;
//         cin >> value; 
//         coins[i] = value; 
//         coin_set.insert(value);
//     }

//     subset_sum(coins, 0, 0, coin_set);

//     for (int value : coin_set)
//     {
//         cout << value << "\n";
//     }
// }


void solve()
{
	int n;
	cin >> n;
	vector<long long> coins(n);
	for(long long& value : coins)
	{
		cin >> value;
	}
	sort(coins.begin(), coins.end());
	long long missing = 1;

	for(long long value : coins)
	{
		if(value > missing)
		{
			break;
		}
		missing += value;
	}

	cout << missing << "\n";
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    solve();
    return 0;
}
