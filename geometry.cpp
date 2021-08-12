#include "geometry.h"
#include <array>



Point::Point(const double x_input,const double y_input) : x(x_input), y(y_input){
    std::cout << "Point default constructor!\n";
}

Point::Point(Point& other) : x(other.x), y(other.y){

}

Point::Point(const Point& other) : x(other.x), y(other.y) {
    std::cout << "Point copy constructor!\n";
}

Point::Point (Point&& other) noexcept : x(other.x), y(other.y) {
    std::cout << "Point move constructor!!\n";
}

const double Point::getX() const{
    return this->x;
}

const double Point::getY() const{
    return this->y;
}

void Point::move_to(double x_new, double y_new){
    this->x= x_new;
    this->y= y_new;
}

void Point::shift(double x_shift, double y_shift){
    this->x+= x_shift;
    this->y+= y_shift;
}

const bool Point::operator==(const Point& other) const{
    return this->x== other.getX() && this->y== other.getY();
}

void Point::resize(){

}

void Point::scale(){

}

void Point::rotate(int degree){

}

Point::~Point(){
}

Vector::Vector() : start(new Point()), end(new Point()){
    this->k = 1;
    this->b = 0;
}

Vector::Vector(Point* start_input, Point* end_input){
    std::cout << "Vector pointers cosntructor!\n";
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

Vector::Vector(const Point& start_input,const Point& end_input) : start(new Point(start_input)), end(new Point(end_input)) {
    if(this->start->getX() != this->end->getX()){
        this->k = (this->start->getY() - this->end->getY()) / (this->start->getX() - this->end->getX());
    }
    else{
        k = 0;
    }
    this->b = this->start->getY() - start->getX() * this->k;
}

Vector::Vector(Point&& start_input, Point&& end_input) :
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

Vector::Vector(const std::pair<std::pair<double,double>,std::pair<double,double>>& args) :
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


Vector::Vector(std::pair<std::pair<double,double>,std::pair<double,double>>&& args) :
    start(new Point(args.first.first, args.first.second)),
    end(new Point(args.second.first, args.second.second)){
    std::cout << "Vector move constructor from pairs!\n";
    if(this->start->getX() != this->end->getX()){
        this->k = (this->start->getY() - this->end->getY()) / (this->start->getX() - this->end->getX());
    }
    else{
        k = 0;
    }
    this->b = this->start->getY() - start->getX() * this->k;
}



Vector::~Vector() {
    delete start;
    delete end;
}

void Vector::shift(double x_shift, double y_shift){
    this->start->shift(x_shift,y_shift);
    this->end->shift(x_shift,y_shift);
}

void Vector::move_to(double x_new, double y_new){
    this->end->move_to(this->start->getX() + x_new, this->start->getY() + y_new);
    this->start->move_to(x_new, y_new);
}

void Vector::resize(){

}

void Vector::scale(){

}

void Vector::rotate(int degree){

}

void Vector::coeff_b_recalculate(){
    if(this->angle != INFINITY){
        this->b = this->start->getY() - start->getX() * this->k;
    }

}

Point Vector::make_normal(){
    const std::array<int,5> quarters = {1,1,1,1,1};
    int quarter = 0;
    double x = 0;
    double y = 0;
    if(this->start->getX() == this->end->getX()){
        if(this->start->getY() > this->end->getY()){
            this->angle = -M_PI_2;
            k = INFINITY;
            b = 0;
            y = -1;

        }
        else if(this->start->getY() < this->end->getY()){
            this->angle = M_PI_2;
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
            this->angle = M_PI;
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

        std::array<const int,5> quantifier {0,0,1,-1,0};
        this->angle = std::atan((this->end->getY() - this->start->getY()) / (this->end->getX() - this->start->getX())) * 180 / M_PI;
        this->angle += 90 * quantifier[quarter];
        x = std::cos(this->angle * M_PI / 180);
        y = std::sin(this->angle * M_PI / 180);
    }
    return {x,y};
}

std::ostream& operator<<(std::ostream & out, const Point& point){
    std:: cout << "(" << point.getX() << ";" << point.getY() << ")";
    return out;
}

std::ostream& operator<<(std::ostream &out, const Vector& vector){
    std::cout << "Start - " << *(vector.start) << "\tend - " << *(vector.end) << std::endl;
    return out;
}
