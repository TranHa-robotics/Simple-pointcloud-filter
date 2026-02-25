#include <gtest/gtest.h>
#include "Core/PointCloud.hpp"
#include "Filters/PassThrough.hpp"
#include "Filters/VoxelFilter.hpp"

// Test 1: Kiểm tra xem PassThrough có cắt đúng trục Z không
TEST(FilterTest, PassThroughLogic) {
    PCP::PointCloud cloud;
    cloud.addPoint(0.0f, 0.0f, 5.0f);  // Nằm trong khoảng [0, 10] -> Giữ lại
    cloud.addPoint(0.0f, 0.0f, 15.0f); // Vượt max_z -> Bỏ
    cloud.addPoint(0.0f, 0.0f, -5.0f); // Dưới min_z -> Bỏ

    PCP::PassThrough filter(0.0f, 10.0f);
    filter.apply(cloud);

    // Chạy Assertions (Kỳ vọng)
    EXPECT_EQ(cloud.size(), 1); // Chỉ còn đúng 1 điểm
    EXPECT_FLOAT_EQ(cloud[0].z(), 5.0f); // Điểm đó phải có z = 5.0
}

// Test 2: Kiểm tra xem VoxelGrid có tính đúng Trọng tâm (Centroid) và băm không gian đúng không
TEST(FilterTest, VoxelGridCentroid) {
    PCP::PointCloud cloud;
    // 2 điểm này chắc chắn nằm trong cùng 1 khối Voxel (nếu leaf_size = 1.0)
    cloud.addPoint(0.1f, 0.1f, 0.1f);
    cloud.addPoint(0.9f, 0.9f, 0.9f);

    PCP::VoxelFilter filter(1.0f);
    filter.apply(cloud);

    EXPECT_EQ(cloud.size(), 1); // 2 điểm phải bị gộp làm 1
    
    // Trọng tâm phải là trung bình cộng của tọa độ
    // Dùng EXPECT_FLOAT_EQ thay vì EXPECT_EQ vì sai số dấu phẩy động của C++
    EXPECT_FLOAT_EQ(cloud[0].x(), 0.5f);
    EXPECT_FLOAT_EQ(cloud[0].y(), 0.5f);
    EXPECT_FLOAT_EQ(cloud[0].z(), 0.5f);
}