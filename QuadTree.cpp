//
// Created by aiden on 23/11/2020.
//

#include "QuadTree.h"



// Check if current quadtree contains the point
bool Quad::inBoundary(Point p) const{
    return (p.x >= topLeft.x &&
            p.x <= botRight.x &&
            p.y >= topLeft.y &&
            p.y <= botRight.y);
}
