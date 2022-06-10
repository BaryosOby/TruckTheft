#ifndef CPPAD03_TRUCK_H
#define CPPAD03_TRUCK_H
#include "Vehicle.h"



class Truck : public Vehicle {
private:
    uint crates_num;
    weak_ptr<Warehouse> curr_warehouse;
    queue<weak_ptr<Warehouse>> warehouse_q;
    queue<uint> crates_q;
    queue<pair<double, double>> arrive_depart_q;

public:
    const weak_ptr<Warehouse> &getCurrWarehouse() const;

    void setCurrWarehouse(const weak_ptr<Warehouse> &currWarehouse);

    const queue<uint> &getCratesQ() const;

    void setCratesQ(const queue<uint> &cratesQ);

    uint getCratesNum() const;

    void setCratesNum(uint cratesNum);

    const queue<weak_ptr<Warehouse>> &getWarehouseQ() const;

    void setWarehouseQ(const queue<weak_ptr<Warehouse>> &warehouseQ);

    const queue<pair<double, double>> &getArriveDepartQ() const;

    void setArriveDepartQ(const queue<pair<double, double>> &arriveDepartQ);

    void update() override;

    void broadcast_status() override;

    void unload(uint crates);
};


#endif //CPPAD03_TRUCK_H
