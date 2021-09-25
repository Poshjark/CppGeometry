#include "geometry.h"
#include <array>




Point::Point(const coord_t x_input,const coord_t y_input) : x(x_input), y(y_input){
#ifdef MDEBUG
    std::cout << "Point default constructor!\n";
#endif
}

Point::Point(Point& other) : x(other.x), y(other.y){
#ifdef MDEBUG
    std::cout << "Ref Point copy constructor!\n";
#endif
}

Point::Point(const Point& other) : x(other.x), y(other.y) {
#ifdef MDEBUG
    std::cout << "Const ref Point copy constructor!\n";
#endif
}

Point::Point (Point&& other) noexcept : x(other.x), y(other.y) {
#ifdef MDEBUG
    std::cout << "Point move constructor!\n";
#endif
}

const coord_t Point::getX() const{
    return this->x;
}

const coord_t Point::getY() const{
    return this->y;
}

void Point::move_to(coord_t x_new, coord_t y_new){
    this->x= x_new;
    this->y= y_new;
}

void Point::shift(coord_t x_shift, coord_t y_shift){
    this->x+= x_shift;
    this->y+= y_shift;
}

const bool Point::operator==(const Point& other) const{
    return this->x== other.getX() && this->y== other.getY();
}

void Point::resize(coord_t length,coord_t width,std::pair<coord_t,coord_t> center){

}

void Point::scale(double scale_,std::pair<coord_t,coord_t> center){

}

void Point::rotate(double degree,std::pair<coord_t,coord_t> center){

}

Point::~Point(){
#ifdef MDEBUG
    std::cout << "Point destructor!\n";
#endif
}

Polyline::Vector::Vector() : start(new Point()), end(new Point()){
    this->k = 1;
    this->b = 0;
}


// Add function coeffs_recalculate merging it with coeff_b_recalculate

Polyline::Vector::Vector(Point* start_input, Point* end_input){
#ifdef MDEBUG
    std::cout << "Vector pointers cosntructor!\n";
#endif
    this->start = start_input;
    this->end = end_input;
    if(this->start->getX() != this->end->getX()){
        this->k = (this->start->getY() - this->end->getY()) / (this->start->getX() - this->end->getX());
    }
    else{
        k = 0;
    }
    this->b = this->start->getY() - start->getX() * this->k;
}


// coeffs_recalculate add instead of if else
Polyline::Vector::Vector(const Point& start_input,const Point& end_input) : start(new Point(start_input)), end(new Point(end_input)) {
    if(this->start->getX() != this->end->getX()){
        this->k = (this->start->getY() - this->end->getY()) / (this->start->getX() - this->end->getX());
    }
    else{
        k = 0;
    }
    this->b = this->start->getY() - start->getX() * this->k;
}

Polyline::Vector::Vector(Point&& start_input, Point&& end_input) :
    start(new Point(std::move(start_input))),
    end(new Point(std::move(end_input))){
    if(this->start->getX() != this->end->getX()){
        this->k = (this->start->getY() - this->end->getY()) / (this->start->getX() - this->end->getX());
    }
    else{
        k = 0;
    }
    this->b = this->start->getY() - start->getX() * this->k;
}

// coeffs_recalculate add instead of if else
Polyline::Vector::Vector(const std::pair<std::pair<coord_t,coord_t>,std::pair<coord_t,coord_t>>& args) :
    start(new Point(args.first.first, args.first.second)),
    end(new Point(args.second.first, args.second.second)){
    if(this->start->getX() != this->end->getX()){
        this->k = (this->start->getY() - this->end->getY()) / (this->start->getX() - this->end->getX());
    }
    else{
        k = 0;
    }
    this->b = this->start->getY() - start->getX() * this->k;
}

// coeffs_recalculate add instead of if else
Polyline::Vector::Vector(std::pair<std::pair<coord_t,coord_t>,std::pair<coord_t,coord_t>>&& args) :
    start(new Point(args.first.first, args.first.second)),
    end(new Point(args.second.first, args.second.second)){
#ifdef MDEBUG
    std::cout << "Vector move constructor from pairs!\n";
#endif
    if(this->start->getX() != this->end->getX()){
        this->k = (this->start->getY() - this->end->getY()) / (this->start->getX() - this->end->getX());
    }
    else{
        k = 0;
    }
    this->b = this->start->getY() - start->getX() * this->k;
}



