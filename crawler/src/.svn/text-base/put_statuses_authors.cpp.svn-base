/*
 * put_links.cpp
 *
 *  Created on: 26 juin 2012
 *      Author: ktvr5725
 */



#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <cstdio>
#include <iostream>
#include <fstream>
#include "database.h"

namespace po = boost::program_options;
using namespace boost::algorithm;
//using namespace boost::lambda;
using namespace std;
using namespace po;

int main(int argc, char* argv[]) {
	  // Declare the supported options.
	  po::options_description desc("Usage: put_statuses_authors \nAllowed options");
	  int count_per_request = 1000;
	  string tmp_str;
      string reply_msg("");
	  desc.add_options()
	    ("help,h", "produce help message")
	  	("count-per-request, c", po::value<string>(),"number of tweets to process per command call")
	  	;
	  po::variables_map vm;
	  po::store(po::parse_command_line(argc, argv, desc), vm);
	  po::notify(vm);
	//cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	  if (vm.count("help"))
	    {
	      cout << desc << "\n";
	      return 1;
	    }
	  if (vm.count("count-per-request"))
	  {
		  count_per_request = atoi(vm["crawling-depth"].as<string>().c_str());
		  if(count_per_request < 0) { count_per_request = 1;}
		  if(count_per_request > 1000) {count_per_request = 1000;}
	  }

      Database db;
      if (db.connect()){
      	cout<<"connected to database"<<endl;
      }else
      {
      	cout<<"could not connect to database"<<endl;
      	return -1;
      }
//log events in database
      time_t rawtime;
      struct tm * timeinfo;
      char  start_time[100];
      time ( &rawtime );
      timeinfo = localtime ( &rawtime );
      strftime (start_time,80,"%c",timeinfo);
      string event("start_put_tweets_authors "), description("");
      event +=(string)start_time;
      db.log(event, description);

      string user_id;
      string fields = string("distance_to_seed, way_to_seed"), distance_to_seed, way_to_seed;
	  for(int k =0; k< count_per_request; k++){
		  if(!db.getFromUserIdStatusesFound(user_id)){
			  cout<<"could not get users ids from database"<<endl;
		  }
		  if(!user_id.compare(""))
		  {
			  break;
		  }



		  if(!db.getUser(reply_msg, user_id, fields)){
        		  cout<<"could not retrieve user info"<<endl;
        		  break;
		  }
		  if(!reply_msg.compare("")){
        		  //The user was not added to the table "users"
			  	  cout<<"Inserting the new user "<<user_id<<endl;
        		  distance_to_seed = boost::lexical_cast<string>(99);
        		  way_to_seed = "'"+user_id+" created relevant status(es)"+"'";
            	  if(!db.addUser(user_id, distance_to_seed, way_to_seed)){
            		  cout<<"could not add user (follower) "<<user_id<<endl;
            		  break;
            	  }
        	  }
        	  else{
        		  //The follower was added
        		  cout<<"The user "<<user_id<< " was added."<<endl;
    	  }



      }
    event = "finish_put_tweets_authors_started_at "+(string)start_time;
    db.log(event, description);
    db.disconnect();
  	cout<<"disconnected from database"<<endl;

	return 0;
}


