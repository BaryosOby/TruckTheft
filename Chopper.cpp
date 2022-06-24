#include "Chopper.h"

double Chopper::getAttackRadius() const {
    return attack_radius;
}

void Chopper::setAttackRadius(double attackRadius) {
    if (attack_radius + attackRadius >= MIN_R && attack_radius + attackRadius <= MAX_R) {
        attack_radius += attackRadius;
    }
}

Chopper::Chopper(string &name, double x, double y) : Vehicle(name, x, y), attack_radius(MIN_R) {
}


void Chopper::update(double general_time) {
    if (state == moving_dest || state == moving_course) {
        drive();
    }
}

void Chopper::broadcast_status() {
    cout << "Chopper " << name << " at ";
    tb.getLocation().print();
    if (state == moving_dest || state == moving_course) {
        cout << ", Heading on course " << (int) tb.getCourse() << " degrees";
        cout << ", speed " << setprecision(2) << tb.getSpeed() * 100 << " km/h" << endl;
    }
}

void Chopper::course(double deg, double speed) {
    tb.setSpeed(speed);
    Vehicle::course(deg);
}

void Chopper::position(double x, double y, double speed) {
    tb.setSpeed(speed);
    Vehicle::position(x, y);
}

void Chopper::position(Point p, double speed) {
    tb.setSpeed(speed);
    Vehicle::position(p);
}
