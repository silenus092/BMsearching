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

#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include "BMsearching.h"
#include "BM.h"
#include "Horspool.h"
#include "HashMethod.h"

using  ns = chrono::milliseconds;
using get_time = chrono::steady_clock ;
std::vector<std::string> stopword_list;
list<ClinicalTrialRecords> Cli_Record_list;
struct Gene {
  string  name;
  string symbols;
} gene_struct[40962];

BM bm ;
Horspool horspool;

int NO_OF_GENE = 40962;
sql::Driver *driver;
sql::Connection *con;
sql::Statement *stmt;
sql::ResultSet *res;
int number_results;

void load_stop_word(){
    ifstream file;
    string line;
    file.open("/home/note/Desktop/Thesis/union_stopword.formated.txt");
    while (getline (file, line))
    	stopword_list.push_back(line);

    cout << "Size of stop word: " << stopword_list.size()<< endl;
}
string Remove_Stop_word(string word){
	cout << "word "<< word << endl;
	 char chars[10] ;
	 string str = word;
	/*for(int  i = 0  ;i < stopword_list.size() ; i++){
		memcpy(chars,stopword_list.at(i).c_str(),stopword_list.at(i).size());
		for ( unsigned int i = 0; i < strlen(chars); ++i ) {
			str.erase( remove(str.begin(), str.end(), chars[i]), str.end() );
	    }
	}*/
		cout << "Str "<< str << endl;
	//return word;
}

void removeSubstrs(string text ) {

	std::string t = text;

	for(int y = 0 ;  y < stopword_list.size()  ; y++){
		std::string s = stopword_list.at(y);
		std::string::size_type i = t.find(s);
			   for (int i = t.find(s);i != std::string::npos; i = t.find(s))
			   t.erase(i, s.length());
	}

	cout << t << '\n';
}


void Create_A_Connection()
{
	/* Create a connection */
	 driver = get_driver_instance();
	 con = driver->connect("tcp://127.0.0.1:3306", "root", "password");

}

void Connect_To_clintrialsgov_out_database(){
	con->setSchema("clintrialsgov_out");
	stmt = con->createStatement();
}

void Construct_Gene_Array(){
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
}
void Fetch_All_Clinical_Records(){
	  stmt = con->createStatement();
	  res = stmt->executeQuery("SELECT  nct_id,brief_title ,brief_summary,detailed_description, criteria from  clinical_study");
}
void Construct_Records(){
	  number_results = res->rowsCount();
	  ClinicalTrialRecords names;

		 while (res->next()) {
			 names.nct_id = res->getString("nct_id");

			 names.brief_title = res->getString("brief_title");
			 //removeSubstrs(res->getString("brief_title"));
			 names.brief_summary = res->getString("brief_summary");
			 names.detailed_description = res->getString("detailed_description");
			 names.criteria= res->getString("criteria");
			 Cli_Record_list.push_back(names);
		 }
		 printf("Size of Clinical Study records: %d \n",Cli_Record_list.size());
}

