#ifndef CPPAD03_CONTROLLER_H
#define CPPAD03_CONTROLLER_H
#define MAX_NAME 12

#include <fstream>
#include <exception>
#include <sstream>
#include "Model.h"

using namespace std;

class Controller {
private:
    map<string, int> choices = {{"default",     0},
                                {"size",        1},
                                {"zoom",        2},
                                {"pan",         3},
                                {"show",        4},
                                {"status",      5},
                                {"go",          6},
                                {"create",      7},
                                {"exit",        8},
                                {"course",      9},
                                {"position",    10},
                                {"destination", 11},
                                {"attack",      12},
                                {"stop",        13}};


public:
    vector<string> split(string& text,const string& delimiter = ",");

    void validFile(const string& fileName, fstream& file);

    void validName(const string& name , int maxSize = MAX_NAME);

    void validTruckLineSyntax(vector<string>& data , bool isFirst = false);

    void parseTruck(string& file_name, fstream& file);

    void validWareLineSyntax(vector<string>& data);

    void parseWarehouse(string& file_name, fstream& file);

    double convertStringToFloat(string &number, bool is_time = false);

    void replaceChar(string& str, const string& c = ".");

    void validStateTrooper(vector<string>& data);

    void removeBrackets(string & str);

    void validChopper(vector<string>& data);
};


#endif //CPPAD03_CONTROLLER_H
