/*
 * BM.h
 *
 *  Created on: Feb 18, 2016
 *      Author: note
 */

#ifndef BM_H_
#define BM_H_
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

class BM {
# define NO_OF_CHARS 256
public:
	BM();
	virtual ~BM();
	void Run_BM(char *x, int m, char *y, int n, string id,string column);
	int MAX (int a, int b) ;
	void badCharHeuristic( char *str, int size, int badchar[NO_OF_CHARS]);
	void search( char *txt,  char *pat , string id,string column);
	bool getMatch();
	void publicFunction();

};

#endif /* BM_H_ */
