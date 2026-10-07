#include "TestRunner.h"
#include "FourSum.cpp"

using namespace std;

void solve();

int main()
{
#ifdef LOCAL_TESTING
    return TestNamed("DistinctNumbers", solve, "tests/DistinctNumbers") ? 0 : 1;
#else
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    solve();
    return 0;
#endif
}
