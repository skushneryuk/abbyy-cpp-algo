#include <stdio.h>
#include <cmath>

class Prism {
double height;
public:
    Prism(double height): height(height) {}

    double Volume() const {
        return Square() * height;
    }

    virtual double Square() const = 0;

    // К этому классу есть одно замечание.
    // В качестве подсказки рекомендую еще раз посмотреть презентацию к первой лекции.

    // Вот что можно добавить
    virtual ~Prism() = default;
};

class Box : public Prism {
double side;
public:
    Box(double height, double side): Prism(height), side(side) {}

    virtual double Square() const override {
        return side * side;
    }

    // И вот это
    virtual ~Box() = default;
};

class Cube : public Box {
public:
    Cube(double side): Box(side, side) {}

    // И еще вот тут
    virtual ~Cube() = default;
};

int main() {
    const Prism *p, *q, *r;
    Box a(0.5, 2), b(5, 0.2);
    Cube c(0.5);

    p = &a; q = &b; r = &c;
    printf("Squares: %3.3lf %3.3lf %3.3lf\n",
           p->Square(), q->Square(), r->Square());
    printf("Volumes: %3.3lf %3.3lf %3.3lf\n",
           p->Volume(), q->Volume(), r->Volume());
    return 0;
}