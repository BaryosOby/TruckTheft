#ifndef CPPAD03_CHOPPER_H
#define CPPAD03_CHOPPER_H
#include "Vehicle.h"

#define SPEED_LIM 170.0
#define MAX_R 20

class Chopper : public Vehicle{
private:
    int attack_radius;

public:
    int getAttackRadius() const;

    void setAttackRadius(int attackRadius);

    Chopper(string& name, double x, double y);
    bool attack(const Vehicle& v);
    void course(double deg, double speed);
    void position(double  x, double y, double speed);

    void update(double general_time) override;
    void broadcast_status() override;
};


#endif //CPPAD03_CHOPPER_H
