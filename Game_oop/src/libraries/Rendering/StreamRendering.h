#ifndef stream_rendering_h
#define stream_rendering_h

#include "RenderingInterface.h"
#include "Tracking/Tracking.h"
#include <iostream>

class StreamRendering : public RenderingInterface{
private:
    std::ostream &out_;
public: 
    StreamRendering(std::ostream &out);
    void print_game(PlayerHandler* handler) override;
    void print_message(Messages message) override;
};

#endif