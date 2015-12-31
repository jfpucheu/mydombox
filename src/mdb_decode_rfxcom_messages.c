/* decode_rfxcom_messages.c */

/*
'------------------------------------------------------------------------------------
' Protocol License Agreement
'
' The RFXtrx protocols are owned by RFXCOM, and are protected under applicable
' copyright laws.
'
' ==================================================================================
' = It is only allowed to use this software or any part of it for RFXCOM products. =
' ==================================================================================
'
' The above Protocol License Agreement and the permission notice shall be included
' in all software using the RFXtrx protocols.
'
' Any use in violation of the foregoing restrictions may subject the user to criminal
' sanctions under applicable laws, as well as to civil liability for the breach of the
' terms and conditions of this license.
'------------------------------------------------------------------------------------- 
*/

#include <stdlib.h>
#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

#include "mdb_rfxcom_const.h"
#include "mdb_log.h"
#include "mdb_mysql.h"
#include "mdb_dvn.h"
#include "mdb_tools.h"
#include "mdb_structures.h"

#define DB_MYSQL 1

extern int 		MDB_CLOUD;
extern int      RECORD;

void print_device_rfx(RfxDevice variable){
    
    log_DEBUG("[RfxDevice] dc_id = %d ,%d",variable.dc_id,variable.dc_id);
    log_DEBUG("[RfxDevice] packettype = %02hhX",variable.packettype);
    log_DEBUG("[RfxDevice] subtype = %02hhX",variable.subtype);
    log_DEBUG("[RfxDevice] id1 = %02hhX",variable.id1);
    log_DEBUG("[RfxDevice] id2 = %02hhX",variable.id2);
    log_DEBUG("[RfxDevice] id3 = %02hhX",variable.id3);
    log_DEBUG("[RfxDevice] id4 = %02hhX",variable.id4);
    log_DEBUG("[RfxDevice] unitcode = %02hhX",variable.unitcode);
    log_DEBUG("[RfxDevice] enable = %d",variable.enable);
    
}

RfxDevice GetRfxDevice(char* data){
    
    RfxDevice device;
    device.dc_id = 0;
    
    unsigned char		packettype = data[1];
    unsigned char		subtype = data[2];
    unsigned char		id1 = "";
    unsigned char		id2 = "";
    unsigned char		id3 = "";
    unsigned char		id4 = "";
    unsigned char		unitcode = "";
    
    char request[256]= "";
	
    switch (packettype)
    {
        case 0x11:
            id1 = data[4];
            id2 = data[5];
            id3 = data[6];
            id4 = data[7];
            unitcode = data[8];
            sprintf(request,"SELECT dc_id,packettype,subtype,id1,id2,id3,id4,unitcode,enable FROM devices \
                          WHERE int_id=%d AND id1='%02hhX'AND id2='%02hhX'AND id3='%02hhX'AND id4='%02hhX' AND unitcode='%02hhX';",1,id1,id2,id3,id4,unitcode);
            break;
        case 0x14:
        case 0x1A:
            id1 = data[4];
            id2 = data[5];
            id3 = data[6];
            unitcode = data[7];
            sprintf(request,"SELECT dc_id,packettype,subtype,id1,id2,id3,id4,unitcode,enable FROM devices \
                		WHERE int_id=%d AND id1='%02hhX'AND id2='%02hhX'AND id3='%02hhX'AND id4='' AND unitcode='%02hhX';",1,id1,id2,id3,unitcode);
            break;
        case 0x40:
        case 0x5A:
        case 0x52:
        case 0x55:
        case 0x56:
            id1 = data[4];
            id2 = data[5];
            sprintf(request,"SELECT dc_id,packettype,subtype,id1,id2,id3,id4,unitcode,enable FROM devices \
                		WHERE int_id=%d AND id1='%02hhX'AND id2='%02hhX'AND id3=''AND id4='' AND unitcode='';",1,id1,id2);
            break;
        default:
            log_DEBUG("[Rfxcom][GetRfxDevice]: PacketType:'%02hhX' Not Supported",packettype);
			return device;
            break;
    }
    
    MYSQL *conn;
    MYSQL_RES *result;
    MYSQL_ROW row;
    
    conn = mysql_connection();
    result = mysql_select(conn,request);
    
    int num_fields = mysql_num_fields(result);
    if (num_fields != 0) {
        
        while ((row = mysql_fetch_row(result))){
            
            device.dc_id = atoi(row[0]);
            device.packettype = stringtohex(row[1]);
            device.subtype = stringtohex(row[2]);
            device.id1 = stringtohex(row[4]);
            device.id2 = stringtohex(row[5]);
            device.id3 = stringtohex(row[6]);
            device.id4 = stringtohex(row[7]);
            device.unitcode = stringtohex(row[8]);
            device.enable=(bool)row[9];
        }
    }
	mysql_free_result(result);
	mysql_close(conn);
    return device;
}

bool addRfxDevice(char* data){
    unsigned char		packettype = data[1];
    unsigned char		subtype = data[2];
    unsigned char		id1 = "";
    unsigned char		id2 = "";
    unsigned char		id3 = "";
    unsigned char		id4 = "";
    unsigned char		unitcode = "";

    char request[300]= "";
    
    switch (packettype)
    {
        case 0x11:
            id1 = data[4];
            id2 = data[5];
            id3 = data[6];
            id4 = data[7];
            unitcode = data[8];
            sprintf(request,"INSERT IGNORE INTO devices (dc_id,last_update,int_id,packettype,subtype,id1,id2,id3,id4,unitcode,com) \
                     SELECT IFNULL(MAX(dc_id),0)+1,NOW(),1,'%02hhX','%02hhX','%02hhX','%02hhX','%02hhX','%02hhX','%02hhX','tx' FROM devices ON DUPLICATE KEY UPDATE last_update=NOW();",\
                     packettype,subtype,id1,id2,id3,id4,unitcode);
            break;
        case 0x14:
        case 0x1A:
            id1 = data[4];
            id2 = data[5];
            id3 = data[6];
            unitcode = data[7];
            sprintf(request,"INSERT IGNORE INTO devices (dc_id,last_update,int_id,packettype,subtype,id1,id2,id3,id4,unitcode,com) \
                     SELECT IFNULL(MAX(dc_id),0)+1,NOW(),1,'%02hhX','%02hhX','%02hhX','%02hhX','%02hhX','','%02hhX','tx' FROM devices ON DUPLICATE KEY UPDATE last_update=NOW();",\
                     packettype,subtype,id1,id2,id3,unitcode);
            break;
        case 0x40:
        case 0x5A:
        case 0x52:
        case 0x55:
        case 0x56:
            id1 = data[4];
            id2 = data[5];
            sprintf(request,"INSERT IGNORE INTO devices (dc_id,last_update,int_id,packettype,subtype,id1,id2,id3,id4,unitcode,com) \
                     SELECT IFNULL(MAX(dc_id),0)+1,NOW(),1,'%02hhX','%02hhX','%02hhX','%02hhX','','','','tx' FROM devices ON DUPLICATE KEY UPDATE last_update=NOW();",\
                     packettype,subtype,id1,id2,id3,id4,unitcode);
            break;
        default:
            log_DEBUG("[Rfxcom] PacketType: '%02hhX' Not Supported",packettype);
			return 0;
            break;
    }
    
    log_DEBUG("[Rfxcom] Record Mode : %d", RECORD);
    if (RECORD == 1) {
        log_INFO("[Rfxcom][addRfxDevice]: Recording new device type : '%02hhX'",packettype);
        mysql_insert(request);
    }
    return 0;
}

// RFXTRX433 Message Decoding

void message_0X00(){

   	log_DEBUG("Message de type: Interface Control");
	log_DEBUG("Not Suported yet");
}

