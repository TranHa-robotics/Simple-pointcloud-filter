#include "Filters/VoxelFilter.hpp"
#include "unordered_map"
#include <cmath>

namespace PCP
{
    // 1. struct tinh hash cho eigen::vector3i de dung duoc trong std::unordered_map
    struct Vector3iHash
    {
        size_t operator()(const Eigen::Vector3i &v) const
        {
            // dung cac so nguyen to lon de tao hash, tranh dung do
            const size_t p1 = 73856093;
            const size_t p2 = 19349663;
            const size_t p3 = 83492791;
            return (v.x() * p1) ^ (v.y() * p2) ^ (v.z() * p3);
        }
    };

    // 2. struct luu tru tam thoi du lieu cua moi voxel
    struct VoxelData
    {
        Eigen::Vector3f sum{0.0f, 0.0f, 0.0f};
        int count = 0;
    };

    VoxelFilter::VoxelFilter(float leaf_size) : leaf_size_(leaf_size) {}

    void VoxelFilter::apply(PointCloud &cloud)
    {
        if (cloud.size() == 0 || leaf_size_ <= 0.0f)
            return;

        // bang bam, hash map luu cac voxel: key la toa do 3D cua voxel, value la du lieu
        std::unordered_map<Eigen::Vector3i, VoxelData, Vector3iHash> voxel_grid;

        // toi uu:nhan nhanh hon chia. tinh nghich dao cua leaf size 1 lan
        float inv_leaf_size = 1.0f / leaf_size_;

        // buoc 1: phan bo tung diem vao dung voxel cua no (spatial hashing)
        for (const auto &pt : cloud)
        {
            // tim toa do (index) cua voxel chua diem nay
            Eigen::Vector3i voxel_idx(
                static_cast<int>(std::floor(pt.x() * inv_leaf_size)),
                static_cast<int>(std::floor(pt.y() * inv_leaf_size)),
                static_cast<int>(std::floor(pt.z() * inv_leaf_size)));

            voxel_grid[voxel_idx].sum += pt;
            voxel_grid[voxel_idx].count++;
        }

        // buoc 2 trich xuat diem dai dien (centroid) tu moi voxel
        PointCloud filtered_cloud;
        filtered_cloud.reserve(voxel_grid.size());

        for (const auto &pair : voxel_grid)
        {
            // centroid = tong toa do / so luong diem
            Eigen::Vector3f centroid = pair.second.sum / pair.second.count;
            filtered_cloud.addPoint(centroid);
        }

        cloud = std::move(filtered_cloud);
    }
}