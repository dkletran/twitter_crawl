/*
 * jsoncrawler.h
 *
 *  Created on: 22 juin 2012
 *      Author: ktvr5725
 */

#ifndef JSONCRAWLER_H_
#define JSONCRAWLER_H_

#include "twitcurl.h"
#include "oauthlib.h"
#include <json/json.h>

class JsonCrawler : public twitCurl{
public:
	bool getAllFollowersIds( std::string& valueOut/*out*/,  std::string& userInfo /* in */, bool isUserId = false /* in */ );
	bool getAllFriendsIds( std::string& valueOut,  std::string& userInfo, bool isUserId = false );
	bool getUsersProfiles(std::string& valueOut /*out*/, std::string& fields/*in*/ , std::string& usersInfo /*in*/, bool isUserId = false /*in*/);
	bool getUserStatusProfile(std::string& statuses, std::string& profile, unsigned long long& newest_status_id, std::string& fields_status, std::string& fields_profile, unsigned long long since_id, std::string& userInfo, bool isUserId = false /*in*/);
	bool searchStatuses(std::string& statuses, int max_count, std::string& query, std::string& fields_status, unsigned long long since_id);
	bool getUserFavourites(std::string& favourites, unsigned long long& newest_status_id, std::string& fields_status,  unsigned long long since_id, std::string& userInfo, bool isUserId = false /*in*/);
	bool getCountryFromString(std::string& country, std::string& country_code, std::string& input /*in*/);

};

#endif /* JSONCRAWLER_H_ */
