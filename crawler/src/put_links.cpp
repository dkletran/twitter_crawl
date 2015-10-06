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
	  po::options_description desc("Usage: put_links \nAllowed options");
	  string crawling_depth = string("1");

	  string tmp_str;
      string reply_msg1(""), reply_msg2(""), reply_msg3("");
	  desc.add_options()
	    ("help,h", "produce help message")
	  	("crawling-depth,d", po::value<string>(),"crawling depth (default 1)")
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
	  if (vm.count("crawling-depth"))
	  {
		  crawling_depth = vm["crawling-depth"].as<string>();
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
      string event("start_put_links "), description("");
      event +=(string)start_time;
      db.log(event, description);

      string condition = "distance_to_seed<"+crawling_depth+ " AND last_get_links > '0000-00-00 00:00:00'";
      string order_by = "last_put_links";
      istringstream iss1, iss2, iss3;
      string user_id, follower_id;
      string fields = string("distance_to_seed, way_to_seed");
	  for(int k =0; k< 1/* default number of users to treat per command call*/; k++){
      if(!db.getUsersIds(reply_msg1, order_by, condition, 10)){
      		cout<<"could not get users ids from database"<<endl;
      }
      iss1.clear();
      iss1.str(reply_msg1);


      while(iss1>>user_id){
    	  cout<<"putting links of the user "<<user_id<<endl;
    	  tmp_str = "CURRENT_TIMESTAMP";
		  if(!db.updateUser(user_id, order_by , tmp_str)){
			  cout<<"could not update user info"<<endl;
		  }
    	  string distance_to_seed, way_to_seed, distance_to_seed_follower, way_to_seed_follower;
    	  if(!db.getUser(reply_msg2, user_id, fields)){
    		  cout<<"could not retrieve user info"<<endl;
    		  continue;
    	  }
    	  iss2.clear();
    	  iss2.str(reply_msg2);
    	  iss2>>distance_to_seed;
    	  iss2>>way_to_seed;
    	  if(!db.getUserFollowers(reply_msg2,  user_id)){
    		  cout<<"could not retrieve user followers info"<<endl;
    		  continue;
    	  }

    	  if(!reply_msg2.compare("")){
    		  continue;
    	  }
    	  iss2.clear();
    	  iss2.str(reply_msg2);
    	  while(iss2>>follower_id){
        	  if(!db.getUser(reply_msg3, follower_id, fields)){
        		  cout<<"could not retrieve user info"<<endl;
        		  continue;
        	  }
        	  if(!reply_msg3.compare("")){
        		  //The follower was not added to the table "users"
        		  cout<<"Inserting the new user "<<follower_id<<endl;
        		  distance_to_seed_follower = boost::lexical_cast<string>(atoi(distance_to_seed.c_str())+1);
        		  way_to_seed_follower = "'"+follower_id+"-"+way_to_seed+"'";
            	  if(!db.addUser(follower_id, distance_to_seed_follower, way_to_seed_follower)){
            		  cout<<"could not add user (follower) "<<follower_id<<endl;
            		  continue;
            	  }
        	  }
        	  else{
        		  //The follower was added
        		  cout<<"The user "<<follower_id<< " was added."<<endl;

        		  iss3.clear();
        		  iss3.str(reply_msg3);
        		  iss3>>distance_to_seed_follower;
        		  iss3>>way_to_seed_follower;
        		  if(atoi(distance_to_seed_follower.c_str())>(atoi(distance_to_seed.c_str())+1)){
        			  //update distance to seed
            		  distance_to_seed_follower = boost::lexical_cast<string>(atoi(distance_to_seed.c_str())+1);
            		  way_to_seed_follower = "'"+follower_id+"-"+way_to_seed+"'";
            		  tmp_str =distance_to_seed_follower+", "+way_to_seed_follower;
            		  if(!db.updateUser(follower_id, fields, tmp_str)){
            			  cout<<"could not update user info"<<endl;

            		  }
        		  }
        	  }
    	  }
    	  tmp_str = "CURRENT_TIMESTAMP";
		  if(!db.updateUser(user_id, order_by , tmp_str)){
			  cout<<"could not update user info"<<endl;
			  continue;
		  }
		  cout<<"added links of the user "<<user_id<<endl;

      }
      }
    event = "finish_put_links_started_at "+(string)start_time;
    db.log(event, description);
    db.disconnect();
  	cout<<"disconnected from database"<<endl;

	return 0;
}


