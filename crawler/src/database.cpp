/*
 * database.cpp
 *
 *  Created on: 25 juin 2012
 *      Author: ktvr5725
 */
#include	<boost/algorithm/string/replace.hpp>
#include "database.h"
#include <fstream>

using namespace mysqlpp;
bool Database::connect(){
	bool connect = Connection::connect("mycrawler_2", "localhost", "ktvr5725", "ktvr5725!!!");
	Query query = this->query();
	query.reset();
	query<<"SET NAMES 'utf8';";
	bool exec = query.exec();
	return connect&&exec;
}
bool Database::updateFollowers(std::string& user_id, std::string& followers){
	Query query = this->query();
	query.reset();
	if(!followers.compare(""))
	{
		std::cout << "nothing to insert"<<std::endl;
		return false;
	}
	query<<"REPLACE INTO followers(user_id, followers) VALUES ('"<<user_id.c_str()<<
			"','"<<followers.c_str()<<"');";
	if(!query.exec()){
		std::cout<<"could not insert followers of the user "<< user_id<<" into database"<<std::endl;
		return false;
	}

	return true;
}

bool Database::updateFriends(std::string& user_id, std::string& friends){
	Query query = this->query();
	query.reset();
	if(!friends.compare(""))
	{
		std::cout << "nothing to insert"<<std::endl;
		return false;
	}
	query<<"INSERT INTO friends(user_id, friends) VALUES ('"<<user_id.c_str()<<
			"','"<<friends.c_str()<<"');";
	if(!query.exec()){
		std::cout<<"could not insert followers of the user "<< user_id<<" into database"<<std::endl;
		return false;
	}

	return true;
}

bool Database::getUsersIds(std::string& result, std::string& order_by, std::string& condition, int count){
	int i, rows_;
	Query query = this->query();
	query.reset();
	query<<"SELECT id FROM users WHERE "<<condition<<" ORDER BY "<<order_by<<" LIMIT "<<count<<";";
	StoreQueryResult res = query.store();
	rows_ = res.num_rows();
	if(rows_){
		result=(std::string)res[0]["id"];
	}
	else
	{
		result = "";
	}
	for(i=1; i<rows_; i++){
		result += "\t"+(std::string)res[i]["id"];
	}
	return true;
}
bool Database::getUser(std::string& result, std::string& user_id, std::string& fields){
	int i, fields_;
	Query query = this->query();
	query.reset();
	query<<"SELECT "<<fields<<" FROM users WHERE id = "<<user_id<<";";
	StoreQueryResult res = query.store();
	if(res.num_rows()){
		result = (std::string)res[0][0];
		fields_=res.num_fields();
		for(i=1; i<fields_; i++){
		result += "\t"+(std::string)res[0][i];
		}
	}
	else
	{
		result="";
	}
	return true;
}

bool Database::getUserFollowers(std::string& result, std::string& user_id){
	Query query = this->query();
	query.reset();
	std::string aid;
	query<<"SELECT followers FROM followers WHERE user_id = "<<user_id<<" ORDER BY date_insert DESC LIMIT 1;";
	StoreQueryResult res = query.store();
	if(res.num_rows()){
		result = boost::algorithm::replace_all_copy((std::string)res[0]["followers"], ",", "\t");
	}
	else
	{
		result = "";
	}

	return true;
}

bool Database::addUser(std::string& user_id, std::string& distance_to_seed, std::string& way_to_seed){
	bool ret = true;
	Query query = this->query();
	query.reset();
	query<<"INSERT INTO users(id, distance_to_seed, way_to_seed, date_insert) VALUES ("<<
			 user_id<<","<<
			 distance_to_seed<<","<<
			 way_to_seed<<", CURRENT_TIMESTAMP)"<<";";
	try{
		ret = query.exec();
	}
	catch(const BadQuery& e)
	{
		std::cout<<e.what()<<std::endl;
		ret = false;
	}
	return ret;
}

