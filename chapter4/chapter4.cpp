// chapter4.cpp
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
void read_position(double* x, double* y, double* z)
{
    *x = 1;
    *y = 2;
    *z = 3;
}

void read_position_byref(double& x, double& y, double& z)
{
    x = 10;
    y = 20;
    z = 30;
}

// this is a call by value
void show_position(double x, double y, double z)
{
    std::cout << "x:" << x << " y:" << y << " z:" << z << "\n";
}

// dynamic memory allocation wit pointers
void allocate_one_dimensional(int num_points)
{
    // allocate 3 doubles for each point (x,y,z)
    double* coords = new double[num_points * 3];
    // do what we want with the points
    for (auto i = 0; i < num_points; ++i)
    {
        // remenber we must move with a step of columns
        double x = coords[i * 3];     // x is first
        double y = coords[i * 3 + 1]; // y is second
        double z = coords[i * 3 + 2]; // z is third
    }
    // release the memory
    delete[] coords;
}

// and now an inefficient way to do it
void allocate_two_dimensional(int num_points)
{
    // first allocate a pointer for each point
    double** coords = new double* [num_points];
    // then allocate memory for each point
    for (auto i = 0; i < num_points; ++i)
        coords[i] = new double[3];

    // play with the points
    for (auto i = 0; i < num_points; ++i)
    {
        // remenber we must move with a step of columns
        double x = coords[i][0];     // x is first
        double y = coords[i][1]; // y is second
        double z = coords[i][2]; // z is third
    }
    // release each point
    for (auto i = 0; i < num_points; ++i)
        delete[] coords[i];
    // and finally release the pointers array
    delete[] coords;
}


int main()
{
    std::cout << "Hello from chapter 4!\n";

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
    read_position(&x, &y, &z);
    // and pass it to another by value
    show_position(x, y, z);

    // and we call the function passing it their references
    read_position_byref(x, y, z);
    // and pass it to another by value
    show_position(x, y, z);

    return 0;
}
