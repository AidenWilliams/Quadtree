//
// Created by aiden on 23/11/2020.
//

#include "QuadTree.h"
///*
// * Transforms Vector by adding scalar to both x,y
// */
//Vector Vector::operator+(int rhs) const {
//    return Vector(x + rhs, y + rhs);
//}
///*
// * Transforms Vector by subtracting scalar to both x,y
// */
//Vector Vector::operator-(int rhs) const {
//    return Vector(x - rhs, y - rhs);
//}
/*
 * Add x and y values of points
 */
Vector Vector::operator+(Vector rhs) const {
    return Vector(x + rhs.x, y + rhs.y);
}
/*
 * Subtracts x and y values of points
 */
Vector Vector::operator-(Vector rhs) const {
    return Vector(x - rhs.x, y - rhs.y);
}
/*
 * Adds x values points but subtracts y values
 */
Vector Vector::operator>>(Vector rhs) const {
    return Vector(x + rhs.x, y - rhs.y);
}
/*
 * Subtracts x values points but adds y values
 */
Vector Vector::operator<<(Vector rhs) const {
    return Vector(x - rhs.x, y + rhs.y);
}

Vector Vector::operator*=(int num) const {
    return Vector(x * num, y * num);
}

Vector Vector::operator/=(int num) const {
    return Vector(x / num, y / num);
}

int Vector::getX() const {
    return x;
}

int Vector::getY() const {
    return y;
}

const Vector &Data::getPos() const {
    return pos;
}

bool Node::contains(Vector a) const {
    return  a.getX() >= centre.getX() - halfSize.getX() &&
            a.getX() <= centre.getX() + halfSize.getX() &&
            a.getY() >= centre.getY() - halfSize.getY() &&
            a.getY() <= centre.getY() + halfSize.getY();
}

bool Node::intersects(Node& other) const
{
    return !(other.centre.getX() - other.halfSize.getX() > centre.getX() + halfSize.getX() ||
             other.centre.getX() + other.halfSize.getX() > centre.getX() - halfSize.getX() ||
             other.centre.getY() - other.halfSize.getY() > centre.getY() + halfSize.getY() ||
             other.centre.getY() + other.halfSize.getY() > centre.getY() - halfSize.getY());
}

const Vector &Node::getCentre() const {
    return centre;
}

const Vector &Node::getHalfSize() const {
    return halfSize;
}

//template <class T>
Quadtree::Quadtree()
{
    nw = nullptr;
    ne = nullptr;
    sw = nullptr;
    se = nullptr;
    boundary = Node();
    objects = std::vector<Data>();
    divided = false;
}

//template <class T>
Quadtree::Quadtree(Node boundary)
{
    nw = nullptr;
    ne = nullptr;
    sw = nullptr;
    se = nullptr;
    this->boundary = boundary;
    objects = std::vector<Data>();
    divided = false;
}

//template <class T>
Quadtree::~Quadtree()
{
    delete nw;
    delete sw;
    delete ne;
    delete se;
}

//template <class T>
void Quadtree::subdivide()
{
    Vector nCentre = boundary.getCentre();

    Vector nHalfSize = boundary.getHalfSize() /= 2;

    nw = new Quadtree(Node(Vector(nCentre - nHalfSize), nHalfSize));
    ne = new Quadtree(Node(Vector(nCentre >> nHalfSize), nHalfSize));
    sw = new Quadtree(Node(Vector(nCentre << nHalfSize), nHalfSize));
    se = new Quadtree(Node(Vector(nCentre + nHalfSize), nHalfSize));

    divided = true;
}

//template <class T>
bool Quadtree::insert(Data d)
{
    if(!boundary.contains(d.getPos()))
    {
        return false;
    }

    if(objects.size() < capacity)
    {
        objects.push_back(d);
        return true;
    }

    if(!divided)
    {
        subdivide();
    }

    if(nw->insert(d))
    {
        return true;
    }
    if(ne->insert(d))
    {
        return true;
    }
    if(sw->insert(d))
    {
        return true;
    }
    if(se->insert(d))
    {
        return true;
    }

    return false;
}

//template <class T>
std::vector<Data> Quadtree::queryRange(Node range)
{
    std::vector<Data> pInRange = std::vector<Data>();

    if(!boundary.intersects(range))
    {
        return pInRange;
    }

    for(auto&& object: objects)
    {
        if(range.contains(object.getPos()))
        {
            pInRange.push_back(object);
        }
    }

    if(nw == nullptr)
    {
        return pInRange;
    }

    std::vector<Data> temp = nw->queryRange(range);
    pInRange.insert(pInRange.end(), temp.begin(), temp.end());

    temp = ne->queryRange(range);
    pInRange.insert(pInRange.end(), temp.begin(), temp.end());

    temp = sw->queryRange(range);
    pInRange.insert(pInRange.end(), temp.begin(), temp.end());

    temp = se->queryRange(range);
    pInRange.insert(pInRange.end(), temp.begin(), temp.end());

    return pInRange;
}