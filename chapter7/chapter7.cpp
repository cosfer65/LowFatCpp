// chapter7.cpp
//

#include <iostream>

// a point in 3D class
class point
{
public:
    double x;
    double y;
    double z;

    // this constructor does it all
    // it accepts initial values and provides default ones
    point(double _x = 0, double _y = 0, double _z = 0) :x(_x), y(_y), z(_z) {
        std::cout << "point created\n";
    }
    /* so these two constructors are obsolete
    point(double _x, double _y, double _z) :x(_x), y(_y), z(_z) {
        std::cout << "point created\n";
    }
    point(){
        x = y = z = 0;
        std::cout << "point created\n";
    }
    */
    // copy constructor
    point(const point& pt) :x(pt.x), y(pt.y), z(pt.z) {
        std::cout << "point copy-created\n";
    }
    // the class destructor
    ~point() {
        std::cout << "~point deleted\n";
    }
};

// a better implementation of the point class
class vertex
{
private:
    // hide implementation details
    double coordinates[3]; // use an array instead of distinct variables

public:
    vertex(double _x = 0, double _y = 0, double _z = 0) :coordinates{ _x,_y,_z } {
        std::cout << "vertex created\n";
    }
    vertex(const vertex& pt) :coordinates{ pt.coordinates[0], pt.coordinates[1], pt.coordinates[2] } {
        std::cout << "vertex copy-created\n";
    }
    ~vertex() {
        std::cout << "vertex deleted\n";
    }
    // we use functions to access the data
    // we still support x,y and z that everyone understands
    // and we use references to directly set coordinates
    double& x() {
        return coordinates[0];
    }
    double& y() {
        return coordinates[1];
    }
    double& z() {
        return coordinates[2];
    }

    // the following function reads member variables
    // and should no modify them
    double get_x() const
    {
        // coordinates[0] = 10; // generates error, read only member function
        return coordinates[0];
    }

    // operator overloading
    // adding two points creates a new point by adding coordinates
    vertex operator+(const vertex& pt)
    {
        return vertex(coordinates[0] + pt.coordinates[0],
            coordinates[1] + pt.coordinates[1],
            coordinates[2] + pt.coordinates[2]);
    }

};

class coin {
public:
    coin() {}
};
class banknote {
public:
    banknote() {}
};
class wallet {
public:
    wallet() {}
    void input(coin* c) { /* handle accordingly */ }
    void input(banknote* b) { /* handle accordingly */ }
};


int main()
{
    std::cout << "Hello from chapter 7!\n";

    // create some points
    point start_point(1, 1, 1);
    point end_point;

    point p1(1, 2, 3);  // create the first point
    // use copy constructor
    point p2(p1);       // create the second copying the first
    point p3 = p2;      // this is equivalent to the above

    vertex v1(1, 2, 3);  // create a point
    v1.y() = 10;         // setting a coordinate
    std::cout << v1.y() << "\n";   // and reading it

    // constants
    const int c = 10;     // const variable
    const int& cr = c;    // reference to const variable
    const int* cp = &c;   // pointer to const variable
    // the following statements generate errors
    // because we  try to modify constant data
    /*
    c = 1;
    cr = 2;
    *cp = 3;
    */ 

    int i, j;
    int* const pi = &i;  // constant pointer initialized
    *pi = 10;            // ok to change content
    //pi = &j;             // error, constant pointer

    // with operator overloading
    // this code is perfectly valid
    vertex _p1(1, 2, 3);    // create a point
    vertex _p2(2, 3, 4);    // create another point
    vertex _p3 = _p2 + _p1;   // and now add them to create a third

    // dynamic memory allocation
    point* ptr = new point(1, 2, 3);
    point* ptr2 = new point(*ptr);

    // simple array allocation
    point* dp = new point[5];
    // allocation with initializers
    point* _dp = new point[5]{ {1, 4, 5},{2, 5, 6},{3, 6, 7},{4, 7, 8},{5, 8, 9} };

    // delete an array of objects
    delete[] dp;
    delete[] _dp;
    // delete one object
    delete ptr;

    return 0;
}
