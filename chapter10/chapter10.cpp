// chapter10.cpp
//

#include <tuple>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

void pairs_and_tuples()
{
    std::cout << "TEST pairs and tuples\n";
    std::pair<int, double> id(1, 2.5);
    std::cout << id.first << ", " << id.second << "\n";
    std::pair<int, double> id2 = id;
    id2.first = 0;
    id2.second = 100;
    std::cout << id2.first << ", " << id2.second << "\n";
    // the ordering is done using the first element
    if (id > id2)
        std::cout << "id is bigger\n";
    else
        std::cout << "id is smaller\n";

    std::tuple<int, int, float> t(1, 2, float(3));
    t = std::make_tuple(3, 4, float(5));
    std::get<2>(t) = 100;
    std::cout << std::get<0>(t) << ", " << std::get<1>(t) << ", " << std::get<2>(t) << "\n";
}
///////////////////////////////////////////////////////////////////////////////////////////

class worker {
public:
    int i;
    std::weak_ptr<worker> leader;
    std::shared_ptr<worker> partner;

    worker(int _i = 0) : i(_i) {
        std::cout << i << " worker created\n";
    }
    ~worker() {
        std::cout << i << " worker destroyed\n";
    }
    void talk() {
        std::cout << i << " i am a worker\n";
    }
};
///////////////////////////////////////////////////////////////////////////////////////////

void test_shared_ppointer()
{
    std::cout << "TEST shared pointers\n";
    // create a place to store the data
    std::shared_ptr<worker> w[3];
    // create a local scope
    {
        std::shared_ptr<worker> sw(new worker);
        sw->i = 100;  // accessing the member variable
        //w[0] = sw;
        //w[1] = sw;
        w[2] = sw;
        // the smart pointer is not deleted here, at the end of scope
        // comment out the above 3 lines and see theresult
    }
    std::cout << w[2]->i << " ---------\n";
    // the smart pointer is deleted after this point
    // when the references to it go out of scope
}
///////////////////////////////////////////////////////////////////////////////////////////

std::shared_ptr<worker> create_team()
{
    std::shared_ptr<worker> l(new worker(1));
    std::shared_ptr<worker> p(new worker(2));
    l->partner = p;
    p->leader = l;

    return l;
}

void test_weak_pointer()
{
    std::cout << "TEST weak pointers\n";
    std::shared_ptr<worker> lead = create_team();
    std::cout << "--------\n";
    // make w2 'talk' 
    lead->partner->talk();
}
///////////////////////////////////////////////////////////////////////////////////////////

void cause_error()
{
    throw std::runtime_error("error");
}

// unique pointer cannot be copied
// the call MUST be with reference
void use_pointer(std::unique_ptr<worker>& ptr)
{
    ptr->talk();
}

void raw_pointer(worker* ptr)
{
    std::cout << "raw:";
    ptr->talk();
}

void test_unique_ptr()
{
    std::cout << "TEST unique pointers\n";
    std::unique_ptr<worker> u(new worker(1));
    // asigning new pointer to 'u' automatically deletes old pointer
    u = std::unique_ptr<worker>(new worker(2));
    // we can get the raw worker pointer

    worker* w = u.get();
    // and use it, but it is not recomended
    raw_pointer(w);

    // this bypasses unique_ptr and will crash the program
    //std::unique_ptr<worker> d(w);

    try {
        cause_error();
        std::cout << "fine!!\n";  // no exception thrown
    }
    catch (...) {  // an exception was thrown
        // unique pointers work with exceptions!
        std::cout << "error!!\n";
    }
    use_pointer(u);
    // transfer ownership to 'cp'
    std::unique_ptr<worker> cp = move(u);
    // 'u' is now invalid, so we use 'cp'
    use_pointer(cp);
}

template<class T>
class pointer_handler {
public:
    T* ptr;
    pointer_handler(T* w = NULL) :ptr(w) {}
    ~pointer_handler() {
        if (ptr) delete ptr;
        ptr = NULL;
    }
};

void test_raw()
{
    pointer_handler<worker> rh(new worker(5));
    // this crashes the program
    //pointer_handler<worker> rh1 = rh;
}

