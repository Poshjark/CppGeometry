#pragma once
#define MDEBUG



#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

typedef double coord_t;

class GeometryObject{
public:
    virtual void move_to(coord_t x_new,coord_t y_new) = 0;
    virtual void shift(coord_t x_shift=0, coord_t y_shift=0) = 0;
    virtual void scale(coord_t) = 0;
    virtual void resize(coord_t) = 0;
    virtual void rotate(coord_t) = 0;
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
    coord_t x, y;
public:
    Point(coord_t x=0, coord_t y=0);
    Point(const Point& other);
    Point(Point& other);
    Point(Point&& other) noexcept;

    friend std::ostream& operator<< (std::ostream &out, const Point &pocoord_t);
    ~Point()  ;

    const coord_t getX() const;
    const coord_t getY() const;

    void move_to(coord_t x_new, coord_t y_new) override;
    void shift(coord_t, coord_t) override ;

    void scale(coord_t) override;
    void resize(coord_t) override;
    void rotate(coord_t) override;

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

class VectorObject : public GeometryObject{
private:
    bool closed;
    std::vector<VectorObject*> data;
#ifdef MDEBUG
public:
#else
private:
#endif
    virtual std::pair<Point,bool> find_cross(VectorObject*) const = 0;
public:
    virtual void equidistant(coord_t,bool direct = true) = 0;
};




class Vector : public VectorObject{


#ifdef MDEBUG
public:
#else
private:
#endif
    Point* start;
    Point* end;
    Point* normal;
    coord_t angle;
    coord_t k;
    coord_t b;
    Point make_normal();
    void coeff_b_recalculate();

public:
    Vector();
    Vector(Point* start_input, Point* end_input);
    Vector(const Point& start_input,const Point& end_input);
    Vector(Point&& start_input, Point&& end_input);
    explicit Vector(const std::pair<std::pair<coord_t,coord_t>,std::pair<coord_t,coord_t>>& args) ;
    explicit Vector(std::pair<std::pair<coord_t,coord_t>,std::pair<coord_t,coord_t>>&& args) ;
    ~Vector();

    friend std::ostream& operator<< (std::ostream &out, const Vector& vector);



    void move_to(coord_t x_new, coord_t y_new)override ;
    void shift(coord_t, coord_t)override ;

    void scale(coord_t) override;
    void resize(coord_t) override;
    void rotate(coord_t) override;

    void equidistant(coord_t,bool direct = true) override;
    std::pair<Point,bool> find_cross(VectorObject*) const override;


    const coord_t get_angle(const char mode = 'd');

    bool operator==(const Vector& other) const;

    std::ostream& print(std::ostream& out = std::cout) const override{
        out << *this;
        return out;
    }
};

class Polyline : public VectorObject{
private:
    std::vector<Point*> data;
    bool closed;
public:

    Polyline();
    Polyline(std::initializer_list<Point*> points);
    Polyline(std::initializer_list<std::pair<coord_t,coord_t>>);

    void move_to(coord_t,coord_t) override;
    void shift(coord_t,coord_t) override;
    void scale(coord_t) override;
    void resize(coord_t) override;
    void rotate(coord_t) override;

    void equidistant(coord_t,bool direct = true) override;
    std::pair<Point,bool> find_cross(VectorObject*) const override;

    std::ostream& print(std::ostream& out = std::cout) const override;
};

#endif // GEOMETRY_H





