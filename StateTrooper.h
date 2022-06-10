//
// Created by Itamar on 08/06/2022.
//

#ifndef CPPAD03_STATETROOPER_H
#define CPPAD03_STATETROOPER_H

#include "Vehicle.h"


class StateTrooper : public Vehicle {
private:
    vector<pair<weak_ptr<Warehouse>,bool> > warehouses;
    Warehouse &start_warehouse;
public:
    StateTrooper(string &name, Warehouse &w) : Vehicle(name, w.getLocation().x, w.getLocation().y),
                                               start_warehouse(w) {
        Vehicle::state = stopped;
        tb.setSpeed(90);
    }

    const vector<pair<weak_ptr<Warehouse>, bool>> &getWarehouses() const {
        return warehouses;
    }

    void pushWarehouse(weak_ptr<Warehouse> &w) {
        auto p = make_pair(w, false);
        warehouses.push_back(p);
    }

    Warehouse &getStartWarehouse() const {
        return start_warehouse;
    }
    void getClosestWarehouse();


    void update(double general_time) override;

};


#endif //CPPAD03_STATETROOPER_H
