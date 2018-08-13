//
//  main.cpp
//  Radians To Degrees
//
//  Created by Kyra Thompson on 8/12/18.
//  Copyright © 2018 Kyra Thompson. All rights reserved.
//

#include <iostream>
#include "std_lib_facilities.h"
#include "tokens.h"
#include "vars.h"
#include "function.h"

const string prompt = "> ";
const string result = "= ";
const double pi = 3.14;
const int degInRad = 180;

//Token_stream ts;
double expression(Token_stream& ts);
double term(Token_stream& ts);
double primary(Token_stream& ts);
double exponent(Token_stream& ts);
double statement(Token_stream& ts);
double degToRad(double num);
double radToDeg(double num);

double expression(Token_stream& ts) {
    double left = term(ts);
    Token t =ts.get();
    while(true) {
        switch(t.kind){
            case '+':
                left += term(ts);
                t = ts.get();
                break;
            case '-':
                left -= term(ts);
                t = ts.get();
                break;
            default:
                ts.putback(t);
                return left;
        }
    }
}
double term(Token_stream& ts) {
    double left = exponent(ts);
    Token t =ts.get();
    while(true) {
        switch(t.kind){
            case '*':{
                left *= exponent(ts);
                t = ts.get();
                break;
            }
            case '/':{
                double div = exponent(ts);
                if (div == 0) {
                    error("can't divide by 0");
                }
                left /= div;
                t = ts.get();
                break;
            }
            case '%':{
                double d = exponent(ts);
                if(d == 0) error(" divide by zero ");
                left = fmod(left,d);
                t = ts.get();
                break;
            }
                
            default:
                ts.putback(t);
                return left;
                
        }
        
    }
}
double primary(Token_stream& ts) {
    Token t = ts.get();
    switch(t.kind){
        case '-':
            return -primary(ts);
        case '(':{
            double d = expression(ts);
            t = ts.get();
            return d;
        }
        case number:
            return t.value;
        case '+':
            return primary(ts);
        case name:
        {
            Token next_t = ts.get();
            if(next_t.kind =='('){
                double d = expression(ts);
                next_t = ts.get();
                if(next_t.kind != ')') error(" ')' expected");
               
                d = call_func(t.name, d);
                return d;
            }
            else{
                ts.putback(next_t);
                return get_value(t.name);
            }
        }
        case degree:{
            Token next_t = ts.get();
            if(next_t.kind =='('){
                double d = expression(ts);
                next_t = ts.get();
                if(next_t.kind != ')') error(" ')' expected");
                d = radToDeg(d);
                return d;
                
            }
        }
        case radian:{
            Token next_t = ts.get();
            if(next_t.kind =='('){
                double d = expression(ts);
                next_t = ts.get();
                if(next_t.kind != ')') error(" ')' expected");
                d = degToRad(d);
                return d;
                
            }
        }
        default:
            error("Error: primary expected");
            
    }
    return t.value;
}
double statement(Token_stream& ts){
    Token t = ts.get();
    if (t.kind == name){
        Token var = t;
        t = ts.get();
        if(t.kind == '=' ){
            double d = expression(ts);
            set_value(var.name,d);
            return d;
        }
        else if(t.kind == print){
            ts.putback(t);
            return get_value(var.name);
        }
        ts.putback(t);
        ts.putback(var);
        return expression(ts);
    }
    ts.putback(t);
    return expression(ts);
}

double exponent(Token_stream& ts){
    double left = primary(ts);
    Token t = ts.get();
    if(t.kind == power){
        double d = primary(ts);
        return pow(left,d);
    }
    else {
        ts.putback(t);
        return left;
    }
}

double degToRad(double num){
    return ((pi/degInRad)*num);
    
};
double radToDeg(double num){
    return ((degInRad/pi)*num);
};
vector<Token> tokens;

void print_token(Token t){
    cout << "Got token of kind " << t.kind << " with value of " << t.value << endl;
}
void clean_up_mess(Token_stream& ts){
    ts.ignore(print);
}
void calculate(Token_stream& ts){
    while (cin){
        try{
            cout << prompt;
            Token t = ts.get();
            while(t.kind == print ) t = ts.get();
            if(t.kind == quit) return;
            ts.putback(t);
            cout << result << setprecision(8) << statement(ts) << '\n';
        }
        catch(exception& e ){
            cerr<< e.what()<< endl;
            clean_up_mess(ts);
            
        }
    }
}

int main() {
    Token_stream ts;
    try{
        calculate(ts);
        return 0;
    }    catch(...){
        cerr << "Unknown exception \n";
        return 2;
    }
    
}
