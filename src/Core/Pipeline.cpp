#include "Core/Pipeline.hpp"
#include <iostream>

namespace PCP {

void Pipeline::addFilter(std::shared_ptr<IFilter> filter) {
    if (filter) {
        filters_.push_back(filter);
    }
}

void Pipeline::run(PointCloud& cloud) {
    for (const auto& filter : filters_) {
        std::cout << "[Pipeline] Running " << filter->getName() << "..." << std::endl;
        filter->apply(cloud);
    }
}

} // namespace PCP