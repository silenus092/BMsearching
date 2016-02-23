//============================================================================
// Name        : BMsearching.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <limits.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include "BM.h"
using namespace std;
using namespace sql::mysql;

int NO_OF_GENE = 40962;
BM bm ;
struct Gene {
  string name;
  string symbols;
} gene_struct[40962];

int main() {
	cout << endl;
	cout << "Running SELECT AS _message..." << endl;

	try{
	  sql::Driver *driver;
	  sql::Connection *con;
	  sql::Statement *stmt;
	  sql::ResultSet *res;

	  /* Create a connection */
	  driver = get_driver_instance();
	  con = driver->connect("tcp://127.0.0.1:3306", "root", "password");

	   /* Connect to the MySQL clintrialsgov_out database */
	   con->setSchema("clintrialsgov_out");

	   stmt = con->createStatement();
	   res = stmt->executeQuery("SELECT  * from  hgnc_complete_set");
	   int i = 0 ;
	   while (res->next()) {
	    // cout << "\t... MySQL replies: ";
	     //cout << res->getString("hgnc_id") << endl;
	     gene_struct[i].name = res->getString("name") ;
	     gene_struct[i].symbols = res->getString("symbol") ;
	     i++;
	   }
	       stmt = con->createStatement();
	  	   res = stmt->executeQuery("SELECT  brief_title from  clinical_trial");
	  	   int j = 0 ;
	  	 while (res->next()) {
	  	   for(j = 0 ; j < NO_OF_GENE ; j++){
	  	    // cout << "\t... MySQL replies: ";
	  	     //cout << res->getString("hgnc_id") << endl;
	  		   	   	string temp_name = res->getString("brief_title");
	  	            char txt[8000] =  temp_name.c_str();
	  			    char pat[8000] =  gene_struct[j].name;
	  			    bm.search(txt, pat);
	  	   }
	  	 }


	   delete res;
	   delete stmt;
	   delete con;
	}catch (sql::SQLException &e){
		  cout << "# ERR: SQLException in " << __FILE__;
		  cout << "(" << __FUNCTION__ << ") on line  << __LINE__ "<< endl;
		  cout << "# ERR: " << e.what();
		  cout << " (MySQL error code: " << e.getErrorCode();
		  cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}
		cout << "gene_struct :"<<  gene_struct[0].symbols << endl;

	  return 0;
}



