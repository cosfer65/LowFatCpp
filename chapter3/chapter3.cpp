// chapter3.cpp
//

#include <iostream>

double calc_avarage(double numbers[5])
{
    double avarage = 0;
    for (auto i = 0; i < 5; ++i)
        avarage += numbers[i];
    avarage /= 5;
    return avarage;
}

int count_length(char s[])
{
    int i = 0;
    while (s[i] != '\0') // until the end of the string
    {
        ++i;
    }
    return i;
}

int main()
{
    std::cout << "Hello from chapter 3!\n";

    // array declaration
    // one dimension
    double coords[3]; // or
    double _coords[3]{ 1, 2, 3 }; // or
    double __coords[]{ 1, 2, 3 };
    // two dimensions
    int img[3][4];
    int _img[3][4]{ {1,2,3,4}, {5,6,7,8}, {9,10,11,12} };
    // three dimensions
    int __animation[2][3][4];
    int _animation[2][3][4]{ 1,2,3,4, 5,6,7,8, 9,10,11,12, 1,2,3,4, 5,6,7,8, 9,10,11,12 };
    int animation[2][3][4]{ { {1,2,3,4}, {5,6,7,8}, {9,10,11,12} }, { {1,2,3,4}, {5,6,7,8}, {9,10,11,12} } };

    // accessing array elements
    coords[0] = 1.23;
    double y = coords[2];

    // strings as arrays
    const int string_length = 50;
    char variable_name[string_length];
    char _variable_name[string_length] = "string_initializer";
    char __variable_name[] = "string_initializer";
    char ___variable_name[string_length]{ "string_initializer" };
    char ____variable_name[]{ "string_initializer" };

    char s[20]{ 0 };
    s[0] = 'C';
    s[1] = '+';
    s[2] = '+';
    std::cout << s << "\n";

    // arrays as arguments
    double numbers[]{ 1,2,3,4,6 };
    double average = calc_avarage(numbers);
    std::cout << "the average is :" << average << "\n";

    char str[] = "this is a string we want to test";
    int len = count_length(str);
    std::cout << "length of \"" << str << "\" is:" << len << "\n";


    return 0;
}
