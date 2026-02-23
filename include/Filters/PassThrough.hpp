#pragma once
#include "Filters/IFilter.hpp"

namespace PCP
{

    class PassThrough : public IFilter
    {
    public:
        // Khoi tao gioi han min/max cua truc z
        PassThrough(float min_z, float max_z);

        // bat buoc override tu IFilter
        void apply(PointCloud &cloud) override;

        std::string getName() const override { return "PassThrough Filter"; }

    private:
        float min_z_;
        float max_z_;
    };
}