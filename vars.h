//
//  vars.hpp
//  variables
//
//  Created by Kyra Thompson on 7/23/18.
//  Copyright © 2018 Kyra Thompson. All rights reserved.
//

#ifndef vars_hpp
#define vars_hpp

#include <stdio.h>
class Variable{
public:
    string name;
    double value;
};
double get_value(string s);
void set_value(string s, double d);



#endif /* vars_hpp */
