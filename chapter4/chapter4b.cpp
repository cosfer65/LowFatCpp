// chapter4b.cpp
//

#include <iostream>
#include "chapter4b.h"

// overlaoded functions
void fancy_printer(int i)
{
    std::cout << "integer:" << i << "\n";
}
void fancy_printer(double d)
{
    std::cout << "double:" << d << "\n";
}
void fancy_printer(char* c)
{
    std::cout << "character:" << c << "\n";
}
void fancy_printer(int i, char* c)
{
    std::cout << "integer:" << i << ", text:" << c << "\n";
}

// default arguments
int multiply(int i, int times/* = 1 */)
{
    return i * times;
}

// the arguments are local variables initialized automatically
// with the values we pass in the function call
// notice the pointer! it holds an address not a value
void local_variables(int i, double* d)
{
    //int j;

    for (int k = 0; k < 10; ++k)
    {
        std::cout << k << "\n";
    }

    //++k;   // error k is out of scope

    // perdectly valid statement, only the value is NOT returned
    // the variable has this value until the end of the function
    i = 100;

    if (i > 10)
    {
        double l = 100 * (*d);
    }

    //std::cout << l << "\n";  // error l is out of scope
}

// a global variable
int some_global_int = 0;

// count how many time we run
int run_counter()
{
    // start with initialization
    static int count = 0;
    // count
    ++count;
    // and return current status
    return count;
}

// this function will run only once
void function_runs_once()
{
    // initialize a static variable to 0
    static int i = 0;
    // if the value of it is 1 return
    // and ignore the rest of the code
    if (i == 1)
        return;
    // set the value to 1
    i = 1;
    // the code from this point on runs only once
}

// indirect recursion
// one function is calling the other
void recur_i();
void secondary()
{
    recur_i();
}
void recur_i()
{
    secondary();
}

// direct recursion
// function calling itself
void recur(int i)
{
    // make sure that recursion will terminate
    if (i<100)
        recur(i+1);
}

// recursive implementation of the factorial
int recursive_factorial(int n)
{
    // according to the mathematical definition
    if (n <= 1)
        return 1;
    // proceed recursively
    return n * recursive_factorial(n - 1);
}

int factorial(int n)
{
    int f = 1;
    for (auto i = 1; i <= n; ++i)
        f *= i;
    return f;
}

// a static variable
// it is not accessible to functions outside this file
static int myvalues[10];
// the only way to set the values in the array
// is by using this fumction
int& getValue(int index)
{
    // if the index is within the array
    // return the appropriate eleent
    if (index >= 0 && index < 10)
        return myvalues[index];
    // othewise return a default variable variable
    // the variable must be static
    static int default_value = 0;
    return default_value;
}

// pointers to functions
// function that takes a function pointer as an argument
void run_iteration(void (*iteration_callback)(int))
{
    // do some task
    // and call a user defined function 
    // when needed
    for (auto i = 0; i < 10; ++i)
        iteration_callback(i);
}

// using pointers to functions
// game_core.h
// this is the header containing core declarations about the game

// first we define the function type
typedef void (*draw_function)();
// and we declare the interface function
void set_draw_function(draw_function function_pointer);

//---------------------------------------------------------

// game_core.cpp
// include game definitions
//#include "game_core.h"

// this is the default draw function
static void draw_idle()
{
}
// we create a pointer and initialize it to the default function
static draw_function draw = draw_idle;

// the interface function
// we call this when we need to change the drawing function
void set_draw_function(draw_function function_pointer)
{
    draw = function_pointer;
}

void main_program_loop()
{
    bool we_are_happy_with_the_game = true;
    while (we_are_happy_with_the_game) {
        // do our gaming stuff
        // and finally call draw to update the scene
        draw();
    }
}
