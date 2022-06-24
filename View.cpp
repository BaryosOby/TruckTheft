#include "View.h"

//check if a location of an object is the radius of a point in the view map
Point View::checkRange(const Point &p) const {
    double x = p.x;
    double y = p.y;
    Point res = Point(UINT32_MAX, UINT32_MAX);
    double curr_x = pan.x;
    double curr_y = pan.y;
    double max_x = curr_x + (size * zoom); // not size-1 because we take one more unit than the map border
    double max_y = curr_y + (size * zoom); // not size-1 because we take one more unit than the map border
    double y_index = pan.y;
    double x_index = pan.x;
    double next_x = curr_x + zoom;
    double next_y = curr_y + zoom;
    while (next_x <= max_x && next_y <= max_y) {
        if (x >= curr_x && x < next_x) {
            res.x = x_index;
        }
        if (y >= curr_y && y < next_y) {
            res.y = y_index;
        }
        curr_x = next_x;
        curr_y = next_y;
        next_x += (zoom);
        next_y += (zoom);
        x_index += zoom;
        y_index += zoom;
    }
    return res;
}

//updating objects that are in the range of the map
void View::objects_in_range() {
    obj_in_range.clear();
    Point check_range;
    string name;
    for (const auto &obj: objects) {
        if (typeid(*(obj.lock())) == typeid(Warehouse)) {
            check_range = checkRange(obj.lock()->getInitLocation());
        } else {
            check_range = checkRange(dynamic_pointer_cast<Vehicle>(obj.lock())->getLocation());
        }
        if (check_range.x != UINT32_MAX && check_range.y != UINT32_MAX) {
            name += obj.lock()->getName()[0];
            name += obj.lock()->getName()[1];
            obj_in_range.insert(pair<pair<double, double>, string>(make_pair(check_range.x, check_range.y), name));
            name = "";
        }
    }
}

const Point &View::getPan() const {
    return pan;
}

void View::setPan(const Point &p) {
    View::pan = p;
}

double View::getZoom() const {
    return zoom;
}

void View::setZoom(double zm) {
    View::zoom = zm;
}

int View::getSize() const {
    return size;
}

void View::setSize(int sze) {
    View::size = sze;
}

View::View() : pan(DEF_PAN, DEF_PAN), zoom(DEF_SCALE), size(DEF_SIZE) {
}

void View::pushObj(const shared_ptr<Sim_obj> &sp) {
    objects.push_back(sp);
}

void View::clear() {
    objects.clear();
}
// print map & objects that in her range
void View::show() {
    objects_in_range();
    cout << "Display size: " << size << ", scale: " << setprecision(2) << zoom << ", origin: ";
    cout << "(" << setprecision(2) << pan.x << "," << setprecision(2) << pan.y << ")" << endl;
    double curr_x = pan.x;
    double curr_y = pan.y + ((size - 1) * zoom);
    double max_range_x = pan.x + ((size - 1) * zoom);
    int toPrint = 0;
    while (curr_y >= pan.y) {
        if (toPrint % 4 == 0) {
            cout << setw(4) << (int)curr_y;
            cout << " ";
        } else {
            cout << "     ";
        }
        toPrint++;
        while (curr_x <= max_range_x) {
            auto p = pair<double, double>(curr_x, curr_y);
            if (obj_in_range.find(p) != obj_in_range.end()) {
                cout << obj_in_range.at(p) << " ";
            } else {
                cout << ".  ";
            }
            curr_x += zoom;
        }
        curr_x = pan.x;
        curr_y -= zoom;
        cout << endl;
    }
    print_x_interval(); //print curr x location
}
// print x bar
void View::print_x_interval() const {
    int toPrint = 1;
    double curr_x = pan.x;
    cout << setw(6) << (int) curr_x;
    curr_x += zoom;
    for (int i = 0; i < size; ++i) {

        if (toPrint % 4 == 0) {
            cout << setw(12) << (int) curr_x;
        }
        curr_x += zoom;
        toPrint++;
    }
    cout << endl;
}
//set default values to the map
void View::def_values() {
    Point p(DEF_PAN, DEF_PAN);
    setPan(p);
    setSize(DEF_SIZE);
    setZoom(DEF_SCALE);
}

