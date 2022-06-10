
#ifndef CPPAD03_TRACK_BASE_H
#define CPPAD03_TRACK_BASE_H

#include <vector>
#include "Geometry.h"

using namespace std;

class Track_base {
private:
    float course;
    float speed;
    Point destination;
    Point location;
public:

    float getCourse() const {
        return course;
    }

    void setCourse(float course) {
        Track_base::course = course;
    }

    float getSpeed() const {
        return speed;
    }

    void setSpeed(float speed) {
        Track_base::speed = speed;
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
