#include "Geometry.h"
#include <cmath>
#include <ctgmath>

const double pi = 2. * atan2(1., 0.);

double to_radians(double theta_d) {
    return theta_d * pi / 180.0;
}

double to_degrees(double theta_r) {
    return theta_r * 180.0 / pi;
}

// sets game directions to ordinary polar degrees.
double to_normal_directions(double theta_d) {
    return (90 - theta_d) < 0 ? (90 - theta_d + 360) : (90 - theta_d);
}

// construct a Cartesian_vector from a Polar_vector
Cartesian_vector::Cartesian_vector(const Polar_vector &pv) {
    delta_x = pv.r * cos(pv.theta);
    delta_y = pv.r * sin(pv.theta);
}

Cartesian_vector::Cartesian_vector() {
    delta_x = 0.0;
    delta_y = 0.0;
}

void Cartesian_vector::operator=(const Polar_vector &pv) {
    delta_x = pv.r * cos(pv.theta);
    delta_y = pv.r * sin(pv.theta);
}

// construct a Polar_vector from a Cartesian_vector
Polar_vector::Polar_vector(const Cartesian_vector &cv) {
    r = sqrt((cv.delta_x * cv.delta_x) + (cv.delta_y * cv.delta_y));
    /* atan2 will return a negative angle for Quadrant III, IV, must translate to I, II */
    theta = atan2(cv.delta_y, cv.delta_x);
    if (theta < 0.)
        theta = 2. * pi + theta; // normalize theta positive
}

Polar_vector::Polar_vector() {
    r = 0.0;
    theta = 0.0;
}

void Polar_vector::operator=(const Cartesian_vector &cv) {
    r = sqrt((cv.delta_x * cv.delta_x) + (cv.delta_y * cv.delta_y));
    /* atan2 will return a negative angle for Quadrant III, IV, must translate to I, II */
    theta = atan2(cv.delta_y, cv.delta_x);
    if (theta < 0.)
        theta = 2. * pi + theta; // normalize theta positive
}

Point::Point(double x, double y) : x(x), y(y) {
}

Point::Point() {
    x = 0.0;
    y = 0.0;
}

void Point::print() const {
    cout << fixed << setprecision(2) << "(" << x << ", " << y << ")";
}
// if in close radius return true
bool Point::operator==(const Point &rhs) const {
    if(abs(x - rhs.x) > 0.1) return false;
    if(abs(y - rhs.y) > 0.1) return false;
    //return x == rhs.x && y == rhs.y;
    return true;
}

double distance(const Point &a, const Point &b) {
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}
