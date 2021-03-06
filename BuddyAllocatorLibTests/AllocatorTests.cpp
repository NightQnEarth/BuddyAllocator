#include "gtest/gtest.h"
#include <gmock/gmock.h>
#include "../BuddyAllocatorLib/Allocator.h"

#define MB 1024
#define DUMP_OUTPUT

TEST(AllocatorTest, AllocateMinBlock)
{
    Allocator allocator(MB);

    auto intPointer = (int*)allocator.Allocate(1);
    ASSERT_NE(intPointer, nullptr);

#ifdef DUMP_OUTPUT
    allocator.Dump();
#endif

    *intPointer = 15;
    ASSERT_EQ(*intPointer, 15);
}

TEST(AllocatorTest, AllocateMaxBlock)
{
    Allocator allocator(MB);

    void* memoryPointer = allocator.Allocate(MB);
    ASSERT_NE(memoryPointer, nullptr);

#ifdef DUMP_OUTPUT
    allocator.Dump();
#endif
}

TEST(AllocatorTest, ThrowOnZeroAllocationRequest)
{
    ASSERT_THROW(Allocator(0), std::out_of_range);

    Allocator allocator(MB);

    ASSERT_THROW(allocator.Allocate(0), std::out_of_range);

#ifdef DUMP_OUTPUT
    allocator.Dump();
#endif
}

TEST(AllocatorTest, AllocateBigBlockAfterSmall)
{
    Allocator allocator(2 * MB);

    void* firstBlock = allocator.Allocate(40);
    ASSERT_NE(firstBlock, nullptr);

    void* secondBlock = allocator.Allocate(260);
    ASSERT_NE(secondBlock, nullptr);

#ifdef DUMP_OUTPUT
    allocator.Dump();
#endif
}

TEST(AllocatorTest, AllocateSmallBlockAfterBigThenFreeBigBlockAndAllocateOneMoreSmall)
{
    Allocator allocator(MB);
    void* bigBlock = allocator.Allocate(256);
    allocator.Allocate(128);
    allocator.Allocate(128);

    allocator.Free(bigBlock);

#ifdef DUMP_OUTPUT
    allocator.Dump();
#endif

    ASSERT_NO_THROW(allocator.Allocate(128));

#ifdef DUMP_OUTPUT
    allocator.Dump();
#endif
}

TEST(AllocatorTest, ThrowOnTooBigAllocationRequest)
{
    Allocator allocator(MB);

    ASSERT_THROW(allocator.Allocate(MB + 1), std::out_of_range);

#ifdef DUMP_OUTPUT
    allocator.Dump();
#endif
}

TEST(AllocatorTest, AllocateMaxSmallBlocksCount)
{
    Allocator allocator(MB);

    size_t maxSmallBlocksCount = MB / (size_t)pow(2, MIN_POWER);

    for (int i = 0; i < maxSmallBlocksCount; ++i)
        ASSERT_NO_THROW(allocator.Allocate(sizeof(int)));

#ifdef DUMP_OUTPUT
    allocator.Dump();
#endif
}

TEST(AllocatorTest, AllocateMaxSmallBlocksCountThenFreeHalfAndAllocateAgain)
{
    Allocator allocator(MB);

    size_t maxSmallBlocksCount = MB / (size_t)pow(2, MIN_POWER);
    void** memoryPointers = new void*[maxSmallBlocksCount];

    for (int i = 0; i < maxSmallBlocksCount; ++i)
        ASSERT_NO_THROW(memoryPointers[i] = allocator.Allocate(sizeof(int)));

    for (int i = 0; i < maxSmallBlocksCount; i += 2)
        ASSERT_NO_THROW(allocator.Free(memoryPointers[i]));

    for (int i = 0; i < maxSmallBlocksCount; i += 2)
        ASSERT_NO_THROW(allocator.Allocate(sizeof(int)));

#ifdef DUMP_OUTPUT
    allocator.Dump();
#endif
}

TEST(AllocatorTest, AllocateTooManyBlocks)
{
    Allocator allocator(MB);

    size_t maxSmallBlocksCount = MB / (size_t)pow(2, MIN_POWER);

    for (int i = 0; i < maxSmallBlocksCount; ++i)
        ASSERT_NO_THROW(allocator.Allocate(sizeof(int)));

    ASSERT_THROW(allocator.Allocate(1), std::out_of_range);
}

TEST(AllocatorTest, AllocateBlockSizeMoreThanOneStandardPage)
{
    Allocator allocator(40 * MB);

    ASSERT_NE(allocator.Allocate(40 * MB), nullptr);

#ifdef DUMP_OUTPUT
    allocator.Dump();
#endif
}