void message_0X01(char message[255]){

	unsigned char		packettype = message[1];
	unsigned char		subtype	= message[2];
	unsigned char		seqnbr = message[3];
	unsigned char		cmnd = message[4];
	unsigned char		msg1 = message[5];
	unsigned char		msg2 = message[6];
	unsigned char		msg3 = message[7];
	unsigned char		msg4 = message[8];
	unsigned char		msg5 = message[9];
	unsigned char		msg6 = message[8];
	unsigned char		msg7 = message[10];
	unsigned char		msg8 = message[11];
	unsigned char		msg9 = message[12];
	
	char subtype_text[64];
	char cmnd_text[128];
	char receivertype_text[64];
	char message3_text[256];
	char message4_text[256];
	char message5_text[256];

	// Subtype for log
	if ( subtype == 0x00){
		sprintf( subtype_text,"Response on a mode command");
	}
	else if (subtype == 0xFF){
		sprintf( subtype_text,"Wrong command received from the application");
	}
	else{
		sprintf( subtype_text,"Not supported");
	}
	// Cmd
	switch ( cmnd ) {
		case 0x00:
			sprintf( cmnd_text,"Reset the receiver/transceiver. No answer is transmitted!");
			break;
		case 0x01:
			sprintf( cmnd_text,"not used");
			break;
		case 0x02:
			sprintf( cmnd_text,"Get Status, return firmware versions and configuration of the interface");
			break;
		case 0x03:
			sprintf( cmnd_text,"Set Mode msg1-msg5, return also the firmware version and configuration of the interface");
			break;
		case 0x06:
			sprintf( cmnd_text,"save receiving modes of the receiver/transceiver in non-volatile memory");
			break;
		case 0x07:
			sprintf( cmnd_text,"not used");
			break;
		case 0x08:
			sprintf( cmnd_text,"T1 – for internal use by RFXCOM");
			break;
		case 0x09:
			sprintf( cmnd_text,"T2 – for internal use by RFXCOM");
			break;			
		case 0x50:
			sprintf( cmnd_text,"select 310MHz in the 310/315 transceiver");
			break;
		case 0x51:
			sprintf( cmnd_text,"select 315MHz in the 310/315 transceiver");
			break;
		case 0x52:
			sprintf( cmnd_text,"not used");
			break;
		case 0x53:
			sprintf( cmnd_text,"not used");
			break;
		case 0x54:
			sprintf( cmnd_text,"not used");
			break;
		case 0x55:
			sprintf( cmnd_text,"select 868.00MHz in the 868 transceiver");
			break;
		case 0x56:
			sprintf( cmnd_text,"select 868.00MHz FSK in the 868 transceiver");
			break;	
		case 0x57:
			sprintf( cmnd_text,"select 868.30MHz in the 868 transceiver");
			break;
		case 0x58:
			sprintf( cmnd_text,"select 868.30MHz FSK in the 868 transceiver");
			break;
		case 0x59:
			sprintf( cmnd_text,"select 868.35MHz in the 868 transceiver");
			break;
		case 0x5A:
			sprintf( cmnd_text,"select 868.35MHz FSK in the 868 transceiver");
			break;
		case 0x5B:
			sprintf( cmnd_text,"select 868.95MHz in the 868 transceiver");
			break;				
		default:
			sprintf( cmnd_text,"Not Supported");
			break;
	}
	
	switch ( msg1 ) {
		case 0x50:
			sprintf( receivertype_text,"310MHz");
			break;
		case 0x51:
			sprintf( receivertype_text,"315MHz");
			break;
		case 0x52:
			sprintf( receivertype_text,"433.92MHz receiver only");
			break;
		case 0x53:
			sprintf( receivertype_text,"433.92MHz transceiver");
			break;
		case 0x55:
			sprintf( receivertype_text,"868.00MHz");
			break;
		case 0x56:
			sprintf( receivertype_text,"868.00MHz FSK");
			break;
		case 0x57:
			sprintf( receivertype_text,"868.30MHz");
			break;
		case 0x58:
			sprintf( receivertype_text,"868.30MHz FSK");
			break;			
		case 0x59:
			sprintf( receivertype_text,"868.35MHz");
			break;
		case 0x5A:
			sprintf( receivertype_text,"868.35MHz FSK");
			break;
		case 0x5B:
			sprintf( receivertype_text,"868.95MHz");
			break;			
		default:
			sprintf( receivertype_text,"Not Supported");
			break;
	}
	
	//affichage des protocol actif
	
		sprintf( message3_text,\
		"AE Blyss = %d \n "\
		"Rubicson = %d \n "\
		"FineOffset/Viking = %d \n "\
		"Lighting4 = %d \n "\
		"RSL = %d \n "\
		"Byron SX = %d \n "\
		"Imagintronix/Opus = %d \n "\
		"Enable display of undecoded = %d \n",(msg3 & 0x01 ? 1 : 0),(msg3 & 0x02 ? 1 : 0),(msg3 & 0x04 ? 1 : 0),(msg3 & 0x08 ? 1 : 0),(msg3 & 0x10 ? 1 : 0),(msg3 & 0x20 ? 1 : 0),(msg3 & 0x40 ? 1 : 0),(msg3 & 0x80 ? 1 : 0));

		sprintf( message4_text,\
		"Mertik = %d \n "\
		"AD LightwaveRF = %d \n "\
		"Hideki/UPM = %d \n "\
		"La Crosse = %d \n "\
		"FS20 = %d \n "\
		"ProGuard = %d \n "\
		"BlindsT0 = %d \n "\
		"BlindsT1 = %d \n",(msg4 & 0x01 ? 1 : 0),(msg4 & 0x02 ? 1 : 0),(msg4 & 0x04 ? 1 : 0),(msg4 & 0x08 ? 1 : 0),(msg4 & 0x10 ? 1 : 0),(msg4 & 0x20 ? 1 : 0),(msg4 & 0x40 ? 1 : 0),(msg4 & 0x80 ? 1 : 0));
		
		sprintf( message5_text,\
		"X10 = %d \n "\
		"ARC = %d \n "\
		"AC = %d \n "\
		"HomeEasy EU = %d \n "\
		"Meiantech = %d \n "\
		"Oregon Scientific = %d \n "\
		"ATI = %d \n "\
		"Visonic = %d \n",(msg5 & 0x01 ? 1 : 0),(msg5 & 0x02 ? 1 : 0),(msg5 & 0x04 ? 1 : 0),(msg5 & 0x08 ? 1 : 0),(msg5 & 0x10 ? 1 : 0),(msg5 & 0x20 ? 1 : 0),(msg5 & 0x40 ? 1 : 0),(msg5 & 0x80 ? 1 : 0));

		
	log_INFO("\n\n Packetype: Interface Message \n Subtype: %s \n Seqnbr: %d \n Cmnd: %s  \n Receiver-Transceiver type: %s \n Firmware Version: %d  \n Protocols Enamble/Disable: \n\n %s %s %s \n", subtype_text,seqnbr,cmnd_text,receivertype_text,msg2,message3_text,message4_text,message5_text);
	
}

void message_0X02(){

   	log_DEBUG("Message de type: Receiver/Transmitter Message");
	log_DEBUG("Not Suported yet");
}

void message_0X03(){

    log_DEBUG("Message de type: Undecoded RF Message");
	log_DEBUG("Not Suported yet");
}

void message_0X10(){

    log_DEBUG("Message de type: Lighting 1");
	log_DEBUG("Not Suported yet");
}

