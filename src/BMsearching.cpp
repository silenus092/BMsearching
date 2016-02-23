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
string  name;
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
	     cout << res->getString("name") <<" : "<< res->getString("symbol") << endl;
		   gene_struct[i].name   = res->getString("name") ;
	      gene_struct[i].symbols = " "+res->getString("symbol")+ " " ;
	     i++;
	   }
	       stmt = con->createStatement();
	  	   res = stmt->executeQuery("SELECT  brief_title from  clinical_study");
	  	   int j = 0 ;
	  	 const clock_t begin_time = clock();
	  	 while (res->next()) {
	  		string temp_name = res->getString("brief_title");
	  		//printf("From Clinical Study: %s \n",temp_name.c_str());
	  		int temp_size = 0;
	  	    temp_size =  temp_name.size();
	  		char txt[temp_size];
	  		char pat[10];
	  		strcpy(txt,temp_name.c_str());
	  		cout << "From Clinical Study:"<< txt << endl;
	  	   for(j = 0 ; j < NO_OF_GENE ; j++){
	  			    //printf("From Clinical Study: %s \n",temp_name.c_str());
	  			    //cout << "Gene Name:"<< gene_struct[j].symbols.c_str() << endl;
	  			  strcpy(pat, gene_struct[j].symbols.c_str());
	  			  bm.search(txt, pat);

	  	   }

	  	 }
	  	cout <<"Usage Time (second): "<< float( clock () - begin_time ) /  CLOCKS_PER_SEC;

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


	  return 0;
}



