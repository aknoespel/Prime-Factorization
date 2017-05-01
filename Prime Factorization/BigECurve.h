//
//  BigECurve.h
//  Prime Factorization
//
//  Created by Alexander Knoespel on 12/27/14.
//  Copyright (c) 2014 Alexander Knoespel. All rights reserved.
//

#ifndef __Prime_Factorization__BigECurve__
#define __Prime_Factorization__BigECurve__


#include <iostream>
#include <exception>
#include "BigIntegerLibrary.h"
using namespace std;
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
class Number{
public:
    Number();
    Number(BigInteger value, BigInteger mod);
    //Number(int value, Ecurve*);
    friend Number operator+(const Number& n1, const Number& n2);
    friend Number operator-(const Number& n1, const Number& n2);
    friend Number operator*(const Number& n1, const Number& n2);
    friend Number operator/(const Number& n1, const Number& n2);
    friend Number operator^(const Number& n, const BigInteger p);
    friend ostream& operator<<(ostream& out, const Number& n);
    friend bool operator==(const Number& n1, const Number& n2);
    friend bool operator!=(const Number& n1, const Number& n2);
    friend bool operator==(const Number& lhs,const BigInteger rhs);
    friend bool operator==(const BigInteger lhs, const Number& rhs);
    friend bool operator!=(const Number& lhs,const BigInteger rhs);
    friend bool operator!=(const BigInteger lhs, const Number& rhs);
    Number& operator*=(const BigInteger n);
    
    BigInteger value;
    BigInteger mod;
};

Number operator*(const Number&, const BigInteger n);
Number operator*(const BigInteger n, const Number&);

class NoInverse: public exception
{
public:
    NoInverse(BigInteger g){
        gcd=g;
    }
    BigInteger gcd;
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
    BigInteger characteristic;
    
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
    Point();
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
void toBinary(BigInteger m,int* &binary);

Point operator+(const Point& a,const Point& b);
Point operator*(const Point& p, const BigInteger m);
Point operator*(const BigInteger m, const Point& p);

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
};
/////////////////////////////////////////////////////////////////

#endif /* defined(__Prime_Factorization__BigECurve__) */
