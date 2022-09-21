#include <stdio.h>

class A {
    int i;
public: 
    A(int x) { i = x; printf("first\n"); }
    virtual ~A() { printf("second\n"); }
    int f() const { return i + g() + h(); }
    virtual int g() const { return i; }
    int h() const { return 6; }
};

class B : public A {
public: 
    B(): A(0) { printf("third\n"); }
    ~B() { printf("fourth\n"); }
    int f() const { return g() - 5; }
    virtual int g() const { return 8; }
    int h() const { return 1; }
};

int main() {
    B b;
    A* p = &b;
    printf("result = (%d ; %d)\n", p->f(), b.f());
    return 0;
}