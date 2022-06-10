//
// Created by Itamar on 08/06/2022.
//

#ifndef CPPAD03_TRACK_BASE_H
#define CPPAD03_TRACK_BASE_H

#include <iostream>
#include <vector>

using namespace std;

class Track_base {
private:
    float course;
    float speed;
    pair<float, float> destination;
    pair<float, float> location;
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

    const pair<float, float> &getDestination() const {
        return destination;
    }

    void setDestination(const pair<float, float> &destination) {
        Track_base::destination = destination;
    }

    const pair<float, float> &getLocation() const {
        return location;
    }

    void setLocation(const pair<float, float> &location) {
        Track_base::location = location;
    }
};


#endif //CPPAD03_TRACK_BASE_H
