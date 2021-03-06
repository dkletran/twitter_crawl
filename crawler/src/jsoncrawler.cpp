/*
 * jsoncrawler.cpp
 *
 *  Created on: 22 juin 2012
 *      Author: ktvr5725
 */

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/replace.hpp>

#include "jsoncrawler.h"
std::string process_string(std::string input_string)
{
	std::string output = boost::algorithm::replace_all_copy(input_string, "\\", "\\\\");
	output = boost::algorithm::replace_all_copy(output, "\"", "\\\"");

	output = "\""+output+"\"";
	return output;
}
bool JsonCrawler::getAllFollowersIds( std::string& valueOut,  std::string& userInfo, bool isUserId  ){
    int size, count=0, i;
	Json::Value root, ids;   // will contains the root value after parsing.
    Json::Reader reader;
    std::string reply_msg, cursor;
    cursor = "-1";
    if(this->followersIdsGet(userInfo, cursor, isUserId))
    {
    	this->getLastWebResponse(reply_msg);
    }
    else
    {
    	return false;
    }
	if(!reader.parse(reply_msg, root))
	{
        // report to the user the failure and their locations in the document.
        std::cout  << "Failed to parse configuration\n"
                   << reader.getFormattedErrorMessages();
        return false;
	}
	ids = root["ids"];
	cursor = root["next_cursor"].asString();
	if (ids.isArray())
	{
		count= size = ids.size();
		valueOut = ids[0].asString();

		for(i=1; i < size; i++){
			valueOut+=", "+ids[i].asString();
		}
	}
	else
	{
		return false;
	}
	while (cursor.compare("0"))
	{
		if(this->followersIdsGet(userInfo, cursor, isUserId))
		    {
		    	this->getLastWebResponse(reply_msg);
		    }
		    else
		    {
		    	return false;
		    }
		if(!reader.parse(reply_msg, root))
		{
	        // report to the user the failure and their locations in the document.
//	        std::cout  << "Failed to parse configuration\n"
	//                   << reader.getFormattedErrorMessages();
	        return false;
		}
		ids = root["ids"];
		cursor = root["next_cursor"].asString();
		if (ids.isArray())
		{
			size = ids.size();
			count += size;
			for(i=0; i < size; i++){
				valueOut+=", "+ids[i].asString();
			}
		}

	}
	std::cout<<"Got "<<count<<" followers of the user "<<userInfo<<std::endl;
    return true;
}

bool JsonCrawler::getAllFriendsIds( std::string& valueOut,  std::string& userInfo, bool isUserId  ){
    int size, count=0, i;
	Json::Value root, ids;   // will contains the root value after parsing.
    Json::Reader reader;
    std::string reply_msg, cursor;
    cursor = "-1";
    if(this->friendsIdsGet(userInfo, cursor, isUserId))
    {
    	this->getLastWebResponse(reply_msg);
    }
    else
    {
    	return false;
    }
	if(!reader.parse(reply_msg, root))
	{
        // report to the user the failure and their locations in the document.
        std::cout  << "Failed to parse configuration\n"
                   << reader.getFormattedErrorMessages();
        return false;
	}
	ids = root["ids"];
	cursor = root["next_cursor"].asString();
	if (ids.isArray())
	{
		count= size = ids.size();

		valueOut = ids[0].asString();
		for(i=1; i < size; i++){
			valueOut+=", "+ids[i].asString();
		}
	}
	else
	{
		return false;
	}
	while (cursor.compare("0"))
	{
		if(this->friendsIdsGet(userInfo, cursor, isUserId))
		    {
		    	this->getLastWebResponse(reply_msg);
		    }
		    else
		    {
		    	return false;
		    }
		if(!reader.parse(reply_msg, root))
		{
	        // report to the user the failure and their locations in the document.
//	        std::cout  << "Failed to parse configuration\n"
	//                   << reader.getFormattedErrorMessages();
	        return false;
		}
		ids = root["ids"];
		cursor = root["next_cursor"].asString();
		if (ids.isArray())
		{
			size = ids.size();
			count += size;
			for(i=0; i < size; i++){
				valueOut+=", "+ids[i].asString();
			}
		}

	}
	std::cout<<"Got "<<count<<" friends of the user "<<userInfo<<std::endl;
    return true;
}

