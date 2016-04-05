/*
 * BM.cpp
 *
 *  Created on: Feb 18, 2016
 *      Author: note
 */
#include "BM.h"
bool Match = false;

BM::BM() {
	// TODO Auto-generated constructor stub

}

BM::~BM() {
	// TODO Auto-generated destructor stub
}
// A utility function to get maximum of two integers
int BM::MAX(int a, int b) {
	return (a > b) ? a : b;
}
void preBmBc(char *x, int m, int bmBc[]) {
	int i;
	for (i = 0; i < NO_OF_CHARS; ++i)
		bmBc[i] = m;
	for (i = 0; i < m - 1; ++i)
		bmBc[x[i]] = m - i - 1;
}

void suffixes(char *x, int m, int *suff) {
	int f, g, i;

	suff[m - 1] = m;
	g = m - 1;
	for (i = m - 2; i >= 0; --i) {
		if (i > g && suff[i + m - 1 - f] < i - g)
			suff[i] = suff[i + m - 1 - f];
		else {
			if (i < g)
				g = i;
			f = i;
			while (g >= 0 && x[g] == x[g + m - 1 - f])
				--g;
			suff[i] = f - g;
		}
	}
}

void preBmGs(char *x, int m, int bmGs[]) {
	int i, j, suff[NO_OF_CHARS];

	suffixes(x, m, suff);

	for (i = 0; i < m; ++i)
		bmGs[i] = m;
	j = 0;
	for (i = m - 1; i >= 0; --i)
		if (suff[i] == i + 1)
			for (; j < m - 1 - i; ++j)
				if (bmGs[j] == m)
					bmGs[j] = m - 1 - i;
	for (i = 0; i <= m - 2; ++i)
		bmGs[m - 1 - suff[i]] = m - 1 - i;
}

void BM::Run_BM(char *pat, int m, char *txt, int n, string id, string column) {
	int i, j, bmGs[NO_OF_CHARS], bmBc[NO_OF_CHARS];

	/* Preprocessing */
	preBmGs(pat, m, bmGs);
	preBmBc(pat, m, bmBc);
	Match = false;
	/* Searching */
	j = 0;
	while (j <= n - m) {
		for (i = m - 1; i >= 0 && pat[i] == txt[i + j]; --i)
			;
		if (i < 0) {
			Match = true;
			cout << "Column name: " << column << " | Pattern ID: " << id
					<< " | Found at: " << j << endl;

			j += bmGs[0];
			break;
		} else
			Match = false;
		j += MAX(bmGs[i], bmBc[txt[i + j]] - m + 1 + i);
	}
	/*if (Match == true) {
		cout << "Text: " << txt << endl;
	}*/

}

// The preprocessing function for Boyer Moore's bad character heuristic
void BM::badCharHeuristic(char *str, int size, int badchar[NO_OF_CHARS]) {
	int i;

	// Initialize all occurrences as -1
	for (i = 0; i < NO_OF_CHARS; i++)
		badchar[i] = -1;

	// Fill the actual value of last occurrence of a character
	for (i = 0; i < size; i++)
		badchar[(int) str[i]] = i;
}

bool BM::getMatch() {
	return Match;
}
/* A pattern searching function that uses Bad Character Heuristic of
 Boyer Moore Algorithm */
void BM::search(std::list<ClinicalTrialRecords> * mylist, char *pat,
		string column) {
	int m = strlen(pat);

	std::list<ClinicalTrialRecords>::iterator it;
	it = mylist->begin();
	if (column == "brief_title") {
		while (it != mylist->end()) {
			string str = it->brief_title;
			char *txt = &str[0u];
			string id = it->nct_id;
			int n = strlen(txt);
			Run_BM(pat, m, txt, n, id, column);
			it++;
		}
	} else if (column == "brief_summary") {
		while (it != mylist->end()) {
			string str = it->brief_summary;
			char *txt = &str[0u];
			string id = it->nct_id;
			int n = strlen(txt);
			Run_BM(pat, m, txt, n, id, column);
			it++;
		}
	} else if (column == "detailed_description") {
		while (it != mylist->end()) {
			string str = it->detailed_description;
			char *txt = &str[0u];
			string id = it->nct_id;
			int n = strlen(txt);
			Run_BM(pat, m, txt, n, id, column);
			it++;
		}
	} else if (column == "criteria") {
		while (it != mylist->end()) {
			string str = it->criteria;
			char *txt = &str[0u];
			string id = it->nct_id;
			int n = strlen(txt);
			Run_BM(pat, m, txt, n, id, column);
			it++;
		}
	}

	//int badchar[NO_OF_CHARS];
	/* thread john(&BM::Run_BM,this, pat,m, txt,n,id,column);
	 john.detach();*/
	/*if (john.joinable())
	 john.join();*/

	/* Fill the bad character array by calling the preprocessing
	 function badCharHeuristic() for given pattern */
	// badCharHeuristic(pat, m, badchar);
	// int s = 0;  // s is shift of the pattern with respect to text
	// while(s <= (n - m))
	//  {
	//     int j = m-1;
	/* Keep reducing index j of pattern while characters of
	 pattern and text are matching at this shift s */
	//     while(j >= 0 && pat[j] == txt[s+j])
	//        j--;
	/* If the pattern is present at current shift, then index j
	 will become -1 after the above loop */
	//    if (j < 0)
	//   {
	//  	Match = true;
	/* Shift the pattern so that the next character in text
	 aligns with the last occurrence of it in pattern.
	 The condition s+m < n is necessary for the case when
	 pattern occurs at the end of text */
	//     s += (s+m < n)? m-badchar[txt[s+m]] : 1;
	//      break;
	//   }
	//   else{
	/* Shift the pattern so that the bad character in text
	 aligns with the last occurrence of it in pattern. The
	 max function is used to make sure that we get a positive
	 shift. We may get a negative shift if the last occurrence
	 of bad character in pattern is on the right side of the
	 current character. */
	//   s += MAX(1, j - badchar[txt[s+j]]);
	//	Match = false;
	//}
	// }
}
void BM::publicFunction() {
	cout << "This class  is for BM " << endl;
}

