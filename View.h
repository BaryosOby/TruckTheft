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


class View {
private:
    Point pan;
    double zoom;
    int size;
    vector<weak_ptr<Sim_obj>> objects;

    Point normalize(const Point& p) const;
    map<Point, string>& objects_in_range();

public:
    View();

    const Point &getPan() const;

    void setPan(const Point &pan);

    double getZoom() const;

    void setZoom(double zoom);

    int getSize() const;

    void setSize(int size);

    void pushObj(const shared_ptr<Sim_obj>& sp);

    void clear();

    void show() const;
};


#endif
