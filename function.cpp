//
//  function.cpp
//  Radians To Degrees
//
//  Created by Kyra Thompson on 8/12/18.
//  Copyright © 2018 Kyra Thompson. All rights reserved.
//
#include "std_lib_facilities.h"
#include <map>
#include "function.h"
map<const string,function<double(double)> > funcTable {
    {"sin", [](double a) { return sin(a); }},
    {"cos", [](double a) { return cos(a); }},
    {"tan", [](double a) { return tan(a); }},
    {"asin", [](double a) { return asin(a); }},
    {"acos", [](double a) { return acos(a); }},
    {"atan", [](double a) { return atan(a); }},
    {"sinh", [](double a) { return sinh(a); }},
    {"cosh", [](double a) { return cosh(a); }},
    {"tanh", [](double a) { return tanh(a); }},
    {"sqrt", [](double a) { return sqrt(a); }},
    {"log", [](double a) { return log(a); }},
    {"log2", [](double a) { return log2(a); }},
    {"log10", [](double a) { return log10(a); }},
};
    
double call_func(string func, double a){
    try {
        return funcTable[func](a);
    }
    
    catch(...){
        cout <<"Error: function not defined " << func << endl;
    }
    
    return 0.0;
}
        
