USE `mydombox`;

INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('10', 'Lighting 1', '00','X10 lighting','', '', '1','1');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('10', 'Lighting 1', '01','ARC','', '', '1','1');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('10', 'Lighting 1', '02','ELRO AB400D (Flamingo)','', '', '1','1');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('10', 'Lighting 1', '03','Waveman','', '', '1','1');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('10', 'Lighting 1', '04','Chacon EMW200','', '', '1','1');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('10', 'Lighting 1', '05','IMPULS','', '', '1','1');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('10', 'Lighting 1', '06','RisingSun','', '', '1','1');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('10', 'Lighting 1', '07','Philips SBC','', '', '1','1');

INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('11', 'Lighting 2', '00','AC,Chacon,DIO','4', '', '','1');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('11', 'Lighting 2', '01','HomeEasy EU','4', '', '','1');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('11', 'Lighting 2', '02','ANSLUT','4', '', '','1');

INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('40', 'Thermostat 1', '00','Digimax, TLX7506','2', '', '','');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('40', 'Thermostat 1', '01','Digimax with short format','2', '', '','');

INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('41', 'Thermostat 2', '00','HomeEasy HE105','', '', '','1');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('41', 'Thermostat 2', '01','RTS10, RFS10, TLX1206','', '', '','1');

INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('50', 'Temperature sensors', '01','THR128/138, THC138','2', '', '','');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('50', 'Temperature sensors', '02','THC238/268,THN132,THWR288,THRN122,THN122,AW129/131','2', '', '','');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('50', 'Temperature sensors', '03','THWR800','2', '', '','');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('50', 'Temperature sensors', '04','RTHN318','2', '', '','');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('50', 'Temperature sensors', '05','La Crosse TX3, TX4, TX17','2', '', '','');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('50', 'Temperature sensors', '06','TS15C','2', '', '','');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('50', 'Temperature sensors', '07','Viking 02811','2', '', '','');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('50', 'Temperature sensors', '08','La Crosse WS2300','2', '', '','');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('50', 'Temperature sensors', '09','RUBiCSON','2', '', '','');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('50', 'Temperature sensors', '0A','TFA 30.3133','2', '', '','');

INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('51', 'Humidity sensors', '01','LaCrosse TX3','2', '', '','');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('51', 'Humidity sensors', '02','LaCrosse WS2300','2', '', '','');

INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('52', 'Temperature and humidity sensors', '01','THGN122/123, THGN132, THGR122/228/238/268','2', '', '','');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('52', 'Temperature and humidity sensors', '02','THGR810, THGN800','2', '', '','');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('52', 'Temperature and humidity sensors', '03','RTGR328','2', '', '','');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('52', 'Temperature and humidity sensors', '04','THGR328','2', '', '','');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('52', 'Temperature and humidity sensors', '05','WTGR800','2', '', '','');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('52', 'Temperature and humidity sensors', '06','THGR918, THGRN228, THGN50','2', '', '','');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('52', 'Temperature and humidity sensors', '07','TFA TS34C, Cresta','2', '', '','');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('52', 'Temperature and humidity sensors', '08','WT260,WT260H,WT440H,WT450,WT450H','2', '', '','');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('52', 'Temperature and humidity sensors', '09','Viking 02035, 02038','2', '', '','');

INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('53', 'Barometric sensors', '01','Reserved for future use','2', '', '','');

INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('54', 'Temperature, humidity and barometric sensors', '01','BTHR918','2', '', '','');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('54', 'Temperature, humidity and barometric sensors', '02','BTHR918N, BTHR968','2', '', '','');

INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('55', 'Rain sensors', '01','RGR126/682/918','2', '', '','');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('55', 'Rain sensors', '02','PCR800','2', '', '','');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('55', 'Rain sensors', '03','TFA','2', '', '','');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('55', 'Rain sensors', '04','UPM RG700','2', '', '','');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('55', 'Rain sensors', '05','WS2300','2', '', '','');

INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('56', 'Wind sensors', '01','WTGR800','2', '', '','');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('56', 'Wind sensors', '02','WGR800','2', '', '','');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('56', 'Wind sensors', '03','STR918, WGR918','2', '', '','');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('56', 'Wind sensors', '04','TFA (WIND4)','2', '', '','');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('56', 'Wind sensors', '05','UPM WDS500','2', '', '','');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('56', 'Wind sensors', '06','WS2300','2', '', '','');

INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('57', 'UV sensors', '01','UVN128, UV138','2', '', '','');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('57', 'UV sensors', '02','UVN800','2', '', '','');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('57', 'UV sensors', '03','TFA','2', '', '','');

INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('58', 'Date/Time sensors', '01','RTGR328N','2', '', '','');

INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('59', 'Current sensors', '01','CM113, Electrisave','2', '', '','');

INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('5A', 'Energy usage sensors', '01','CM119/160','2', '', '','');
INSERT IGNORE INTO type (packettype, packetdescription, subtype,subdescription,id_nb,groupcode_nb,housecode_nb,unitcode_nb) VALUES ('5A', 'Energy usage sensors', '02','CM180','2', '', '','');
