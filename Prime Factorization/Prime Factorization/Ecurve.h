//
//  Ecurve.h
//  Prime Factorization
//
//  Created by Alexander Knoespel on 12/22/14.
//  Copyright (c) 2014 Alexander Knoespel. All rights reserved.
//

#ifndef __Prime_Factorization__Ecurve__
#define __Prime_Factorization__Ecurve__
#include <iostream>
#include <exception>
using namespace std;
//class Number;
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
class Number{
public:
    Number();
    Number(int value, int mod);
    //Number(int value, Ecurve*);
    friend Number operator+(const Number& n1, const Number& n2);
    friend Number operator-(const Number& n1, const Number& n2);
    friend Number operator*(const Number& n1, const Number& n2);
    friend Number operator/(const Number& n1, const Number& n2);
    friend ostream& operator<<(ostream& out, const Number& n);
    friend bool operator==(const Number& n1, const Number& n2);
    friend bool operator!=(const Number& n1, const Number& n2);
    friend bool operator==(const Number& lhs,const int rhs);
    friend bool operator==(const int lhs, const Number& rhs);
    friend bool operator!=(const Number& lhs,const int rhs);
    friend bool operator!=(const int lhs, const Number& rhs);
    Number& operator*=(const int n);
    
    int value;
    int mod;
};

Number operator*(const Number&, const int n);
Number operator*(const int n, const Number&);

class NoInverse: public exception
{
public:
    NoInverse(int g){
        gcd=g;
    }
    int gcd;
private:
    virtual const char* what() const throw()
    {
        return "No inverse";
    }
};
/////////////////////////////////////////////////////////////////
class Ecurve{
public:
    Ecurve();
    Ecurve(Number& a, Number& b);
    int characteristic;
    
    Number* a;
    Number* b;
};

class NotValidCurve: public exception
{
    virtual const char* what() const throw()
    {
        return "Not Valid Curve";
    }
};

//////////////////////////////////////////////////////////////////
class Point{
public:
    Point(Number a, Number b, Ecurve*);
    Point(Ecurve*);
    Point(const Point&); //copy constructor
    friend bool operator==(const Point& n1, const Point& n2);
    friend bool operator!=(const Point& n1, const Point& n2);
    friend ostream& operator<<(ostream& out, const Point& n);
    Point& operator=(const Point& p);
    Ecurve* curve;
    Number a,b;
    bool infinity;
};
//only takes positive integers
void toBinary(int m,int* &binary);

Point operator+(const Point& a,const Point& b);
Point operator*(const Point& p, const int m);
Point operator*(const int m, const Point& p);

class NotOnCurve: public exception
{
    virtual const char* what() const throw()
    {
        return "Not On Curve";
    }
};

class InputMismatch: public exception
{
    virtual const char* what() const throw()
    {
        return "InputMismatch";
    }
};/////////////////////////////////////////////////////////////////
#include <stdio.h>

#endif /* defined(__Prime_Factorization__Ecurve__) */
