#ifndef BMsearching_H
#define BMsearching_H
#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <thread>
#include <list>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <boost/unordered_map.hpp>
using namespace std;
using namespace sql::mysql;



// Global Variables

	struct ClinicalTrialRecords {
			string nct_id;
			string brief_title;
			string brief_summary;
			string detailed_description;
			string criteria;
		};




#endif
