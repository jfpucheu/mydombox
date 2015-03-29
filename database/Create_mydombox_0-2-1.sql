-- phpMyAdmin SQL Dump
-- version 4.0.4
-- http://www.phpmyadmin.net
--
-- Client: localhost
-- Généré le: Dim 08 Décembre 2013 à 11:17
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
CREATE DATABASE IF NOT EXISTS `mydombox` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;
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
  `packettype` varchar(2) NOT NULL,
  `subtype` varchar(2) NOT NULL,
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
  PRIMARY KEY (`dc_id`),
  UNIQUE KEY `id1` (`id1`,`id2`,`id3`,`id4`,`unitcode`,`groupcode`,`housecode`)
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
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=0 ;

-- --------------------------------------------------------

--
-- Structure de la table `lighting`
--

DROP TABLE IF EXISTS `lighting`;
CREATE TABLE IF NOT EXISTS `lighting` (
  `dc_id` int(4) NOT NULL,
  `datetime` datetime NOT NULL,
  `light_mode` enum('off','on','Set level','Group Off','Group On','Set Group level') NOT NULL,
  `dim_level` varchar(2) DEFAULT NULL,
  `signal_level` int(11) DEFAULT NULL,
  `processed` int(1) NOT NULL DEFAULT '0',
  UNIQUE KEY `dc_id` (`dc_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

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
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=0 ;

-- --------------------------------------------------------

--
-- Structure de la table `scenario_info`
--

DROP TABLE IF EXISTS `scenario_info`;
CREATE TABLE IF NOT EXISTS `scenario_info` (
  `sc_id` int(11) NOT NULL,
  `th_id` int(11) NOT NULL,
  `sc_name` varchar(32) NOT NULL,
  UNIQUE KEY `sc_id` (`sc_id`)
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
  KEY `id` (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=0 ;

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
  `home_screen` TINYINT( 1 ) NOT NULL DEFAULT '1',
  PRIMARY KEY (`th_id`),
  UNIQUE KEY `sensor_id` (`sensor_id`,`recept_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Structure de la table `type`
--

DROP TABLE IF EXISTS `type`;
CREATE TABLE IF NOT EXISTS `type` (
  `type_id` int(4) NOT NULL AUTO_INCREMENT,
  `packettype` varchar(2) NOT NULL,
  `packetdescription` varchar(100) NOT NULL,
  `subtype` varchar(2) NOT NULL,
  `subdescription` varchar(100) NOT NULL,
  `id_nb` int(4) NOT NULL,
  `groupcode_nb` int(4) NOT NULL,
  `housecode_nb` int(4) NOT NULL,
  `unitcode_nb` int(4) NOT NULL,
  PRIMARY KEY (`type_id`),
  UNIQUE KEY `packettype` (`packettype`,`subtype`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=0 ;

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
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=0 ;

INSERT INTO database_version VALUES ('0.2.1',now(), 'Create_mydombox_0-2-1');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
