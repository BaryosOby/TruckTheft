#ifndef CPPAD03_TRUCK_H
#define CPPAD03_TRUCK_H

#include "Vehicle.h"


class Truck : public Vehicle {
private:
    int crates_num{};
    weak_ptr<Warehouse> next_warehouse;
    double next_arrive{};
    double next_depart{};
    int next_unload{};

    queue<weak_ptr<Warehouse>> warehouse_q;
    queue<int> crates_q;
    queue<pair<double, double>> arrive_depart_q;

public:
    Truck(string &name, double x, double y) : Vehicle(name, x, y) {
        Vehicle::state = moving_dest;
    }

    void course(double deg) override {} // doing nothing in truck
    void position(double x, double y) override {} // doing nothing in truck

    const weak_ptr<Warehouse> &getCurrWarehouse() const;

    void setNextWarehouse();

    const queue<int> &getCratesQ() const;

    void pushCrates(int crates) {
        crates_q.push(crates);
    }

    void popCrates() {
        crates_q.pop();
    }

    int getCratesNum() const;

    void setCratesNum(int cratesNum);

    const queue<weak_ptr<Warehouse>> &getWarehouseQ() const;

    void pushWarehouse(weak_ptr<Warehouse> &warehouse) {
        warehouse_q.push(warehouse);
    }

    void popWarehouse() {
        warehouse_q.pop();
    }

    const queue<pair<double, double>> &getArriveDepartQ() const;

    void pushArriveDepart(pair<double, double> &p) {
        arrive_depart_q.push(p);
    }

    void popArriveDepart() {
        arrive_depart_q.pop();
    }

    void update(double general_time) override;

    void broadcast_status() override;

    void unload();

    void setSpeedByDriveTime();


};


#endif
