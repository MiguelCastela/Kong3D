#include <algorithm>
#include <cmath>
#include <vector>
#include "ofApp.h"
#include "background.h"
#include "materials.h"
using namespace std;


Background::Background() {
}

void Background::draw() {
    loadMaterial(3);

    glPushMatrix();
        glScalef(gw() , gw(), gw());
        cube_unit(0.5);
    glPopMatrix();

}
