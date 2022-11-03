// chapter5.cpp
//

#include <iostream>

// eliminate duplicate integers in a sorted array of length len
int array_compactor(int* arr, int len)
{
    // we read and write ath the same array
    // the rading pointer advances at every iteration
    // while the writing stays while we encounter douplicates

    // we need a pointer to the writing position
    // initialy set at the start of the array
    int* wr = arr;
    // advance the reading pointer
    ++arr;
    // the length of the 'clear' array is at least 1
    int l = 1;
    // the reading pointer is at the first position
    // at advance the reading position and the reading counter
    // until we reach the array length
    for (auto i = 1; i < len; ++i, ++arr)
    {
        // if the current element is not the same as the previous
        // wr points to the previous and arr to the current
        if (*wr != *arr)
        {
            // advance the writing pointer one position
            ++wr;
            // and the length of the 'clean' array
            ++l;
        }
        // copy the content of the reading position
        // to the writing positin
        *wr = *arr;
    }
    // return the number of unique elements
    return l;
}

// chack if the string is palindrome
bool is_palindrome(char* arr)
{
    // setup initial conditions
    // a pointer to the first character
    char* start = arr;
    // and anoter one to the last
    char* term = arr; // start at the beginning
    while (*term != '\0')  // go to the terminating '\0'
        ++term;
    --term;  // and back up to the last charachter

    // the term pointer points to higher address
    while (term > start)   // and while this is true
    {
        // if the characters at the opposite sides
        // are not the same, return false
        if (*term != *start)
            return false;
        // otherwise advance the start pointer
        // and back up the term pointer
        // this way we examine symmtrical positions
        // and the pointers will cross at the middle of the string
        // when they cross the loop will break
        ++start;
        --term;
    }
    // reaching this point means no error was found
    // it is safe to return true
    return true;
}

// this function takes the addresses of the variables
// we can modify the contents of the addresses aka 
// the variable in the calling function
void read_position(double* x, double* y, double* z)
{
    *x = 1;
    *y = 2;
    *z = 3;
}

// C++ introduced the concept of reference
// these are ordinary looking variables that actualy refer to other variables
// this wa we can modify the original ones without the odd syntax above
// he compiler takes care of everything
// here we also use the feature of function overloading
// this function and the one above have the same name
// but they have different types of arguments
// this allows the compiler to select the correct one when we call them.
void read_position(double& x, double& y, double& z)
{
    x = 10;
    y = 20;
    z = 30;
}

// this is a call by value
// we only need a read only access so we just create 
// temporary copies of the values of the variables
void show_position(double x, double y, double z)
{
    std::cout << "x:" << x << " y:" << y << " z:" << z << "\n";
}

void do_stuff_with_points(double* points, int num_points)
{
    for (auto i = 0; i < num_points; ++i)
    {
        // remember each point takes up three places
        double x = points[i * 3];     // x is first
        double y = points[i * 3 + 1]; // y is second
        double z = points[i * 3 + 2]; // z is third
    }
}

void do_stuff_with_points(double** points, int num_points)
{
    for (auto i = 0; i < num_points; ++i)
    {
        // remember each point takes up three places
        double x = points[i][0];     // x is first
        double y = points[i][1]; // y is second
        double z = points[i][2]; // z is third
    }
}

// dynamic memory allocation with pointers
double* allocate_one_dimensional(int num_points)
{
    // allocate 3 doubles for each point (x,y,z)
    double* coords = new double[num_points * 3];

    // and return the allocated memory
    return coords;
}

// and now an inefficient way to do it
double** allocate_two_dimensional(int num_points)
{
    // first allocate a pointer for each point
    double** coords = new double* [num_points];
    // then allocate memory for each point
    for (auto i = 0; i < num_points; ++i)
        coords[i] = new double[3];

    // this method is not efficient and should not be used for such simple cases
    // it is presented here for educational purposes only

    return coords;
}

void dynamic_memory_demo()
{
#define NUM_POINTS 100

    double* points = allocate_one_dimensional(NUM_POINTS);
    // do what we want with the points
    do_stuff_with_points(points, NUM_POINTS);
    // always release the memory when we no longer need it
    delete[] points;

    // and now an inefficient way to do it
    double** points2 = allocate_two_dimensional(NUM_POINTS);
    // do what we want with the points
    do_stuff_with_points(points2, NUM_POINTS);
    // always release the memory when we no longer need it
    // this time releasing the memory is not so easy
    // release each point
    for (auto i = 0; i < NUM_POINTS; ++i)
        delete[] points2[i];
    // and finally release the pointers array
    delete[] points2;
}

int main()
{
    std::cout << "Hello from chapter 5!\n";

    int var = 0;
    int* ptr = &var;  // get a reference to var via its address

    *ptr = 10;    // we actually modify var
    std::cout << "var=" << var << "\n";

    // an array of integers
    int iarr[10];
    // accessed via a pointer
    // the array variable itself is a pointer
    ptr = iarr; // or
    // we car get a pointer to the first element
    ptr = &iarr[0];

    // ------------------------

    // create a sorted array with duplicate elements
    int arr[]{ 1,2,2,2,2,3,4,4,5,5,6,7,7,8,9,10 };
    // use the sizeof operator to count the number of elements
    // we divide the size of the memory allocated by the size of the element
    int len = sizeof(arr) / sizeof(int);

    // call our function to 'clean' the array
    // and return the number of unique elements
    len = array_compactor(arr, len);
    // after the call the array is NOT shorter
    // we just moved the unique elements in the first len positions

    // print the 'clean' part of the array
    // we could use arr[i] notation but we are using pointer aritmetic
    for (auto i = 0; i < len; ++i)
        std::cout << *(arr + i) << ",";
    std::cout << "\n";

    // ---------------------------------------
    // const means that the string cannot me modified
    // const char* str = "abcdedcba";
    char str[] = "abcdedcba";
    if (is_palindrome(str))
        std::cout << "palindrome\n";
    else
        std::cout << "not palindrome\n";


    // ---------------------------------------
    // here we declare our viriables
    double x, y, z;
    // and we call the function passing it their addresses
    // the called function will set the values of our variables
    read_position(&x, &y, &z);
    // and pass it to another by value
    show_position(x, y, z);

    // the same job done in the C++ way
    // and we call the function passing it their references
    // the called function will set the values of our variables
    read_position(x, y, z);
    // and pass it to another by value
    show_position(x, y, z);


    return 0;
}