Polyline::Vector::~Vector() {
    delete start;
    delete end;
}

void Polyline::Vector::shift(coord_t x_shift, coord_t y_shift){
    this->start->shift(x_shift,y_shift);
    this->end->shift(x_shift,y_shift);
}

void Polyline::Vector::move_to(coord_t x_new, coord_t y_new){
    this->end->move_to(this->start->getX() + x_new, this->start->getY() + y_new);
    this->start->move_to(x_new, y_new);
}

void Polyline::Vector::resize(coord_t length,coord_t width,std::pair<coord_t,coord_t> center){

}

void Polyline::Vector::scale(coord_t,std::pair<coord_t,coord_t> center){

}

void Polyline::Vector::rotate(coord_t,std::pair<coord_t,coord_t> center){

}

void Polyline::Vector::coeff_b_recalculate(){
    if(this->angle != INFINITY){
        this->b = this->start->getY() - start->getX() * this->k;
    }

}

Point Polyline::Vector::make_normal(){
    const std::array<int,5> quarters = {1,1,1,1,1};
    int quarter = 0;
    coord_t x = 0;
    coord_t y = 0;
    if(this->start->getX() == this->end->getX()){
        if(this->start->getY() > this->end->getY()){
            this->angle = -90;
            k = INFINITY;
            b = 0;
            y = -1;

        }
        else if(this->start->getY() < this->end->getY()){
            this->angle = 90;
            k = INFINITY;
            b = 0;
            y = 1;
        }
        else{
            this->b = this->k = this->angle = INFINITY;
        }

    }
    else if(this->start->getY() == this->end->getY()){
        if(this->start->getX() < this->end->getX()){
            this->angle = 0;
            k = 0;
            b = 0;
            x = 1;
        }
        else if(this->start->getX() > this->end->getX()){
            this->angle = 180;
            std::cout<< "FLAG\n";
            x= -1;

        }
    }
    else if(this->start->getX() < this->end->getX()){
        if(this->start->getY() < this->end->getY()){
            quarter = 1;
        }
        else if(this->start->getY() > this->end->getY()){
            quarter = 4;
        }
    }
    else if(this->start->getX() > this->end->getX()){
        if(this->start->getY() > this->end->getY()){
            quarter = 3;
        }
        else if(this->start->getY() < this->end->getY()){
            quarter = 2;
        }
    }
    std::cout << "Quarter is " << quarter << std::endl;
    if (quarter != 0){

        std::array<const int,5> quantifier {0,0,2,-2,0};
        this->angle = std::atan((this->end->getY() - this->start->getY()) / (this->end->getX() - this->start->getX())) * 180 / M_PI;
        this->angle += 90 * quantifier[quarter];
        x = std::cos(this->angle * M_PI / 180);
        y = std::sin(this->angle * M_PI / 180);
    }
    return {x,y};
}

std::pair<Point,bool> Polyline::Vector::find_cross(VectorObject*) const{
    return {{0,0},0};
}

void Polyline::Vector::equidistant(coord_t, bool direct){
    int sign = direct ? 1 : -1;
    this->start->shift(this->normal->getX() * sign, this->normal->getY() * sign);
    this->end->shift(this->normal->getX() * sign, this->normal->getY() * sign);
}

std::ostream& operator<<(std::ostream & out, const Point& point){
    out << "(" << point.getX() << ";" << point.getY() << ")";
    return out;
}

std::ostream& operator<<(std::ostream &out, const Polyline::Vector& vector){
    out << "Start - " << *(vector.start) << "\tend - " << *(vector.end) << std::endl;
    return out;
}
std::ostream& operator<<(std::ostream& out, const GeometryObject& object){
    return object.print(out);
}


void Polyline::move_to(coord_t x_new, coord_t y_new){

}

void Polyline::shift(coord_t, coord_t){

}

void Polyline::scale(coord_t,std::pair<coord_t,coord_t> center){

}

void::Polyline::resize(coord_t length,coord_t width,std::pair<coord_t,coord_t> center){

}

void Polyline::rotate(coord_t,std::pair<coord_t,coord_t> center){

}

Polyline::Polyline(std::initializer_list<std::pair<coord_t,coord_t>>){

}

std::ostream& Polyline::print(std::ostream& out) const{
    return out;
}

void Polyline::equidistant(coord_t,bool direct){

}

std::pair<Point,bool> Polyline::find_cross(VectorObject*) const{
    return {{0,0},0};
}
