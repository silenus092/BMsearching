#ifndef BMsearching_H
#define BMsearching_H
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
using namespace std;
using namespace sql::mysql;

int NO_OF_GENE = 40962;
sql::Driver *driver;
sql::Connection *con;
sql::Statement *stmt;
sql::ResultSet *res;
int number_results;

// Global Variables
	struct Gene {
	  string  name;
	  string symbols;
	} gene_struct[40962];




#endif
