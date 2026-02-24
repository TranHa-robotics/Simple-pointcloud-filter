#include "Core/PointCloud.hpp"
#include "Core/Pipeline.hpp"
#include "Core/Timer.hpp"
#include "Filters/PassThrough.hpp"
#include "Filters/VoxelFilter.hpp"
#include <iostream>
#include <filesystem>
#include <future>
#include <string>

PCP::PointCloud processChunk(PCP::PointCloud chunk) {
    PCP::Pipeline pipeline;
    pipeline.addFilter(std::make_shared<PCP::PassThrough>(0.0f, 10.0f));
    pipeline.addFilter(std::make_shared<PCP::VoxelFilter>(0.5f));

    pipeline.run(chunk);
    return chunk;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <path to cloud file> <number_of_threads" << std::endl;
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
    int num_threads = 1; 

    if(argc == 2) {
        std::cout << "Number of threads not received, default: 4\n";
        num_threads = 4;
    }
    else {
        num_threads = std::stoi(argv[2]);
    }
        size_t chunk_size = cloud.size() / num_threads;

    std::vector<std::future<PCP::PointCloud>> futures;
    
    {
        PCP::Timer t("Multithreaded processing"); // bat dau bam gio 

        // 1. chia data cho 4 phu bep 
        for(int i = 0; i < num_threads; i++) {
            size_t start_idx = i * chunk_size;
            // luong cuoi cung nhan toan bo phan le con lai 
            size_t end_idx = (i == num_threads -1) ? cloud.size() : start_idx + chunk_size;

            PCP::PointCloud chunk;
            chunk.reserve(end_idx - start_idx);
            for(size_t j = start_idx; j < end_idx; j++) {
                chunk.addPoint(cloud[j]);
            }

            // 2. nem viec cho luong phu 
            futures.push_back(std::async(std::launch::async, processChunk, std::move(chunk)));
        }

        cloud.clear();
        for(auto& f: futures) {
            cloud += f.get();
        }
        
        if(num_threads >=2) {
            PCP::VoxelFilter final_filter(0.5f);
            final_filter.apply(cloud);
        }
    }

    cloud.save(filepath_save);

    return 0;
}