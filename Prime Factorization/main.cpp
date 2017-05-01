//
//  main.cpp
//  Prime Factorization
//
//  Created by Alexander Knoespel on 12/22/14.
//  Copyright (c) 2014 Alexander Knoespel. All rights reserved.
//

#include <iostream>
#include "LenstraBig.h"
#include "BigIntegerLibrary.h"
#include "BigECurve.h"
using namespace std;
int main(int argc, const char * argv[]) {
    for(int i=0; i<5; i++){
        
    }
    BigInteger a=14627349456;
    BigInteger b=121334636;
    //cout<<a*b<<endl;
    Number c=Number(4,7);
    Number d=c^4;
    //int e=5^2;
    //cout<<d<<endl;
    //factor(10000);
    //factor(a*b);
    
    BigInteger n;
    cout<<"Enter Integer To Factor:"<<endl;
    cin>>n;
    //cout<<n<<"end"<<endl;
    factor(n);
    
    return 0;
}
