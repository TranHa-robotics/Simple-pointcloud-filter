#include "Filters/PassThrough.hpp"
#include <iostream>

namespace PCP {
    PassThrough::PassThrough(float min_z, float max_z):
        min_z_(min_z), max_z_(max_z) {}
    
    void PassThrough::apply(PointCloud& cloud) {
        // 1. Tao container de chua cac diem thoa man
        PointCloud filtered_cloud;

        // 2. Reverse bo nho de tranh Reallocation 
        filtered_cloud.reserve(cloud.size());

        // 3. Duyet qua tung diem 
        for(const auto& pt : cloud) {
            if(pt.z() >= min_z_ && pt.z() <= max_z_) {
                filtered_cloud.addPoint(pt);
            }
        }

        // 4. In log
        std::cout << "[PassThrough] Filtered from " << cloud.size() 
                    << " to " << filtered_cloud.size() << " points\n";
        
        // 5. gan nguoc lai du lieu
        cloud = std::move(filtered_cloud);
    }
}