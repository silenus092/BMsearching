//
// Created by note on 27/6/2559.
//

#include "HashMethod.h"

void seach_by_hash(char *p,char *t );

void HashMethod::find_pattern(std::list<ClinicalTrialRecords> * mylist , char *pat , string column){
    std::list<ClinicalTrialRecords>::iterator it;
    it = mylist->begin();
    if (column == "brief_title") {
        while (it != mylist->end()) {
            string str = it->brief_title;
            char *txt = &str[0u];
            string id = it->nct_id;
            int n = strlen(txt);
            seach_by_hash(pat, txt, id,column);
            it++;
        }
    } else if (column == "brief_summary") {
        while (it != mylist->end()) {
            string str = it->brief_summary;
            char *txt = &str[0u];
            string id = it->nct_id;
            int n = strlen(txt);
            seach_by_hash(pat, txt, id,column);
            it++;
        }
    } else if (column == "detailed_description") {
        while (it != mylist->end()) {
            string str = it->detailed_description;
            char *txt = &str[0u];
            string id = it->nct_id;
            int n = strlen(txt);
            seach_by_hash(pat,  txt, id,column);
            it++;
        }
    } else if (column == "criteria") {
        while (it != mylist->end()) {
            string str = it->criteria;
            char *txt = &str[0u];
            string id = it->nct_id;
            int n = strlen(txt);
            seach_by_hash(pat, txt , id,column);
            it++;
        }
    }
}

void seach_by_hash(char *p,char *t ,string  id , string column){
    char * pch = strtok (t," ,.-()");
    std::hash<std::string> str_hash;
    while (pch != NULL)
    {
        //printf ("%s\n",pch);
        if(str_hash(pch) == str_hash(p) ){
            cout << column<< " : "<< id << " : Founded " << endl;

        }
        pch = strtok (NULL, " ,.-");
    }
}