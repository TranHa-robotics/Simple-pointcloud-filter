#pragma once 
#include "Filters/IFilter.hpp"

namespace PCP {
    class VoxelFilter : public IFilter {
        public:
            explicit VoxelFilter(float leaf_size);
            void apply(PointCloud& cloud) override;
            std::string getName() const override { return "Voxel Grid Filter";}
        public:
            float leaf_size_;
    };
}