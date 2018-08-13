//
//  vars.cpp
//  variables
//
//  Created by Kyra Thompson on 7/23/18.
//  Copyright © 2018 Kyra Thompson. All rights reserved.
//
#include "std_lib_facilities.h"
#include "vars.h"


vector<Variable> var_table;
double get_value(string s){
    for(Variable var: var_table)
        if(var.name == s) return var.value;
    return 0.0;
}
void set_value(string s, double d){
    for(Variable& var : var_table){
        if (var.name == s){
            var.value = d;
            return;
        }
    }
    var_table.push_back(Variable{s,d});
}
