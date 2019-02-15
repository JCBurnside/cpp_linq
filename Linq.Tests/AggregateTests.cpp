#include "gtest/gtest.h"
#include "Linq.hpp"
using namespace Linq;

TEST(AggregateTests,simpleFunction)
{
    int func(int a, int b)
    {
        return a + b;
    }
    int resultFunction = LinqWrapper({1,2,3}).Aggregate(func);
    int resultLamda=LinqWrapper({1,2,3}).Aggregate([](int a, int b)-> int { return a + b; });
    EXPECT_EQ(resultLamda,6);
    EXPECT_EQ(resultFunction, 6);
}

TEST(AggregateTests,withDifferentTypes)
{
}


TEST(AggregateTests,withSeed)
{
    struct Accumulator
    {

    };
    auto result;
}