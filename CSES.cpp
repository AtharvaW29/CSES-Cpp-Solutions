#include "TestRunner.h"
#include "FourSum.cpp"

int main()
{
    return Test(FourSum, "TestCase/FourSum") ? 0 : 1;
}
