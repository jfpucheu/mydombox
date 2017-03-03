-- MySQL dump 10.13  Distrib 5.6.24, for osx10.8 (x86_64)
--
-- Host: localhost    Database: mydombox
-- ------------------------------------------------------
-- Server version	5.6.24

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

DROP DATABASE IF EXISTS `mydombox`;
CREATE DATABASE `mydombox`;
USE `mydombox`;

--
-- Table structure for table `database_version`
--

DROP TABLE IF EXISTS `database_version`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `database_version` (
  `db_version` varchar(20) NOT NULL,
  `db_info_date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `db_info_desc` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`db_version`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `devices`
--

DROP TABLE IF EXISTS `devices`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `devices` (
  `dc_id` int(4) NOT NULL,
  `dc_name` char(24) DEFAULT NULL,
  `last_update` datetime NOT NULL,
  `packettype` varchar(4) NOT NULL,
  `subtype` varchar(2) NOT NULL,
  `type` varchar(2) NOT NULL,
  `int_id` tinyint(3) unsigned NOT NULL,
  `address` varchar(127) NOT NULL,
  `id1` varchar(2) NOT NULL,
  `id2` varchar(2) NOT NULL,
  `id3` varchar(2) NOT NULL,
  `id4` varchar(2) NOT NULL,
  `unitcode` varchar(2) NOT NULL,
  `groupcode` varchar(2) NOT NULL,
  `housecode` varchar(2) NOT NULL,
  `com` enum('rx','tx','xx') NOT NULL DEFAULT 'rx',
  `reverse` tinyint(1) NOT NULL DEFAULT '0',
  `enable` tinyint(1) NOT NULL DEFAULT '1',
  `new` tinyint(1) NOT NULL DEFAULT '1',
  `deleted` tinyint(1) NOT NULL DEFAULT '0',
  `home_screen` tinyint(1) NOT NULL DEFAULT '1',
  `home_data1` double(8,2) DEFAULT NULL,
  `home_data2` double(8,2) DEFAULT NULL,
  `home_data3` double(8,2) DEFAULT NULL,
  `iss_status` tinyint(4) NOT NULL DEFAULT '0',
  `iss_stream` char(32) NOT NULL DEFAULT '',
  `dc_logo` varchar(32) DEFAULT NULL,
  PRIMARY KEY (`dc_id`),
  UNIQUE KEY `device` (`int_id`,`address`,`id1`,`id2`,`id3`,`id4`,`unitcode`,`groupcode`,`housecode`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `energy`
--

DROP TABLE IF EXISTS `energy`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `energy` (
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
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `energy_edf`
--

DROP TABLE IF EXISTS `energy_edf`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `energy_edf` (
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
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `interfaces`
--

DROP TABLE IF EXISTS `interfaces`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `interfaces` (
  `int_id` tinyint(3) unsigned NOT NULL,
  `int_name` varchar(16) NOT NULL,
  UNIQUE KEY `int_id` (`int_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `network`
--

DROP TABLE IF EXISTS `network`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `network` (
  `hostname` varchar(32) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `parameters`
--

DROP TABLE IF EXISTS `parameters`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `parameters` (
  `name` text CHARACTER SET utf8 NOT NULL,
  `value` text CHARACTER SET utf8 NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `scenario`
--

DROP TABLE IF EXISTS `scenario`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `scenario` (
  `pg_id` int(11) NOT NULL AUTO_INCREMENT,
  `sc_id` int(11) NOT NULL,
  `sc_day` int(11) NOT NULL,
  `sc_periode_start` time NOT NULL,
  `sc_periode_stop` time NOT NULL,
  `tp_prog` int(11) NOT NULL,
  PRIMARY KEY (`pg_id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `scenario_info`
--

DROP TABLE IF EXISTS `scenario_info`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `scenario_info` (
  `sc_id` int(11) NOT NULL AUTO_INCREMENT,
  `th_id` int(11) NOT NULL,
  `sc_type` enum('daily','weekly') NOT NULL DEFAULT 'daily',
  `sc_name` varchar(32) NOT NULL,
  UNIQUE KEY `sc_id` (`sc_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `scheduler`
--

DROP TABLE IF EXISTS `scheduler`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `scheduler` (
  `sch_id` int(11) NOT NULL AUTO_INCREMENT,
  `dc_id` int(11) NOT NULL,
  `sch_day` tinyint(4) NOT NULL,
  `sch_time` time NOT NULL,
  `sch_action` varchar(8) CHARACTER SET utf8 NOT NULL,
  PRIMARY KEY (`sch_id`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `state`
--

DROP TABLE IF EXISTS `state`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `state` (
  `dc_id` int(4) NOT NULL,
  `datetime` datetime NOT NULL,
  `device_mode` varchar(32) NOT NULL,
  `dim_level` varchar(2) DEFAULT NULL,
  `signal_level` int(11) DEFAULT NULL,
  `processed` int(1) NOT NULL DEFAULT '0',
  UNIQUE KEY `dc_id` (`dc_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `temperature`
--

DROP TABLE IF EXISTS `temperature`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `temperature` (
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
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `thermostat`
--

DROP TABLE IF EXISTS `thermostat`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `thermostat` (
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
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `type`
--

DROP TABLE IF EXISTS `type`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `type` (
  `type_id` smallint(5) unsigned NOT NULL,
  `int_id` tinyint(4) unsigned NOT NULL,
  `packettype` varchar(4) NOT NULL,
  `packetdescription` varchar(100) NOT NULL,
  `subtype` varchar(2) NOT NULL,
  `type` varchar(2) NOT NULL,
  `subdescription` varchar(100) NOT NULL,
  PRIMARY KEY (`type_id`),
  UNIQUE KEY `type` (`int_id`,`packettype`,`subtype`,`type`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `weather`
--

DROP TABLE IF EXISTS `weather`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `weather` (
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
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

INSERT INTO database_version VALUES ('0.6.3',now(), 'Creation_mydombox_0-6-3.sql');

/*!40101 SET character_set_client = @saved_cs_client */;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2016-01-10 10:55:37
