#include "gtest/gtest.h"
#include <gmock/gmock.h>
#include "../BuddyMemoryAllocatorLib/Allocator.h"

class AllocatorDefinition : public testing::Test
{
public:
    Allocator allocator;
};

TEST_F(AllocatorDefinition, empty_test)
{
    ASSERT_TRUE(true);
}
