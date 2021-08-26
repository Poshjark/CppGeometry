#pragma once


#define MDEBUG

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>


class GeometryObject{
public:
    virtual void move_to(double x_new,double y_new) = 0;
    virtual void shift(double x_shift=0, double y_shift=0) = 0;
    virtual void scale(int) = 0;
    virtual void resize(int) = 0;
    virtual void rotate(int) = 0;
    virtual std::ostream& print(std::ostream& out = std::cout) const = 0;
    virtual ~GeometryObject(){};
};

class Point : public GeometryObject{
#ifdef MDEBUG
public:
#else
private:
#endif
    bool is_visible;
    double x, y;
public:
    Point(double x=0, double y=0);
    Point(const Point& other);
    Point(Point& other);
    Point(Point&& other) noexcept;

    friend std::ostream& operator<< (std::ostream &out, const Point &point);
    ~Point()  ;

    const double getX() const;
    const double getY() const;

    void move_to(double x_new, double y_new) override;
    void shift(double, double) override ;

    void scale(int) override;
    void resize(int) override;
    void rotate(int) override;

    Point& operator=(const Point& other){
        this->x = other.x;
        this->y = other.y;
        return *this;
    }

    Point& operator=(Point&& other){
        this->x = other.x;
        this->y = other.y;
        return *this;
    }
    std::ostream& print(std::ostream& out = std::cout) const{
        out << *this;
        return out;
    }
    const bool operator==(const Point& other) const;

};

class Vector : public GeometryObject{


#ifdef MDEBUG
public:
#else
private:
#endif
    Point* start;
    Point* end;
    Point* normal;
    double angle;
    double k;
    double b;
    Point make_normal();
    void coeff_b_recalculate();

public:
    Vector();
    Vector(Point* start_input, Point* end_input);
    Vector(const Point& start_input,const Point& end_input);
    Vector(Point&& start_input, Point&& end_input);
    explicit Vector(const std::pair<std::pair<double,double>,std::pair<double,double>>& args) ;
    explicit Vector(std::pair<std::pair<double,double>,std::pair<double,double>>&& args) ;
    ~Vector();

    friend std::ostream& operator<< (std::ostream &out, const Vector& vector);



    void move_to(double x_new, double y_new)override ;
    void shift(double, double)override ;

    void scale(int) override;
    void resize(int) override;
    void rotate(int) override;

    const double get_angle(const char mode = 'd');

    bool operator==(const Vector& other) const;

    std::ostream& print(std::ostream& out = std::cout) const override{
        out << *this;
        return out;
    }
};



#endif // GEOMETRY_H