///////////////////////////////////////////////////////////////////////////////////////////
#include <cassert>
template<class T>
class pointer_check {
public:
    T ob;
    pointer_check(const T t) {
        if (std::is_arithmetic<T>::value)
        {
            std::cout << "value OK\n";
            ob = t;
        }
        else
        {
            std::cout << "error not a number\n";
            assert(0);
        }
    }
};

void string_sample()
{
    std::string s1("this is ");
    std::string s2("a string");
    std::string s3(s1 + s2);
    std::cout << s3 << "\n";

    // use the C printf function to print the string
    // this function requires a char* pointer
    printf("%s\n", s3.c_str());

    // append some text
    s3 += " for testing";
    std::cout << s3 << "\n";
    // get a substring from position 2 and of length 6
    std::cout << s3.substr(2, 6) << "\n";
    // replace fro char 2 to 4 with the string 'lala'
    s3.replace(2, 4, "lala");
    std::cout << s3 << "\n";
    // find 'str' and print from there to the end of string
    size_t p = s3.find("str");
    if (p != std::string::npos) std::cout << s3.substr(p) << "\n";
    // use array notation to access characters
    std::cout << "sixth character=" << s3[5] << "\n";
}



///////////////////////////////////////////
// function objects
// our compare function object
template<class T>
class compare {
public:
    bool operator()(T l, T r) {
        // return the comparison result
        return l < r;
    }
};

// simple templated function to find an extreme value
// in a vector of T using the function object above
// if no comare type is given <int> is assumed
template<class T, class comp = compare<int>>
T find_extreme(std::vector<T>& v)
{
    comp c;   // create the compare object
    T ex = v[0];  // the first is the extreme
    // iterate vector
    for (auto it = v.begin(); it != v.end(); ++it)
    {
        // if a new extreme is found, store it
        if (c(ex, *it))
            ex = *it;
    }
    // return extreme
    return ex;
}

void functor_sample()
{
    std::cout << "function object sample\n";
    std::vector<int> v;
    for (int i : {1, 8, 5, 6, 3, 4, 0, 9, 7, 2})
        v.push_back(i);
    // first run with default compare template
    auto r = find_extreme<int>(v);
    std::cout << "extreme int value:" << r << "\n";

    std::vector<double> d;
    for (double i : {1.2, 8.3, 5.4, 6.5, 3.6, 4.7, 0.8, 9.9, 7.1, 2.2})
        d.push_back(i);
    // for second run we request compare for doubles
    auto q = find_extreme<double, compare<double>>(d);
    std::cout << "extreme double value:" << q << "\n";
}

//////////////////////////////////////////////////////////////////////////////
// lamda functions
// 
// this function iterates the vector and
// counts how many times the 'func' returns true
template<class T, class func>
int count_objects(std::vector<T>& v, func f)
{
    int count = 0;
    for (auto it = v.begin(); it != v.end(); ++it)
    {
        if (f(*it))
            ++count;
    }
    return count;
}

void labda_sample()
{
    // basic lambda, we create an inline function
    auto greet = []() {std::cout << "lambda sample\n"; };
    greet();

    std::vector<int> v;
    for (int i : {1, 8, 3, 4, 0, 9, 7, 2, 1, 3, 5, 6, 3, 4, 7, 2, 1, 8, 5, 6, 3, 9, 7, 2})
        v.push_back(i);
    // count how many '3's are in the vector
    auto se = [](int i) { return i == 3; };
    std::cout << "found:" << count_objects(v, se) << "\n";

    // count how many numbers in the vector are between 3 and 7
    // we can write the code inline, but it is not so readable
    std::cout << "found:" << count_objects(v, [](int i) { return i >= 3 && i <= 7; }) << "\n";

    int x = 2;
    // here we define a labbda function that returns 'bool'
    // the return type in this example is optional
    // it is also accessing access the local variable by value
    auto l = [=](int y) ->bool { return y * x; };
    std::cout << "result:" << l(3) << "\n";

    // here we are accessing x by reference
    auto lr = [&](int y) {++x; return y * x; };
    std::cout << "result:" << x << ", " << lr(4) << "\n";
}

///////////////////////////////////////////////////////////////////////////
// algorithms

class point {
public:
    int x, y;
    point(int _x = 0, int _y = 0) :x(_x), y(_y) {}
    ~point() {}
};

