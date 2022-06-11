#include "Chopper.h"

int Chopper::getAttackRadius() const {
    return attack_radius;
}

void Chopper::setAttackRadius(int attackRadius) {
    attack_radius += attackRadius;
}

Chopper::Chopper(string &name, double x, double y) : Vehicle(name, x, y), attack_radius(MIN_R) {
}


void Chopper::update(double general_time) {
    if(state == moving_dest || state == moving_course){
        drive();
    }
}

void Chopper::broadcast_status() {
    cout << "Chopper " << name << " at ";
    tb.getLocation().print();
    if(state == moving_dest || state == moving_course){
        cout << ", Heading on course " << setprecision(2) << tb.getCourse() << " degrees";
        cout << ", speed " << setprecision(2) << tb.getSpeed() << " km/h" << endl;
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