void message_0X11(char message[255]){

	unsigned char		packettype = message[1];
	unsigned char		subtype	= message[2];
	unsigned char		seqnbr = message[3];
	unsigned char		id1 = message[4];
	unsigned char		id2 = message[5];
	unsigned char		id3 = message[6];
	unsigned char		id4 = message[7];
	unsigned char		unitcode = message[8];
	char 				cmnd_text[64];
	unsigned char		level = message[10];
	unsigned char 		rssi = ((message[11] >> 4) & 0X0F);
	
	char subtype_text[64];

    
    RfxDevice device;
    addRfxDevice(message);
    device = GetRfxDevice(message);
    print_device_rfx(device);
    
    log_DEBUG("[RfxDevice] device: %d",device.dc_id);
    
    if (device.dc_id != 0){
    
        // Subtype for log
        if ( subtype == 0x00){
            sprintf( subtype_text,"AC");
        }
        else if (subtype == 0x01){
            sprintf( subtype_text,"HomeEasy EU");
        }
        else if (subtype == 0x02){
            sprintf( subtype_text,"ANSLUT");
        }
        else{
            sprintf( subtype_text,"Not supported");
        }
        // Cmd
        switch ( message[9] ) {
            case 0x00:
                sprintf( cmnd_text,"Off");
                break;
            case 0x01:
                sprintf( cmnd_text,"On");
                break;
            case 0x02:
                sprintf( cmnd_text,"Set level");
                break;
            case 0x03:
                sprintf( cmnd_text,"group Off");
                break;
            case 0x04:
                sprintf( cmnd_text,"group On");
                break;
            case 0x05:
                sprintf( cmnd_text,"Set group level");
                break;
            default:
                sprintf( cmnd_text,"Not Supported");
                break;
        }
        log_DEBUG("\n\n Packetype: LIGHTING 2 \n Subtype: %s \n Seqnbr: %d \n id1: %02hhX  \n id2: %02hhX \n id3: %02hhX  \n id4: %02hhX \n Unit: %d \n Command : %s \n Level: %d \n rssi: %d \n", subtype_text,seqnbr,id1,id2,id3,id4,unitcode,cmnd_text,level,rssi);
        
        // MYSQL INSERTION
        if ( DB_MYSQL == 1){
                         
            mysql_insert("INSERT INTO state (dc_id,datetime,device_mode,dim_level,signal_level) VALUES (%d,NOW(),'%s',%d,%d)\
                ON DUPLICATE KEY UPDATE datetime=NOW(),device_mode='%s',dim_level=%d,signal_level=%d;",device.dc_id,cmnd_text,level,rssi,cmnd_text,level,rssi);
        }
        
            // MDB CLOUD
        if ( MDB_CLOUD == 1){

            MYSQL *conn;
            MYSQL_RES *result;
            MYSQL_ROW row;
            
            int iss_status=0;
            char iss_stream[32];
            int enable=0;
            int deleted=0;
            
            /*Recherche des parametres du status ISS*/	
            conn = mysql_connection();
            result = mysql_select(conn,"SELECT iss_status,iss_stream,enable,deleted FROM devices WHERE id1='%02hhX' AND id2='%02hhX' AND id3='%02hhX' AND id4='%02hhX' AND unitcode=%d LIMIT 1", id1,id2,id3,id4,unitcode);
            
            int num_fields = mysql_num_fields(result);

                while (row = mysql_fetch_row(result)){
                    iss_status = atoi(row[0]);
                    strcpy(iss_stream, row[1]);
                    enable = atoi(row[2]);
                    deleted = atoi(row[3]);
                };
                
            mysql_free_result(result);
            mysql_close(conn);

            log_DEBUG("MDB Cloud: ISS status : %d  Stream: %s",iss_status,iss_stream);

            if (( iss_status == 1) && ( enable == 1) && (deleted== 0)){
                post_stream_value(iss_stream,"[{ \"value\": \"%s\"}]",cmnd_text);
            }
        }
    }
}

//0x14 Lighting5 (AD)
void message_0X14(char message[255]){

	unsigned char		packettype = message[1];
	unsigned char		subtype	= message[2];
	unsigned char		seqnbr = message[3];
	unsigned char		id1 = message[4];
	unsigned char		id2 = message[5];
	unsigned char		id3 = message[6];
	unsigned char		unitcode = message[7];
	char 				cmnd_text[64];
	unsigned char		level = message[9];
	unsigned char 		rssi = ((message[10] >> 4) & 0X0F);
	
	char subtype_text[32];
    
    RfxDevice device;
    addRfxDevice(message);
    device = GetRfxDevice(message);
    print_device_rfx(device);
    
    log_DEBUG("[RfxDevice] device: %d",device.dc_id);
	
    if (device.dc_id != 0){
	// Subtype for log
        if ( subtype == 0x00){
            sprintf( subtype_text,"LightwaweRF,Siemens");	
            // Cmd
            switch ( message[8] ) {
                case 0x00:
                    sprintf( cmnd_text,"Off");
                    break;
                case 0x01:
                    sprintf( cmnd_text,"On");
                    break;
                case 0x02:
                    sprintf( cmnd_text,"Group Off");
                    break;
                case 0x03:
                    sprintf( cmnd_text,"mood1");
                    break;
                case 0x04:
                    sprintf( cmnd_text,"mood2");
                    break;
                case 0x05:
                    sprintf( cmnd_text,"mood3");
                    break;
                case 0x06:
                    sprintf( cmnd_text,"mood4");
                    break;
                case 0x07:
                    sprintf( cmnd_text,"mood5");
                    break;
                case 0x08:
                    sprintf( cmnd_text,"reserved");
                    break;
                case 0x09:
                    sprintf( cmnd_text,"reserved");
                    break;
                case 0x0A:
                    sprintf( cmnd_text,"unlock");
                    break;
                case 0x0B:
                    sprintf( cmnd_text,"lock");
                    break;
                case 0x0C:
                    sprintf( cmnd_text,"all lock");
                    break;
                case 0x0D:
                    sprintf( cmnd_text,"close");
                    break;
                case 0x0E:
                    sprintf( cmnd_text,"stop");
                    break;
                case 0x0F:
                    sprintf( cmnd_text,"open");
                    break;
                case 0x10:
                    sprintf( cmnd_text,"set level");
                    break;
                case 0x11:
                    sprintf( cmnd_text,"Colour Palette");
                    break;
                case 0x12:
                    sprintf( cmnd_text,"Colour Tone");
                    break;
                case 0x13:
                    sprintf( cmnd_text,"Color Cycle");
                    break;
                default:
                    sprintf( cmnd_text,"Not Supported");
                    break;
            }	
        }
        else if (subtype == 0x01){
            sprintf( subtype_text,"EMW100 GAO/Everflourish");
            // Cmd
            switch ( message[8] ) {
                case 0x00:
                    sprintf( cmnd_text,"Off");
                    break;
                case 0x01:
                    sprintf( cmnd_text,"On");
                    break;
                case 0x02:
                    sprintf( cmnd_text,"Learn");
                    break;
                default:
                    sprintf( cmnd_text,"Not Supported");
                    break;
            }
        }
        else if (subtype == 0x02){
            sprintf( subtype_text,"BBSB new types ");
            // Cmd
            switch ( message[8] ) {
                case 0x00:
                    sprintf( cmnd_text,"Off");
                    break;
                case 0x01:
                    sprintf( cmnd_text,"On");
                    break;
                case 0x02:
                    sprintf( cmnd_text,"Group off");
                    break;
                case 0x03:
                    sprintf( cmnd_text,"Group on");
                    break;
                default:
                    sprintf( cmnd_text,"Not Supported");
                    break;
            }
        }
        else if (subtype == 0x03){
            sprintf( subtype_text,"MDREMOTE LED dimmer");
            // Cmd
            switch ( message[8] ) {
                case 0x00:
                    sprintf( cmnd_text,"Power");
                    break;
                case 0x01:
                    sprintf( cmnd_text,"Light");
                    break;
                case 0x02:
                    sprintf( cmnd_text,"Bright");
                    break;
                case 0x03:
                    sprintf( cmnd_text,"Dim");
                    break;
                case 0x04:
                    sprintf( cmnd_text,"100%");
                    break;
                case 0x05:
                    sprintf( cmnd_text,"50%");
                    break;
                case 0x06:
                    sprintf( cmnd_text,"25%");
                    break;
                case 0x07:
                    sprintf( cmnd_text,"Mode+");
                    break;
                case 0x08:
                    sprintf( cmnd_text,"Speed-");
                    break;
                case 0x09:
                    sprintf( cmnd_text,"Speed+");
                    break;
                case 0x0A:
                    sprintf( cmnd_text,"Mode-");
                    break;
                default:
                    sprintf( cmnd_text,"Not Supported");
                    break;
            }
        }
        else if (subtype == 0x04){
            sprintf( subtype_text,"Conrad RSL2");
            // Cmd
            switch ( message[8] ) {
                case 0x00:
                    sprintf( cmnd_text,"off");
                    break;
                case 0x01:
                    sprintf( cmnd_text,"on");
                    break;
                case 0x02:
                    sprintf( cmnd_text,"group off");
                    break;
                case 0x03:
                    sprintf( cmnd_text,"group on");
                    break;
                default:
                    sprintf( cmnd_text,"Not Supported");
                    break;
            }
        }
        else if (subtype == 0x05){
            sprintf( subtype_text,"Livolo");
            // Cmd
            switch ( message[8] ) {
                case 0x00:
                    sprintf( cmnd_text,"Group Off");
                    break;
                case 0x01:
                    sprintf( cmnd_text,"On/Off dimmer or Gang1");
                    break;
                case 0x02:
                    sprintf( cmnd_text,"Dim+ or Gang2 on/off");
                    break;
                case 0x03:
                    sprintf( cmnd_text,"Dim- or Gang3 on/off");
                    break;
                default:
                    sprintf( cmnd_text,"Not Supported");
                    break;
            }
        }
        else if (subtype == 0x06){
            sprintf( subtype_text,"RGB TRC02");
            // Cmd
            switch ( message[8] ) {
                case 0x00:
                    sprintf( cmnd_text,"Off");
                    break;
                case 0x01:
                    sprintf( cmnd_text,"On");
                    break;
                case 0x02:
                    sprintf( cmnd_text,"Bright");
                    break;
                case 0x03:
                    sprintf( cmnd_text,"Dim");
                    break;
                case 0x04:
                    sprintf( cmnd_text,"Color+");
                    break;
                case 0x05:
                    sprintf( cmnd_text,"Color-");
                    break;
                default:
                    if ( 0x06 <= message[8] <=  0x84 )
                    {
                        sprintf( cmnd_text,"Color : %02hhX", message[8] );
                    }
                    else
                    {
                        sprintf( cmnd_text,"Not Supported");
                    }
                break;
            }		
            
        }
        else{
            sprintf( subtype_text,"Not supported");
        }
        
        log_DEBUG("\n\n Packetype: LIGHTING 2 \n Subtype: %s \n Seqnbr: %d \n id1: %02hhX  \n id2: %02hhX \n id3: %02hhX  \n Unit: %d \n Command : %s \n Level: %d \n rssi: %d \n", subtype_text,seqnbr,id1,id2,id3,unitcode,cmnd_text,level,rssi);
        
        // MYSQL INSERTION
        if ( DB_MYSQL == 1){
                         
            mysql_insert("INSERT INTO state (dc_id,datetime,device_mode,dim_level,signal_level) VALUES (%d,NOW(),'%s',%d,%d)\
                                      ON DUPLICATE KEY UPDATE datetime=NOW(),device_mode='%s',dim_level=%d,signal_level=%d;",device.dc_id,cmnd_text,level,rssi,cmnd_text,level,rssi);
        }
        
            // MDB CLOUD
        if ( MDB_CLOUD == 1){

            MYSQL *conn;
            MYSQL_RES *result;
            MYSQL_ROW row;
            
            int iss_status=0;
            char iss_stream[32];
            int enable=0;
            int deleted=0;
            
            /*Recherche des parametres du status ISS*/	
            conn = mysql_connection();
            result = mysql_select(conn,"SELECT iss_status,iss_stream,enable,deleted FROM devices WHERE id1='%02hhX' AND id2='%02hhX' AND id3='%02hhX' AND unitcode=%d LIMIT 1", id1,id2,id3,unitcode);
            
            int num_fields = mysql_num_fields(result);

                while (row = mysql_fetch_row(result)){
                    iss_status = atoi(row[0]);
                    strcpy(iss_stream, row[1]);
                    enable = atoi(row[2]);
                    deleted = atoi(row[3]);
                };
                
            mysql_free_result(result);
            mysql_close(conn);

            log_DEBUG("MDB Cloud: ISS status : %d  Name: %s",iss_status,iss_stream);

            if (( iss_status == 1) && ( enable == 1) && (deleted== 0)){
                //post_ISS(iss_stream,"{\"unit\":{\"label\":\"Command\",\"symbol\": \"Text\" },\"value\":\"%s\"}",cmnd_text);
                post_stream_value(iss_stream,"[{ \"value\": \"%s\" }]",cmnd_text);
            }
        }
                     
    }
}

