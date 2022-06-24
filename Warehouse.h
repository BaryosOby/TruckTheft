#ifndef EXC03_WAREHOUSE_H
#define EXC03_WAREHOUSE_H

#include "Sim_obj.h"

class Warehouse : public Sim_obj {
private:
    int inventory;

public:
    Warehouse(string &name, double x, double y, int init = 0) : Sim_obj(name, x, y), inventory(init) {}

    int getInventory() const {
        return inventory;
    }

    void setInventory(int crates) {
        Warehouse::inventory += crates;
    }

    void update(double general_time) override {}

    void broadcast_status() override {
        cout << "Warehouse " << Sim_obj::name << " at position ";
        Sim_obj::init_location.print();
        cout << ", Inventory: " << inventory << endl;
    }

    void stop() override {}
};


#endif
