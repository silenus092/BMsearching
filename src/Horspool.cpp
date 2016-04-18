/*
 * Horspool.cpp
 *
 *  Created on: Apr 2, 2016
 *      Author: note
 */

#include "Horspool.h"
int bmBc[NO_OF_CHARS];

Horspool::Horspool() {
	// TODO Auto-generated constructor stub

}

Horspool::~Horspool() {
	// TODO Auto-generated destructor stub
}

void Horspool::HORSPOOL_preBmBc(char *x, int m) {
	int i;
	for (i = 0; i < NO_OF_CHARS; ++i)
		bmBc[i] = m;
	for (i = 0; i < m - 1; ++i)
		bmBc[x[i]] = m - i - 1;
}

bool Horspool::getMatch()
{
  return Match ;
}

void Horspool::Run_HORSPOOL(char *x, int m, char *y, int n,string id,string column) {
   int j;
   char c;

   /* Preprocessing */
  HORSPOOL_preBmBc(x, m);
   /* Searching */
   j = 0;
  /*while (j <= n - m) {
	   //cout << "J: "<< j << endl;
      c = y[j + m - 1];
      if (x[m - 1] == c && memcmp(x, y + j, m-1 ) == 0){
    	  cout << "Column name: "<< column << " | Pattern ID: "<< id <<" | Found at: "<< j << endl;
    	  break;
      }else{
       j += bmBc[c];
      }
   }*/
   while (j <= n - m) {
 	      c = y[j + m - 1];
 	      if (x[m - 1] == c && memcmp(x, y + j, m - 1) == 0){
 	    	  cout << "Found at:" <<j<< endl;
 	      }
 	      j += bmBc[c];
 	   }
   //delete [] bmBc;
}


void Horspool::search_HP(std::list<ClinicalTrialRecords> * mylist,  char *pat ,string column){
    int m = strlen(pat);
    //int n = strlen(txt);

    std::list<ClinicalTrialRecords>::iterator it;
    	it = mylist->begin();
    	if (column == "brief_title") {
    		while (it != mylist->end()) {
    			string str = it->brief_title;
    			char *txt = &str[0u];
    			string id = it->nct_id;
    			int n = strlen(txt);
    			Run_HORSPOOL(pat, m, txt, n, id, column);
    			it++;
    		}
    	} else if (column == "brief_summary") {
    		while (it != mylist->end()) {
    			string str = it->brief_summary;
    			char *txt = &str[0u];
    			string id = it->nct_id;
    			int n = strlen(txt);
    			Run_HORSPOOL(pat, m, txt, n, id, column);
    			it++;
    		}
    	} else if (column == "detailed_description") {
    		while (it != mylist->end()) {
    			string str = it->detailed_description;
    			char *txt = &str[0u];
    			string id = it->nct_id;
    			int n = strlen(txt);
    			Run_HORSPOOL(pat, m, txt, n, id, column);
    			it++;
    		}
    	} else if (column == "criteria") {
    		while (it != mylist->end()) {
    			string str = it->criteria;
    			char *txt = &str[0u];
    			string id = it->nct_id;
    			int n = strlen(txt);
    			Run_HORSPOOL(pat, m, txt, n, id, column);
    			it++;
    		}
    	}

	//Run_HORSPOOL(pat,m,txt,n,id,column);
}



