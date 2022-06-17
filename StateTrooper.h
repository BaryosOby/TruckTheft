#ifndef CPPAD03_STATETROOPER_H
#define CPPAD03_STATETROOPER_H

#include "Vehicle.h"


class StateTrooper : public Vehicle {
private:
    vector<pair<weak_ptr<Warehouse>,bool> > warehouses;
    int warehouse_idx{};

public:
    StateTrooper(string &name, double x, double y) : Vehicle(name, x, y){
        Vehicle::state = stopped;
        tb.setSpeed(0.9);
    }

    const vector<pair<weak_ptr<Warehouse>, bool>> &getWarehouses() const {
        return warehouses;
    }

    void pushWarehouse(weak_ptr<Warehouse> &w) {
        auto p = make_pair(w, false);
        warehouses.push_back(p);
    }

    void getClosestWarehouse();

    void update(double general_time) override;
    void broadcast_status() override;

};


#endif
