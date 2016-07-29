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

#include "BMsearching.h"
#include "BM.h"
#include "Horspool.h"
#include "HashMethod.h"
#include "ctpl.h"
#include "ThreadPool.h"
#include <sstream>


using ns = chrono::milliseconds;
using get_time = chrono::steady_clock;
std::vector<std::string> stopword_list;
list <ClinicalTrialRecords> Cli_Record_list;
list <Gene> gene_struct;



BM bm;
Horspool horspool;

int NO_OF_GENE = 40962;
sql::Driver *driver;
sql::Connection *con;
sql::Statement *stmt;
sql::ResultSet *res;
int number_results;
typedef boost::unordered_map<std::string,std::vector<string>> unordered_map;
  unordered_map invert_map , invert_map_BMH;
// You could also take an existing vector as a parameter.
vector<string> split(string str, char delimiter) {
    vector<string> internal;

    stringstream ss(str); // Turn the string into a stream.
    string tok;

    while (getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }

    return internal;
}

void load_stop_word() {
    ifstream file;
    string line;
    file.open("/home/note/Desktop/Thesis/mysqlstopword.sorted.txt");
    while (getline(file, line))
        stopword_list.push_back(line);

    cout << "Size of stop word: " << stopword_list.size() << endl;
}


string Remove_Stop_word(string line) {
   // cout << "Text: " << line << endl;
    char *txt =  &line[0];
    string new_sentences;
    char * pch = strtok (txt," ,.()null");
    while (pch != NULL) {
        int flag= 0;
        /*for (int i = 0; i < stopword_list.size(); i++) {
            if (boost::iequals(pch ,stopword_list[i])) {
                flag = 1;
                break;
            }
        }*/
        if( std::find(stopword_list.begin(), stopword_list.end(), pch) != stopword_list.end() != std::string::npos){
            new_sentences.append(pch);
        }
        /*if(flag !=1){
            new_sentences.append(pch);
        }*/

        pch = strtok(NULL, " ,.():;\n");
    }
    new_sentences.erase(remove_if(new_sentences.begin(), new_sentences.end(), [](char c) { return !isalnum(c); } ), new_sentences.end());
    //cout << "After removed: " << new_sentences << endl;
    return new_sentences;
   /* for (int i = 0; i < stopword_list.size(); i++) {
        memcpy(chars, stopword_list.at(i).c_str(), stopword_list.at(i).size());
        for (unsigned int i = 0; i < strlen(chars); ++i) {
            str.erase(remove(str.begin(), str.end(), chars[i]), str.end());
        }
    }*/

}

/*string remove_non_alphanumeric(string line){
    return line.erase(remove_if(line.begin(), line.end(),
                        [](char c) {
                            return !isalnum(c);
                        } ), line.end());
}*/

void Create_A_Connection() {
    /* Create a connection */
    driver = get_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "password");

}

void Connect_To_clintrialsgov_out_database() {
    con->setSchema("clintrialsgov_out");
    stmt = con->createStatement();
}

void Construct_Gene_Array() {
    res = stmt->executeQuery("SELECT  * from  hgnc_complete_set");
    int i = 0;
    Gene names;
    while (res->next()) {
        // cout << "\t... MySQL replies: ";
        //cout << res->getString("name") <<" : "<< res->getString("symbol") << endl;
        names.name = res->getString("name");
        if (res->getString("symbol").compare("T") == 0)
            names.symbols = " " + res->getString("symbol") + " ";
        else
            names.symbols = res->getString("symbol");
        i++;
        gene_struct.push_back(names);
    }
    cout << "gene lsit size:" << gene_struct.size()<<endl;

}

void Fetch_All_Clinical_Records() {
    stmt = con->createStatement();
    res = stmt->executeQuery(
            "SELECT  nct_id,brief_title ,brief_summary,detailed_description, criteria from  clinical_study");
}

void Construct_Records() {
    number_results = res->rowsCount();
    ClinicalTrialRecords names;

    while (res->next()) {

        names.nct_id = res->getString("nct_id");
        names.brief_title = Remove_Stop_word(res->getString("brief_title"));
        names.brief_summary = Remove_Stop_word(res->getString("brief_summary"));
        names.detailed_description = Remove_Stop_word(res->getString("detailed_description"));
        names.criteria = Remove_Stop_word(res->getString("criteria"));
        Cli_Record_list.push_back(names);

    }
    printf("Size of Clinical Study records: %d \n", Cli_Record_list.size());
}

