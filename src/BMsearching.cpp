//============================================================================
// Name        : BMsearching.cpp

// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
/*
 * This program compare with sql command below
 * USE clintrialsgov_out;
SELECT c.nct_id , c.brief_summary
FROM clinical_study c
WHERE MATCH (brief_title ,
brief_summary,detailed_description, criteria) AGAINST ("CIN1");

*/
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
	     //cout << res->getString("name") <<" : "<< res->getString("symbol") << endl;
		   gene_struct[i].name   = res->getString("name") ;
		   if(res->getString("symbol").compare("T") == 0)
			   gene_struct[i].symbols = " "+res->getString("symbol")+" " ;
		   else
			   gene_struct[i].symbols = res->getString("symbol") ;
	     i++;
	   }
	   cout << "Construct Genes complete" << endl;
	       stmt = con->createStatement();
	  	   res = stmt->executeQuery("SELECT  nct_id,brief_title ,brief_summary,detailed_description, criteria from  clinical_study");
	  	 //printf("Size Clinical Study: %s \n",res->rowsCount());
	  	   int j = 0 ;
	  	 const clock_t begin_time = clock();
	  	 while (res->next()) {
	  		string id = res->getString("nct_id");
	  		string temp_name = res->getString("brief_title");
	  		//string temp_brief_summary = res->getString("brief_summary");
	  		//string temp_detailed_description = res->getString("detailed_description");
	  		//string temp_criteria= res->getString("criteria");
	  		//printf("From Clinical Study: %s \n",temp_name.c_str());
	  		int temp_size = 0;
	  	    temp_size =  temp_name.size();
	  		char txt[temp_size];
	  		char pat[10];
	  		strcpy(txt,temp_name.c_str());
	  		strcpy(pat, "CIN1");
	  		/**/

	  		  bm.search(txt, pat ,id);
	  		  if(!bm.getMatch()){
	  		  string temp_brief_summary_name = res->getString("brief_summary");
	  		  int temp_brief_summary = 0;
	  		  	    temp_brief_summary =  temp_brief_summary_name.size();
	  		  		char txt_brief_summary[temp_brief_summary];
	  		  		strcpy(txt_brief_summary,temp_brief_summary_name.c_str());
	  		  		bm.search(txt_brief_summary, pat ,id);
	  		  }
	  		  if(!bm.getMatch()){
	  			 string temp_detailed_description_name = res->getString("detailed_description");
	  				  		  		int temp_detailed_description = 0;
	  				  		  		temp_detailed_description =  temp_detailed_description_name.size();
	  				  		  		char txt_detailed_description[temp_detailed_description];
	  				  		  		strcpy(txt_detailed_description,temp_detailed_description_name.c_str());
	  				  		  		bm.search(txt_detailed_description, pat ,id);
	  		  }
	  		  if(!bm.getMatch() ){
	  			  			 string temp_detailed_description_name = res->getString("detailed_description");
	  			  				  		  		int temp_detailed_description = 0;
	  			  				  		  		temp_detailed_description =  temp_detailed_description_name.size();
	  			  				  		  		char txt_detailed_description[temp_detailed_description];
	  			  				  		  		strcpy(txt_detailed_description,temp_detailed_description_name.c_str());
	  			  				  		  		bm.search(txt_detailed_description, pat ,id);
	  		 }
	  		  if(!bm.getMatch()){
	  		  	string temp_criteria_name = res->getString("criteria");
	  			int temp_criteria = 0;
	  			  		  		temp_criteria =  temp_criteria_name.size();
	  			  		  		char txt_criteria[temp_criteria];
	  			  		  		strcpy(txt_criteria,temp_criteria_name.c_str());
	  			  		  		bm.search(txt_criteria, pat ,id);
	  		  }
	  	   /*for(j = 0 ; j < NO_OF_GENE ; j++){
	  			    //printf("From Clinical Study: %s \n",temp_name.c_str());
	  			    //cout << "Gene Name:"<< gene_struct[j].symbols.c_str() << endl;
	  			  strcpy(pat, gene_struct[j].symbols.c_str());
	  			  bm.search(txt, pat);
	  	   }*/

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



