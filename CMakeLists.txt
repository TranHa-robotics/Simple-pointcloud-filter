cmake_minimum_required(VERSION 3.10)
project(pointcloud_processing)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Eigen3 REQUIRED)

# add_library(VoxelFilter STATIC VoxelFilter.cpp)
# target_include_directories(VoxelFilter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/Filters)

# add_library(PassThrough STATIC PassThrough.cpp)
# target_include_directories(PassThrough PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/Filters)

# add_library(PointCloud STATIC PointCloud.cpp)
# target_include_directories(PointCloud PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/Core)

# add_library(Pipeline STATIC Pipeline.cpp)
# target_include_directories(Pipeline PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/Core)
# CHIA NHU TREN QUA VUN, CHIA THEO CHUC NANG 
add_library(Core STATIC
    src/Core/PointCloud.cpp
    src/Core/Pipeline.cpp 
)

target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(Core PUBLIC Eigen3::Eigen)

# --- 2. Tạo Interface cho Filter ---
add_library(FilterInterface INTERFACE)
target_include_directories(FilterInterface INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(FilterInterface INTERFACE Core) # Filter cần hiểu PointCloud là gì

# --- 3. Tạo thư viện Filters (Gộp các filter lại) ---
add_library(Filters STATIC 
    src/Filters/VoxelFilter.cpp
    src/Filters/PassThrough.cpp
)
target_link_libraries(Filters PUBLIC FilterInterface) # Kế thừa interface

# --- 4. Main App ---
add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE Core Filters)

# --- 5. Tests ---
add_executable(TestPointCloud tests/TestPointCloud.cpp)
target_link_libraries(TestPointCloud PRIVATE Core Filters)

add_executable(TestPassThroughFilter tests/TestPassThroughFilter.cpp)
target_link_libraries(TestPassThroughFilter PRIVATE Core Filters)

add_executable(TestVoxelGridFilter tests/TestVoxelGridFilter.cpp)
target_link_libraries(TestVoxelGridFilter PRIVATE Core Filters)
