//
//  token.cpp
//  calc variables
//
//  Created by Kyra Thompson on 7/18/18.
//  Copyright © 2018 Kyra Thompson. All rights reserved.
//
#include "std_lib_facilities.h"
#include "tokens.h"

Token Token_stream::popback() {
    Token t = buffer.back();
    buffer.pop_back();
    return t;
}
void Token_stream::putback(Token t){
    buffer.push_back(t);
}
Token Token_stream::get(){
    if(buffer.size() > 0){
        Token t = popback();
        return t;
    }
    char ch;
    cin >> ch;
    switch(ch) {
        case print:
        case quit:
        case'(':
        case'+':
        case ')':
        case'-':
        case'*':
        case '/':
        case '%':
        case '=':
        case power:
        case degree:
        case radian:
            return Token{ch};
        case'0': case'1': case'2' :case'3': case'4':
        case'5': case '6': case'7': case'8': case '9': case '.':
        {
            cin.putback(ch);
            double val;
            cin >> val;
            return Token{number, val};
        }
        default:
            if(isalpha(ch)){
                string s;
                s+=ch;
                while(cin.get(ch) && (isalpha(ch) || isdigit(ch))) s+=ch;
                cin.putback(ch);
                return Token{name,s};
            }
            return Token{invalid, double(ch)};
    }
    return Token{quit};
}
void Token_stream::ignore(char c){
    while(buffer.size()>0){
        Token t = popback();
        if (t.kind == c) return;
    }
    char ch = 0;
    while(cin >> ch){
        if(ch == c) return;
    }
}
