use mydombox;
#[0.2.1]
#ALTER TABLE `thermostat` CHANGE `home_screen` `home_screen` TINYINT( 1 ) NOT NULL DEFAULT '1';

#ALTER TABLE `scenario_info` ADD `sc_type` ENUM( 'daily', 'weekly' ) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT 'daily' AFTER `th_id` ;
#ALTER TABLE `scenario_info` CHANGE `sc_id` `sc_id` INT( 11 ) NOT NULL AUTO_INCREMENT ;

#INSERT INTO database_version VALUES ('0.2.1',now(), 'Migation_mydombox_0-2-0_to_0-2-1.sql');

#[0.3.0]

#CREATE TABLE IF NOT EXISTS `energy_edf` (
#  `dc_id` smallint(5) unsigned NOT NULL,
#  `datetime` datetime NOT NULL,
#  `optarif` varchar(4) NOT NULL,
#  `isousc` tinyint(3) unsigned DEFAULT NULL,
#  `hchp` int(10) unsigned DEFAULT NULL,
#  `hchc` int(10) unsigned DEFAULT NULL,
#  `ptec` varchar(4) NOT NULL,
#  `iinst` smallint(5) unsigned DEFAULT NULL,
#  `iinst1` smallint(5) unsigned DEFAULT NULL,
#  `iinst2` smallint(5) unsigned DEFAULT NULL,
#  `iinst3` smallint(5) unsigned DEFAULT NULL,
#  `imax` smallint(5) unsigned DEFAULT NULL,
#  `imax1` smallint(5) unsigned DEFAULT NULL,
#  `imax2` smallint(5) unsigned DEFAULT NULL,
#  `imax3` smallint(5) unsigned DEFAULT NULL,
#  `pmax` smallint(5) unsigned DEFAULT NULL,
#  `papp` smallint(5) unsigned DEFAULT NULL,
#  `hphc` varchar(1) NOT NULL,
#  `motdetat` varchar(6) NOT NULL,
#  `ppot` varchar(2) NOT NULL,
#  `adps` smallint(5) unsigned DEFAULT NULL,
#  `adir1` smallint(5) unsigned DEFAULT NULL,
#  `adir2` smallint(5) unsigned DEFAULT NULL,
#  `adir3` smallint(5) unsigned DEFAULT NULL
#) ENGINE=InnoDB DEFAULT CHARSET=utf8;

#CREATE TABLE IF NOT EXISTS `interfaces` (
#  `int_id` tinyint(3) unsigned NOT NULL,
#  `int_name` varchar(16) NOT NULL,
#  UNIQUE KEY `int_id` (`int_id`)
#) ENGINE=InnoDB DEFAULT CHARSET=utf8;

#INSERT INTO `mydombox`.`interfaces` (`int_id`, `int_name`) VALUES ('1', 'rfxtrx433'), ('2', 'rpidom');

#ALTER TABLE `devices` CHANGE `packettype` `packettype` VARCHAR( 4 ) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL ;

#ALTER TABLE `devices` ADD `int_id` TINYINT UNSIGNED NOT NULL AFTER `subtype` , ADD `address` VARCHAR( 16 ) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL AFTER `int_id` ;

#ALTER TABLE `type` CHANGE `packettype` `packettype` VARCHAR( 4 ) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL ;
#ALTER TABLE `type` CHANGE `type_id` `type_id` SMALLINT UNSIGNED NOT NULL ;
#ALTER TABLE `type` ADD `int_id` TINYINT NOT NULL AFTER `type_id` ;
#ALTER TABLE `type` CHANGE `int_id` `int_id` TINYINT( 4 ) UNSIGNED NOT NULL ;

#DROP TABLE `type`;

#CREATE TABLE IF NOT EXISTS `type` (
#  `type_id` smallint(5) unsigned NOT NULL,
#  `int_id` tinyint(4) unsigned NOT NULL,
#  `packettype` varchar(4) NOT NULL,
#  `packetdescription` varchar(100) NOT NULL,
#  `subtype` varchar(2) NOT NULL,
#  `subdescription` varchar(100) NOT NULL,
#  PRIMARY KEY (`type_id`),
#  UNIQUE KEY `packettype` (`packettype`,`subtype`)
#) ENGINE=InnoDB DEFAULT CHARSET=utf8;

#UPDATE `mydombox`.`devices` SET `int_id` = '1';

#ALTER TABLE `mydombox`.`devices` DROP INDEX `id1` , ADD UNIQUE `device` (`int_id`, `address` , `id1` , `id2` , `id3` , `id4` , `unitcode` , `groupcode` , `housecode` ) COMMENT '';

#ALTER TABLE `weather` ADD INDEX ( `dc_id` );

#DROP INDEX id ON temperature;
#ALTER TABLE `temperature` ADD INDEX ( `dc_id` );

#ALTER TABLE `energy` ADD INDEX ( `dc_id` );
#ALTER TABLE `energy_edf` ADD INDEX ( `dc_id` );

#ALTER TABLE `energy_edf` ADD `id` INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY FIRST ;

