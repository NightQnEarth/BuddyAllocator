cmake_minimum_required(VERSION 3.14)
project(BuddyMemoryAllocator)

set(CMAKE_CXX_STANDARD 17)

include_directories ("${PROJECT_SOURCE_DIR}/BuddyMemoryAllocatorLib")
include_directories ("${PROJECT_SOURCE_DIR}/BuddyMemoryAllocatorLibTests")
include_directories(BuddyMemoryAllocatorLibTests/lib/googletest-release-1.8.1/googletest/include)
include_directories(BuddyMemoryAllocatorLibTests/lib/googletest-release-1.8.1/googlemock/include)

add_subdirectory (BuddyMemoryAllocatorLib)
add_subdirectory(BuddyMemoryAllocatorLibTests)

add_executable(BuddyMemoryAllocator main.cpp BuddyMemoryAllocatorLibTests/AllocatorTests.cpp)
target_link_libraries (BuddyMemoryAllocator BuddyMemoryAllocatorLib BuddyMemoryAllocatorLibTests)
