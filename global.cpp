#include "global.h"

Global global;

Global::Global(){
    marioDim = ofVec3f(5,5,5);

    // Space between platforms
    platDim = ofVec3f(marioDim.x*20, marioDim.x*2, marioDim.z*1.4);
    empty_space = platDim.y;
    ladDim = ofVec3f(marioDim.x*3, empty_space + platDim.y, marioDim.z/4);
    barrelDim = ofVec3f(marioDim.x, marioDim.y, marioDim.z);
    ladHitBoxDim = ofVec3f(ladDim.x, ladDim.y+1, ladDim.z*2);

    left_limit = -platDim.x/2 + marioDim.x/2;
    right_limit = platDim.x/2 - marioDim.x/2;
}