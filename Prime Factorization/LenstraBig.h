//
//  LenstraBig.h
//  Prime Factorization
//
//  Created by Alexander Knoespel on 12/27/14.
//  Copyright (c) 2014 Alexander Knoespel. All rights reserved.
//

#ifndef __Prime_Factorization__LenstraBig__
#define __Prime_Factorization__LenstraBig__

#include <stdio.h>
#include "BigInteger.h"
#include <iostream>


void factor(BigInteger n);
bool isPrime(BigInteger n);
std::istream& operator>> (std::istream& in, BigInteger& n);

#endif /* defined(__Prime_Factorization__LenstraBig__) */