void message_0X1A(char message[255]){

	unsigned char		packettype = message[1];
	unsigned char		subtype	= message[2];
	unsigned char		seqnbr = message[3];
	unsigned char		id1 = message[4];
	unsigned char		id2 = message[5];
	unsigned char		id3 = message[6];
	unsigned char		unitcode = message[7];
	char 				cmnd_text[64];
	unsigned char		rfu1 = message[9];
	unsigned char		rfu2 = message[10];
	unsigned char		rfu3 = message[11];
	unsigned char 		rssi = ((message[12] >> 4) & 0X0F);	
	
	char subtype_text[64];
    
    RfxDevice device;
    addRfxDevice(message);
    device = GetRfxDevice(message);
    print_device_rfx(device);
    
    log_DEBUG("[RfxDevice] device: %d",device.dc_id);

    if (device.dc_id != 0){
    
        // Subtype for log
        if ( subtype == 0x00){
            sprintf( subtype_text,"RFY");
        }
        else if (subtype == 0x01){
            sprintf( subtype_text,"RFY ext");
        }
        else{
            sprintf( subtype_text,"Not supported");
        }

        // Cmd
        switch ( message[8] ) {
            case 0x00:
                sprintf( cmnd_text,"stop");
                break;
            case 0x01:
                sprintf( cmnd_text,"up");
                break;
            case 0x02:
                sprintf( cmnd_text,"up + stop");
                break;
            case 0x03:
                sprintf( cmnd_text,"down");
                break;
            case 0x04:
                sprintf( cmnd_text,"down + stop");
                break;
            case 0x05:
                sprintf( cmnd_text,"up + down");
                break;
            case 0x07:
                sprintf( cmnd_text,"Program");
                break;
            case 0x08:
                sprintf( cmnd_text,"Program > 2 seconds");
                break;
            case 0x09:
                sprintf( cmnd_text,"Program > 7 seconds");
                break;
            case 0x10:
                sprintf( cmnd_text,"Program > 2 seconds");
                break;
            case 0x0A:
                sprintf( cmnd_text,"stop >2 seconds");
                break;
            case 0x0B:
                sprintf( cmnd_text,"stop >5 seconds");
                break;
            case 0x0C:
                sprintf( cmnd_text,"up + down >5 seconds");
                break;
            case 0x0D:
                sprintf( cmnd_text,"Erase this RFY remote from the RFXtrx");
                break;
            case 0x0E:
                sprintf( cmnd_text,"Erase all RFY remotes from the RFXtrx");
                break;
            default:
                sprintf( cmnd_text,"Not Supported");
                break;
        }

        log_DEBUG("\n\n Packetype: RFY \n Subtype: %s \n Seqnbr: %d \n id1: %02hhX  \n id2: %02hhX \n id3: %02hhX  \n Unitcode: %d \n Command : %s \n rssi: %d \n", subtype_text,seqnbr,id1,id2,id3,unitcode,cmnd_text,rssi);

        if ( DB_MYSQL == 1){
            
            mysql_insert("INSERT INTO state (dc_id,datetime,device_mode,dim_level,signal_level) VALUES (%d,NOW(),'%s',%d,%d)\
                         ON DUPLICATE KEY UPDATE datetime=NOW(),device_mode='%s',dim_level=%d,signal_level=%d;",device.dc_id,cmnd_text,rssi,cmnd_text,rssi);
        }
    }
}

