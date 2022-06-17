#ifndef EXC03_VIEW_H
#define EXC03_VIEW_H

#include "VehicleFactory.h"
#include "Warehouse.h"
#include <map>

#define MIN_SIZE 6
#define MAX_SIZE 30
#define DEF_SIZE 25
#define DEF_SCALE 2.0
#define DEF_PAN 0.0

class Model;


class View {
private:
    Point pan;
    double zoom;
    int size;
    vector<weak_ptr<Sim_obj>> objects;

    map<pair<double, double>, string> obj_in_range;

    Point checkRange(const Point &p) const;

    void fixPrint(double maxRange,double r) const;

    void print_x_interval() const;

    void print_y_interval(int& toPrint,double max_range_y,double curr_y) const;

public:
    View();

    map<pair<double, double>, string> &objects_in_range();

    const Point &getPan() const;

    void setPan(const Point &pan);

    double getZoom() const;

    void setZoom(double zoom);

    int getSize() const;

    void setSize(int size);

    void pushObj(const shared_ptr<Sim_obj> &sp);

    void clear();

    void show() const;
};


#endif
