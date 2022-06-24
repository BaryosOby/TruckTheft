#include "Chopper.h"

double Chopper::getAttackRadius() const {
    return attack_radius;
}
// after chopper try to attack change radius
void Chopper::setAttackRadius(double attackRadius) {
    if (attack_radius + attackRadius >= MIN_R && attack_radius + attackRadius <= MAX_R) {
        attack_radius += attackRadius;
    }
}

Chopper::Chopper(string &name, double x, double y) : Vehicle(name, x, y), attack_radius(MIN_R) {
}

// update chopper movement
void Chopper::update(double general_time) {
    if (state == moving_dest || state == moving_course) {
        drive();
    }
}
//print chopper status
void Chopper::broadcast_status() {
    cout << "Chopper " << name << " at ";
    tb.getLocation().print();
    if (state == moving_dest || state == moving_course) {
        cout << ", Heading on course " << ((int) tb.getCourse() + 90) % 360 << " degrees";
        cout << ", speed " << fixed << setprecision(2) << (tb.getSpeed() * 100) << " km/h" << endl;
    }
}
//set course & speed
void Chopper::course(double deg, double speed) {
    tb.setSpeed(speed);
    Vehicle::course(deg);
}
//set position & speed by given two coordinates
void Chopper::position(double x, double y, double speed) {
    tb.setSpeed(speed);
    Vehicle::position(x, y);
}
//set position & speed by given point
void Chopper::position(Point p, double speed) {
    tb.setSpeed(speed);
    Vehicle::position(p);
}
