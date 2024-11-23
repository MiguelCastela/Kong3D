#include "global.h"

Global global;

Global::Global(){
    marioDim = ofVec3f(5,5,5);

    // Space between platforms
    platDim = ofVec3f(marioDim.x*30, marioDim.x*2, marioDim.z*1.4);


    empty_space = platDim.y;



    ladDim = ofVec3f(2*marioDim.x, empty_space + platDim.y, marioDim.z/4);



    barrelDim = ofVec3f(marioDim.x, marioDim.y, marioDim.z);


    ladHitBoxDim_barrel = ofVec3f(ladDim.x, ladDim.y-barrelDim.y+1 , ladDim.z*2);


    //ladders that don't exist
    fakeLadDim = ofVec3f(ladDim.x, ladDim.y, ladDim.z);


    marioPos = ofVec3f(0, 0, 0);    

    barrelPos = ofVec3f(0, 0, 0);

    kongPos = ofVec3f(0, 0, 0);

    kongDim = ofVec3f(marioDim.x , marioDim.y , marioDim.z );

    ladHitBoxDim_mario = ofVec3f(0.1, ladDim.y, ladDim.z);



    paulinePos = ofVec3f(0, 0, 0);
    paulineDim = ofVec3f(marioDim.x, marioDim.y, marioDim.z);
    

    left_limit = -platDim.x/2 + marioDim.x/2;
    right_limit = platDim.x/2 - marioDim.x/2;
}