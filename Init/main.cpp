#include "Game.h"
#include "Controller.h"

int main ( int argc, char *argv[] )
{
    
    
    const uint8_t framerate = 60;
    const uint8_t delay = 1000 / framerate;
    
    unsigned frame_start;
    unsigned frame_time;
    
    int width = 1280;
    int height = 720;
    
    auto *controller = new Controller ( );
    controller->Run ( width, height, frame_start, frame_time, framerate, delay );
    
    return 0;
}