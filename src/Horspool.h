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
#include <thread>
#include <list>
#include "BMsearching.h"
#include <boost/algorithm/string.hpp>
using namespace std;

class Horspool {
# define NO_OF_CHARS 256
private:
	bool Match = false;

public:
	Horspool();
	virtual ~Horspool();
	void HORSPOOL_preBmBc(char *x, int m,int bmBc[]);
	bool getMatch();
	void Run_HORSPOOL(const char *x, int m, const char *y, int n,string id,string column,int bmBc[NO_OF_CHARS]);

	void search_HP( list<ClinicalTrialRecords> *mylist,  char *pat ,string column );
};

#endif /* HORSPOOL_H_ */
