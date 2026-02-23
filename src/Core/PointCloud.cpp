#include "Core/PointCloud.hpp"
#include <fstream>
#include <iostream>

namespace PCP
{
    PointCloud::PointCloud(const std::string &filepath)
    {
        if (!load(filepath))
        {
            std::cerr << "[Error]: Failed to load pointcloud file";
        }
    }

    bool PointCloud::load(const std::string &filepath)
    {
        std::ifstream file(filepath);
        if (!file.is_open())
        {
            std::cerr << "[Error]: Cannot open file " << filepath << std::endl;
            return false;
        }

        points_.clear();
        float x, y, z;
        while (file >> x >> y >> z)
        {
            points_.emplace_back(x, y, z);
        }

        file.close();
        std::cout << "[Info] loaded " << points_.size() << " points" << std::endl;
        return true;
    }

    bool PointCloud::save(const std::string& filepath) const 
    {
        std::ofstream file(filepath);
        if(!file.is_open())
        {
            std::cerr << "[Error]: Cannot open file " << filepath << std::endl;
            return false;
        }

        // cai dat do chinh xac de tranh mat du lieu khi ghi ra file
        file.precision(6);
        file << std::fixed;

        for(const auto& point : points_)
        {
            file << point.x() << " " << point.y() << " " << point.z() << std::endl;
        }
        file.close();
        std::cout << "[Info]: Saved " << points_.size() << " points to file " << filepath << std::endl;
        return true;
    }

    PointCloud& PointCloud::operator+=(const PointCloud &other) {
        if(this == &other) {
            // copy tam thoi roi insert
            PointCloud temp = other;
            points_.insert(points_.end(), temp.begin(), temp.end());
            return *this;
        }

        points_.reserve(points_.size() + other.size());
        points_.insert(points_.end(), other.begin(), other.end());
        
        return *this;
    }
} // PCP