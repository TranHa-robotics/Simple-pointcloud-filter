#include "Core/PointCloud.hpp"
#include "Filters/VoxelFilter.hpp"
#include <string>
#include <iostream>
#include <filesystem>

int main(int argc, char* argv[]) {
    if(argc < 2) {
        std::cout << "Usage: " << argv[0] << " <path to cloud file>" << std::endl;
        return 1;
    }

    std::string filepath = argv[1];
    std::filesystem::path p(filepath);
    // std::string filepath_save = filepath + "save.txt";
    std::string filepath_save = (p.parent_path() / (p.stem().string() + "_vxg_filtered.txt")).string();
    PCP::PointCloud pc;
    PCP::VoxelFilter vxg_filter(1.0);
    if(!pc.load(filepath))
        return -1;
    vxg_filter.apply(pc);
    if(!pc.save(filepath_save));
        return -1;
    return 0 ;
}