void message_0X40(char message[255]){

	unsigned char		packettype = message[1];
	unsigned char		subtype	= message[2];
	unsigned char		seqnbr = message[3];
	unsigned char		id1 = message[4];
	unsigned char		id2 = message[5];
	unsigned char 		temperature = message[6];
	unsigned char 		temperature_set = message[7];
	unsigned char 		mode = (message[8] & 0X80);
	unsigned char 		status = (message[8] & 0x03) ;
	unsigned char 		rssi = ((message[9] >> 4) & 0X0F);
	
	char subtype_text[64];
	char mode_text[8];
	char status_text[32];
    
    RfxDevice device;
    addRfxDevice(message);
    device = GetRfxDevice(message);
    print_device_rfx(device);
	
	log_DEBUG("[RfxDevice] device: %d",device.dc_id);

    if (device.dc_id != 0){
	
		// Subtype for log
		if ( subtype == 0x00){
			sprintf( subtype_text,"Digimax, TLX7506");
		}
		else if (subtype == 0x01){
			sprintf( subtype_text,"Digimax with short format (no set point)");
		}
		else{
			sprintf( subtype_text,"Not supported");
		}
		// Mode for log
		if ( mode == 0x00){
			sprintf( mode_text,"Heating");
		}
		else if (mode == 0x01){
			sprintf( mode_text,"Cooling");
		}
		else{
			sprintf( mode_text,"Not supported");
		}
		// Status for log
		if ( status == 0x00){
			sprintf( status_text,"No Status Available");
		}
		else if (status == 0x01){
			sprintf( status_text,"Demand");
		}
		else if (status == 0x02){
			sprintf( status_text,"No Demand");
		}
		else if (status == 0x03){
			sprintf( status_text,"Initialazing");
		}
		else{
			sprintf( status_text,"Not supported");
		}
		log_DEBUG("\n\n Packetype: THERMOSTAT 1 \n Subtype: %s \n Seqnbr: %d \n id1: %02hhX  \n id2: %02hhX \n Temperature: %d \n Temperature Set: %d \n Mode: %s \n Status: %s \n rssi: %d \n", subtype_text,seqnbr,id1,id2,temperature,temperature_set,mode_text,status_text,rssi);
	
		// MYSQL INSERTION
		if ( DB_MYSQL == 1){
					
			mysql_insert("UPDATE devices SET last_update=NOW(),home_data1=%d WHERE dc_id=%d;\
						INSERT INTO temperature (dc_id,datetime,seqnbr,temperature,temperature_set,mode,status,signal_level) VALUES (%d,NOW(),%d,%d,%d,'%s','%s',%d);\
						",temperature,device.dc_id,device.dc_id,seqnbr,temperature,temperature_set,mode_text,status_text,rssi);
		}
	
		// MDB CLOUD
		if ( MDB_CLOUD == 1){

			MYSQL *conn;
			MYSQL_RES *result;
			MYSQL_ROW row;
		
			int iss_status=0;
			char iss_stream[32];
			int enable=0;
			int deleted=0;
		
			/*Recherche des parametres du status ISS*/	
			conn = mysql_connection();
			result = mysql_select(conn,"SELECT iss_status,iss_stream,enable,deleted FROM devices WHERE id1='%02hhX' AND id2='%02hhX' LIMIT 1;", id1,id2);
		
			int num_fields = mysql_num_fields(result);

				while (row = mysql_fetch_row(result)){
					iss_status = atoi(row[0]);
					strcpy(iss_stream, row[1]);
					enable = atoi(row[2]);
					deleted = atoi(row[3]);
				};
			
			mysql_free_result(result);
			mysql_close(conn);

			log_DEBUG("MDB Cloud: ISS status : %d  Name: %s",iss_status,iss_stream);

			if (( iss_status == 1) && ( enable == 1) && (deleted== 0)){
				//post_ISS(iss_stream,"{\"unit\":{\"label\":\"Celsius\",\"symbol\": \"C\" },\"value\":\"%d\"}",temperature);
				post_stream_value(iss_stream,"[{ \"value\": \"%d\" }]",temperature);
			}
		}
	}
}

void message_0X5A(char message[255]){

	unsigned char		packettype = message[1];
	unsigned char		subtype	= message[2];
	unsigned char		seqnbr = message[3];
	unsigned char		id1 = message[4];
	unsigned char		id2 = message[5];
	unsigned char 		count = message[6];
	unsigned long 		instant = ((message[7] << 24) | ((message[8] << 16) | ((message[9] << 8) | (message[10]))));
	unsigned long long 	total = ((((message[11] * 1ULL)  << 40) | (((message[12] * 1ULL) << 32) | ((message[13] << 24) | ((message[14] << 16) | ((message[15] << 8) | (message[16])))))) / 223.666);
	unsigned char		battery_level = (message[17] & 0X0F);	
	unsigned char 		rssi = ((message[17] >> 4) & 0X0F);	
	
	char subtype_text[32];
    
    RfxDevice device;
    addRfxDevice(message);
    device = GetRfxDevice(message);
    print_device_rfx(device);
	
	log_DEBUG("[RfxDevice] device: %d",device.dc_id);

    if (device.dc_id != 0){
	
		if ( subtype == 0x01){
			sprintf( subtype_text,"ELEC2, CM119/160");
		}
		else if (subtype == 0x02){
			sprintf( subtype_text,"ELEC3, CM180");
		}
		else{
			sprintf( subtype_text,"Not Supported");
		}
		log_DEBUG("\n\n Packetype: ENERGY USAGE SENSORS \n Subtype: %s \n Seqnbr: %d \n id1: %02hhX  \n id2: %02hhX \n Count: %d \n Instant: %ld \n Total: %lld \n Battery_level: %d \n rssi: %d \n", subtype_text,seqnbr,id1,id2,count,instant,total,battery_level,rssi);		

	
		// MYSQL INSERTION
		if ( DB_MYSQL == 1){
			
			mysql_insert("UPDATE devices SET last_update=NOW(),home_data1=%d WHERE dc_id=%d;\
						INSERT INTO energy (dc_id,datetime,count,instant,total,battery,signal_level) VALUES (%d,NOW(),%d,%d,%lld,%d,%d);\
						",instant,device.dc_id,device.dc_id,count,instant,total,battery_level,rssi);
		}
	
		// MDB CLOUD
		if ( MDB_CLOUD == 1){

			MYSQL *conn;
			MYSQL_RES *result;
			MYSQL_ROW row;
		
			int iss_status=0;
			char iss_stream[32];
			int enable=0;
			int deleted=0;
		
			/*Recherche des parametres du status ISS*/	
			conn = mysql_connection();
			result = mysql_select(conn,"SELECT iss_status,iss_stream,enable,deleted FROM devices WHERE id1='%02hhX' AND id2='%02hhX' LIMIT 1;", id1,id2);
		
			int num_fields = mysql_num_fields(result);

				while (row = mysql_fetch_row(result)){
					iss_status = atoi(row[0]);
					strcpy(iss_stream, row[1]);
					enable = atoi(row[2]);
					deleted = atoi(row[3]);
				};
			
			mysql_free_result(result);
			mysql_close(conn);

			log_DEBUG("MDB Cloud: ISS status : %d  Name: %s",iss_status,iss_stream);

			if (( iss_status == 1) && ( enable == 1) && (deleted== 0)){
				//post_ISS(iss_stream,"{\"unit\":{\"label\":\"Watt\",\"symbol\": \"W\" },\"value\":\"%d\"}",instant);
				post_stream_value(iss_stream,"[{ \"value\": \"%d\" }]",instant);
			
			}
		}
	}
}

