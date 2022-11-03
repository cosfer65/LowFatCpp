#ifndef __CHAPTER4B_H__
#define __CHAPTER4B_H__

// overlaoded functions
void fancy_printer(int i);
void fancy_printer(double d);
void fancy_printer(char* c);
void fancy_printer(int i, char* c);

// default arguments
int multiply(int i, int times = 1);

// a global variable
extern int some_global_int;

// count how many time we run
int run_counter();

// this function will run only once
void function_runs_once();

// recursion
void secondary();
void recur_i();
void recur(int i);

// recursive implementation of the factorial
int recursive_factorial(int n);

int factorial(int n);

// a static array somewhere in our code
// static int myvalues[10];
// the only way to set the values in the array
// is by using this fumction
int& getValue(int index);

// pointers to functions
// function that takes a function pointer as an argument
void run_iteration(void (*iteration_callback)(int));

// using pointers to functions
// first we define the function type
typedef void (*draw_function)();
// and we declare the interface function
void set_draw_function(draw_function function_pointer);

// the interface function
// we call this when we need to change the drawing function
void set_draw_function(draw_function function_pointer);

void main_program_loop();

#endif // __CHAPTER4B_H__
