// chapter6.cpp
//

#include <iostream>

// C++ structures

// a point in 3D has three coordinates
struct point
{
    double x;
    double y;
    double z;
};

// an imaginary object in a game
// using another struct as a member variable
struct space_ship
{
    // its location in space
    point location;
    // and its state (whatever that might be)
    int state;
};

void show_array_of_strutcs()
{
    // an array of points
    point the_points[10];

    // iterate through the points, and access their attributes
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

// accessing and mifying structured data
void do_stuff_with_points(point* points, int num_points)
{
    for (auto i = 0; i < num_points; ++i)
    {
        // we always move to the next point regardless of their size
        // no more complex memory access, simple and clear code
        double x = points[i].x; // fetch x
        double y = points[i].y; // fetch y
        double z = points[i].z; // fetch z
        // meaningless calculations but still quite representative
        // of how to access and modify our data
        points[i].x = x + y;
        points[i].y = y + z;
        points[i].z = z + x;
    }
}

// this is an abstract use of structures
void an_application_of_points()
{
#define NUM_POINTS 100
    // allocate NUM_POINTS (100) points
    point* the_points = allocate_points(NUM_POINTS);

    // perform some imaginary calulations
    do_stuff_with_points(the_points, NUM_POINTS);

    // always release the memory when we no longer need it
    delete the_points;
}

// this is how copying a struct works
void copy_simple_structs()
{
    point pt1;
    pt1.x = pt1.y = pt1.z = 1;

    // copy one structure to another
    point pt2 = pt1;
    // this will print "1,1,1"
    std::cout << pt2.x << "," << pt2.y << "," << pt2.z << "\n";
}

// but what happens when we have pointers?
// this is not as simple as a point!
struct complex_geometric_object {
    // dynamic array of points defining the object
    point* the_points;
    // number of points 
    int num_points;
};

void perform_shallow_copy()
{
#define NUM_VERTICES 5
    // this is a shape with 5 vertices (could have as many as we like!)
    complex_geometric_object pent;
    // allocate the points of the object
    pent.the_points = allocate_points(NUM_VERTICES);
    pent.num_points = NUM_VERTICES;

    // create a copy of our original geometric object
    complex_geometric_object pent_copy = pent;

    // now is time to release the dynamically allocated memory
    delete pent.the_points;
    delete pent_copy.the_points;
}

// here is what we could do
// create a function that performs a complete copy
complex_geometric_object custom_copy(complex_geometric_object& original)
{
    // create a shallow copy of the original
    complex_geometric_object copy = original;

    // now we go one step further
    // allocate new memory for the points of the object
    copy.the_points = allocate_points(copy.num_points);
    // use a standard library function to copy the contents
    // of the original object to the copy
    memcpy(copy.the_points, original.the_points, copy.num_points * sizeof(point));

    return copy;
}

void copy_complex_struct()
{
#define NUM_VERTICES 5
    // this is a shape with 5 vertices (could have as many as we like!)
    complex_geometric_object pent;
    // allocate the points of the object
    pent.the_points = allocate_points(NUM_VERTICES);
    pent.num_points = NUM_VERTICES;

    // use our custom copy function
    // shallow copy that occurs now is OK
    // we are copying a pointer that would otherwise be lost!
    complex_geometric_object pent_copy = custom_copy(pent);

    // now is time to release the dynamically allocated memory
    delete pent.the_points;
    delete pent_copy.the_points;
}

// getting a pointer to a struct
// and accessing its members
void pointer_to_struct()
{
    // declare a variable of type point
    point pt;
    // declare a pointer to a point
    // and assign the address of pt
    point* ppt = &pt;

    // set a member of pt
    pt.x = 10;
    // and read it through the pointer
    std::cout << ppt->x << "\n";
    // or
    std::cout << (*ppt).x << "\n";
}

// pointers and references to structs 
void pointers_and_references()
{
    // an array of points
    point points[10];

    // getting a pointer to the first element of the array
    point* ptr = &points[0];
    // or alternatively
    point* _ptr = points;
    // these are equivalent
    // and they all access the first element of the array
    ptr->x = 100;
    (*ptr).x = 100;
    _ptr->x = 100;
    (*_ptr).x = 100;

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
        std::cout << "we are IDLE\n";
        break;
    case walking:
        std::cout << "we are WALKING\n";
        break;
    case running:
        std::cout << "we are RUNNING\n";
        break;
    case jumping:
        std::cout << "we are JUMPING\n";
        break;
    default:  // if we add more states in the enum
              // and forget to update the code
              // we get a runtime warning
        std::cout << "unhandled case!!!\n";
        break;
    }
}

int main()
{
    std::cout << "Hello from chapter 6!\n";

    show_array_of_strutcs();
    an_application_of_points();
    copy_simple_structs();
    copy_complex_struct();
    show_state();

    return 1;
}
