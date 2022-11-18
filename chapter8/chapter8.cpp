// chapter8.cpp
//

#include <iostream>

// some fundamental stuff in 3D space
class point {
protected:   // only child classes can access these
    double x, y, z;
public:
    point(double _x = 0, double _y = 0, double _z = 0) :x(_x), y(_y), z(_z) {}
    ~point() {}
};

// a solid object definition
class solid_object {
protected:
    double mass;
    point position;
public:
    solid_object(double m = 0) : mass(m) {}
    virtual ~solid_object() {}
    // pure virtual function
    virtual double volume() const = 0;
};

// the cube is a special solid object
class cube : public solid_object {
protected:
    double edge_length;
public:
    cube(double m, double el) :solid_object(m), edge_length(el) {}
    virtual ~cube() {}
    virtual double volume() const { return edge_length * edge_length * edge_length; }
};

// so is a sphere
const double pi = 3.1415926;
class sphere :public solid_object {
protected:
    double radius;
public:
    sphere(double m, double r) :solid_object(m), radius(r) {}
    virtual ~sphere() {}
    virtual double volume() const { return 4 * pi * radius * radius * radius / 3; }
};

// access control
class base {
public:
    base() {}
    virtual ~base() {}
    int x;    // a public variable
    void do_job() {   // and a public function
        x = 0;
        y = 1;
        z = 2;
    }
protected:
    int y;  // a protected variable
private:
    int z;  // and a private variable
};

class public_derived : public base {  // public inheritance
public:
    public_derived() {}
    virtual ~public_derived() {}
    void do_sth() {
        do_job();  // public and protected members are accessible
        x = 0;
        y = 1;
        //z = 2;  private is not accessible
    }
};
class protected_derived : protected base {  // protected inheritance
public:
    protected_derived() {}
    virtual ~protected_derived() {}
    void do_sth_else() {
        x = 0;     // again public and protected are accessible
        y = 1;
        //z = 2;   while private is not
    }
};

// deriving from a protected derived class
class after_protected : public protected_derived {
public:
    after_protected() {}
    virtual ~after_protected() {}

    void after_thought() {
        x = 100; // we still have access to the base class
    }
};

class private_derived : private base { // private inheritance
public:
    private_derived() {}
    virtual ~private_derived() {}
    void do_sth_new() {
        x = 0;
        y = 1;
        //z = 2;
    }
};

class after_private : public private_derived {
public:
    after_private() {}
    ~after_private() {}
    void after_all() {
        // x = 1;    we no longer have access to the base class
    }
};

// multilevel inheritance
class vehicle {
public:
    vehicle() { std::cout << "vehicle\n"; }
    virtual ~vehicle() {}
    virtual void print() = 0;
};
// car is a vehicle
class car :public vehicle {
public:
    car() { std::cout << "car\n"; }
    virtual ~car() {}
    virtual void print() {
        std::cout << "i am a car\n";
    }
};
// sports_car is a car, and a vehicle
class sports_car :public car {
public:
    sports_car() { std::cout << "sports car\n"; }
    virtual ~sports_car() {}
    virtual void print() {
        std::cout << "i am a sports car\n";
    }
};

class made_by_me {
public:
    made_by_me() { std::cout << "my product\n"; }
    virtual ~made_by_me() {}
    virtual void print() {
        std::cout << "this is my product\n";
    }
};

class my_car :public car, public made_by_me {
public:
    my_car() { std::cout << "my car\n"; }
    virtual ~my_car() {}
    virtual void print() {
        std::cout << "this is my car\n";
    }
};

void inheritance()
{
    public_derived object1;
    protected_derived object2;
    private_derived object3;

    object1.do_job();    // base members are accessible
    // object2.do_job(); // base members are not accessible

    base* optr1 = &object1;  // object1 is base
    // base* optr2 = &object2;  // object2 has no accessible interface to base

    my_car c;
    // access the base functions
    std::cout << "access the base classes functions\n";
    c.car::print();
    c.made_by_me::print();
    // access the class function
    std::cout << "access the class function\n";
    c.print();
}

// virtual inheritance
class a_base {
protected:
    int x;
public:
    a_base() { std::cout << "a_base\n"; }
    virtual ~a_base() { std::cout << "~a_base\n"; }
};

// these classes have one instance of the base class each
class b_base : public a_base {
public:
    b_base() { std::cout << "b_base\n"; x = 10; }
    virtual ~b_base() { std::cout << "~b_base\n"; }
};
class c_base : public a_base {
public:
    c_base() { std::cout << "c_base\n"; x = 20; }
    virtual ~c_base() { std::cout << "~c_base\n"; }
};
// the result is in this class
class d_class : public b_base, public c_base {
public:
    d_class() { std::cout << "d_class\n"; }
    virtual ~d_class() { std::cout << "~d_class\n"; }
    void print() {
        std::cout << b_base::x << "," << c_base::x << "\n";
    }
};

// these classes share the same instance of the base class 
class e_base : virtual public a_base {
public:
    e_base() { std::cout << "e_base\n"; x = 10; }
    virtual ~e_base() { std::cout << "~e_base\n"; }
};
class f_base : virtual public a_base {
public:
    f_base() { std::cout << "f_base\n"; x = 20; }
    virtual ~f_base() { std::cout << "~f_base\n"; }
};

class g_class : public e_base, public f_base {
public:
    g_class() { std::cout << "g_class\n"; }
    virtual ~g_class() { std::cout << "~g_class\n"; }
    void print() {
        std::cout << e_base::x << "," << f_base::x << "\n";
    }
};

void virtual_inheritance()
{
    d_class dc;
    dc.print();
    g_class gc;
    gc.print();
}

// friends
class _f_base {
private:
    int prx;
protected:
    int pry;
public:
    int puz;

    _f_base() {}
    ~_f_base() {}
    // declare friend function
    friend void my_friend_function();
    // declare friend class
    friend class my_friend_class;
};

void my_friend_function()
{
    _f_base fb;
    // access private variable
    fb.prx = 100;
}

class my_friend_class {
private:
    _f_base fb;
public:
    my_friend_class() {
        // access protected variable
        fb.pry = 200;
    }
};

int main()
{
    std::cout << "Hello from chapter 8!\n";

    solid_object* objects[2];
    objects[0] = new cube(1, 2);
    objects[1] = new sphere(1, 3);

    double volume1 = objects[0]->volume();
    double volume2 = objects[1]->volume();
    delete objects[0];

    // RTTI
    cube* c = dynamic_cast<cube*>(objects[1]);

    inheritance();

    virtual_inheritance();

    return 0;
}
