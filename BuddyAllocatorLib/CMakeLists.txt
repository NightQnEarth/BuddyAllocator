project(BuddyAllocatorLib)

set(HEADER_FILES
        Allocator.h)

set(SOURCE_FILES
        Allocator.cpp)

add_library(BuddyAllocatorLib STATIC ${SOURCE_FILES} ${HEADER_FILES})
