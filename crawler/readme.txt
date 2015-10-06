Twitter crawl*

Database:
 	followers : followers of a user
 	friends: who follow a given user
 	statuses: collected statuses of all users in the table "users"
 	favourites: collected favourite tweet of all users in the table "users"
 	statuses_found : collected statuses from search api (which contain a relevant string (query))
 	users: list of all users (from "follow chain" or author of statuses found (distance_to_seed =99 in this cases))
 	user_profiles: collected users' profiles
 	
 	log: log of crawl component call
 	
Crawler components:
	get_links
	get_search
	update_status_profiles (update statuses and profiles and favourites of the users)
			get_favourites (get all favourites of users)
			update_status_profiles
	put_new_users
		put_links
		put_statuses_athors