#pragma once
#include "Core/PointCloud.hpp"
#include "Filters/IFilter.hpp"
#include <vector>
#include <memory> // Cho std::shared_ptr

namespace PCP {

class Pipeline {
public:
    // Thêm một filter vào cuối dây chuyền
    void addFilter(std::shared_ptr<IFilter> filter);

    // Chạy toàn bộ dây chuyền trên đám mây điểm
    void run(PointCloud& cloud);

private:
    // Chứa danh sách các filter bằng con trỏ thông minh để tận dụng đa hình (Polymorphism)
    std::vector<std::shared_ptr<IFilter>> filters_;
};

} // namespace PCP