void foreach_sample()
{
    std::cout << "first sample\n";

    std::vector<point> v;
    for (auto i = 0; i < 5; ++i)
        v.push_back(point(i + 1, i + 2));

    // from the first point to the last apply the lambda function
    // move all the points by a fixed amount
    std::for_each(v.begin(), v.end(), [](point& p) {p.x += 2; p.y += 7; });
    // print the coordinates of all the points
    std::for_each(v.begin(), v.end(), [](point& p) {std::cout << p.x << ", " << p.y << "\n"; });
}

void sort_sample()
{
    std::cout << "sort sample\n";
    std::vector<std::pair<int, std::string>> v;
    int count = 1;
    for (int i : {1, 8, 5, 6, 3, 4, 0, 9, 7, 2})
    {
        std::string name = "object " + std::to_string(count++);
        v.push_back(std::pair<int, std::string>(i, name));
    }

    std::cout << "unsorted vector\n";
    std::for_each(v.begin(), v.end(), [](std::pair<int, std::string>& p)
        {std::cout << p.first << ", " << p.second << "\n"; });
    std::cout << "sorted by their integer\n";
    std::sort(v.begin(), v.end());
    std::for_each(v.begin(), v.end(), [](std::pair<int, std::string>& p)
        {std::cout << p.first << ", " << p.second << "\n"; });
    std::cout << "sorted by their string\n";
    std::sort(v.begin(), v.end(), [](std::pair<int, std::string>& l, std::pair<int, std::string>& r)
        {return l.second > r.second; });
    std::for_each(v.begin(), v.end(), [](std::pair<int, std::string>& p)
        {std::cout << p.first << ", " << p.second << "\n"; });
}

void partial_sort_sample()
{
    std::cout << "partial_sort sample\n";
    std::vector<std::pair<int, std::string>> v;
    int count = 1;
    for (int i : {10, 8, 5, 6, 3, 4, 0, 9, 7, 2, 11, 13, 19, 17, 16, 14, 12, 15, 18, 1})
    {
        std::string name = "object " + std::to_string(count++);
        v.push_back(std::pair<int, std::string>(i, name));
    }
    std::for_each(v.begin(), v.end(), [](std::pair<int, std::string>& p)
        {std::cout << p.first << ", " << p.second << "\n"; });
    std::cout << "---------------\n";
    std::partial_sort(v.begin(), v.begin() + 7, v.begin() + 12);
    std::for_each(v.begin(), v.end(), [](std::pair<int, std::string>& p)
        {std::cout << p.first << ", " << p.second << "\n"; });
}

class foo {
public:
    int x;
    std::string s;
    foo(int xx = 0, std::string ss = "") :x(xx), s(ss) {
    }
    // overloaded operators to be used by std::find
    // find integer
    bool operator==(int i) {
        if (i == x)
            return true;
        return false;
    }
    // find matching object
    bool operator==(const foo& f) {
        if (f.x == x && f.s == s)
            return true;
        return false;
    }
    // find string
    bool operator==(const std::string& _s) {
        if (_s == s)
            return true;
        return false;
    }
};

void find_sample()
{
    std::cout << "find sample\n";
    std::vector<foo> v;
    int count = 1;
    for (int i : {10, 8, 5, 6, 3, 4, 0, 9, 7, 2, 11, 13, 19, 17, 16, 14, 12, 15, 18, 1})
    {
        std::string name = "object " + std::to_string(count++);
        v.push_back(foo(i, name));
    }

    auto p = std::find(v.begin(), v.end(), "object 4");
    if (p != v.end())
        std::cout << "found:" << p->x << ", " << p->s << "\n";
    else
        std::cout << "not found\n";
}

void find_if_sample()
{
    std::cout << "find if sample\n";
    std::vector<foo> v;
    int count = 1;
    for (int i : {10, 8, 5, 6, 3, 4, 0, 9, 7, 2, 11, 13, 19, 17, 16, 14, 12, 15, 18, 1})
    {
        std::string name = "object " + std::to_string(count++);
        v.push_back(foo(i, name));
    }

    auto p = std::find_if(v.begin(), v.end(), [](const foo& f)
        {return f.s == "object 8"; });
    if (p != v.end())
        std::cout << "find_if:" << p->x << ", " << p->s << "\n";
    else
        std::cout << "not found\n";

    auto p1 = std::find_if_not(v.begin(), v.end(), [](const foo& f)
        {return f.s == "object 8"; });
    if (p1 != v.end())
        std::cout << "find_if_not:" << p1->x << ", " << p1->s << "\n";
    else
        std::cout << "not found\n";
}

