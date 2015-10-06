/*
 * get_status_profiles.cpp
 *	Get at put users profiles and status.
 *  Created on: 29 juin 2012
 *      Author: ktvr5725
 */
#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>

#include <cstdio>
#include <iostream>
#include <fstream>
#include <json/json.h>
#include "database.h"
#include "jsoncrawler.h"

using namespace std;
namespace po = boost::program_options;
using namespace boost::algorithm;
int main(int argc, char* argv[]) {
	  // Declare the supported options.
	  po::options_description desc("Usage: get_links \nAllowed options");
	  JsonCrawler twitterObj;
	  string tmp_str;
    char tmp_buf[1024];
	  string crawling_depth = string("2");
    string tokenFile("twitterClient_token_key.txt");
    string tokenSecret("twitterClient_token_secret.txt");
    string reply_msg(""),reply_msg1(""),reply_msg2("");
    int crawl_max_retry = 3;
    int users_count = 3000;
	  desc.add_options()
	    ("help,h", "produce help message")
	  	("username,u", po::value<string>(),"twitter username (required)")
	  	("password,p", po::value<string>(),"password (required)")
	  	("consumer-key,k", po::value<string>(), "twitter application consumer key (required)")
	  	("consumer-secret,s", po::value<string>(),"twitter application consumer secret key (required)")
	  	("token-key,t", po::value<string>(),"twitter application token key file (default: twitterClient_token_key.txt)")
	  	("token-secret,x", po::value<string>(),"twitter application token secret key file (default: twitterClient_token_secret.txt)")
	  	("proxy-host,h", po::value<string>(),"proxy host address")
	  	("proxy-port,i", po::value<string>(),"proxy port address")
	  	("crawling-depth,d", po::value<string>(),"crawling depth (default 2)")
	  	("users-count,c", po::value<string>(),"number of users to crawl link (default 3000)")
	  	("crawl-max-retry,r", po::value<string>(),"maximum number of retry (between 1 and 10, default 3)")
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
	  if (vm.count("proxy-host")&&vm.count("proxy-port"))
	  {
		  tmp_str = vm["proxy-host"].as<string>();
		  twitterObj.setProxyServerIp(tmp_str);
		  tmp_str = vm["proxy-port"].as<string>();
		  twitterObj.setProxyServerPort(tmp_str);
	  }
	  if (vm.count("username"))
	  {
	  	  tmp_str = vm["username"].as<string>();
	  	  twitterObj.setTwitterUsername(tmp_str);
	  }
	  else
	  {
	  	  cout<<"Username required"<<endl;
	  	  return 1;
	  }

	  if (vm.count("password"))
	  {
		  tmp_str = vm["password"].as<string>();
	  	  twitterObj.setTwitterPassword(tmp_str);
	  }
	  else
	  {
	  	  cout<<"Password required"<<endl;
	  	  return 1;
	  }

	  if (vm.count("consumer-key"))
	  {
		  tmp_str = vm["consumer-key"].as<string>();
		  twitterObj.getOAuth().setConsumerKey(tmp_str);
	  }
	  else
	  {
		  cout<<"Consumer key required"<<endl;
		  return 1;
	  }

	  if (vm.count("consumer-secret"))
	  {
		  tmp_str = vm["consumer-secret"].as<string>();
		  twitterObj.getOAuth().setConsumerSecret(tmp_str);
	  }
	  else
	  {
		  cout<<"Consumer secret key required"<<endl;
		  return 1;
	  }
	  if (vm.count("token-key"))
	  {
		  tokenFile = vm["token-key"].as<string>();
	  }
	  if (vm.count("token-secret"))
	  {
		  tokenSecret = vm["token-secret"].as<string>();
	  }
	  if (vm.count("crawling-depth"))
	  {
		  crawling_depth = vm["crawling-depth"].as<string>();
	  }
	  if (vm.count("crawl-max-retry"))
	  {
		  crawl_max_retry = atoi(vm["crawl-max-retry"].as<string>().c_str());
		  if(crawl_max_retry < 1) { crawl_max_retry = 1;}
		  if(crawl_max_retry > 10) { crawl_max_retry = 10;}

	  }
	  if (vm.count("users-count"))
	  {
		  crawl_max_retry = atoi(vm["users-count"].as<string>().c_str());
		  if(users_count < 0) { users_count = 1;}
		  if(crawl_max_retry > 100000) { users_count = 100000;}

	  }
	  /* OAuth flow begins */
	  /* Step 1: Check if we alredy have OAuth access token from a previous run */
	   string myOAuthAccessTokenKey("");
	   string myOAuthAccessTokenSecret("");
	   ifstream oAuthTokenKeyIn;
	   ifstream oAuthTokenSecretIn;

	   oAuthTokenKeyIn.open( tokenFile.c_str());
	   oAuthTokenSecretIn.open( tokenSecret.c_str() );

	   memset( tmp_buf, 0, 1024 );
	   oAuthTokenKeyIn >> tmp_buf;
	   myOAuthAccessTokenKey = tmp_buf;

	   memset( tmp_buf, 0, 1024 );
	   oAuthTokenSecretIn >> tmp_buf;
	   myOAuthAccessTokenSecret = tmp_buf;
     oAuthTokenKeyIn.close();
     oAuthTokenSecretIn.close();

     if( myOAuthAccessTokenKey.size() && myOAuthAccessTokenSecret.size() )
     {
      /* If we already have these keys, then no need to go through auth again */
//        printf( "\nUsing:\nKey: %s\nSecret: %s\n\n", myOAuthAccessTokenKey.c_str(), myOAuthAccessTokenSecret.c_str() );

	      twitterObj.getOAuth().setOAuthTokenKey( myOAuthAccessTokenKey );
	      twitterObj.getOAuth().setOAuthTokenSecret( myOAuthAccessTokenSecret );
	   }
	   else
	   {
	        /* Step 2: Get request token key and secret */
	      string authUrl;
	      twitterObj.oAuthRequestToken( authUrl );

	          /* Step 3: Get PIN  */
	      memset( tmp_buf, 0, 1024 );
	      printf( "\nDo you want to visit twitter.com for PIN (0 for no; 1 for yes): " );
	      gets( tmp_buf );
	      tmp_str = tmp_buf;
	      if( string::npos != tmp_str.find( "1" ) )
	      {
	              /* Ask user to visit twitter.com auth page and get PIN */
	          memset( tmp_buf, 0, 1024 );
	          printf( "\nPlease visit this link in web browser and authorize this application:\n%s", authUrl.c_str() );
	          printf( "\nEnter the PIN provided by twitter: " );
	          gets( tmp_buf );
	          tmp_str = tmp_buf;
	          twitterObj.getOAuth().setOAuthPin( tmp_str );
	      }
	      else
	      {
	            /* Else, pass auth url to twitCurl and get it via twitCurl PIN handling */
	          twitterObj.oAuthHandlePIN( authUrl );
	      }

	          /* Step 4: Exchange request token with access token */
	      twitterObj.oAuthAccessToken();

	          /* Step 5: Now, save this access token key and secret for future use without PIN */
	      twitterObj.getOAuth().getOAuthTokenKey( myOAuthAccessTokenKey );
	      twitterObj.getOAuth().getOAuthTokenSecret( myOAuthAccessTokenSecret );

	          /* Step 6: Save these keys in a file or wherever */
	      ofstream oAuthTokenKeyOut;
	      ofstream oAuthTokenSecretOut;

	      oAuthTokenKeyOut.open( tokenFile.c_str() );
	      oAuthTokenSecretOut.open( tokenSecret.c_str() );

	      oAuthTokenKeyOut.clear();
	      oAuthTokenSecretOut.clear();

	      oAuthTokenKeyOut << myOAuthAccessTokenKey.c_str();
	      oAuthTokenSecretOut << myOAuthAccessTokenSecret.c_str();

	      oAuthTokenKeyOut.close();
	      oAuthTokenSecretOut.close();
	  }
	      /* OAuth flow ends */
    twitterObj.setTwitterApiType(twitCurlTypes::eTwitCurlApiFormatJson);

    Database db;
    if (db.connect()){
    	cout<<"connected to database"<<endl;
    }else
    {
    	cout<<"could not connect to database"<<endl;
    	return -1;
    }
    time_t rawtime;
    struct tm * timeinfo;
    char  start_time[100];
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    strftime (start_time,80,"%c",timeinfo);
    string event("start_update_users "), description("");
    event += (string)start_time;
    db.log(event, description);
    string order_by = "last_update, distance_to_seed";
    string condition = "distance_to_seed<"+crawling_depth;

    if(!db.getUsersIds(reply_msg, order_by, condition, users_count/*default number of users to treat per command call*/)){
    		cout<<"could not get users ids from database"<<endl;
    }
    istringstream iss(reply_msg), iss1;
    string user_id, fields_update(""), values_update("");
    int i;
    string profile(""), statuses(""), fields("last_status"),
    		fields_profile("screen_name, id, created_at, name, description, protected, contributors_enabled, default_profile, verified, geo_enable, is_translator, profile_background_tile, profile_use_background_image, profile_background_image_url, default_profile_image, location, time_zone, statuses_count, followers_count, friends_count, listed_count, profile_link_color, status_text, notifications, following, follow_request_sent, utc_offset, profile_text_color, profile_sidebar_border_color, profile_image_url, url, profile_sidebar_fill_color, profile_image_url_http, favourites_count, lang"),
    		fields_status("id, user_id, created_at, text, source, truncated, in_reply_to_status_id, in_reply_to_user_id, retweet_count, geo, coordinates, place, contributors, favorited, retweeted, retweeted_status, retweeted_user_id, possibly_sensitive, user_mentions, hashtags, urls");
    unsigned long long last_id, since_id;
    while(iss>>user_id){
  	  cout<<"updating profile and statuses of the user "<<user_id<<endl;
	  if(!db.getUser(reply_msg2, user_id, fields)){
		  cout<<"could not retrieve user info"<<endl;
		  continue;
	  }
	  iss1.clear();
	  iss1.str(reply_msg2);
	  iss1>>since_id;
  	  for(i=0;i<crawl_max_retry;i++)
  	  {
  		  last_id = 0;
  		  if(!twitterObj.getUserStatusProfile(statuses, profile, last_id, fields_status, fields_profile, since_id, user_id, true)){
  	          	   	cout<<"Error get data from twitter. Retrying..."<<endl;
  	          	   	usleep(50000);
  	         	  }
  	        	 else
  	        	 {
  	        		 break;
  	        	 }
  	  }

  	  if(i == crawl_max_retry){
  	    		  cout<<"Error get data from twitter. Moving on..."<<endl;
  	    		  fields_update = "last_update"; values_update = "CURRENT_TIMESTAMP";
  	        	  if(!db.updateUser(user_id, fields_update, values_update))
  	        	  {
  	        		  cout <<"error update user"<<endl;
  	        	  }
  	    		  continue;
  	  }

	  if(db.insertProfile(fields_profile, profile)){
	    cout<<"inserted profile for the user "<<user_id<<endl;
	  }
	  if(db.insertStatuses(fields_status, statuses)){
	    cout<<"inserted statuses for the user "<<user_id<<endl;
	  }
	  fields_update = "last_update, last_status";
	  values_update = "CURRENT_TIMESTAMP, "+boost::lexical_cast<string>(last_id);
	  if(!db.updateUser(user_id, fields_update, values_update))
	  {
		  cout <<"error update user"<<endl;
	  }

    }

    event = "finish_update_users_started_at "+(string)start_time;
    db.log(event, description);
    db.disconnect();

  	cout<<"disconnected from database"<<endl;

	return 0;
}


