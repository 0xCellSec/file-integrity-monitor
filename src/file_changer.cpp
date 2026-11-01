#include "file_changer.hpp"
#include <fstream>
#include <iostream>


void ThreatSimulator::modifyFile(std::string target_file_path)
{
    std::cout << "Modifying: " << target_file_path << std::endl;
    const char* actor_input = "file modified here";
    std::fstream outfile(target_file_path, std::ios::out | std::ios::app);
    if (!outfile.is_open())
    {
            std::cout << "ERROR: couldn't open writeable file" << std::endl;
            return;
    }
    
    outfile << actor_input << std::endl;
    outfile.close();
    return;
}