bool JsonCrawler::getUsersProfiles(std::string& valueOut, std::string& fields/* fields */, std::string& usersInfo, bool isUserId){
		Json::Value root,  array_fields, value;   // will contains the root value after parsing.
	    Json::Reader reader;
	    std::string reply_msg;
	    int size, fields_count, i, j;

	    if(this->usersGet(usersInfo,  isUserId))
	    {
	    	this->getLastWebResponse(reply_msg);
	    }
	    else
	    {
	    	return false;
	    }
		if(!reader.parse(reply_msg, root))
		{
	        // report to the user the failure and their locations in the document.
	        std::cout  << "Failed to parse configuration\n"
	                   << reader.getFormattedErrorMessages();
	        return false;
		}
		boost::erase_all(fields, " ");
		reader.parse("[{\"name\":\""+boost::algorithm::replace_all_copy(fields, ",", "\"}, {\"name\":\"")+"\"}]", array_fields);
		fields_count = array_fields.size();

		if (root.isArray())
		{
			size = root.size();
			valueOut = "";
			for(i=0; i < size; i++){
				valueOut += "(";
				for(j=0; j < fields_count; j++){
					value = root[i][array_fields[j]["name"].asString()];
					//std::cout<<value.asString()<<std::endl;
					if (!array_fields[j]["name"].asString().compare("created_at")){
						valueOut += "STR_TO_DATE('"+value.asString()+"', '%a %b %d %T +0000 %Y')";
					}else if (value.isString()){
						valueOut += process_string(value.asString());
					}
					else if (value.isNull()){
						valueOut += "null";
					}
					else if (value.isInt()){
						valueOut += value.asString();
					}else if (value.isBool()){
						valueOut += value.asBool()?"1":"0";
					}else{
						valueOut += "null";
					}

					if(j<fields_count-1){
						valueOut += ", ";
					}

				}
				valueOut += ")";
				if(i<size-1){
					valueOut += ", ";
				}
			}
		}

	return true;
}
#define TWEETS_PER_REQUEST 175
bool JsonCrawler::getUserStatusProfile(std::string& status, std::string& profile, unsigned long long& newest_status_id, std::string& fields_status/* fields */, std::string& fields_profile, unsigned long long since_id, std::string& userInfo, bool isUserId){
	Json::Value root,  array_fields_status, array_fields_profile, value;   // will contains the root value after parsing.
    Json::Reader reader;
    std::string reply_msg;
    int size, fields_status_count, fields_profile_count, i, j, k, elements_count, tweets_count = 0;
    unsigned long long last_min_id;
	boost::erase_all(fields_profile, " ");
	reader.parse("[{\"name\":\""+boost::algorithm::replace_all_copy(fields_profile, ",", "\"}, {\"name\":\"")+"\"}]", array_fields_profile);
	boost::erase_all(fields_status, " ");
	reader.parse("[{\"name\":\""+boost::algorithm::replace_all_copy(fields_status, ",", "\"}, {\"name\":\"")+"\"}]", array_fields_status);
	fields_status_count = array_fields_status.size();
	fields_profile_count = array_fields_profile.size();

    if(this->timelineUserGet(false, true, TWEETS_PER_REQUEST, since_id, 0, userInfo, isUserId))
    {
    	this->getLastWebResponse(reply_msg);
    }
    else
    {
    	return false;
    }
	if(!reader.parse(reply_msg, root))
	{
        // report to the user the failure and their locations in the document.
        std::cout  << "Failed to parse configuration\n"
                   << reader.getFormattedErrorMessages();
        return false;
	}
	size = 0;
	if (root.isArray())
	{
		size = root.size();
		tweets_count += size;
		newest_status_id = root[0]["id"].asInt64();

		if(!root[0]["user"].isNull()){
			profile = "(";

			for(j=0; j < fields_profile_count; j++){
							value = root[0]["user"][array_fields_profile[j]["name"].asString()];
							//std::cout<<value.asString()<<std::endl;
							if (!array_fields_profile[j]["name"].asString().compare("created_at")){
								profile += "STR_TO_DATE('"+value.asString()+"', '%a %b %d %T +0000 %Y')";
							}else if (value.isString()){
								profile += process_string(value.asString());
							}
							else if (value.isNull()){
								profile += "null";
							}
							else if (value.isInt()){
								profile += value.asString();
							}else if (value.isBool()){
								profile += value.asBool()?"1":"0";
							}else{
								profile += "null";
							}

							if(j<fields_profile_count-1){
								profile += ", ";
							}

						}
			profile += ")";
			}
			status="";
			for(i=0; i < size; i++){
				status+="(";
				for(j=0; j < fields_status_count; j++){
									value = root[i][array_fields_status[j]["name"].asString()];
									//std::cout<<value.asString()<<std::endl;
									if(!array_fields_status[j]["name"].asString().compare("user_id")){
										status += root[i]["user"]["id"].asString();
									} else if(!array_fields_status[j]["name"].asString().compare("user_mentions")){
										value = root[i];
										elements_count = value["entities"].isNull()?0:value["entities"]["user_mentions"].size();
										status += "\"";
										for(k=0; k < elements_count-1; k++)
										{
											status += value["entities"]["user_mentions"][k]["id"].asString()+",";
										}
										status += elements_count?value["entities"]["user_mentions"][k]["id"].asString()+"\"":"\"";
									}else if (!array_fields_status[j]["name"].asString().compare("urls")){
										value = root[i];
										elements_count = value["entities"].isNull()?0:value["entities"]["urls"].size();
										status += "\"";
										for(k=0; k < elements_count-1; k++)
										{
											status += value["entities"]["urls"][k]["expanded_url"].asString()+",";
										}
										status += elements_count?value["entities"]["urls"][k]["expanded_url"].asString()+"\"":"\"";
									}else if (!array_fields_status[j]["name"].asString().compare("hashtags")){
										value = root[i];

										elements_count = value["entities"].isNull()?0:value["entities"]["hashtags"].size();
										status += "\"";
										for(k=0; k < elements_count-1; k++)
										{
											status += value["entities"]["hashtags"][k]["text"].asString()+",";
										}
										status += elements_count?value["entities"]["hashtags"][k]["text"].asString()+"\"":"\"";

									}else if (!array_fields_status[j]["name"].asString().compare("retweeted_user_id")){
										value = root[i];
										status += value["retweeted_status"].isNull()?"null":value["retweeted_status"]["user"]["id"].asString();
									}else if (!array_fields_status[j]["name"].asString().compare("retweeted_status")){
										value = root[i];

										status += value["retweeted_status"].isNull()?"null":value["retweeted_status"]["id"].asString();
									}else if (!array_fields_status[j]["name"].asString().compare("created_at")){
										status += "STR_TO_DATE('"+value.asString()+"', '%a %b %d %T +0000 %Y')";
									}else if (value.isString()){
										status += process_string(value.asString());

									}
									else if (value.isNull()){

										status += "null";
									}
									else if (value.isInt64()||value.isInt()){

										status += value.asString();

									}else if (value.isBool()){
										status += value.asBool()?"1":"0";
									}else{
										status += "null";
									}

									if(j<fields_status_count-1){
										status += ", ";
									}

								}
				status+=")";
				if(i<size-1){
					status += ", ";
				}

			}


	}

	while (size > 0){
		if(!root.isArray()) break;
		last_min_id = root[size-1]["id"].asUInt64();
	    if(this->timelineUserGet(true, true, TWEETS_PER_REQUEST, since_id, last_min_id-1, userInfo, isUserId))
	    {
	    	this->getLastWebResponse(reply_msg);
	    }
	    else
	    {
	    	this->getLastCurlError(reply_msg);
	    	std::cout<<reply_msg<<std::endl;
	    	break;
	    }
	    root.clear();
		if(!reader.parse(reply_msg, root))
		{
	        // report to the user the failure and their locations in the document.
	        std::cout  << "Failed to parse configuration\n"
	                   << reader.getFormattedErrorMessages();
	        if(tweets_count>500)
	        {
	        	break;
	        }
	        else
	        {
	        	return false;
	        }
		}
		if (root.isArray())
		{
				size = root.size();
				tweets_count += size;

				for(i=0; i < size; i++){
								status+=",(";
								for(j=0; j < fields_status_count; j++){
													value = root[i][array_fields_status[j]["name"].asString()];
													//std::cout<<value.asString()<<std::endl;
													if(!array_fields_status[j]["name"].asString().compare("user_id")){
														status += root[i]["user"]["id"].asString();
													} else 	if(!array_fields_status[j]["name"].asString().compare("user_mentions")){
														value = root[i];
														elements_count = value["entities"].isNull()?0:value["entities"]["user_mentions"].size();
														status += "\"";
														for(k=0; k < elements_count-1; k++)
														{
															status += value["entities"]["user_mentions"][k]["id"].asString()+",";
														}
														status += elements_count?value["entities"]["user_mentions"][k]["id"].asString()+"\"":"\"";
													}else if (!array_fields_status[j]["name"].asString().compare("urls")){
														value = root[i];
														elements_count = value["entities"].isNull()?0:value["entities"]["urls"].size();
														status += "\"";
														for(k=0; k < elements_count-1; k++)
														{
															status += value["entities"]["urls"][k]["expanded_url"].asString()+",";
														}
														status += elements_count?value["entities"]["urls"][k]["expanded_url"].asString()+"\"":"\"";
													}else if (!array_fields_status[j]["name"].asString().compare("hashtags")){
														value = root[i];

														elements_count = value["entities"].isNull()?0:value["entities"]["hashtags"].size();
														status += "\"";
														for(k=0; k < elements_count-1; k++)
														{
															status += value["entities"]["hashtags"][k]["text"].asString()+",";
														}
														status += elements_count?value["entities"]["hashtags"][k]["text"].asString()+"\"":"\"";

													}else if (!array_fields_status[j]["name"].asString().compare("retweeted_user_id")){
														value = root[i];
														status += value["retweeted_status"].isNull()?"null":value["retweeted_status"]["user"]["id"].asString();
													}else if (!array_fields_status[j]["name"].asString().compare("retweeted_status")){
														value = root[i];

														status += value["retweeted_status"].isNull()?"null":value["retweeted_status"]["id"].asString();
													}
													else if (!array_fields_status[j]["name"].asString().compare("created_at")){
														status += "STR_TO_DATE('"+value.asString()+"', '%a %b %d %T +0000 %Y')";
													}
													else if (value.isString()){
														status += process_string(value.asString());
													}
													else if (value.isNull()){

														status += "null";
													}
													else if (value.isInt64()||value.isInt()){

														status += value.asString();

													}else if (value.isBool()){
														status += value.asBool()?"1":"0";
													}else{
														status += "null";
													}

													if(j<fields_status_count-1){
														status += ", ";
													}

												}
								status+=")";

							}

		}

	}
	std::cout<<"Got "<<tweets_count<<" tweets of the user "<<userInfo<<std::endl;
	if (tweets_count<=0) return false;
	return true;
}


