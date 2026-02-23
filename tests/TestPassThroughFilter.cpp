#include "Core/PointCloud.hpp"
#include "Filters/PassThrough.hpp"
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
    std::string filepath_save = (p.parent_path() / (p.stem().string() + "_pt_filtered.txt")).string();
    PCP::PointCloud pc;
    PCP::PassThrough pt_filter(1.2, 5.0);
    if(!pc.load(filepath))
        return -1;
    pt_filter.apply(pc);
    if(!pc.save(filepath_save));
        return -1;
    return 0 ;
}