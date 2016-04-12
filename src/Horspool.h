/*
 * Horspool.h
 *
 *  Created on: Apr 2, 2016
 *      Author: note
 */

#ifndef HORSPOOL_H_
#define HORSPOOL_H_
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
class Horspool {
# define NO_OF_CHARS 256
private:
	bool Match = false;
public:
	Horspool();
	virtual ~Horspool();
	void HORSPOOL_preBmBc(char *x, int m);
	bool getMatch();
	void Run_HORSPOOL(char *x, int m, char *y, int n,string id,string column);
	void search( char *txt,  char *pat , string id,string column);
};

#endif /* HORSPOOL_H_ */
