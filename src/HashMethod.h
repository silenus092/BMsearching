//
// Created by note on 27/6/2559.
//

#ifndef BMSEARCHING_HASHMETHOD_H
#define BMSEARCHING_HASHMETHOD_H

#include <string.h>
#include <stdio.h>
#include <iostream>
#include "BMsearching.h"

using namespace std;
class HashMethod {
    public:
    static void find_pattern(std::list<ClinicalTrialRecords> * mylist , char *p ,string column);

};
void seach_by_hash(char *p,char *t ,string  id,string column);

#endif //BMSEARCHING_HASHMETHOD_H
