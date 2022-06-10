#ifndef EXC03_WAREHOUSE_H
#define EXC03_WAREHOUSE_H
#include "Sim_obj.h"

class Warehouse: public Sim_obj{
private:
    uint inventory;

public:
    Warehouse(string& name, double x, double y, uint init=0):Sim_obj(name, x, y), inventory(init){}

    uint getInventory() const {
        return inventory;
    }

    void setInventory(uint crates) {
        Warehouse::inventory += crates;
    }

    void update() override {}

    void broadcast_status() override {
        cout << "Warehouse " << Sim_obj::name << " at position ";
        Sim_obj::location.print();
        cout <<", Inventory: " << inventory << endl;
    }
};


#endif
