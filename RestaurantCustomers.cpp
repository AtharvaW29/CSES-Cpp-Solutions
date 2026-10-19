#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    
    vector<pair<int, int>> events;
    
    for (int i = 0; i < n; i++) {
        int start, end;
        cin >> start >> end;
        events.push_back({start, 1});
        events.push_back({end, -1});
    }
    
    sort(events.begin(), events.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        if (a.first == b.first) {
            return a.second < b.second;
        }
        return a.first < b.first;
    });

    int max_overlapping = 0;
    int current_overlapping = 0;
    
    for (const auto& event : events) {
        current_overlapping += event.second;
        max_overlapping = max(max_overlapping, current_overlapping);
    }
    
    cout << max_overlapping << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}
