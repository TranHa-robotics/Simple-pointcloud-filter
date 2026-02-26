# Simple-pointcloud-filter

# Multithreaded Point Cloud Pre-processor

A lightweight C++17 tool for preprocessing 3D point cloud data. 

In a SLAM pipeline, this step is like prepping ingredients before cooking—washing and dicing the vegetables. It removes unnecessary parts (filtering noise) and reduces the overall volume (downsampling) so the downstream algorithms can process the data much faster.

## Technical Features

* C++ Architecture: Utilizes interfaces (abstract classes), smart pointers, and move semantics for safe and efficient memory management.
* Voxel Grid Filter: Implements spatial hashing using `std::unordered_map` with a custom hash function to merge points (O(1) lookup).
* Multithreading: Uses `std::async` following a Map-Reduce pattern to partition data, accelerating processing speed without altering the final centroid coordinates.
* Optimization: Relies solely on the Eigen3 library (header-only) for 3D vector math, completely eliminating the overhead of heavy dependencies like PCL.

## System Requirements
* CMake >= 3.10
* C++17 compatible compiler (GCC/Clang/MSVC)
* Eigen3 library

## Build and Run Instructions

1. Build the project:
```bash
mkdir build && cd build
cmake ..
make -j4