bool JsonCrawler::getUserFavourites(std::string& status, unsigned long long& newest_status_id, std::string& fields_status/* fields */,  unsigned long long since_id, std::string& userInfo, bool isUserId){
	Json::Value root,  array_fields_status, array_fields_profile, value;   // will contains the root value after parsing.
    Json::Reader reader;
    std::string reply_msg;
    int size, fields_status_count, fields_profile_count, i, j, k, elements_count, tweets_count = 0;
    unsigned long long last_min_id;
	boost::erase_all(fields_status, " ");
	reader.parse("[{\"name\":\""+boost::algorithm::replace_all_copy(fields_status, ",", "\"}, {\"name\":\"")+"\"}]", array_fields_status);
	fields_status_count = array_fields_status.size();
	fields_profile_count = array_fields_profile.size();

    if(this->favoritesGet(true, true, TWEETS_PER_REQUEST, since_id, 0, userInfo, isUserId))
    {
    	this->getLastWebResponse(reply_msg);
    }
    else
    {
    	return false;
    }
	if(!reader.parse(reply_msg, root))
	{
        // report to the user the failure and their locations in the document.
        std::cout  << "Failed to parse configuration\n"
                   << reader.getFormattedErrorMessages();
        return false;
	}
	size = 0;
	if (root.isArray())
	{
		size = root.size();
		tweets_count += size;
		newest_status_id = root[0]["id"].asInt64();


			status="";
			for(i=0; i < size; i++){
				status+="(";
				for(j=0; j < fields_status_count; j++){
									value = root[i][array_fields_status[j]["name"].asString()];
									//std::cout<<value.asString()<<std::endl;
									if(!array_fields_status[j]["name"].asString().compare("of_user_id")){
										status += isUserId?userInfo:0;
									} else if(!array_fields_status[j]["name"].asString().compare("user_id")){
										status += root[i]["user"]["id"].asString();
									} else if(!array_fields_status[j]["name"].asString().compare("user_mentions")){
										value = root[i];
										elements_count = value["entities"].isNull()?0:value["entities"]["user_mentions"].size();
										status += "\"";
										for(k=0; k < elements_count-1; k++)
										{
											status += value["entities"]["user_mentions"][k]["id"].asString()+",";
										}
										status += elements_count?value["entities"]["user_mentions"][k]["id"].asString()+"\"":"\"";
									}else if (!array_fields_status[j]["name"].asString().compare("urls")){
										value = root[i];
										elements_count = value["entities"].isNull()?0:value["entities"]["urls"].size();
										status += "\"";
										for(k=0; k < elements_count-1; k++)
										{
											status += value["entities"]["urls"][k]["expanded_url"].asString()+",";
										}
										status += elements_count?value["entities"]["urls"][k]["expanded_url"].asString()+"\"":"\"";
									}else if (!array_fields_status[j]["name"].asString().compare("hashtags")){
										value = root[i];

										elements_count = value["entities"].isNull()?0:value["entities"]["hashtags"].size();
										status += "\"";
										for(k=0; k < elements_count-1; k++)
										{
											status += value["entities"]["hashtags"][k]["text"].asString()+",";
										}
										status += elements_count?value["entities"]["hashtags"][k]["text"].asString()+"\"":"\"";

									}else if (!array_fields_status[j]["name"].asString().compare("retweeted_user_id")){
										value = root[i];
										status += value["retweeted_status"].isNull()?"null":value["retweeted_status"]["user"]["id"].asString();
									}else if (!array_fields_status[j]["name"].asString().compare("retweeted_status")){
										value = root[i];

										status += value["retweeted_status"].isNull()?"null":value["retweeted_status"]["id"].asString();
									}else if (!array_fields_status[j]["name"].asString().compare("created_at")){
										status += "STR_TO_DATE('"+value.asString()+"', '%a %b %d %T +0000 %Y')";
									}else if (value.isString()){
										status += process_string(value.asString());

									}
									else if (value.isNull()){

										status += "null";
									}
									else if (value.isInt64()||value.isInt()){

										status += value.asString();

									}else if (value.isBool()){
										status += value.asBool()?"1":"0";
									}else{
										status += "null";
									}

									if(j<fields_status_count-1){
										status += ", ";
									}

								}
				status+=")";
				if(i<size-1){
					status += ", ";
				}

			}


	}

	while (size > 0){
		if(!root.isArray()) break;
		last_min_id = root[size-1]["id"].asUInt64();
	    if(this->favoritesGet(true, true, TWEETS_PER_REQUEST, since_id, last_min_id-1, userInfo, isUserId))
	    {
	    	this->getLastWebResponse(reply_msg);
	    }
	    else
	    {
	    	this->getLastCurlError(reply_msg);
	    	std::cout<<reply_msg<<std::endl;
	    	break;
	    }
	    root.clear();
		if(!reader.parse(reply_msg, root))
		{
	        // report to the user the failure and their locations in the document.
	        std::cout  << "Failed to parse configuration\n"
	                   << reader.getFormattedErrorMessages();
	        if(tweets_count>500)
	        {
	        	break;
	        }
	        else
	        {
	        	return false;
	        }
		}
		if (root.isArray())
		{
				size = root.size();
				tweets_count += size;

				for(i=0; i < size; i++){
								status+=",(";
								for(j=0; j < fields_status_count; j++){
													value = root[i][array_fields_status[j]["name"].asString()];
													//std::cout<<value.asString()<<std::endl;

													if(!array_fields_status[j]["name"].asString().compare("of_user_id")){
														status += isUserId?userInfo:0;
													} else if(!array_fields_status[j]["name"].asString().compare("user_id")){
														status += root[i]["user"]["id"].asString();
													} else 	if(!array_fields_status[j]["name"].asString().compare("user_mentions")){
														value = root[i];
														elements_count = value["entities"].isNull()?0:value["entities"]["user_mentions"].size();
														status += "\"";
														for(k=0; k < elements_count-1; k++)
														{
															status += value["entities"]["user_mentions"][k]["id"].asString()+",";
														}
														status += elements_count?value["entities"]["user_mentions"][k]["id"].asString()+"\"":"\"";
													}else if (!array_fields_status[j]["name"].asString().compare("urls")){
														value = root[i];
														elements_count = value["entities"].isNull()?0:value["entities"]["urls"].size();
														status += "\"";
														for(k=0; k < elements_count-1; k++)
														{
															status += value["entities"]["urls"][k]["expanded_url"].asString()+",";
														}
														status += elements_count?value["entities"]["urls"][k]["expanded_url"].asString()+"\"":"\"";
													}else if (!array_fields_status[j]["name"].asString().compare("hashtags")){
														value = root[i];

														elements_count = value["entities"].isNull()?0:value["entities"]["hashtags"].size();
														status += "\"";
														for(k=0; k < elements_count-1; k++)
														{
															status += value["entities"]["hashtags"][k]["text"].asString()+",";
														}
														status += elements_count?value["entities"]["hashtags"][k]["text"].asString()+"\"":"\"";

													}else if (!array_fields_status[j]["name"].asString().compare("retweeted_user_id")){
														value = root[i];
														status += value["retweeted_status"].isNull()?"null":value["retweeted_status"]["user"]["id"].asString();
													}else if (!array_fields_status[j]["name"].asString().compare("retweeted_status")){
														value = root[i];

														status += value["retweeted_status"].isNull()?"null":value["retweeted_status"]["id"].asString();
													}
													else if (!array_fields_status[j]["name"].asString().compare("created_at")){
														status += "STR_TO_DATE('"+value.asString()+"', '%a %b %d %T +0000 %Y')";
													}
													else if (value.isString()){
														status += process_string(value.asString());
													}
													else if (value.isNull()){

														status += "null";
													}
													else if (value.isInt64()||value.isInt()){

														status += value.asString();

													}else if (value.isBool()){
														status += value.asBool()?"1":"0";
													}else{
														status += "null";
													}

													if(j<fields_status_count-1){
														status += ", ";
													}

												}
								status+=")";

							}

		}

	}
	std::cout<<"Got "<<tweets_count<<" favourites of the user "<<userInfo<<std::endl;
	if (tweets_count<=0) return false;
	return true;
}