int main() {

	int badchar[NO_OF_CHARS];
	 cout << "Number of threads = " <<  thread::hardware_concurrency() << endl;
	try{
	    cout << "load stop word" << endl;
	    load_stop_word();

	     cout << "Create_A_Connection" << endl;
	     Create_A_Connection();
	     cout << "Connect to the MySQL clintrialsgov_out database" << endl;
	    Connect_To_clintrialsgov_out_database();
	     cout << "Construct Genes" << endl;
	     Construct_Gene_Array();
	     cout << "Fetch All Clinical Records" << endl;
	     const clock_t constructe_begin_time = clock();
	    auto start = get_time::now();
	 Fetch_All_Clinical_Records();
	 Construct_Records();
	 auto end = get_time::now();
	 auto diff = end - start;
	 cout <<"-------*------- Load data : CPU Usage Time (second): "<< float( clock () - constructe_begin_time ) /  CLOCKS_PER_SEC <<  endl;
	 cout<<"Load data Elapsed time is :  "<< chrono::duration_cast<ns>(diff).count()/1000<<" s "<<endl;
	 char pat[5];
	 strcpy(pat, "CIN1");
        // strcpy(pat, "BCL5");
     const clock_t begin_time = clock();
        thread john( HashMethod::find_pattern,&Cli_Record_list, pat ,"brief_title");
       // thread sam( HashMethod::find_pattern,&Cli_Record_list, pat ,"brief_summary");
        //thread jane( HashMethod::find_pattern,&Cli_Record_list, pat ,"detailed_description");
       // thread ploy( HashMethod::find_pattern,&Cli_Record_list, pat ,"criteria");

            john.join();
            cout <<"--- john back : <<  "<< endl;


           sam.join();
            cout <<"--- sam back : <<  "  << endl;

           // jane.join();
            cout <<"--- jane back : <<  "  << endl;


           // ploy.join();
            cout <<"--- ploy back : <<  "  << endl;

     cout <<"-------*-------HASH Usage Time (second): "<< float( clock () - begin_time ) /  CLOCKS_PER_SEC <<  endl;
	 //const clock_t begin_time = clock();


        /*thread john(&BM::search,&bm,&Cli_Record_list, pat ,"brief_title");
	  		thread sam(&BM::search,&bm,&Cli_Record_list, pat ,"brief_summary");
	  		thread jane(&BM::search,&bm,&Cli_Record_list, pat ,"detailed_description");
	  		thread ploy(&BM::search,&bm,&Cli_Record_list, pat ,"criteria");

	  		if (john.joinable()){
	  		    john.join();
	  		cout <<"--- john back : <<  "  << endl;
	  		}
	  		if (sam.joinable()){
	  			sam.join();
	  		cout <<"--- sam back : <<  "  << endl;
	  		}
	  		if (jane.joinable()){
	  			jane.join();
	  		cout <<"--- jane back : <<  "  << endl;
	  		}
	  		if (ploy.joinable()){
	  			ploy.join();
	  		cout <<"--- ploy back : <<  "  << endl;
	  		}
	   cout <<"-------*------- BM Usage Time (second): "<< float( clock () - begin_time ) /  CLOCKS_PER_SEC <<  endl;
*/
	/*   const clock_t begin_time_1 = clock();
	   try
	    {
		  		thread john1(&Horspool::search_HP,&horspool,&Cli_Record_list, pat ,"brief_title");
		  		thread sam1(&Horspool::search_HP,&horspool,&Cli_Record_list, pat ,"brief_summary");
		  		thread jane1(&Horspool::search_HP,&horspool,&Cli_Record_list, pat ,"detailed_description");
		  		thread ploy1(&Horspool::search_HP,&horspool,&Cli_Record_list, pat ,"criteria");

		  		if (john1.joinable()){
		  			john1.join();
		  		cout <<"--- john1 back : <<  "  << endl;
		  		}

		  		if (sam1.joinable()){
		  			sam1.join();
		  		  cout <<"--- sam1 back : <<  "  << endl;
		  		}


		  			jane1.join();
		  			cout <<"--- jane1 back : <<  "  << endl;
		  			ploy1.join();
		  			cout <<"--- ploy1 back : <<  "  << endl;

	    }catch (exception& e)
	    {
	      cout << "Standard exception: " << e.what() << endl;
	    }

	   cout <<"-------*------- BMH Usage Time (second): "<< float( clock () - begin_time_1 ) /  CLOCKS_PER_SEC;*/
	   /*int x = 0;
	   const clock_t begin_time_horspool = clock();
		  	 while (res->next() && x < 1500) {
		  		string id = res->getString("nct_id");
		  		string temp_name = res->getString("brief_title");
		  		//string temp_brief_summary = res->getString("brief_summary");
		  		//string temp_detailed_description = res->getString("detailed_description");
		  		//string temp_criteria= res->getString("criteria");
		  		printf("%d From Clinical Study: %s \n",x++,temp_name.c_str() );
		  		int temp_size = 0;
		  	    temp_size =  temp_name.size();
		  		char txt[temp_size];
		  		char pat[5];
		  		strcpy(txt,temp_name.c_str());
		  		strcpy(pat, "CIN1");
		  	     int m = strlen(pat);
		  	    horspool.HORSPOOL_preBmBc(pat ,m);
		  		horspool.search(txt, pat ,id ,"brief_title");
		  		 /* if(!horspool.getMatch()){
		  		  string temp_brief_summary_name = res->getString("brief_summary");
		  		  int temp_brief_summary = 0;
		  		  	    temp_brief_summary =  temp_brief_summary_name.size();
		  		  		char txt_brief_summary[temp_brief_summary];
		  		  		strcpy(txt_brief_summary,temp_brief_summary_name.c_str());
		  		  	horspool.search(txt_brief_summary, pat ,id,"brief_summary");
		  		  }
		  		  if(!horspool.getMatch()){
		  			 string temp_detailed_description_name = res->getString("detailed_description");
		  				  		  		int temp_detailed_description = 0;
		  				  		  		temp_detailed_description =  temp_detailed_description_name.size();
		  				  		  		char txt_detailed_description[temp_detailed_description];
		  				  		  		strcpy(txt_detailed_description,temp_detailed_description_name.c_str());
		  				  		  	horspool.search(txt_detailed_description, pat ,id,"detailed_description");
		  		  }
		  		  if(!horspool.getMatch() ){
		  			  			 string temp_detailed_description_name = res->getString("detailed_description");
		  			  				  		  		int temp_detailed_description = 0;
		  			  				  		  		temp_detailed_description =  temp_detailed_description_name.size();
		  			  				  		  		char txt_detailed_description[temp_detailed_description];
		  			  				  		  		strcpy(txt_detailed_description,temp_detailed_description_name.c_str());
		  			  				  		  horspool.search(txt_detailed_description, pat ,id,"detailed_description");
		  		 }
		  		  if(!horspool.getMatch()){
		  		  	string temp_criteria_name = res->getString("criteria");
		  			int temp_criteria = 0;
		  			  		  		temp_criteria =  temp_criteria_name.size();
		  			  		  		char txt_criteria[temp_criteria];
		  			  		  		strcpy(txt_criteria,temp_criteria_name.c_str());
		  			  		  	horspool.search(txt_criteria, pat ,id,"criteria");
		  		  }*/
		  	// }
		  // cout <<"-------*------- BM-Horspool Usage Time (second): "<< float( clock () - begin_time_horspool ) /  CLOCKS_PER_SEC;


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