void message_0X52(char message[255]){
	unsigned char		packettype = message[1];
	unsigned char		subtype	= message[2];
	unsigned char		seqnbr = message[3];
	unsigned char		id1 = message[4];
	unsigned char		id2 = message[5];
	float				temperature = decode_temperature( &message[6], &message[7]);
	unsigned char   	humidity = message[8];
	unsigned char    	humidity_status = message[9];
	unsigned char		battery_level = (message[10] & 0X0F);	
	unsigned char 		rssi = ((message[10] >> 4) & 0X0F);	
	
	char subtype_text[32];
	char humidity_text[8];
    
    RfxDevice device;
    addRfxDevice(message);
    device = GetRfxDevice(message);
    print_device_rfx(device);
    
	log_DEBUG("[RfxDevice] device: %d",device.dc_id);

    if (device.dc_id != 0){
	
		switch ( message[2] ) {
			case 0x01:
				sprintf( subtype_text,"THGN122/123, THGN132, THGR122/228/238/268");
				break;
			case 0x02:
				sprintf( subtype_text,"THGR810, THGN800, THGR810");
				break;
			case 0x03:
				sprintf( subtype_text,"RTGR328");
				break;
			case 0x04:
				sprintf( subtype_text,"THGR328");
				break;
			case 0x05:
				sprintf( subtype_text,"WTGR800");
				break;
			case 0x06:
				sprintf( subtype_text,"THGR918/928, THGRN228, THGN500");
				break;
			case 0x07:
				sprintf( subtype_text,"TFA TS34C, Cresta");
				break;
			case 0x08:
				sprintf( subtype_text,"WT260,WT260H,WT440H,WT450,WT450H)");
				break;
			case 0x09:
				sprintf( subtype_text,"Viking 02035,02038 (02035 has no humidity)");
				break;
			case 0x0A:
				sprintf( subtype_text,"TH10 is Rubicson");
				break;
			case 0x0B:
				sprintf( subtype_text,"TH11 is EW109");
				break;
			case 0x0C:
				sprintf( subtype_text,"TH12 is Imagintronix Soil sensor");
				break;			
			default:
				sprintf( subtype_text,"Not Supported");
				break;
		}

			if ( humidity_status == 0x00){
					sprintf( humidity_text,"normal");
			}
			else if ( humidity_status == 0x01){
					sprintf( humidity_text,"confort");
			}
			else if ( humidity_status == 0x02){
					sprintf( humidity_text,"dry");
			}
			else if ( humidity_status == 0x03){
					sprintf( humidity_text,"wet");
			}
			else{
					sprintf( humidity_text,"Not Supported");
			}
		log_DEBUG("\n\n Packetype: TEMPERATURE AND HUMIDITY SENSORS \n Subtype: %s \n Seqnbr: %d \n id1: %02hhX  \n id2: %02hhX \n Temperature: %.2f \n Humidity: %d \n Humidity Status: %s \n Battery_level: %d \n rssi: %d \n", subtype_text,seqnbr,id1,id2,temperature,humidity,humidity_text,battery_level,rssi);		

		// MYSQL INSERTION
		if ( DB_MYSQL == 1){
		
			mysql_insert("UPDATE devices SET last_update=NOW(),home_data1=%.2f,home_data2=%d WHERE dc_id=%d;\
						INSERT INTO weather (dc_id,datetime,seqnbr,temperature,humidity,humidity_status,battery,signal_level) VALUES (%d,NOW(),%d,%.2f,%d,'%s',%d,%d);\
						",temperature,humidity,device.dc_id,device.dc_id,seqnbr,temperature,humidity,humidity_text,battery_level,rssi);
		}
	
			// MDB CLOUD
		if ( MDB_CLOUD == 1){

			MYSQL *conn;
			MYSQL_RES *result;
			MYSQL_ROW row;
		
			int iss_status=0;
			char iss_stream[32];
			char nametype[50];
			int enable=0;
			int deleted=0;
		
			/*Recherche des parametres du status ISS*/	
			conn = mysql_connection();
			result = mysql_select(conn,"SELECT iss_status,iss_stream,enable,deleted FROM devices WHERE id1='%02hhX' AND id2='%02hhX' LIMIT 1;", id1,id2);
		
			int num_fields = mysql_num_fields(result);

				while (row = mysql_fetch_row(result)){
					iss_status = atoi(row[0]);
					strcpy(iss_stream, row[1]);
					enable = atoi(row[2]);
					deleted = atoi(row[3]);
				};
			
			mysql_free_result(result);
			mysql_close(conn);

			log_DEBUG("MDB Cloud: ISS status : %d  Name: %s",iss_status,iss_stream);

			if (( iss_status == 1) && ( enable == 1) && (deleted== 0)){
				//sprintf(nametype,"%s_temperature",iss_stream);
				//post_ISS(nametype,"{\"unit\":{\"label\":\"Celsius\",\"symbol\": \"C\" },\"value\":\"%.2f\"}",temperature);
				//sprintf(nametype,"%s_humidity",iss_stream);
				//post_ISS(nametype,"{\"unit\":{\"label\":\"Humidity\",\"symbol\": \"%\" },\"value\":\"%d\"}",humidity);
				post_stream_value(iss_stream,"[{ \"value\": { \"Temperature\" : \"%.2f\", \"Humidity\" : \"%d\" }}]",temperature, humidity);
			}
		}
	}	
}

void message_0X55(char message[255]){

	unsigned char		packettype = message[1];
	unsigned char		subtype	= message[2];
	unsigned char		seqnbr = message[3];
	unsigned char		id1 = message[4];
	unsigned char		id2 = message[5];
	float 				rainrate = 0;
	float 				raintotal = 0;	
	float				raintotalmm = 0;
	unsigned char		battery_level = (message[11] & 0X0F);	
	unsigned char 		rssi = ((message[11] >> 4) & 0X0F);	
	
	char subtype_text[32];
    
    RfxDevice device;
    addRfxDevice(message);
    device = GetRfxDevice(message);
    print_device_rfx(device);
    
	log_DEBUG("[RfxDevice] device: %d",device.dc_id);

    if (device.dc_id != 0){
	
		switch ( message[2] ) {
			case 0x01:
				sprintf( subtype_text,"RGR126/682/918/928");
				break;
			case 0x02:
				sprintf( subtype_text,"PCR800");
				break;
			case 0x03:
				sprintf( subtype_text,"TFA");
				break;
			case 0x04:
				sprintf( subtype_text,"UPM RG700");
				break;
			case 0x05:
				sprintf( subtype_text,"WS2300");
				break;
			case 0x06:
				sprintf( subtype_text,"La Crosse TX5");
				break;
			default:
				sprintf( subtype_text,"Not Supported");
				break;
		}                                                                             

			if ( message[2] == 0x01){
				rainrate = ((message[6] << 8) | (message[7]));
			}
			else if ( message[2] == 0x02){
				rainrate = (((message[6] << 8) | (message[7]))/100);			
			}
			else{	
				rainrate = 0;
			}
		
			// calculating Total rain
			if ( message[2] == 0x06){
				raintotal = (((message[8] << 16) | (message[9] << 8)) + ((message[10])*0.266));	
			}
			else{	
				raintotal = (((message[8] << 16) | ((message[9] << 8) | (message[10]))) / 10);
			}		
		
			raintotalmm = raintotal / 10 ;
		
		log_DEBUG("\n\n Packetype: RAIN SENSSORS \n Subtype: %s \n Seqnbr: %d \n id1: %02hhX  \n id2: %02hhX \n Rain Rate: %.2f mm/h \n Total Rain: %.2f mm\n Battery_level: %d \n rssi: %d \n", subtype_text,seqnbr,id1,id2,rainrate,raintotalmm,battery_level,rssi);		

		// MYSQL INSERTION
		if ( DB_MYSQL == 1){
		
			mysql_insert("UPDATE devices SET last_update=NOW(),home_data1=%.2f,home_data2=%.2f WHERE dc_id=%d;\
						INSERT INTO weather (dc_id,datetime,seqnbr,rainrate,raintotal,battery,signal_level) VALUES (%d,NOW(),%d,%.2f,%.2f,%d,%d);\
						",rainrate,raintotal,device.dc_id,device.dc_id,seqnbr,rainrate,raintotal,battery_level,rssi);
		}
			// MDB CLOUD
		if ( MDB_CLOUD == 1){

			MYSQL *conn;
			MYSQL_RES *result;
			MYSQL_ROW row;
		
			int iss_status=0;
			char iss_stream[32];
			char nametype[50];
			int enable=0;
			int deleted=0;
		
			/*Recherche des parametres du status ISS*/	
			conn = mysql_connection();
			result = mysql_select(conn,"SELECT iss_status,iss_stream,enable,deleted FROM devices WHERE id1='%02hhX' AND id2='%02hhX' LIMIT 1;", id1,id2);
			log_DEBUG_SQL("SELECT iss_status,iss_stream,enable,deleted FROM devices WHERE id1='%02hhX' AND id2='%02hhX' LIMIT 1;", id1,id2);
		
			int num_fields = mysql_num_fields(result);

				while (row = mysql_fetch_row(result)){
					iss_status = atoi(row[0]);
					strcpy(iss_stream, row[1]);
					enable = atoi(row[2]);
					deleted = atoi(row[3]);
				};
			
			mysql_free_result(result);
			mysql_close(conn);

			log_DEBUG("MDB Cloud: ISS status : %d  Name: %s",iss_status,iss_stream);

			if (( iss_status == 1) && ( enable == 1) && (deleted== 0)){
				//sprintf(nametype,"%s_rain_total",iss_stream);
				//post_ISS(nametype,"{\"unit\":{\"label\":\"Millimeter\",\"symbol\": \"mm\" },\"value\":\"%.2f\"}",raintotalmm);
				//sprintf(nametype,"%s_rain_rate",iss_stream);
				//post_ISS(nametype,"{\"unit\":{\"label\":\"Milimeter/Hour\",\"symbol\": \"mm/hour\" },\"value\":\"%.2f\"}",rainrate);
				post_stream_value(iss_stream,"[{ \"value\": \"%.2f\" }]",raintotalmm);
			}
		}
	}
}

