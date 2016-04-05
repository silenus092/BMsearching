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

using namespace std;
struct ClinicalTrialRecords {
		string nct_id;
		string brief_title;
		string brief_summary;
		string detailed_description;
		string criteria;
	};
class BM {
# define NO_OF_CHARS 256


public:

	BM();
	virtual ~BM();
	void Run_BM(char *x, int m, char *y, int n, string id,string column);
	int MAX (int a, int b) ;
	void badCharHeuristic( char *str, int size, int badchar[NO_OF_CHARS]);
	void search( list<ClinicalTrialRecords> *list,  char *pat ,string column);
	bool getMatch();
	void publicFunction();

};

#endif /* BM_H_ */
