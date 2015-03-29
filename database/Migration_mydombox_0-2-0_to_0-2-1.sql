use mydombox;
#[G00R02C01]
ALTER TABLE `thermostat` CHANGE `home_screen` `home_screen` TINYINT( 1 ) NOT NULL DEFAULT '1';

ALTER TABLE `scenario_info` ADD `sc_type` ENUM( 'daily', 'weekly' ) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT 'daily' AFTER `th_id` ;
ALTER TABLE `scenario_info` CHANGE `sc_id` `sc_id` INT( 11 ) NOT NULL AUTO_INCREMENT ;

INSERT INTO database_version VALUES ('0.2.1',now(), 'Migation_mydombox_0-2-0_to_0-2-1.sql');