void find_first_of_sample()
{
    std::cout << "find_first_of sample\n";
    // our data
    std::vector<int> v{ 10, 8, 5, 6, 3, 4, 0, 9, 7, 2, 11, 13, 19, 17, 16, 14, 12, 15, 18, 1 };
    // what we are looking for
    std::vector<int> s{ 1,2,3 };

    // find the first occurance of any element of 's' in 'v'
    auto f = std::find_first_of(v.begin(), v.end(), s.begin(), s.end());
    if (f != v.end())
        std::cout << "find_first_of:" << *f << "\n";
    else
        std::cout << "not found\n";
}

void bounds_sample()
{
    std::cout << "bounds sample\n";
    std::vector<int> v{ 10, 8, 5, 6, 3, 4, 0, 9, 5, 2, 11, 13, 19, 17, 16, 5, 12, 15, 18, 1 };
    std::sort(v.begin(), v.end());
    auto s = std::lower_bound(v.begin(), v.end(), 5);
    auto e = std::upper_bound(v.begin(), v.end(), 5);
    for (auto p = s; p != e; ++p)
    {
        std::cout << *p << "\n";
    }
}

void copy_sample()
{
    std::cout << "copy sample\n";
    std::vector<int> v{ 10, 8, 5, 6, 3, 4, 0, 9, 5, 2, 11, 13, 19, 17, 16, 5, 12, 15, 18, 1 };
    std::vector<int> l;

    // copy 4 items in l
    std::copy(v.begin(), v.begin() + 4, std::back_inserter(l));
    // print the result
    std::for_each(l.begin(), l.end(), [](int p) {std::cout << p << "\n"; });
    std::cout << "-----------\n";
    // copy te odd numbers to another vector
    std::vector<int> odds;
    std::copy_if(v.begin(), v.end(), std::back_inserter(odds), [](int i) {return i % 2; });
    std::for_each(odds.begin(), odds.end(), [](int p) {std::cout << p << "\n"; });
}

void remove_sample()
{
    std::cout << "remove sample\n";
    std::vector<int> v{ 10, 8, 5, 6, 3, 4, 0, 9, 5, 2, 11, 13, 19, 17, 16, 5, 12, 15, 18, 1 };
    std::for_each(v.begin(), v.end(), [](int p) {std::cout << p << " "; });
    std::cout << "\n";

    // remove 5s
    auto i1 = std::remove(v.begin(), v.end(), 5);
    // clear the unwanted elements
    v.erase(i1, v.end());
    // print the result
    std::for_each(v.begin(), v.end(), [](int p) {std::cout << p << " "; });
    std::cout << "\n";

    // remove odds
    auto i2 = std::remove_if(v.begin(), v.end(), [](int i) {return i % 2; });
    v.erase(i2, v.end());
    std::for_each(v.begin(), v.end(), [](int p) {std::cout << p << " "; });
    std::cout << "\n";
}

void merge_sample()
{
    std::cout << "merge sample\n";
    std::vector<int> v{ 1,2,3,4,5,6 };
    std::vector<int> w{ 10,11,12,13,14 };
    std::vector<int> r;

    std::merge(v.begin(), v.end(), w.begin(), w.end(), std::back_inserter(r));
    std::for_each(r.begin(), r.end(), [](int p) {std::cout << p << " "; });
    std::cout << "\n";
}

void minmax_sample()
{
    std::cout << "min/max sample\n";

    std::cout << std::min(3, 4) << "\n";
    // an error in the compare function can make max to return min!
    std::cout << std::max({ 3,4,5,6,2 }, [](int i, int j) {return i > j; }) << "\n";
}

int main()
{
    std::cout << "Hello from chapter 10!\n";

    pairs_and_tuples();
    test_shared_ppointer();
    test_weak_pointer();
    test_unique_ptr();
    test_raw();
    string_sample();

    functor_sample();
    labda_sample();

    foreach_sample();
    sort_sample();
    partial_sort_sample();
    find_sample();
    find_if_sample();
    find_first_of_sample();
    bounds_sample();
    copy_sample();
    remove_sample();
    merge_sample();
    minmax_sample();

    return 0;
}
