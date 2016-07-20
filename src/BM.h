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
#include <thread>
#include <list>
#include <mutex>
#include "BMsearching.h"
using namespace std;

class BM {

# define NO_OF_CHARS 256
public:
	typedef boost::unordered_map<std::string,std::vector<string>> unordered_map;
	unordered_map *local_map;
	BM();
	virtual ~BM();
	void Run_BM(char *x, int m, char *y, int n, string id, string column, int bmGs[256], int bmBc[256]);
	int MAX (int a, int b) ;
	void badCharHeuristic( char *str, int size, int badchar[NO_OF_CHARS]);
	void search( list<ClinicalTrialRecords> *list,  char *pat ,string column ,  unordered_map *pMap);
	bool getMatch();
	void publicFunction();
	std::mutex mylock;

};

#endif /* BM_H_ */