#ALTER TABLE `devices` ADD `last_update` DATETIME NOT NULL AFTER `dc_name` ;
#ALTER TABLE `devices` ADD `home_data1` FLOAT NULL , ADD `home_data2` FLOAT NULL , ADD `home_data3` FLOAT NULL ;
#ALTER TABLE `devices` CHANGE `home_data1` `home_data1` FLOAT( 5, 2 ) NULL DEFAULT NULL , CHANGE `home_data2` `home_data2` FLOAT( 5, 2 ) NULL DEFAULT NULL , CHANGE `home_data3` `home_data3` FLOAT( 5, 2 ) NULL DEFAULT NULL ;

#INSERT INTO database_version VALUES ('0.3.0',now(), 'Migation_mydombox_0-2-1_to_0-3-0.sql');

#[0.4.0]

#ALTER TABLE `devices` ADD `m2x_status` TINYINT NOT NULL DEFAULT '0',
#ADD `m2x_name` CHAR( 24 ) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL ;

#INSERT INTO database_version VALUES ('0.4.0',now(), 'Migation_mydombox_0-3-0_to_0-4-0.sql');

#[0.5.0]
#ALTER TABLE `lighting` CHANGE `light_mode` `light_mode` VARCHAR( 32 ) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL ;
#ALTER TABLE `lighting` CHANGE `light_mode` `device_mode` VARCHAR( 32 ) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL ;
#RENAME TABLE `lighting` TO `state`;

#ALTER TABLE `devices` CHANGE `address` `address` VARCHAR( 127 ) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL ;
#ALTER TABLE `devices` CHANGE `home_data1` `home_data1` DOUBLE( 8, 2 ) NULL DEFAULT NULL ;
#ALTER TABLE `devices` CHANGE `home_data2` `home_data2` DOUBLE( 8, 2 ) NULL DEFAULT NULL ;
#ALTER TABLE `devices` CHANGE `home_data3` `home_data3` DOUBLE( 8, 2 ) NULL DEFAULT NULL ;

#ALTER TABLE `devices` CHANGE `m2x_status` `iss_status` TINYINT( 4 ) NOT NULL DEFAULT '0',CHANGE `m2x_name` `iss_stream` CHAR( 32 ) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL ;

#CREATE TABLE `scheduler` (
#`sch_id` int(11) NOT NULL,
#  `dc_id` int(11) NOT NULL,
#  `sch_day` tinyint(4) NOT NULL,
#  `sch_time` time NOT NULL,
#  `sch_action` varchar(8) CHARACTER SET utf8 NOT NULL
#) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

#ALTER TABLE `scheduler` ADD PRIMARY KEY (`sch_id`);
#ALTER TABLE `scheduler` MODIFY `sch_id` int(11) NOT NULL AUTO_INCREMENT;

#ALTER TABLE `devices` ADD `type` VARCHAR( 2 ) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL AFTER `subtype` ;
#ALTER TABLE `type` ADD `type` VARCHAR( 2 ) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL AFTER `subtype` ;

#ALTER TABLE `mydombox`.`type` DROP INDEX `packettype` , ADD UNIQUE `type` (`int_id`,`packettype`,`subtype`, `type`) COMMENT '';
#ALTER TABLE `devices` MODIFY COLUMN iss_stream char(32)  NOT NULL DEFAULT '';

#INSERT INTO database_version VALUES ('0.5.0',now(), 'Migation_mydombox_0-4-0_to_0-5-0.sql');

#[0.6.0]

#ALTER TABLE devices ADD dc_logo VARCHAR(32) AFTER iss_stream;
#UPDATE devices SET dc_logo="mdb_thermometre.png" WHERE packettype="50";
#UPDATE devices SET dc_logo="mdb_thermo_humi.png" WHERE packettype="52";
#UPDATE devices SET dc_logo="mdb_pluie.png" WHERE packettype="55";
#UPDATE devices SET dc_logo="mdb_vent.png" WHERE packettype="56";
#UPDATE devices SET dc_logo="mdb_light.png" WHERE packettype="11";
#UPDATE devices SET dc_logo="mdb_chroma.png" WHERE packettype="14";
#UPDATE devices SET dc_logo="mdb_volet.png" WHERE packettype="1A";
#UPDATE devices SET dc_logo="mdb_elec.png" WHERE packettype="5A";
#UPDATE devices SET dc_logo="mdb_thermometre.png" WHERE packettype="40";
#UPDATE devices SET dc_logo="mdb_elec.png" WHERE packettype="ERDF";
#UPDATE devices SET dc_logo="mdb_thermometre.png" WHERE packettype="1W28";
#UPDATE devices SET dc_logo="mdb_elec.png" WHERE packettype="WP";

#[0.6.1]
#ALTER TABLE devices ADD reverse TINYINT(2) NOT NULL DEFAULT 0 AFTER com;
#INSERT INTO database_version VALUES ('0.6.1',now(), 'Migation_mydombox_0-6-0_to_0-6-1.sql');

#[0.6.2]
INSERT INTO database_version VALUES ('0.6.2',now(), 'Migation_mydombox_0-6-1_to_0-6-2.sql');