project(BuddyMemoryAllocatorLib)

set(HEADER_FILES
        Allocator.h)

set(SOURCE_FILES
        Allocator.cpp)

add_library(BuddyMemoryAllocatorLib STATIC ${SOURCE_FILES} ${HEADER_FILES})
