//
//  token.hpp
//  calc variables
//
//  Created by Kyra Thompson on 7/18/18.
//  Copyright © 2018 Kyra Thompson. All rights reserved.
//

#ifndef token_h
#define token_h

#include <stdio.h>
const char invalid = 'i';
const char number = '8';
const char quit = 'q';

const char name = 'a';
const char print = ';';
const char power = '^';
const char mod = '%';
const char degree = 'd';
const char radian = 'r';

class Token{
public:
    char kind;
    string name;
    double value;
    Token(char ch) : kind{ch} {}
    Token(char ch, double val) : kind{ch}, value{val} {}
    Token(char ch, string n) : kind{ch}, name{n} {}
};
class Token_stream {
public:
    Token get();
    void putback(Token t);
    void ignore(char c);
    Token popback();
private:
    vector<Token> buffer;
};

#endif /* token_h */
