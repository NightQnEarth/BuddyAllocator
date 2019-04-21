#include "gtest/gtest.h"
#include <gmock/gmock.h>
#include "../BuddyAllocatorLib/Allocator.h"

class AllocatorDefinition : public testing::Test
{
public:
    Allocator allocator = Allocator(1024);
};

TEST_F(AllocatorDefinition, empty_test)
{
    ASSERT_TRUE(true);
}
