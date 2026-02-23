#include "Core/PointCloud.hpp"
#include <string>
#include <iostream>
int main(int argc, char* argv[]) {
    if(argc < 2) {
        std::cout << "Usage: " << argv[0] << "<path to cloud file>" << std::endl;
        return 1;
    }

    std::string filepath = argv[1];
    std::string filepath_save = filepath + "save.txt";
    PCP::PointCloud pc;
    if(!pc.load(filepath))
        return -1;
    pc += pc;
    if(!pc.save(filepath_save));
        return -1;
    return 0 ;
}