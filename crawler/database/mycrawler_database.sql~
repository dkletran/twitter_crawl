-- phpMyAdmin SQL Dump
-- version 3.2.2.1
-- http://www.phpmyadmin.net
--
-- Serveur: localhost
-- Généré le : Ven 13 Juillet 2012 à 15:46
-- Version du serveur: 5.1.55
-- Version de PHP: 5.3.6

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Base de données: `mycrawler_test`
--

-- --------------------------------------------------------

--
-- Structure de la table `favourites`
--

CREATE TABLE IF NOT EXISTS `favourites` (
  `aid` int(15) NOT NULL AUTO_INCREMENT,
  `of_user_id` int(15) NOT NULL,
  `id` bigint(25) NOT NULL,
  `user_id` int(15) NOT NULL,
  `checked_mentions_retweets` tinyint(1) NOT NULL DEFAULT '0',
  `date_insert` timestamp NULL DEFAULT CURRENT_TIMESTAMP,
  `created_at` timestamp NULL DEFAULT '0000-00-00 00:00:00',
  `text` tinytext,
  `source` tinytext,
  `truncated` tinyint(1) DEFAULT '0',
  `in_reply_to_status_id` bigint(25) DEFAULT '0',
  `in_reply_to_user_id` int(15) DEFAULT '0',
  `in_reply_to_screen_name` varchar(32) DEFAULT NULL,
  `retweet_count` int(11) DEFAULT '0',
  `geo` varchar(15) DEFAULT NULL,
  `coordinates` varchar(15) DEFAULT NULL,
  `place` varchar(20) DEFAULT NULL,
  `contributors` varchar(15) DEFAULT NULL,
  `favorited` tinyint(1) DEFAULT NULL,
  `retweeted` int(1) DEFAULT NULL,
  `retweeted_status` bigint(25) DEFAULT NULL,
  `retweeted_user_id` int(15) DEFAULT NULL,
  `possibly_sensitive` tinyint(1) DEFAULT NULL,
  `user_mentions` tinytext,
  `hashtags` tinytext,
  `urls` tinytext,
  PRIMARY KEY (`aid`),
  KEY `user_id` (`user_id`),
  KEY `aid` (`aid`),
  KEY `checked_mentions_retweets` (`checked_mentions_retweets`),
  KEY `in_reply_to_status_id` (`in_reply_to_status_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Structure de la table `followers`
--

CREATE TABLE IF NOT EXISTS `followers` (
  `aid` int(15) NOT NULL AUTO_INCREMENT,
  `user_id` int(15) NOT NULL,
  `date_insert` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `followers` longtext NOT NULL,
  KEY `user_id` (`user_id`),
  KEY `aid` (`aid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Structure de la table `friends`
--

CREATE TABLE IF NOT EXISTS `friends` (
  `aid` int(15) NOT NULL AUTO_INCREMENT,
  `user_id` int(15) NOT NULL,
  `date_insert` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `friends` longtext NOT NULL,
  KEY `user_id` (`user_id`),
  KEY `aid` (`aid`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Structure de la table `log`
--

CREATE TABLE IF NOT EXISTS `log` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `client` varchar(25) NOT NULL,
  `event` varchar(100) NOT NULL,
  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `description` varchar(100) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Structure de la table `retweets`
--

CREATE TABLE IF NOT EXISTS `retweets` (
  `aid` int(15) NOT NULL AUTO_INCREMENT,
  `id` bigint(25) NOT NULL,
  `retweet_count` int(10) NOT NULL,
  `retweeted_by` mediumtext NOT NULL,
  PRIMARY KEY (`aid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Structure de la table `statuses`
--

CREATE TABLE IF NOT EXISTS `statuses` (
  `aid` int(15) NOT NULL AUTO_INCREMENT,
  `id` bigint(25) NOT NULL,
  `user_id` int(15) NOT NULL,
  `checked_mentions_retweets` tinyint(1) NOT NULL DEFAULT '0',
  `date_insert` timestamp NULL DEFAULT CURRENT_TIMESTAMP,
  `created_at` timestamp NULL DEFAULT '0000-00-00 00:00:00',
  `text` tinytext,
  `source` tinytext,
  `truncated` tinyint(1) DEFAULT '0',
  `in_reply_to_status_id` bigint(25) DEFAULT '0',
  `in_reply_to_user_id` int(15) DEFAULT '0',
  `in_reply_to_screen_name` varchar(32) DEFAULT NULL,
  `retweet_count` int(11) DEFAULT '0',
  `geo` varchar(15) DEFAULT NULL,
  `coordinates` varchar(15) DEFAULT NULL,
  `place` varchar(20) DEFAULT NULL,
  `contributors` varchar(15) DEFAULT NULL,
  `favorited` tinyint(1) DEFAULT NULL,
  `retweeted` int(1) DEFAULT NULL,
  `retweeted_status` bigint(25) DEFAULT NULL,
  `retweeted_user_id` int(15) DEFAULT NULL,
  `possibly_sensitive` tinyint(1) DEFAULT NULL,
  `user_mentions` tinytext,
  `hashtags` tinytext,
  `urls` tinytext,
  PRIMARY KEY (`id`),
  KEY `user_id` (`user_id`),
  KEY `aid` (`aid`),
  KEY `checked_mentions_retweets` (`checked_mentions_retweets`),
  KEY `in_reply_to_status_id` (`in_reply_to_status_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Structure de la table `statuses_found`
--

CREATE TABLE IF NOT EXISTS `statuses_found` (
  `aid` int(15) NOT NULL AUTO_INCREMENT,
  `id` bigint(25) NOT NULL,
  `from_user_id` int(15) NOT NULL,
  `to_user_id` int(15) NOT NULL,
  `checked` tinyint(1) NOT NULL DEFAULT '0',
  `date_insert` timestamp NULL DEFAULT CURRENT_TIMESTAMP,
  `created_at` timestamp NULL DEFAULT '0000-00-00 00:00:00',
  `text` tinytext,
  `source` tinytext,
  `truncated` tinyint(1) DEFAULT '0',
  `in_reply_to_status_id` bigint(25) DEFAULT '0',
  `in_reply_to_user_id` int(15) DEFAULT '0',
  `in_reply_to_screen_name` varchar(32) DEFAULT NULL,
  `retweet_count` int(11) DEFAULT '0',
  `geo` varchar(15) DEFAULT NULL,
  `coordinates` varchar(15) DEFAULT NULL,
  `place` varchar(20) DEFAULT NULL,
  `contributors` varchar(15) DEFAULT NULL,
  `favorited` tinyint(1) DEFAULT NULL,
  `retweeted` int(1) DEFAULT NULL,
  `retweeted_status` bigint(25) DEFAULT NULL,
  `retweeted_user_id` int(15) DEFAULT NULL,
  `possibly_sensitive` tinyint(1) DEFAULT NULL,
  `user_mentions` tinytext,
  `hashtags` tinytext,
  `urls` tinytext,
  `iso_language_code` varchar(5) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `user_id` (`from_user_id`),
  KEY `aid` (`aid`),
  KEY `checked_mentions_retweets` (`checked`),
  KEY `in_reply_to_status_id` (`in_reply_to_status_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Structure de la table `users`
--

CREATE TABLE IF NOT EXISTS `users` (
  `id` int(15) NOT NULL,
  `screen_name` varchar(32) NOT NULL,
  `way_to_seed` text NOT NULL,
  `distance_to_seed` int(11) NOT NULL,
  `date_insert` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `last_update` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `last_status` bigint(25) NOT NULL,
  `last_get_favourites` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `last_favourite` bigint(25) NOT NULL DEFAULT '0',
  `last_put` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `last_get` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `last_put_links` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `last_get_links` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Structure de la table `user_profiles`
--

CREATE TABLE IF NOT EXISTS `user_profiles` (
  `aid` int(15) NOT NULL AUTO_INCREMENT,
  `screen_name` varchar(32) NOT NULL,
  `id` int(15) DEFAULT '0',
  `date_insert` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `created_at` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `name` varchar(32) DEFAULT NULL,
  `description` tinytext,
  `protected` tinyint(1) DEFAULT '0',
  `contributors_enabled` tinyint(1) DEFAULT NULL,
  `default_profile` tinyint(1) DEFAULT NULL,
  `verified` tinyint(1) DEFAULT NULL,
  `geo_enable` tinyint(1) DEFAULT NULL,
  `is_translator` tinyint(1) DEFAULT NULL,
  `profile_background_tile` tinyint(1) DEFAULT NULL,
  `profile_use_background_image` tinyint(1) DEFAULT NULL,
  `profile_background_image_url` tinytext,
  `default_profile_image` tinyint(1) DEFAULT NULL,
  `location` varchar(64) DEFAULT NULL,
  `time_zone` tinytext,
  `statuses_count` int(11) DEFAULT NULL,
  `followers_count` int(11) DEFAULT NULL,
  `friends_count` int(11) DEFAULT NULL,
  `listed_count` int(11) DEFAULT NULL,
  `status_text` tinytext,
  `profile_link_color` varchar(10) DEFAULT NULL,
  `follow_request_sent` tinyint(1) DEFAULT NULL,
  `notifications` tinyint(1) DEFAULT NULL,
  `following` tinyint(1) DEFAULT NULL,
  `utc_offset` int(5) DEFAULT NULL,
  `profile_text_color` varchar(5) DEFAULT NULL,
  `profile_sidebar_border_color` varchar(5) DEFAULT NULL,
  `profile_image_url` varchar(50) DEFAULT NULL,
  `url` varchar(50) DEFAULT NULL,
  `profile_sidebar_fill_color` varchar(5) DEFAULT NULL,
  `profile_image_url_http` varchar(50) DEFAULT NULL,
  `favourites_count` int(5) DEFAULT NULL,
  `lang` char(5) DEFAULT NULL,
  PRIMARY KEY (`aid`),
  KEY `id` (`id`),
  KEY `check_id` (`id`),
  KEY `check_foreign_id` (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8;
