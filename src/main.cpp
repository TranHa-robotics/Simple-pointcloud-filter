#include "Core/PointCloud.hpp"
#include "Core/Pipeline.hpp"
#include "Filters/PassThrough.hpp"
#include "Filters/VoxelFilter.hpp"
#include <iostream>
#include <filesystem>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <path to cloud file>" << std::endl;
        return 1;
    }
    // 1. Load data
    PCP::PointCloud cloud;

    std::string filepath = argv[1];
    std::filesystem::path p(filepath);
    // std::string filepath_save = filepath + "save.txt";
    std::string filepath_save = (p.parent_path() / (p.stem().string() + "_multi_filtered.txt")).string();

    if (!cloud.load(filepath))
    {
        return -1;
    }

    // 2. Setup Pipeline
    PCP::Pipeline pipeline;

    // std::make_shared (C++11/14/17) cấp phát bộ nhớ an toàn và nhanh hơn dùng 'new'
    pipeline.addFilter(std::make_shared<PCP::PassThrough>(0.0f, 10.0f));
    pipeline.addFilter(std::make_shared<PCP::VoxelFilter>(0.5f));

    // 3. Chạy toàn bộ dây chuyền
    pipeline.run(cloud);

    // 4. Lưu kết quả
    cloud.save(filepath_save);

    return 0;
}