void message_0X56(char message[255]){

	unsigned char		packettype = message[1];
	unsigned char		subtype	= message[2];
	unsigned char		seqnbr = message[3];
	unsigned char		id1 = message[4];
	unsigned char		id2 = message[5];
	int 				winddirection = ((message[6] << 8) | message[7]);
	int 				av_speed = (((message[8] << 8) | (message[9]))/10);
	int 				gust = (((message[10] << 8) | (message[11]))/10);
	float				temperature = decode_temperature( &message[12], &message[13]);
	float				windchill = decode_temperature( &message[14], &message[15]);	
	unsigned char		battery_level = (message[16] & 0X0F);	
	unsigned char 		rssi = ((message[16] >> 4) & 0X0F);	
	
	char subtype_text[32];
    
    RfxDevice device;
    addRfxDevice(message);
    device = GetRfxDevice(message);
    print_device_rfx(device);

	log_DEBUG("[RfxDevice] device: %d",device.dc_id);

    if (device.dc_id != 0){
	
		switch ( message[2] ) {
			case 0x01:
				sprintf( subtype_text,"WTGR800");
				break;
			case 0x02:
				sprintf( subtype_text,"WGR800");
				break;
			case 0x03:
				sprintf( subtype_text,"STR918, WGR918, WGR928");
				break;
			case 0x04:
				sprintf( subtype_text,"TFA");
				break;
			case 0x05:
				sprintf( subtype_text,"UPM WDS500");
				break;
			case 0x06:
				sprintf( subtype_text,"WS2300");
				break;
			default:
				sprintf( subtype_text,"Not Supported");
				break;
		}                                                                             
		
		// 2 case WIND4 and others
	
		if ( message[2] == 0x04 )
		{
		//WIND 4 (more informations)
			log_DEBUG("\n\n Packetype: WIND SENSSORS \n Subtype: %s \n Seqnbr: %d \n id1: %02hhX  \n id2: %02hhX \n Direction: %d degrees \n Average Speed: %d m/sec \n Wind gust: %d m/sec \n Temperature: %.2f  \n Wind chill: %.2f \n Battery_level: %d \n rssi: %d \n", subtype_text,seqnbr,id1,id2,winddirection,av_speed,gust,temperature,windchill,battery_level,rssi);		

			// MYSQL INSERTION
			if ( DB_MYSQL == 1){
		
				mysql_insert("UPDATE devices SET last_update=NOW(),home_data1=%d,home_data2=%d,home_data3=%d WHERE dc_id=%d;\
						INSERT INTO weather (dc_id,datetime,seqnbr,winddirection,av_speed,gust,temperature,windchill,battery,signal_level) VALUES (%d,NOW(),%d,%d,%d,%d,%.2f,%.2f,%d,%d);\
						",winddirection,av_speed,gust,device.dc_id,device.dc_id,seqnbr,winddirection,av_speed,gust,temperature,windchill,battery_level,rssi);
			}
		}
		else
		{
			log_DEBUG("\n\n Packetype: WIND SENSSORS \n Subtype: %s \n Seqnbr: %d \n id1: %02hhX  \n id2: %02hhX \n Direction: %d degrees \n Average Speed: %d m/sec \n Wind gust: %d m/sec \n Battery_level: %d \n rssi: %d \n", subtype_text,seqnbr,id1,id2,winddirection,av_speed,gust,battery_level,rssi);		

			// MYSQL INSERTION
			if ( DB_MYSQL == 1){
		
				mysql_insert("UPDATE devices SET last_update=NOW(),home_data1=%d,home_data2=%d,home_data3=%d WHERE dc_id=%d;\
						INSERT INTO weather (dc_id,datetime,seqnbr,winddirection,av_speed,gust,battery,signal_level) VALUES (%d,NOW(),%d,%d,%d,%d,%d,%d);\
						",winddirection,av_speed,gust,device.dc_id,device.dc_id,seqnbr,winddirection,av_speed,gust,battery_level,rssi);
			}
		}
	
		// MDB CLOUD
		if ( MDB_CLOUD == 1){

			MYSQL *conn;
			MYSQL_RES *result;
			MYSQL_ROW row;
		
			int iss_status=0;
			char iss_stream[32];
			char nametype[50];
			int enable=0;
			int deleted=0;
		
			/*Recherche des parametres du status ISS*/	
			conn = mysql_connection();
			result = mysql_select(conn,"SELECT iss_status,iss_stream,enable,deleted FROM devices WHERE id1='%02hhX' AND id2='%02hhX' LIMIT 1;", id1,id2);
		
			int num_fields = mysql_num_fields(result);

				while (row = mysql_fetch_row(result)){
					iss_status = atoi(row[0]);
					strcpy(iss_stream, row[1]);
					enable = atoi(row[2]);
					deleted = atoi(row[3]);
				};
			
			mysql_free_result(result);
			mysql_close(conn);

			log_DEBUG("MDB Cloud: ISS status : %d  Name: %s",iss_status,iss_stream);

			if (( iss_status == 1) && ( enable == 1) && (deleted== 0)){
				//sprintf(nametype,"%s_gust",iss_stream);
				//post_ISS(nametype,"{\"unit\":{\"label\":\"Speed\",\"symbol\": \"m/s\" },\"value\":\"%d\"}",gust);
				//sprintf(nametype,"%s_direction",iss_stream);
				//post_ISS(nametype,"{\"unit\":{\"label\":\"Degree\",\"symbol\": \"&ordm\" },\"value\":\"%d\"}",winddirection);
				post_stream_value(iss_stream,"[{ \"value\": \"%d\" }]",gust);
			}
		}
	}
}

// RPIDOM Message Decoding
void message_EDF1(char message[20][18]){

	char				ADCO[13]; 	strcpy(ADCO,message[0]);
	char				OPTARIF[5];	strcpy(OPTARIF,message[1]);
	
	int					ISOUSC = 	atoi(message[2]);
	unsigned long		HCHP = 		atol(message[3]);
	unsigned long		HCHC = 		atol(message[4]);	
	char				PTEC[5];	strcpy(PTEC,message[5]);	
	int					IINST = 	atoi(message[6]);
	int					IMAX = 		atoi(message[7]);
	int					PAPP = 		atoi(message[8]);
	char				HHPHC[2]; 	strcpy(HHPHC,message[9]);
	char				MOTDETAT[7];strcpy(MOTDETAT,message[10]);
	int					ADPS = 		atoi(message[11]);
	
		log_DEBUG("\n\n Packetype: EDF MONOPHASE \n Adresse du compteur: %s \n Option tarifaire: %s \n Intensité souscrite: %d A \n Index Heures Pleines: %d Wh \n Index Heures Creuses: %d Wh \n Periode Tarifaire en cours: %s \n Intensite instantanee: %d A \n Intensite maximale: %d A \n Puissance apparente: %d VA \n Horaire Heures Pleines Heures Creuses: %s \n Mot d Etat du compteur: %s \n Avertissement Depassement de Puissance Souscrite: %d \n ",ADCO,OPTARIF,ISOUSC,HCHP,HCHC,PTEC,IINST,IMAX,PAPP,HHPHC,MOTDETAT,ADPS);		

		// MYSQL INSERTION
	if ( DB_MYSQL == 1){

        mysql_insert("INSERT IGNORE INTO devices (dc_id,last_update,packettype,subtype,int_id,address,com,home_data1) SELECT IFNULL(MAX(dc_id),0)+1,NOW(),'ERDF','01','2','%s','tx',%d FROM devices ON DUPLICATE KEY UPDATE last_update=NOW(),home_data1=%d;\
                    INSERT INTO energy_edf (dc_id,datetime,optarif,isousc,hchp,hchc,ptec,iinst,imax,papp,hphc,motdetat,adps) VALUES ((select dc_id from devices where address='%s' LIMIT 1),NOW(),'%s',%d,%d,%d,'%s',%d,%d,%d,'%s','%s',%d);\
                     ",ADCO,IINST,IINST,ADCO,OPTARIF,ISOUSC,HCHP,HCHC,PTEC,IINST,IMAX,PAPP,HHPHC,MOTDETAT,ADPS);
					
	}
}

