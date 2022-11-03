// chapter6.cpp
//

#include <iostream>

// C++ structures
struct object
{
    double x;
    double y;
    double z;

    int state;
};
object o;

// a point in 3D has three coordinates
struct point
{
    double x;
    double y;
    double z;
};
void some_function()
{
    // an array of points
    point the_points[10];

    // iteration through the points
    for (auto i = 0; i < 10; ++i)
        the_points[i].x = 10;
}

// dynamic memory allocation with pointers
point* allocate_points(int num_points)
{
    // we simply request memory enough for our points
    // the call is similar to the one dimensional array
    // it IS an one dimensional array of points
    point* coords = new point[num_points];

    // and return the allocated memory
    return coords;
}

void do_stuff_with_points(point* points, int num_points)
{
    for (auto i = 0; i < num_points; ++i)
    {
        // we always move to the next point regardless of their size
        // no more complex memory access, simple and clear code
        double x = points[i].x; // fetch x
        double y = points[i].y; // fetch y
        double z = points[i].z; // fetch z
    }
}

void a_function_dealing_with_points()
{
#define NUM_POINTS 100
    point* the_points = allocate_points(NUM_POINTS);

    do_stuff_with_points(the_points, NUM_POINTS);

    // always release the memory when we no longer need it
    delete the_points;
}

void copy_simple_structs()
{
    point pt1;
    pt1.x = pt1.y = pt1.z = 1;

    // copy one structure to another
    point pt2 = pt1;
    // this will print "1,1,1"
    std::cout << pt2.x << "," << pt2.y << "," << pt2.z << "\n";
}

struct complex_geometric_object {
    // dynamic array of points defining the object
    point* the_points;
    // number of points 
    int num_points;
};

void copy_complex_struct()
{
#define NUM_POINTS 100

    complex_geometric_object cgo;
    // allocate the points of the object
    cgo.the_points = allocate_points(NUM_POINTS);
    cgo.num_points = NUM_POINTS;

    // create a copy of our original geometric object
    complex_geometric_object cgo_copy = cgo;

    // now is time to release the dynamically allocated memory
    delete cgo.the_points;
    delete cgo_copy.the_points;
}



    // allocate the points of the object
    cgo_copy.the_points = allocate_points(cgo.num_points);
    cgo_copy.num_points = cgo.num_points;

}

void cpp_structures2()
{
    struct dtype {
        int* ar;
        int br[5];
        int l;
    };
    dtype v1, v2;

    // allocating the pointer results in a valid pointer
    v1.ar = new int[10];      //remember to DELETE

    // copying here, copies to ‘br’ invalid uninitialized data
    // but ‘ar’ pointer is valid and copied to the second
    v2 = v1;

    // set ‘br’ in ‘v1’
    for (int i = 0; i < 5; ++i)
        v1.br[i] = i + 101;

    // see what we have copied so far
    for (int i = 0; i < 10; ++i)
        std::cout << v2.ar[i] << "\n";
    for (int i = 0; i < 5; ++i)
        std::cout << "--" << v2.br[i] << "\n";

    // copying here, valid data to ‘br'
    v2 = v1;

    for (int i = 0; i < 10; ++i)
        std::cout << v2.ar[i] << "\n";
    for (int i = 0; i < 5; ++i)
        std::cout << "--" << v2.br[i] << "\n";

    // now we set in ‘v1’ but we actually modify ‘v2’ as well
    for (int i = 0; i < 10; ++i)
        v1.ar[i] = i + 11;

    for (int i = 0; i < 10; ++i)
        std::cout << v2.ar[i] << "\n";
    for (int i = 0; i < 5; ++i)
        std::cout << "--" << v2.br[i] << "\n";
}

void pointers_and_references()
{
    // an array of points
    point points[10];

    point* ptr = &points[0];
    // or alternatively
    point* _ptr = points;
    ptr->x = 100;
    (*ptr).y = 200;

    // a point variable
    point pt;
    // and a reference to it
    point& rpt = pt;

    // we set the variable
    pt.x = 123;
    // and read the reference
    std::cout << rpt.x << "\n";
}

// enumearions
enum states { idle, walking, running, jumping };
void show_state(states my_state = idle)
{
    switch (my_state)
    {
    case idle:
        // we do some stuff
        break;
    case walking:
        // we do some stuff
        break;
    case running:
        // we do some stuff
        break;
    case jumping:
        // we do some stuff
        break;
    default:  // if we add more states in the enum
              // and forget to update the code
              // we get a runtime warning
        std::cout << "unhandled case!!!\n";
        abort();  // crash the program to force a fix
        break;
    }
}

int main()
{
    std::cout << "Hello from chapter 6!\n";

    some_function();
    cpp_structures();
    pointers_and_references();
    show_state();

    return 1;
}
