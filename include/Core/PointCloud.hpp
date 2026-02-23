#pragma once

#include <vector>
#include <string>
#include <Eigen/Dense>

namespace PCP
{
    class PointCloud
    {
    public:
        using Point = Eigen::Vector3f;
        using Container = std::vector<Point>;

        using iterator = Container::iterator;
        using const_iterator = Container::const_iterator;

        // 1. constructor
        PointCloud() = default;
        // explicit de tranh convert ngam dinh tu string sang PointCloud?
        explicit PointCloud(const std::string &filepath);

        // 2. File I/O
        bool load(const std::string &filepath);
        bool save(const std::string &filepath) const;

        // 3. Data access
        Point &operator[](size_t index) { return points_[index]; }
        const Point &operator[](size_t index) const { return points_[index]; }

        // add point
        void addPoint(const Point &pt) { points_.push_back(pt); }
        void addPoint(float x, float y, float z)
        {
            points_.emplace_back(x, y, z);
        }

        // 4. memory management
        size_t size() const { return points_.size(); }
        void reserve(size_t n) { points_.reserve(n); }
        void clear() { points_.clear(); }

        // 5. iterator support (bat buoc de dung voi thu vien algorithm)
        iterator begin() { return points_.begin(); }
        iterator end() { return points_.end(); }

        const_iterator begin() const { return points_.begin(); }
        const_iterator end() const { return points_.end(); }

        // 6. Operator overloading cho phep cong 2 dam may diem
        PointCloud &operator+=(const PointCloud &other);

        // get raw pointer
        Point *data() { return points_.data(); }

    private:
        Container points_;
    };
}