void message_EDF3(char message[20][18]){

	char				ADCO[13]; 	strcpy(ADCO,message[0]);
	char				OPTARIF[5];	strcpy(OPTARIF,message[1]);

	int					ISOUSC = 	atoi(message[2]);
	unsigned long		HCHP = 		atol(message[3]);
	unsigned long		HCHC = 		atol(message[4]);
	
	char				PTEC[5];	strcpy(PTEC,message[5]);
	
	int					IINST1 = 	atoi(message[6]);
	int					IINST2 = 	atoi(message[7]);
	int 				IINST3 =	atoi(message[8]);
	int					IMAX1 = 	atoi(message[9]);
	
	int			 		IMAX2 = 	atoi(message[10]);
	int					IMAX3 = 	atoi(message[11]);
	int					PMAX = 		atoi(message[12]);
	int					PAPP = 		atoi(message[13]);
	
	char				HHPHC[2]; 	strcpy(HHPHC,message[14]);
	char				MOTDETAT[7];strcpy(MOTDETAT,message[15]);
	char				PPOT[3];	strcpy(PPOT,message[16]);
	
	int					ADIR1 = 	atoi(message[17]);
	int					ADIR2 = 	atoi(message[18]);
	int					ADIR3 = 	atoi(message[19]);	

	log_DEBUG("Packetype: EDF TRIPHASE \n Adresse du compteur: %s \n Option tarifaire: %s \n Intensité souscrite: %d A \n Index Heures Pleines: %d Wh \n Index Heures Creuses: %d Wh \n Periode Tarifaire en cours: %s \n Intensite instantanee phase 1: %d A \n Intensite instantanee phase 2: %d A \n Intensite instantanee phase 3: %d A \n Intensite maximale Phase 1: %d A \n Intensite maximale Phase 2: %d A \n Intensite maximale Phase 3: %d A \n Puissance maximale triphasee atteinte: %d W \n Puissance apparente triphasee: %d VA \n Horaire Heures Pleines Heures Creuses: %s \n Mot d Etat du compteur: %s \n Presence des potentiels: %s \n Avertissement Depassement intensite Phase 1: %d \n Avertissement Depassement intensite Phase 2: %d \n Avertissement Depassement intensite Phase 3: %d",ADCO,OPTARIF,ISOUSC,HCHP,HCHC,PTEC,IINST1,IINST2,IINST3,IMAX1,IMAX2,IMAX3,PMAX,PAPP,HHPHC,MOTDETAT,PPOT,ADIR1,ADIR2,ADIR3);		

		// MYSQL INSERTION
	if ( DB_MYSQL == 1){
		
        mysql_insert("INSERT IGNORE INTO devices (dc_id,last_update,packettype,subtype,int_id,address,com,home_data1,home_data2,home_data3) SELECT IFNULL(MAX(dc_id),0)+1,NOW(),'ERDF','03','2','%s','tx',%d,%d,%d FROM devices ON DUPLICATE KEY UPDATE last_update=NOW(),home_data1=%d,home_data2=%d,home_data3=%d;\
                    INSERT INTO energy_edf (dc_id,datetime,optarif,isousc,hchp,hchc,ptec,iinst1,iinst2,iinst3,imax1,imax2,imax3,pmax,papp,hphc,motdetat,ppot,adir1,adir2,adir3) VALUES ((select dc_id from devices where address='%s' LIMIT 1),NOW(),'%s',%d,%d,%d,'%s',%d,%d,%d,%d,%d,%d,%d,%d,'%s','%s','%s',%d,%d,%d);\
            ",ADCO,IINST1,IINST2,IINST3,IINST1,IINST2,IINST3,ADCO,OPTARIF,ISOUSC,HCHP,HCHC,PTEC,IINST1,IINST2,IINST3,IMAX1,IMAX2,IMAX3,PMAX,PAPP,HHPHC,MOTDETAT,PPOT,ADIR1,ADIR2,ADIR3);
					
	}
	
		// MDB CLOUD
	if ( MDB_CLOUD == 1){

		MYSQL *conn;
		MYSQL_RES *result;
		MYSQL_ROW row;
		
		int iss_status=0;
		char iss_stream[32];
		char nametype[50];
		int enable=0;
		int deleted=0;
		
		/*Recherche des parametres du status ISS*/	
		conn = mysql_connection();
		result = mysql_select(conn,"SELECT iss_status,iss_stream,enable,deleted FROM devices WHERE address='%s' LIMIT 1;", ADCO);
		
		int num_fields = mysql_num_fields(result);

			while (row = mysql_fetch_row(result)){
				iss_status = atoi(row[0]);
				strcpy(iss_stream, row[1]);
				enable = atoi(row[2]);
				deleted = atoi(row[3]);
			};
			
		mysql_free_result(result);
		mysql_close(conn);

		log_DEBUG("MDB Cloud: ISS status : %d  Name: %s",iss_status,iss_stream);

		if (( iss_status == 1) && ( enable == 1) && (deleted== 0)){
			//sprintf(nametype,"%s_Phase1",iss_stream);
			//post_ISS(nametype,"{\"unit\":{\"label\":\"Watt\",\"symbol\": \"W\" },\"value\":\"%d\"}",IINST1);
			//sprintf(nametype,"%s_Phase2",iss_stream);
			//post_ISS(nametype,"{\"unit\":{\"label\":\"Watt\",\"symbol\": \"W\" },\"value\":\"%d\"}",IINST2);
			//sprintf(nametype,"%s_Phase3",iss_stream);
			//post_ISS(nametype,"{\"unit\":{\"label\":\"Watt\",\"symbol\": \"W\" },\"value\":\"%d\"}",IINST3);
			post_stream_value(iss_stream,"[{ \"value\": \"%d\" }]",IINST1);
		}
	}
}

void message_1W28(char address[16] ,char message[256]){

	char 	tmpData[5];   // Temp C * 1000 reported by device
	float	temperature = 0;

	strncpy(tmpData, strstr(message, "t=") + 2, 5);
	temperature = strtof(tmpData, NULL) / 1000;
	
	log_DEBUG("\n\n Packetype: 1 Wire \n Subtype: 28 \n  address: %s \n Temperature: %.2f C \n", address,temperature);

	// MYSQL INSERTION
	if ( DB_MYSQL == 1){
				
		mysql_insert("INSERT IGNORE INTO devices (dc_id,last_update,packettype,subtype,int_id,address,com,home_data1) SELECT IFNULL(MAX(dc_id),0)+1,NOW(),'1W28','01',2,'%s','tx', %.2f FROM devices ON DUPLICATE KEY UPDATE last_update=NOW(),home_data1=%.2f;\
					INSERT INTO temperature (dc_id,datetime,temperature) VALUES ((select dc_id from devices where address='%s' LIMIT 1),NOW(),%.2f);\
					",address,temperature,temperature,address,temperature);
	}	
	
	if ( MDB_CLOUD == 1){
	
		MYSQL *conn;
		MYSQL_RES *result;
		MYSQL_ROW row;
		
		int iss_status=0;
		char iss_stream[32];
		int enable=0;
		int deleted=0;
		
		/*Recherche des parametres du status ISS*/	
		conn = mysql_connection();
		result = mysql_select(conn,"SELECT iss_status,iss_stream,enable,deleted FROM devices WHERE address='%s' LIMIT 1;", address);
		
		int num_fields = mysql_num_fields(result);
	
			while (row = mysql_fetch_row(result)){
				iss_status = atoi(row[0]);
				strcpy(iss_stream, row[1]);
				enable = atoi(row[2]);
				deleted = atoi(row[3]);
			};
			
		mysql_free_result(result);
		mysql_close(conn);
	
		log_DEBUG("MDB Cloud: ISS status : %d  Name: %s",iss_status,iss_stream);
	
		if (( iss_status == 1) && ( enable == 1) && (deleted== 0)){
			//post_ISS(iss_stream,"{\"unit\":{\"label\":\"Celsius\",\"symbol\": \"C\" },\"value\":\"%.2f\"}",temperature);
			post_stream_value(iss_stream,"[{ \"value\": \"%d\" }]",temperature);
		}

	}
}