bool Database::log(std::string& events, std::string& description){
	bool ret = true;
	Query query = this->query();
	query.reset();
	query<<"INSERT INTO log(event, description, client) VALUES ('"<<
			 events<<"','"<<
			 description<<"', USER());";
	try{
		ret = query.exec();
	}
	catch(const BadQuery& e)
	{
		std::cout<<e.what()<<std::endl;
		ret = false;
	}
	return ret;
}

bool Database::updateUser(std::string& user_id, std::string& fields, std::string& values){
	bool ret = true;
	Query query=this->query();
	query.reset();
	std::string field, value;
	std::istringstream issfields(boost::algorithm::replace_all_copy(fields, ",", "\t")), issvalues(boost::algorithm::replace_all_copy(values, ",", "\t"));
	query<<"UPDATE users SET ";
	issfields>>field; issvalues>>value;
	query<<field<<"="<<value;
	while ((issfields>>field)&&(issvalues>>value)){
		query<<", "<<field <<"="<<value;
	}
	query<<" WHERE id="<<user_id<<";";
	try{
		ret = query.exec();
	}
	catch(const BadQuery& e)
	{
		std::cout<<e.what()<<std::endl;
		ret = false;
	}
	return ret;
}
bool Database::insertProfile(std::string& fields, std::string& values){
	bool ret = true;
	Query query=this->query();
	query.reset();
	query<<"INSERT INTO user_profiles ("<<fields<<") VALUES "<<values<<";";
	try{
		ret = query.exec();
	}
	catch(const BadQuery& e)
	{
		std::cout<<e.what()<<std::endl;
		ret = false;
	}
	return ret;
}

bool Database::insertStatuses(std::string& fields, std::string& values){
	bool ret = true;

	Query query=this->query();
	query.reset();
	query<<"INSERT INTO statuses ("<<fields<<") VALUES "<<values<<";";
	try{
		ret = query.exec();
	}
	catch(const BadQuery& e)
	{
		std::cout<<e.what()<<std::endl;

		ret = false;
	}
	return ret;
}

bool Database::insertFavourites(std::string& fields, std::string& values){
	bool ret = true;

	Query query=this->query();
	query.reset();
	query<<"INSERT INTO favourites ("<<fields<<") VALUES "<<values<<";";
	try{
		ret = query.exec();
	}
	catch(const BadQuery& e)
	{
		std::cout<<e.what()<<std::endl;

		ret = false;
	}
	return ret;
}

bool Database::insertStatusesSearch(std::string& fields, std::string& values){
	bool ret = true;

	Query query=this->query();
	query.reset();
	query<<"INSERT INTO statuses_found ("<<fields<<") VALUES "<<values<<";";
	try{
		ret = query.exec();
	}
	catch(const BadQuery& e)
	{
		std::cout<<e.what()<<std::endl;

		ret = false;
	}
	return ret;
}
bool Database::getLastStatusFoundId(std::string& status_id)
{
	Query query = this->query();
	query.reset();
	query<<"SELECT id FROM statuses_found ORDER BY id DESC LIMIT 1";
	StoreQueryResult res = query.store();
	if(res.num_rows()){
		status_id = (std::string)res[0][0];
	}
	else
	{
		status_id="";
	}
	return true;
}
bool Database::getFromUserIdStatusesFound(std::string& id){
	Query query = this->query();
	query.reset();
	query<<"SELECT from_user_id FROM statuses_found  WHERE checked=0 AND iso_language_code='fr' ORDER BY created_at LIMIT 1;";
	StoreQueryResult res = query.store();
	id="";
	if(res.num_rows()){
		id = (std::string)res[0][0];
		query.reset();
		query<<"UPDATE statuses_found SET checked=1 WHERE from_user_id="<<id<<";";
		if(!query.exec()) return false;
	}
	else
	{
		id="";
	}
	return true;
}
