project(BuddyMemoryAllocatorLibTests)

add_subdirectory(lib/googletest-release-1.8.1)

include_directories(lib/googletest-release-1.8.1/googletest/include)
include_directories(lib/googletest-release-1.8.1/googlemock/include)

add_library(BuddyMemoryAllocatorLibTests TestsRunner.h TestsRunner.cpp AllocatorTests.cpp)

target_link_libraries(BuddyMemoryAllocatorLibTests BuddyMemoryAllocatorLib gtest gtest_main)
