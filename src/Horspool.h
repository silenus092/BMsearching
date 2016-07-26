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
#include <mutex>

using namespace std;

class Horspool {
# define NO_OF_CHARS 256
private:
	bool Match = false;

public:
	typedef boost::unordered_map<std::string,std::vector<string>> unordered_map;
	unordered_map *local_map;
	Horspool();
	virtual ~Horspool();
	void HORSPOOL_preBmBc(char *x, int m,int bmBc[]);
	bool getMatch();
	void Run_HORSPOOL(const char *x, int m, const char *y, int n,string id,string column,int bmBc[NO_OF_CHARS]);

	void search_HP( list<ClinicalTrialRecords> *mylist,  std::list<Gene> *gene_struct,string column ,  unordered_map *pMap);
	std::mutex mylock;
};

#endif /* HORSPOOL_H_ */
