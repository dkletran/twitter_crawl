/*
 * database.h
 *
 *  Created on: 25 juin 2012
 *      Author: ktvr5725
 */

#ifndef DATABASE_H_
#define DATABASE_H_

#include <mysql/mysql.h>
#include <mysql++/mysql++.h>
static std::string condition = std::string("1");
static std::string order_by = std::string("id");
class Database: public mysqlpp::Connection {

public:
	bool connect();
	bool log(std::string& event, std::string& description);
	bool updateFollowers(std::string& user_id, std::string& followers);
	bool updateFriends(std::string& user_id, std::string& friends);
	bool getUsersIds(std::string& result, std::string& order_by = order_by, std::string& condtion = condition, int count = 10000);
	bool getUser(std::string& result, std::string& user_id, std::string& fields);
	bool getUserFollowers(std::string& result, std::string& user_id);
	bool addUser(std::string& user_id, std::string& distance_to_seed, std::string& way_to_seed);
	bool updateUser(std::string& user_id, std::string& fields, std::string& values);
	bool insertProfile(std::string& fields, std::string& values);
	bool insertStatuses(std::string& fields, std::string& values);
	bool insertFavourites(std::string& fields, std::string& values);

	bool getLastStatusFoundId(std::string& status_id);
	bool insertStatusesSearch(std::string& fields, std::string& values);
	bool getFromUserIdStatusesFound(std::string& id);
};

#endif /* DATABASE_H_ */
