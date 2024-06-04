#ifndef file_rendering_h
#define file_rendering_h

#include "RenderingInterface.h"
#include "Tracking/Tracking.h"
#include <iostream>
#include <fstream>
#include <string>

class FileRendering : public RenderingInterface{
private:
    std::ofstream out_;
public: 
    FileRendering(std::string file_name);
    ~FileRendering() override;
    void print_game(PlayerHandler* handler) override;
    void print_message(Messages message) override;
};

#endif