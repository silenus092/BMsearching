/*
 * BM.h
 *
 *  Created on: Feb 18, 2016
 *      Author: note
 */

#ifndef BM_H_
#define BM_H_

class BM {
# define NO_OF_CHARS 256
public:
	BM();
	virtual ~BM();
	int max (int a, int b) ;
	void badCharHeuristic( char *str, int size, int badchar[NO_OF_CHARS]);
	void search( char *txt,  char *pat);
};

#endif /* BM_H_ */
