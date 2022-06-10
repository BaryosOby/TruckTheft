#include "Chopper.h"

int Chopper::getAttackRadius() const {
    return attack_radius;
}

void Chopper::setAttackRadius(int attackRadius) {
    attack_radius = attackRadius;
}

Chopper::Chopper(string &name, double x, double y) : Vehicle(name, x, y), attack_radius(2) {

}

bool Chopper::attack(const Vehicle &v) {
    return false;
}

void Chopper::update(double general_time) {

}

void Chopper::broadcast_status() {

}
