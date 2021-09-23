#include <iostream>
#include <math.h>

using namespace std;

class Parallelogram {
private:
    size_t _length;
    size_t _width;
    double _angle;
public:
    Parallelogram(size_t length, size_t width, double angle): _length(length), _width(width), _angle(angle) {}

    virtual size_t getLength() const {
        return _length;
    }

    virtual size_t getWidth() const {
        return _width;
    }

    virtual double getAngle() const {
        return _angle;
    }

    virtual void setLength(size_t length) {
        _length = length;
    }

    virtual void setWidth(size_t width) {
        _width = width;
    }

    virtual void setAngle(double angle) {
        _angle = angle;
    }

    virtual double getArea() const {
        return (_length * _width * sin(_angle));
    }
};

class Rectable: private Parallelogram {
public:
    Rectable(size_t length, size_t width): Parallelogram(length, width, 2*M_PI) {}

    size_t getLength() const override {
        return Parallelogram::getLength();
    }

    size_t getWidth() const override {
        return Parallelogram::getWidth();
    }

    void setLength(size_t size) override {
        Parallelogram::setLength(size);
    }

    void setWidth(size_t size) override {
        Parallelogram::setWidth(size);
    }

    double getArea() const override {
        return Parallelogram::getArea();
    }
private:
    double getAngle() const override {
        throw std::exception();
    }

    void setAngle(double angle) override {
        throw std::exception();
    }
};

class Diamond: private Parallelogram {
public:
    Diamond(size_t size, double angle): Parallelogram(size, size, angle) {}

    size_t getLength() const override {
        return Parallelogram::getLength();
    }

    void setLength(size_t size) override {
        Parallelogram::setLength(size);
        Parallelogram::setWidth(size);
    }

    double getAngle() const override {
        return Parallelogram::getAngle();
    }

    void setAngle(double angle) override {
        Parallelogram::setAngle(angle);
    }

    double getArea() const override {
        return Parallelogram::getArea();
    }
private:
    size_t getWidth() const override {
        throw std::exception();
    }

    void setWidth(size_t size) override {
        throw std::exception();
    }
};

class Square: virtual public Rectable, virtual public Diamond {
public:
    explicit Square(size_t size) : Rectable(size, size), Diamond(size, 2*M_PI) {}

    using Diamond::getLength;
    using Diamond::setLength;

    using Rectable::getArea;
};

int main() {
    return 0;
}