int main() {

    cout << "Number of threads = " << thread::hardware_concurrency() << endl;
    //ctpl::thread_pool thread_pool (thread::hardware_concurrency());
    ThreadPool thread_pool(thread::hardware_concurrency());
    try {
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
        cout << "-------*------- Load data : CPU Usage Time (second): " <<
        float(clock() - constructe_begin_time) / CLOCKS_PER_SEC << endl;
        cout << "Load data Elapsed time is :  " << chrono::duration_cast<ns>(diff).count() / 1000 << " s " << endl;

        char pat[5];
        strcpy(pat, "CIN1");
        //strcpy(pat, "FOXP3");
        const clock_t begin_time = clock();
       /*thread john( HashMethod::find_pattern, &Cli_Record_list, pat, "brief_title");
        thread sam( HashMethod::find_pattern, &Cli_Record_list, pat ,"brief_summary");
        thread jane( HashMethod::find_pattern, &Cli_Record_list, pat ,"detailed_description");
        thread ploy( HashMethod::find_pattern, &Cli_Record_list, pat ,"criteria");

        //thread_pool.waitFinished();
         john.join();
         cout <<"--- john back ---   "  << endl;
          sam.join();
         cout <<"--- sam back ---  "  << endl;
         jane.join();
         cout <<"--- jane back ---   "  << endl;
         ploy.join();
         cout <<"--- ploy back ---   "  << endl;*/
         cout << "-------*-------HASH Usage Time (second): " << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;
        const clock_t begin_time1 = clock();


        //thread_pool.enqueue(&BM::search,&bm,&Cli_Record_list, pat ,"brief_title");
        //thread_pool.enqueue(&BM::search,&bm,&Cli_Record_list, pat ,"brief_summary");
        // thread_pool.enqueue(&BM::search,&bm,&Cli_Record_list, pat ,"detailed_description");
        //thread_pool.enqueue(&BM::search,&bm,&Cli_Record_list, pat ,"criteria");

         thread john(&BM::search,&bm,&Cli_Record_list, &gene_struct ,"brief_title",&invert_map);
         thread sam(&BM::search,&bm,&Cli_Record_list, &gene_struct ,"brief_summary",&invert_map);
         thread jane(&BM::search,&bm,&Cli_Record_list, &gene_struct ,"detailed_description",&invert_map);
         thread ploy(&BM::search,&bm,&Cli_Record_list, &gene_struct ,"criteria",&invert_map);

         john.join();
        // cout <<"--- john1 back : <<  "  << endl;
         sam.join();
        // cout <<"--- sam1 back : <<  "  << endl;
         jane.join();
        // cout <<"--- jane1 back : <<  "  << endl;
         ploy.join();
        // cout <<"--- ploy1 back : <<  "  << endl;


        cout << "-------*------- BM Usage Time (second): " << float(clock() - begin_time1) / CLOCKS_PER_SEC << endl;

        for (const auto &p : invert_map){
            std::cout << p.first << ";"  ;
            for( const auto& text : invert_map[ p.first] ){
                cout << text << " , ";
            }
            cout  << '\n';
        }

        const clock_t begin_time_2 = clock();
        try {
            thread john1(&Horspool::search_HP, &horspool, &Cli_Record_list, &gene_struct ,  "brief_title" ,&invert_map_BMH);
            thread sam1(&Horspool::search_HP, &horspool, &Cli_Record_list, &gene_struct ,   "brief_summary",&invert_map_BMH);
            thread jane2(&Horspool::search_HP, &horspool, &Cli_Record_list, &gene_struct ,  "detailed _description",&invert_map_BMH);
            thread ploy1(&Horspool::search_HP, &horspool, &Cli_Record_list, &gene_struct ,"criteria",&invert_map_BMH);

            john1.join();
            cout << "--- john1 back : <<  " << endl;
            sam1.join();
            cout << "--- sam1 back : <<  " << endl;
            jane2.join();
            cout << "--- jane1 back : <<  " << endl;
            ploy1.join();
            cout << "--- ploy1 back : <<  " << endl;

        } catch (exception &e) {
            cout << "Standard exception: " << e.what() << endl;
        }


        cout << "-------*------- BMH Usage Time (second): " << float(clock() - begin_time_2) / CLOCKS_PER_SEC<< endl;
        for (const auto &p : invert_map_BMH){
            std::cout << p.first << ";"  ;
            for( const auto& text : invert_map_BMH[ p.first] ){
                cout << text << " , ";
            }
            cout  << '\n';
        }

        cout << "-------*------- Searching : -------*------- " << endl;
        const clock_t begin_time_3 = clock();
        std::cout << "Found: " <<std::boolalpha << (invert_map.find("REN") != invert_map.end()) << '\n';
        cout << "-------*------- Searching Time (second):  " << float(clock() - begin_time_3) / CLOCKS_PER_SEC <<endl;
        delete res;
        delete stmt;
        delete con;
    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line  << __LINE__ " << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
    return 0;
}



