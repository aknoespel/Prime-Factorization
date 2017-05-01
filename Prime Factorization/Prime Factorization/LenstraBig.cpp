//
//  LenstraBig.cpp
//  Prime Factorization
//
//  Created by Alexander Knoespel on 12/27/14.
//  Copyright (c) 2014 Alexander Knoespel. All rights reserved.
//

#include "LenstraBig.h"
#include "BigECurve.h"
#include <queue>
std::queue<BigInteger> myqueue;
void factor(BigInteger n){
    cout<<"Factorization of "<<n<<":"<<endl;
    myqueue.push(n);
    while(myqueue.size()!=0){
        BigInteger m= myqueue.front();
        myqueue.pop();
        if(isPrime(m)){
            cout<<m<<", ";
        }
        else{
            //cout<<"factoring "<<m<<endl;
        try{
            Number b=Number(1,m);
            Point factorials[10];
            //Point* factorials=new Point[10];
           for(int tries=0;  ; tries++){
               //cout<<"tries: "<<tries<<endl;
            //until factor found, keep picking a
            for(int i=0; i<10; i++){
                try{
                    Number a=Number(i,m);
                    Ecurve curve=Ecurve(a,b);
                    Point p;
                    //Point p=Point(Number(0,m),Number(1,m),&curve);
                    if(tries==0){
                        factorials[i]=Point(Number(0,m),Number(1,m),&curve);
                    }
                    p=factorials[i];
                    //cout<<i<<endl;
                    for(int j=10*tries+1; j<=10*tries+10; j++){
                        //cout<<j<<endl;
                        p=p*j;
                    }
                    (factorials[i])=p;
                }catch(NotValidCurve& e){
                    
                }
            }
        }
            //delete factorials;
        }catch(NoInverse& e){
            myqueue.push(m/e.gcd);
            myqueue.push(e.gcd);
        }
        }
    }
    cout<<endl;
}

bool isPrime(BigInteger n){
    //a^(p-1)=1 mod p
    //return false;
    Number a=Number(3,n);
    Number b=Number(5,n);
    if(n==3 || n==5){
        return true;
    }
    if(n%3==0 ||n%5==0){
        return false;
    }
  //  Number c=(a^6==1);
    if(((a^(n-1))==1) && (b^(n-1))==1){
        return true;
    }
    return false;
    
}


istream& operator>> (istream& in,  BigInteger& n){
    n=0;
    while(true){
    char ch;
    in.get(ch);
        //in>>ch;
        int digit=ch-'0';
        //cout<<ch<<endl;
        //cout<<digit<<"digit"<<endl;
        if(digit<0 || digit>9){
            //cout<<n<<endl;
            return in;
        }
        n*=10;
        n+=digit;
    }
}
