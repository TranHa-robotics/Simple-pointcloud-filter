#pragma once
#include "Core/PointCloud.hpp"

namespace PCP {
    class IFilter {
        public:
            virtual void apply(PointCloud& cloud) = 0;
            virtual std::string getName() const = 0;

    };
} // namespace PCP