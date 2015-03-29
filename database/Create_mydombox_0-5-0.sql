-- phpMyAdmin SQL Dump
-- version 4.0.4
-- http://www.phpmyadmin.net
--
-- Client: localhost
-- Généré le: Mer 04 Mars 2015 à 14:29
-- Version du serveur: 5.6.12-log
-- Version de PHP: 5.4.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Base de données: `mydombox`
--
CREATE DATABASE IF NOT EXISTS `mydombox` DEFAULT CHARACTER SET latin1 COLLATE latin1_swedish_ci;
USE `mydombox`;

-- --------------------------------------------------------

--
-- Structure de la table `database_version`
--

DROP TABLE IF EXISTS `database_version`;
CREATE TABLE IF NOT EXISTS `database_version` (
  `db_version` varchar(20) NOT NULL,
  `db_info_date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `db_info_desc` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`db_version`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Structure de la table `devices`
--

DROP TABLE IF EXISTS `devices`;
CREATE TABLE IF NOT EXISTS `devices` (
  `dc_id` int(4) NOT NULL,
  `dc_name` char(24) DEFAULT NULL,
  `last_update` datetime NOT NULL,
  `packettype` varchar(4) NOT NULL,
  `subtype` varchar(2) NOT NULL,
  `int_id` tinyint(3) unsigned NOT NULL,
  `address` varchar(128) NOT NULL,
  `id1` varchar(2) NOT NULL,
  `id2` varchar(2) NOT NULL,
  `id3` varchar(2) NOT NULL,
  `id4` varchar(2) NOT NULL,
  `unitcode` varchar(2) NOT NULL,
  `groupcode` varchar(2) NOT NULL,
  `housecode` varchar(2) NOT NULL,
  `com` enum('rx','tx','xx') NOT NULL DEFAULT 'rx',
  `enable` tinyint(1) NOT NULL DEFAULT '1',
  `new` tinyint(1) NOT NULL DEFAULT '1',
  `deleted` tinyint(1) NOT NULL DEFAULT '0',
  `home_screen` tinyint(1) NOT NULL DEFAULT '1',
  `home_data1` double(8,2) DEFAULT NULL,
  `home_data2` double(8,2) DEFAULT NULL,
  `home_data3` float(5,2) DEFAULT NULL,
  `iss_status` tinyint(4) NOT NULL DEFAULT '0',
  `iss_stream` char(32) NOT NULL,
  PRIMARY KEY (`dc_id`),
  UNIQUE KEY `device` (`int_id`,`address`,`id1`,`id2`,`id3`,`id4`,`unitcode`,`groupcode`,`housecode`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Structure de la table `energy`
--

DROP TABLE IF EXISTS `energy`;
CREATE TABLE IF NOT EXISTS `energy` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `dc_id` int(4) NOT NULL,
  `datetime` datetime DEFAULT NULL,
  `count` int(11) DEFAULT NULL,
  `instant` int(11) DEFAULT NULL,
  `total` int(11) DEFAULT NULL,
  `ch1` float(5,2) DEFAULT NULL,
  `ch2` float(5,2) DEFAULT NULL,
  `ch3` float(5,2) DEFAULT NULL,
  `battery` int(11) DEFAULT NULL,
  `signal_level` int(11) DEFAULT NULL,
  `processed` int(1) DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `dc_id` (`dc_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=137060 ;

-- --------------------------------------------------------

--
-- Structure de la table `energy_edf`
--

DROP TABLE IF EXISTS `energy_edf`;
CREATE TABLE IF NOT EXISTS `energy_edf` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `dc_id` smallint(5) unsigned NOT NULL,
  `datetime` datetime NOT NULL,
  `optarif` varchar(4) NOT NULL,
  `isousc` tinyint(3) unsigned DEFAULT NULL,
  `hchp` int(10) unsigned DEFAULT NULL,
  `hchc` int(10) unsigned DEFAULT NULL,
  `ptec` varchar(4) NOT NULL,
  `iinst` smallint(5) unsigned DEFAULT NULL,
  `iinst1` smallint(5) unsigned DEFAULT NULL,
  `iinst2` smallint(5) unsigned DEFAULT NULL,
  `iinst3` smallint(5) unsigned DEFAULT NULL,
  `imax` smallint(5) unsigned DEFAULT NULL,
  `imax1` smallint(5) unsigned DEFAULT NULL,
  `imax2` smallint(5) unsigned DEFAULT NULL,
  `imax3` smallint(5) unsigned DEFAULT NULL,
  `pmax` smallint(5) unsigned DEFAULT NULL,
  `papp` smallint(5) unsigned DEFAULT NULL,
  `hphc` varchar(1) NOT NULL,
  `motdetat` varchar(6) NOT NULL,
  `ppot` varchar(2) NOT NULL,
  `adps` smallint(5) unsigned DEFAULT NULL,
  `adir1` smallint(5) unsigned DEFAULT NULL,
  `adir2` smallint(5) unsigned DEFAULT NULL,
  `adir3` smallint(5) unsigned DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `dc_id` (`dc_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=9260 ;

-- --------------------------------------------------------

--
-- Structure de la table `interfaces`
--

DROP TABLE IF EXISTS `interfaces`;
CREATE TABLE IF NOT EXISTS `interfaces` (
  `int_id` tinyint(3) unsigned NOT NULL,
  `int_name` varchar(16) NOT NULL,
  UNIQUE KEY `int_id` (`int_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Structure de la table `network`
--

DROP TABLE IF EXISTS `network`;
CREATE TABLE IF NOT EXISTS `network` (
  `hostname` varchar(32) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Structure de la table `parameters`
--

DROP TABLE IF EXISTS `parameters`;
CREATE TABLE IF NOT EXISTS `parameters` (
  `name` text CHARACTER SET utf8 NOT NULL,
  `value` text CHARACTER SET utf8 NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Structure de la table `scenario`
--

DROP TABLE IF EXISTS `scenario`;
CREATE TABLE IF NOT EXISTS `scenario` (
  `pg_id` int(11) NOT NULL AUTO_INCREMENT,
  `sc_id` int(11) NOT NULL,
  `sc_day` int(11) NOT NULL,
  `sc_periode_start` time NOT NULL,
  `sc_periode_stop` time NOT NULL,
  `tp_prog` int(11) NOT NULL,
  PRIMARY KEY (`pg_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=10 ;

-- --------------------------------------------------------

--
-- Structure de la table `scenario_info`
--

DROP TABLE IF EXISTS `scenario_info`;
CREATE TABLE IF NOT EXISTS `scenario_info` (
  `sc_id` int(11) NOT NULL AUTO_INCREMENT,
  `th_id` int(11) NOT NULL,
  `sc_type` enum('daily','weekly') NOT NULL DEFAULT 'daily',
  `sc_name` varchar(32) NOT NULL,
  UNIQUE KEY `sc_id` (`sc_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=5 ;

-- --------------------------------------------------------

--
-- Structure de la table `state`
--

DROP TABLE IF EXISTS `state`;
CREATE TABLE IF NOT EXISTS `state` (
  `dc_id` int(4) NOT NULL,
  `datetime` datetime NOT NULL,
  `device_mode` varchar(32) NOT NULL,
  `dim_level` varchar(2) DEFAULT NULL,
  `signal_level` int(11) DEFAULT NULL,
  `processed` int(1) NOT NULL DEFAULT '0',
  UNIQUE KEY `dc_id` (`dc_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Structure de la table `temperature`
--

DROP TABLE IF EXISTS `temperature`;
CREATE TABLE IF NOT EXISTS `temperature` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `dc_id` int(4) NOT NULL,
  `datetime` datetime DEFAULT NULL,
  `seqnbr` varchar(2) DEFAULT NULL,
  `temperature` float(5,2) DEFAULT NULL,
  `temperature_set` float(5,2) DEFAULT NULL,
  `mode` varchar(8) DEFAULT NULL,
  `status` varchar(10) DEFAULT NULL,
  `signal_level` int(11) DEFAULT NULL,
  `processed` int(1) DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `dc_id` (`dc_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=22914 ;

-- --------------------------------------------------------

--
-- Structure de la table `thermostat`
--

DROP TABLE IF EXISTS `thermostat`;
CREATE TABLE IF NOT EXISTS `thermostat` (
  `th_id` int(4) NOT NULL,
  `sensor_id` int(4) NOT NULL,
  `recept_id` int(4) NOT NULL,
  `th_name` varchar(20) NOT NULL,
  `th_use` enum('on','off') NOT NULL,
  `th_mode` enum('manual','auto') NOT NULL,
  `tp_set` float(5,2) NOT NULL,
  `sc_id` int(11) DEFAULT NULL,
  `home_screen` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`th_id`),
  UNIQUE KEY `sensor_id` (`sensor_id`,`recept_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Structure de la table `type`
--

DROP TABLE IF EXISTS `type`;
CREATE TABLE IF NOT EXISTS `type` (
  `type_id` smallint(5) unsigned NOT NULL,
  `int_id` tinyint(4) unsigned NOT NULL,
  `packettype` varchar(4) NOT NULL,
  `packetdescription` varchar(100) NOT NULL,
  `subtype` varchar(2) NOT NULL,
  `subdescription` varchar(100) NOT NULL,
  PRIMARY KEY (`type_id`),
  UNIQUE KEY `packettype` (`packettype`,`subtype`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Structure de la table `weather`
--

DROP TABLE IF EXISTS `weather`;
CREATE TABLE IF NOT EXISTS `weather` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `dc_id` int(4) NOT NULL,
  `datetime` datetime DEFAULT NULL,
  `seqnbr` varchar(2) DEFAULT NULL,
  `temperature` float(5,2) DEFAULT NULL,
  `humidity` int(11) DEFAULT NULL,
  `humidity_status` varchar(16) DEFAULT NULL,
  `barometric` int(11) DEFAULT NULL,
  `forecast` int(11) DEFAULT NULL,
  `rainrate` float(5,2) DEFAULT NULL,
  `raintotal` double(6,2) DEFAULT NULL,
  `winddirection` int(11) DEFAULT NULL,
  `av_speed` int(11) DEFAULT NULL,
  `windchill` float(5,2) DEFAULT NULL,
  `gust` int(11) DEFAULT NULL,
  `uv` int(11) DEFAULT NULL,
  `battery` int(11) DEFAULT NULL,
  `signal_level` int(11) DEFAULT NULL,
  `processed` int(1) DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `dc_id` (`dc_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=3 ;

INSERT INTO database_version VALUES ('0.5.0',now(), 'Creation_mydombox_0-5-0.sql');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
