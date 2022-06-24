#ifndef CPPAD03_CHOPPER_H
#define CPPAD03_CHOPPER_H

#include "Vehicle.h"

#define SPEED_LIM 1.7
#define MAX_R 0.2
#define MIN_R 0.02

class Truck;

class Chopper : public Vehicle {
private:
    double attack_radius;

public:
    double getAttackRadius() const;

    void setAttackRadius(double attackRadius);

    Chopper(string &name, double x, double y);

    void course(double deg, double speed);

    void position(double x, double y, double speed);

    void position(Point p, double speed);


    void update(double general_time) override;

    void broadcast_status() override;
};


#endif
