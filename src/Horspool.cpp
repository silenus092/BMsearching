/*
 * Horspool.cpp
 *
 *  Created on: Apr 2, 2016
 *      Author: note
 */

#include "Horspool.h"


Horspool::Horspool() {
	// TODO Auto-generated constructor stub

}

Horspool::~Horspool() {
	// TODO Auto-generated destructor stub
}

void Horspool::HORSPOOL_preBmBc(char *x, int m, int bmBc[]) {
	int i;
	for (i = 0; i < NO_OF_CHARS; ++i)
		bmBc[i] = m;
	m = m-1;
	for (i = 0; i < m ; ++i)
		bmBc[x[i]] = m - i ;
}

bool Horspool::getMatch()
{
  return Match ;
}

void Horspool::Run_HORSPOOL(const char *pat, int m, const char *txt, int n,string id,string column,int bmBc[NO_OF_CHARS]) {
   int j =0 ;
   char c;

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
   //cout << "Column name: "<< column << " | Pattern ID: "<< id <<" | txt: "<< txt<< endl;
   int count =0;
        while (j <= n ) {

			if(j + m-1 < sizeof(txt)){
				c = txt[j + m-1];
			}else{
				c =  txt[j + m];
			}


			cout << "C: "<< c << endl;
 	      if (pat[m - 1] == c && memcmp(pat, txt + j, m - 1) == 0){
 	    	  cout <<id << " " <<column << " Found at:" <<j<< endl;

 	    	 break;
 	      }

 	      j += bmBc[c];


 	     //cout <<"c "<< bmBc[c] <<" j " <<j << endl;
 	   }

}

const  char* boyermoore_horspool_memmem(const  char* haystack,
												size_t hlen,
												const  char* needle,
												size_t nlen,string id,string column,int bmBc[NO_OF_CHARS])
{
	size_t scan = 0;
	 /* Officially called:
                                          * bad character shift */
	//cout << "Column name: "<< column << " | Pattern ID: "<< id <<" | txt: "<< haystack<< endl;
	/* Sanity checks on the parameters */
	if (nlen <= 0 || !haystack || !needle)
		return NULL;


	/* C arrays have the first byte at [0], therefore:
     * [nlen - 1] is the last byte of the array. */
	size_t last = nlen - 1;



	/* ---- Do the matching ---- */

	/* Search the haystack, while the needle can still be within it. */
	while (hlen >= nlen)
	{
		/* scan from the end of the needle */
		for (scan = last; haystack[scan] == needle[scan]; scan = scan - 1)
		{

			if (scan == 0)
			{
				cout <<id << " " <<column << " Found at:" <<haystack<< endl;
				return haystack;
			}
		}

		/* otherwise, we need to skip some bytes and start again.
           Note that here we are getting the skip value based on the last byte
           of needle, no matter where we didn't match. So if needle is: "abcd"
           then we are skipping based on 'd' and that value will be 4, and
           for "abcdd" we again skip on 'd' but the value will be only 1.
           The alternative of pretending that the mismatched character was
           the last character is slower in the normal case (Eg. finding
           "abcd" in "...azcd..." gives 4 by using 'd' but only
           4-2==2 using 'z'. */
		hlen     -= bmBc[haystack[last]];
		haystack += bmBc[haystack[last]];

	}

	return NULL;
}

void Horspool::search_HP(std::list<ClinicalTrialRecords> * mylist,  char *pat ,string column){
    int m = strlen(pat);
    //int n = strlen(txt);
    int bmBc[NO_OF_CHARS];
    /* Preprocessing */
   HORSPOOL_preBmBc(pat, m,bmBc);
    std::list<ClinicalTrialRecords>::iterator it;
    	it = mylist->begin();
    	if (column == "brief_title") {
    		while (it != mylist->end()) {
    			string str = it->brief_title;
    			char *txt = &str[0u];
    			string id = it->nct_id;
    			int n = strlen(txt);
    			Run_HORSPOOL(pat, m, txt, n, id, column,bmBc);
    			it++;
    		}
    	} else if (column == "brief_summary") {
    		while (it != mylist->end()) {
    			string str = it->brief_summary;
    			char *txt = &str[0u];
    			string id = it->nct_id;
    			int n = strlen(txt);
    			Run_HORSPOOL(pat, m, txt, n, id, column,bmBc);
    			it++;
    		}
    	} else if (column == "detailed_description") {
    		while (it != mylist->end()) {
    			string str = it->detailed_description;
    			char *txt = &str[0u];
    			string id = it->nct_id;
    			int n = strlen(txt);
    			Run_HORSPOOL(pat, m, txt, n, id, column,bmBc);
				//boyermoore_horspool_memmem( txt, n,pat, m, id, column,bmBc);
    			it++;
    		}
    	} else if (column == "criteria") {
    		while (it != mylist->end()) {
    			string str = it->criteria;
    			char *txt = &str[0u];
    			string id = it->nct_id;
    			int n = strlen(txt);
    			Run_HORSPOOL(pat, m, txt, n, id, column,bmBc);
    			it++;
    		}
    	}

	//Run_HORSPOOL(pat,m,txt,n,id,column);
}



