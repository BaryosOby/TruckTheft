
#ifndef CPPAD03_TRACK_BASE_H
#define CPPAD03_TRACK_BASE_H

#include <vector>
#include "Geometry.h"

using namespace std;

class Track_base {
private:
    double course;
    double speed;
    Point destination;
    Point location;
public:

    Track_base(double c, double s, double xD, double, double yD, double xL, double yL) : course(c), speed(s), destination(xD,yD), location(xL,yL){}

    double getCourse() const {
        return course;
    }

    void setCourse(double rhs) {
        Track_base::course = rhs;
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
    }

    const Point &getLocation() const {
        return location;
    }

    void setLocation(double x, double y) {
        location.setCord(x, y);
    }
};


#endif //CPPAD03_TRACK_BASE_H
