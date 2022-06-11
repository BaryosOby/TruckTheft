
#ifndef CPPAD03_TRACK_BASE_H
#define CPPAD03_TRACK_BASE_H
#include <vector>
#include "Warehouse.h"

using namespace std;

class Track_base {
private:
    double course;
    double speed;
    Point destination;
    Point location;
public:

    Track_base(double x, double y) :course(0), speed(0), destination(), location(x, y) {}
    Track_base() :course(0), speed(0), destination(), location() {}

    double getCourse() const {
        return course;
    }

    void setCourseByCords(double x, double y) {
        Cartesian_vector cv;
        cv.delta_x = x - location.x;
        cv.delta_y = y - location.y;
        Polar_vector pv(cv);
        course = to_degrees(pv.theta);
    }

    void setCourseByDeg(double deg){
        course = to_normal_directions(deg);
    }

    double getSpeed() const {
        return speed;
    }

    void setSpeed(double rhs) {
        Track_base::speed = rhs;
    }

    const Point &getDestination() const {
        return destination;
    }

    void setDestination(double x, double y) {
        destination.setCord(x, y);
        setCourseByCords(destination.x, destination.y);
    }

    void setDestination(const Point& p){
        destination = p;
        setCourseByCords(destination.x, destination.y);
    }

    const Point &getLocation() const {
        return location;
    }

    void setLocation(double x, double y) {
        location.setCord(x, y);
    }

    void drive(double time=1){
        double distance = speed * time;
        Polar_vector pv;
        pv.r = distance;
        pv.theta = to_radians(course);
        Cartesian_vector cv(pv);
        location.setCord(cv.delta_x, cv.delta_y);
    }


};


#endif
