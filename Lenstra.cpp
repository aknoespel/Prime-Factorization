//
//  Lenstra.cpp
//  Prime Factorization
//
//  Created by Alexander Knoespel on 12/23/14.
//  Copyright (c) 2014 Alexander Knoespel. All rights reserved.
//

#include "Lenstra.h"
#include "Ecurve.h"
#include <queue>
std::queue<int> myqueue;
void factor(int n){
    cout<<"Factorization of "<<n<<":"<<endl;
    myqueue.push(n);
    //int factor;
    while(myqueue.size()!=0){
        int m= myqueue.front();
        myqueue.pop();
        try{
            Number b=Number(1,m);
            //until factor found, keep picking a
            for(int i=0; i<10; i++){
                try{
                    Number a=Number(i,m);
                    Ecurve curve=Ecurve(a,b);
                    Point p=Point(Number(0,m),Number(1,m),&curve);
                    for(int j=2; j<10; j++){
                        p=p*j;
                    }
                    
                }catch(NotValidCurve& e){
                    
                }
            }
            cout<<m<<", ";
        }catch(NoInverse& e){
            myqueue.push(m/e.gcd);
            myqueue.push(e.gcd);
        }
    }
    cout<<endl;
}