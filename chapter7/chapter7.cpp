// chapter7.cpp
//

#include <iostream>

// a point in 3D class
class    point
{
    double x;
    double y;
    double z;

public:
    // this constructor does it all
    // it accepts initial values and provides default ones
    point(double _x = 0, double _y = 0, double _z = 0) :x(_x), y(_y), z(_z) {
        std::cout << "point created\n";
    }
    // copy constructor
    point(const point& pt) :x(pt.x), y(pt.y), z(pt.z) {
        std::cout << "point copy-created\n";
    }
    // the class destructor
    ~point() {
        std::cout << "~point deleted\n";
    }
    // member function that moves (translates) the point
    void translate(double _x, double _y, double _z) {
        x += _x;
        y += _y;
        z += _z;
    }
    point operator+(const point& pt)
    {
        return point(x + pt.x, y + y, z + z);
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
    const double& x() const {
        return coordinates[0];
    }
    double& y() {
        return coordinates[1];
    }
    double& z() {
        return coordinates[2];
    }

    void translate(double x, double y, double z) {
        coordinates[0] += x;
        coordinates[1] += y;
        coordinates[2] += z;
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

// this function takes a reference to a constant string
void print_out_string(const std::string& str)
{
    // this is a legitimate use of the constant variable
    // reading its value is fine
    std::cout << str << "\n";

    // if we try to modify the string 
    // a compilation error is generated
    // uncomment this line and try to compile
    // srt = "some other value";
}

void call_print()
{
    std::string str("hello world");
    // we can call the function passing it some veriable
    print_out_string(str);
    // or we can create a temporary argument on the stack
    print_out_string("temporary value");
}

class solid_body {
    double m_mass;
public:
    solid_body(double m = 0) :m_mass(m) {}

    // this function gives read only access to the object's mass
    const double& mass() { return m_mass; }
};

class point2d {
    double x;
    double y;
public:
    point2d(double _x = 0, double _y = 0) :x(_x), y(_y) {}
    // the following function reads member variables
    // and should no modify them
    double get_x() const {
        std::cout << "constant function:" << x << "\n";
        return x;
    }
    // the following function modifies member variables
    double get_x() {
        x = 10;
        std::cout << "non constant function:" << x << "\n";
        return x;
    }
};

void demo_const_function()
{
    point2d p(0, 0);
    const point2d cp = p;
    // notice which overloaded function is called 
    // based on weather the object is const
    std::cout << p.get_x() << ", " << cp.get_x() << "\n";
}

int main()
{
    std::cout << "Hello from chapter 7!\n";

    demo_const_function();
    return 0;
}
