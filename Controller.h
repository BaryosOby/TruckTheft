//
// Created by Itamar on 01/06/2022.
//

#ifndef CPPAD03_CONTROLLER_H
#define CPPAD03_CONTROLLER_H
#define MAX_NAME 12
#include <iostream>
#include <vector>
#include <fstream>
#include <exception>
#include <sstream>
using namespace std;
class Controller {
public:
    vector<string> split(string& text,const string& delimiter = ",");

    void validFile(const string& fileName, fstream& file);

    void validName(const string& name , int maxSize = MAX_NAME);

    void validTruck(vector<string>& data , bool isFirst = false);

    float convertStringToFloat(string & number);

    void replaceChar(string& str, const string& c = ".");

    void validStateTrooper(vector<string>& data);

    void removeBrackets(string & str);

    void validChopper(vector<string>& data);
};


#endif //CPPAD03_CONTROLLER_H