bool JsonCrawler::searchStatuses(std::string& status, int max_count, std::string& query, std::string& fields_status, unsigned long long since_id){
	Json::Value root0, root,  array_fields_status, array_fields_profile, value;   // will contains the root value after parsing.
    Json::Reader reader;
    std::string reply_msg;
    std::string lang="fr";
    int size, fields_status_count, fields_profile_count, i, j, k, elements_count, tweets_count = 0;
    unsigned long long last_min_id;
	boost::erase_all(fields_status, " ");
	reader.parse("[{\"name\":\""+boost::algorithm::replace_all_copy(fields_status, ",", "\"}, {\"name\":\"")+"\"}]", array_fields_status);
	fields_status_count = array_fields_status.size();
	fields_profile_count = array_fields_profile.size();
	tweets_count=0;
    if(this->search(query, since_id, 0, lang))
    {
    	this->getLastWebResponse(reply_msg);
    }
    else
    {
    	return false;
    }

	if(!reader.parse(reply_msg, root0))
	{
        // report to the user the failure and their locations in the document.
        std::cout  << "Failed to parse configuration\n"
                   << reader.getFormattedErrorMessages();
        return false;
	}
	size = 0;
	root = root0["results"];

	if (root.isArray())
	{
		size = root.size();
		tweets_count += size;


			status="";
			for(i=0; i < size; i++){
				status+="(";
				for(j=0; j < fields_status_count; j++){
									value = root[i][array_fields_status[j]["name"].asString()];
									//std::cout<<value.asString()<<std::endl;
									if(!array_fields_status[j]["name"].asString().compare("user_id")){
										status += root[i]["user"]["id"].asString();
									} else if(!array_fields_status[j]["name"].asString().compare("user_mentions")){
										value = root[i];
										elements_count = value["entities"].isNull()?0:value["entities"]["user_mentions"].size();
										status += "\"";
										for(k=0; k < elements_count-1; k++)
										{
											status += value["entities"]["user_mentions"][k]["id"].asString()+",";
										}
										status += elements_count?value["entities"]["user_mentions"][k]["id"].asString()+"\"":"\"";
									}else if (!array_fields_status[j]["name"].asString().compare("urls")){
										value = root[i];
										elements_count = value["entities"].isNull()?0:value["entities"]["urls"].size();
										status += "\"";
										for(k=0; k < elements_count-1; k++)
										{
											status += value["entities"]["urls"][k]["expanded_url"].asString()+",";
										}
										status += elements_count?value["entities"]["urls"][k]["expanded_url"].asString()+"\"":"\"";
									}else if (!array_fields_status[j]["name"].asString().compare("hashtags")){
										value = root[i];

										elements_count = value["entities"].isNull()?0:value["entities"]["hashtags"].size();
										status += "\"";
										for(k=0; k < elements_count-1; k++)
										{
											status += value["entities"]["hashtags"][k]["text"].asString()+",";
										}
										status += elements_count?value["entities"]["hashtags"][k]["text"].asString()+"\"":"\"";

									}else if (!array_fields_status[j]["name"].asString().compare("retweeted_user_id")){
										value = root[i];
										status += value["retweeted_status"].isNull()?"null":value["retweeted_status"]["user"]["id"].asString();
									}else if (!array_fields_status[j]["name"].asString().compare("retweeted_status")){
										value = root[i];

										status += value["retweeted_status"].isNull()?"null":value["retweeted_status"]["id"].asString();
									}else if (!array_fields_status[j]["name"].asString().compare("created_at")){
										status += "STR_TO_DATE('"+value.asString()+"', '%a, %d %b %Y %T +0000')";
									}else if (value.isString()){
										status += process_string(value.asString());

									}
									else if (value.isNull()){

										status += "null";
									}
									else if (value.isInt64()||value.isInt()){

										status += value.asString();

									}else if (value.isBool()){
										status += value.asBool()?"1":"0";
									}else{
										status += "null";
									}

									if(j<fields_status_count-1){
										status += ", ";
									}

								}
				status+=")";
				if(i<size-1){
					status += ", ";
				}

			}


	}
	while ((size > 0)&&(tweets_count<max_count)){
		if(!root.isArray()) break;
		last_min_id = root[size-1]["id"].asUInt64();
	    if(this->search(query,since_id, last_min_id-1))
	    {
	    	this->getLastWebResponse(reply_msg);
	    }
	    else
	    {
	    	this->getLastCurlError(reply_msg);
	    	std::cout<<reply_msg<<std::endl;
	    	break;
	    }
	    root.clear();
		if(!reader.parse(reply_msg, root0))
		{
	        // report to the user the failure and their locations in the document.
	        std::cout  << "Failed to parse configuration\n"
	                   << reader.getFormattedErrorMessages();
	        if(tweets_count>max_count)
	        {
	        	break;
	        }
	        else
	        {
	        	return false;
	        }
		}

		root = root0["results"];

		if (root.isArray())
		{
				size = root.size();
				tweets_count += size;

				for(i=0; i < size; i++){
								status+=",(";
								for(j=0; j < fields_status_count; j++){
													value = root[i][array_fields_status[j]["name"].asString()];
													//std::cout<<value.asString()<<std::endl;
													if(!array_fields_status[j]["name"].asString().compare("user_id")){
														status += root[i]["user"]["id"].asString();
													} else 	if(!array_fields_status[j]["name"].asString().compare("user_mentions")){
														value = root[i];
														elements_count = value["entities"].isNull()?0:value["entities"]["user_mentions"].size();
														status += "\"";
														for(k=0; k < elements_count-1; k++)
														{
															status += value["entities"]["user_mentions"][k]["id"].asString()+",";
														}
														status += elements_count?value["entities"]["user_mentions"][k]["id"].asString()+"\"":"\"";
													}else if (!array_fields_status[j]["name"].asString().compare("urls")){
														value = root[i];
														elements_count = value["entities"].isNull()?0:value["entities"]["urls"].size();
														status += "\"";
														for(k=0; k < elements_count-1; k++)
														{
															status += value["entities"]["urls"][k]["expanded_url"].asString()+",";
														}
														status += elements_count?value["entities"]["urls"][k]["expanded_url"].asString()+"\"":"\"";
													}else if (!array_fields_status[j]["name"].asString().compare("hashtags")){
														value = root[i];

														elements_count = value["entities"].isNull()?0:value["entities"]["hashtags"].size();
														status += "\"";
														for(k=0; k < elements_count-1; k++)
														{
															status += value["entities"]["hashtags"][k]["text"].asString()+",";
														}
														status += elements_count?value["entities"]["hashtags"][k]["text"].asString()+"\"":"\"";

													}else if (!array_fields_status[j]["name"].asString().compare("retweeted_user_id")){
														value = root[i];
														status += value["retweeted_status"].isNull()?"null":value["retweeted_status"]["user"]["id"].asString();
													}else if (!array_fields_status[j]["name"].asString().compare("retweeted_status")){
														value = root[i];

														status += value["retweeted_status"].isNull()?"null":value["retweeted_status"]["id"].asString();
													}
													else if (!array_fields_status[j]["name"].asString().compare("created_at")){
														status += "STR_TO_DATE('"+value.asString()+"', '%a, %d %b %Y %T +0000')";
													}
													else if (value.isString()){
														status += process_string(value.asString());
													}
													else if (value.isNull()){

														status += "null";
													}
													else if (value.isInt64()||value.isInt()){

														status += value.asString();

													}else if (value.isBool()){
														status += value.asBool()?"1":"0";
													}else{
														status += "null";
													}

													if(j<fields_status_count-1){
														status += ", ";
													}

												}
								status+=")";

							}

		}

	}
	std::cout<<"Got "<<tweets_count<<" for the query "<<query<<std::endl;
	if (tweets_count<=0) return false;
	return true;
}

bool JsonCrawler::getCountryFromString(std::string& country, std::string& country_code, std::string& input /*in*/){
    std::string reply_msg;
    Json::Value root;
    Json::Reader reader;

	if(this->geoSearch(input))
    {
    	this->getLastWebResponse(reply_msg);
    }
    else
    {
    	return false;
    }
	if(!reader.parse(reply_msg, root))
	{
        // report to the user the failure and their locations in the document.
        std::cout  << "Failed to parse configuration\n"
                   << reader.getFormattedErrorMessages();
        return false;
	}
	if(root["result"]["places"].isArray()&&root["result"]["places"].size())
	{
		country = root["result"]["places"][0]["country"].asString();
		country_code = root["result"]["places"][0]["country_code"].asString();
		return true;
	}
	return false;
}

