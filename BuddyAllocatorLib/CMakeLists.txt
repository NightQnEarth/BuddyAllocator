project(BuddyAllocatorLib)

set(HEADER_FILES
        Allocator.h
        BlockStatus.h
        MemoryBlock.h)

set(SOURCE_FILES
        Allocator.cpp
        MemoryBlock.cpp)

add_library(BuddyAllocatorLib STATIC ${SOURCE_FILES} ${HEADER_FILES})
