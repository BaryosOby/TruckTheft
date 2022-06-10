#ifndef CPPAD03_TRUCK_H
#define CPPAD03_TRUCK_H

#include "Vehicle.h"


class Truck : public Vehicle {
private:
    uint crates_num{};
    weak_ptr<Warehouse> next_warehouse;
    double next_arrive{};
    double next_depart{};
    uint next_unload{};

    queue<weak_ptr<Warehouse>> warehouse_q;
    queue<uint> crates_q;
    queue<pair<double, double>> arrive_depart_q;

public:
    Truck(string &name, double x, double y) : Vehicle(name,x,y){
        Vehicle::state = moving;
    }

    const weak_ptr<Warehouse> &getCurrWarehouse() const;

    void setCurrWarehouse(const weak_ptr<Warehouse> &currWarehouse);

    const queue<uint> &getCratesQ() const;

   // void setCratesQ(const queue<uint> &cratesQ);
    void pushCrates(uint & crates){
        crates_q.push(crates);
    }
    void popCrates(){
        crates_q.pop();
    }

    uint getCratesNum() const;

    void setCratesNum(uint cratesNum);

    const queue<weak_ptr<Warehouse>> &getWarehouseQ() const;

    //void setWarehouseQ(const queue<weak_ptr<Warehouse>> &warehouseQ);
    void pushWarehouse(weak_ptr<Warehouse>& warehouse){
        warehouse_q.push(warehouse);
    }
    void popWarehouse(){
        warehouse_q.pop();
    }

    const queue<pair<double, double>> &getArriveDepartQ() const;

   // void setArriveDepartQ(const queue<pair<double, double>> &arriveDepartQ);
    void pushArriveDepart(pair<double, double>& p){
        arrive_depart_q.push(p);
    }
    void popArriveDepart(){
        arrive_depart_q.pop();
    }
    void update(double general_time) override;

    void broadcast_status() override;

    void unload();

    void setSpeedByDriveTime();
};


#endif //CPPAD03_TRUCK_H
