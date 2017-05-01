//
//  Ecurve.cpp
//  Prime Factorization
//
//  Created by Alexander Knoespel on 12/22/14.
//  Copyright (c) 2014 Alexander Knoespel. All rights reserved.
//

#include "Ecurve.h"

Ecurve::Ecurve(Number& a, Number& b):
a(&a),b(&b){
    if(a.mod!=b.mod){
        throw NotValidCurve();
    }
    if(a.mod==2 || a.mod==3){
        throw NotValidCurve();
    }
    if(4*a*a*a+27*b*b==0){
        throw NotValidCurve();
    }
    characteristic=a.mod;
    
}
/////////////////////////////////////////////////////
Point::Point(Number a, Number b, Ecurve* curve):
a(a),b(b),curve(curve),infinity(false){
    if(b*b!=a*a*a+*(curve->a)*a+*(curve->b)){
        //cout<<"before crash "<<b*b<<" "<<a*a*a+*(curve->a)*a+*(curve->b)<<endl;
        // throw NotOnCurve();
    }
}
Point::Point(Ecurve* curve):
a(Number(0,curve->characteristic)),b(Number(0,curve->characteristic)),curve(curve),infinity(true){
    
}

Point::Point(const Point& p):
a(p.a), b(p.b), curve(p.curve),infinity(p.infinity){
    
}//copy constructor

Point operator+(const Point& p1, const Point& p2){
    if(p1.curve!=p2.curve){
        throw InputMismatch();
    }
    if(p1.infinity){
        return Point(p2);
    } else if(p2.infinity){
        return Point(p1);
    } else if (p1.a==p2.a && p1.b==-1*p2.b){
        return Point(p1.curve);
    }
    else if(p1!=p2){
        Number m=(p2.b-p1.b)/(p2.a-p1.a);
        Number x3=m*m-p1.a-p2.a;
        Number y3=m*(x3-p1.a)+p1.b;
        return Point(x3,y3,(p1.curve));
    } else {
        Number m=(3*p1.a*p1.a + *p1.curve->a)/(p1.b+p1.b);
        Number x3=m*m-p1.a-p1.a;
        Number y3=m*(x3-p1.a)+p1.b;
        return Point(x3,y3,(p1.curve));
    }
    
}

//Assignment operators
Point& Point::operator=(const Point& p){
    a=p.a;
    b=p.b;
    curve=p.curve;
    infinity=p.infinity;
    return *this;
}
bool operator==(const Point& p1, const Point& p2){
    return (p1.infinity==true && p2.infinity==true)|| (p1.a==p2.a && p1.b==p2.b && p1.curve==p2.curve && !p1.infinity && !p2.infinity);
}

bool operator!=(const Point& p1, const Point& p2){
    return !(p1==p2);
}

ostream& operator<<(ostream& out, const Point& p){
    if(p.infinity){
        out<<"INFINITY"<<endl;
    } else{
        out<<p.a.value <<" , "<<p.b.value;
    }
    return out;
}

//function returns consecutive numbers representing binary digits of m
//dynamically allocated list
void toBinary(int m,int* &binary){
    int n=m;
    int digits=0;
    while(n!=0){
        int d=n%2;
        n=(n-d)/2;
        digits++;
    }
    int* temp=new int[digits+1];
    temp[0]=digits;
    n=m;
    int i=1;
    while(n!=0){
        int d=n%2;
        n=(n-d)/2;
        *(temp+i)=d;
        //cout<<*(temp+i)<<endl;
        i++;
    }
    binary=temp;
    
}

Point operator*(const Point& p, const int m){
    int* n;
    toBinary(m,n);
    int digits=n[0];
    Point r0=Point(p.curve);
    Point r1=p;
    for(int i=digits; i>0; i--){
        if(n[i]==0){
            r1=r0+r1;
            r0=r0+r0;
        } else{
            r0=r0+r1;
            r1=r1+r1;
        }
    }
    delete n;
    return r0;
}

Point operator*(const int m, const Point& p){
    int* n;
    toBinary(m,n);
    int digits=n[0];
    Point r0=Point(p.curve);
    Point r1=p;
    for(int i=digits; i>0; i--){
        if(n[i]==0){
            r1=r0+r1;
            r0=r0+r0;
        } else{
            r0=r0+r1;
            r1=r1+r1;
        }
    }
    delete n;
    return r0;
}

////////////////////////////////////////////////////
//empty Number constructor
Number::Number(){
    
}

Number::Number(int value, int mod):
value(value%mod),mod(mod){
    
}

ostream& operator<<(ostream& out, const Number& n){
    out<<n.value;
    return out;
}

Number& Number::operator*=(const int n){
    value=(value*n)%mod;
    return *this;
}

Number operator*(const Number& number, const int n){
    Number answer(number);
    answer*=n;
    return answer;
}

Number operator*(const int n, const Number& number){
    Number answer(number);
    answer*=n;
    return answer;
}

bool operator==(const Number& n1, const Number& n2){
    // return n1.value%n1.mod==n2.value%n1.mod && n1.mod==n2.mod;
    return (n1.value-n2.value)%n1.mod==0 && n1.mod==n2.mod;
}

bool operator!=(const Number& n1, const Number& n2){
    return !(n1==n2);
}

//for compare to constants shorthand
bool operator==(const Number& lhs,const int rhs){
    Number n2=Number(rhs,lhs.mod);
    return lhs==n2;
}
bool operator==(const int lhs, const Number& rhs){
    Number n2=Number(lhs,rhs.mod);
    return rhs==n2;
}

bool operator!=(const Number& lhs,const int rhs){
    
    return !(lhs==rhs);
}
bool operator!=(const int lhs, const Number& rhs){
    return !(lhs==rhs);
}

Number operator+(const Number& n1, const Number& n2){
    if(n1.mod==n2.mod){
        return Number((n1.value+n2.value)%(n1.mod),n1.mod);
    } else{
        return Number();
    }
}
Number operator-(const Number& n1, const Number& n2){
    if(n1.mod==n2.mod){
        return Number((n1.value-n2.value)%(n1.mod),n1.mod);
    } else{
        return Number();
    }
}
Number operator*(const Number& n1, const Number& n2){
    if(n1.mod==n2.mod){
        return Number((n1.value*n2.value)%(n1.mod),n1.mod);
    } else{
        return Number();
    }
}
Number operator/(const Number& n1, const Number& n2){
    if(n1.mod==n2.mod){
        //find inverse of n2
        int inverse;
        //make n2 value positive
        int q=(n2.value)%n2.mod;
        if(q<0){
            q+=n2.mod;
        }
        //use extended euclid algorithm
        int x=q;
        int y=n2.mod;
        int a=1, b=0, c=0, d=1;
        while(x!=1 && y!=1){
            if(x==0){
                throw NoInverse(y);
            }
            if(y==0){
                throw NoInverse(x);
            }
            if(x>y){
                int p=x/y;
                a=a-p*c;
                b=b-p*d;
                x=x-p*y;
            } else{
                int p=y/x;
                c=c-p*a;
                d=d-p*b;
                y=y-p*x;
            }
        }
        if(x==1){
            inverse=a%n2.mod;
        } else{
            inverse=c%n2.mod;
        }
        return n1*Number(inverse,n2.mod);
    } else{
        return Number();
    }
}
