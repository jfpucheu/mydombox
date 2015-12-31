/* mdb_decode_enocean_message.c */

#include <stdio.h>   /* Standard input/output definitions */
#include <stdlib.h>
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

#include "mdb_log.h"
#include "mdb_enocean_const.h"
#include "mdb_mysql.h"
#include "mdb_tools.h"

extern 	int 	RECORD;

float enDecodeTemperature(int ScaleMin,int ScaleMax,int RangeMin,int RangeMax,int RawData)
{
    
    float multiplier = (ScaleMax - ScaleMin)*1.0 / (RangeMax - RangeMin);
    float value = multiplier * (RawData-RangeMin) + ScaleMin;
    
    return value;
}

float enDecodeTemperature10bit(float ScaleMin,float ScaleMax,int RangeMin,int RangeMax,unsigned char RawData1,unsigned char RawData2)
{
    int RawData = (int)RawData2;
    
    if (RawData1 & 0x01 ? 1 : 0)
        RawData = RawData + 512;
        
    if (RawData1 & 0x02 ? 1 : 0)
        RawData = RawData + 1024;

    
    float multiplier = (ScaleMax - ScaleMin)*1.0 / (RangeMax - RangeMin);
    float value = multiplier * (RawData-RangeMin) + ScaleMin;
    
    return value;
}

void print_device(EnDevice variable){
    
    log_DEBUG("[EnDevice] dc_id = %d",variable.dc_id);
    log_DEBUG("[EnDevice] rorg = %02hhX",variable.rorg);
    log_DEBUG("[EnDevice] func = %02hhX",variable.func);
    log_DEBUG("[EnDevice] type = %02hhX",variable.type);
    log_DEBUG("[EnDevice] id1 = %02hhX",variable.id1);
    log_DEBUG("[EnDevice] id2 = %02hhX",variable.id2);
    log_DEBUG("[EnDevice] id3 = %02hhX",variable.id3);
    log_DEBUG("[EnDevice] id4 = %02hhX",variable.id4);
    log_DEBUG("[EnDevice] enable = %d",variable.enable);
    
}

EnDevice GetEnDevice(char* data){
    
    EnDevice device;
    device.dc_id = 0;
    
    unsigned char		packettype = data[0];
    unsigned char		id1 = "";
    unsigned char		id2 = "";
    unsigned char		id3 = "";
    unsigned char		id4 = "";
    
    switch (packettype)
    {
    case 0xD5:
        id1 = data[2];
        id2 = data[3];
        id3 = data[4];
        id4 = data[5];
        break;
    case 0xF6:
        id1 = data[2];
        id2 = data[3];
        id3 = data[4];
        id4 = data[5];
        break;
    case 0xA5:
        id1 = data[5];
        id2 = data[6];
        id3 = data[7];
        id4 = data[8];
        break;
    case 0xD2:
        id1 = data[7];
        id2 = data[8];
        id3 = data[9];
        id4 = data[10];
        break;
    default:
        log_DEBUG("[EnOcean] TYPE: Not Supported");
        break;
    }

    MYSQL *conn;
    MYSQL_RES *result;
    MYSQL_ROW row;
    
    conn = mysql_connection();
    result = mysql_select(conn,"SELECT dc_id,packettype,subtype,type,id1,id2,id3,id4,enable FROM devices \
                          WHERE int_id=%d AND id1='%02hhX'AND id2='%02hhX'AND id3='%02hhX'AND id4='%02hhX';",4,id1,id2,id3,id4);
    
    int num_fields = mysql_num_fields(result);
    if (num_fields != 0) {
        
        while ((row = mysql_fetch_row(result))){
            
            device.dc_id = atoi(row[0]);
            device.rorg = stringtohex(row[1]);
            device.func = stringtohex(row[2]);
            device.type = stringtohex(row[3]);
            device.id1 = stringtohex(row[4]);
            device.id2 = stringtohex(row[5]);
            device.id3 = stringtohex(row[6]);
            device.id4 = stringtohex(row[7]);
            device.enable=(bool)row[8];
        }
    }
    return device;
}

bool addEnoceanDevice(char* data)
{
    unsigned char		rorg = data[0];
    unsigned char		id1 = "";
    unsigned char		id2 = "";
    unsigned char		id3 = "";
    unsigned char		id4 = "";
    
    switch (rorg)
    {
        case 0xD5:
            id1 = data[2];
            id2 = data[3];
            id3 = data[4];
            id4 = data[5];
            break;
        case 0xF6:
            id1 = data[2];
            id2 = data[3];
            id3 = data[4];
            id4 = data[5];
            break;
        case 0xA5:
            id1 = data[5];
            id2 = data[6];
            id3 = data[7];
            id4 = data[8];
            break;
        case 0xD2:
            id1 = data[7];
            id2 = data[8];
            id3 = data[9];
            id4 = data[10];
            break;
        default:
            log_DEBUG("[EnOcean] TYPE: Not Supported");
            break;
    }
    
    log_DEBUG("[EnOcean] Record Mode : %d", RECORD);
    if (RECORD == 1) {
        log_INFO("[EnOcean] Recording new device type : %02hhX",rorg);
        mysql_insert("INSERT IGNORE INTO devices (dc_id,last_update,packettype,int_id,id1,id2,id3,id4,com) \
                     SELECT IFNULL(MAX(dc_id),0)+1,NOW(),'%02hhX',4,'%02hhX','%02hhX','%02hhX','%02hhX','tx' FROM devices ON DUPLICATE KEY UPDATE last_update=NOW();",\
                     rorg,id1,id2,id3,id4);
    }
    return 0;
}

bool enMessage_0XD5(char* data)
{
    unsigned char		packettype = data[0];
    char 				contact_text[8];
    char 				lean_button_text[16];
    unsigned char		id1 = data[2];
    unsigned char		id2 = data[3];
    unsigned char		id3 = data[4];
    unsigned char		id4 = data[5];
    
    EnDevice device;
    addEnoceanDevice(data);
    device = GetEnDevice(data);
    print_device(device);
    
    if (device.dc_id != 0){
        
    	if (data[1] & 0x01 ? 1 : 0)
        	sprintf( contact_text,"closed");
    	else
        	sprintf( contact_text,"open");
    
    	if (data[1] & 0x08 ? 1 : 0)
        	sprintf( lean_button_text,"not pressed");
    	else
        	sprintf( lean_button_text,"pressed");

            
        mysql_insert("INSERT INTO state (dc_id,datetime,device_mode) VALUES (%d,NOW(),'%s')\
                         ON DUPLICATE KEY UPDATE device_mode='%s';",device.dc_id,contact_text,contact_text);

    	log_DEBUG("\n\n [EnOcean] \n Packetype: 1BS Telegram  \n id1: %02hhX  \n id2: %02hhX \n id3: %02hhX  \n id4: %02hhX \n Learn Button: %s \n Contact: %s \n",id1,id2,id3,id4,lean_button_text,contact_text);
    }
    
}

bool enMessage_0XA5(char* data)
{
    unsigned char		packettype = data[0];
    char 				LRN_Bit_text[20];
    float temperature;
    int humidity;
    unsigned char		id1 = data[5];
    unsigned char		id2 = data[6];
    unsigned char		id3 = data[7];
    unsigned char		id4 = data[8];
    
    EnDevice device;
    addEnoceanDevice(data);
    device = GetEnDevice(data);
    print_device(device);
    
    log_DEBUG("[EnOcean] device: %d",device.dc_id);

    if (device.dc_id != 0){
        
        // Decoding LRN Bit for all 0x0A5
        if (data[1] & 0x08 ? 1 : 0)
            sprintf( LRN_Bit_text,"Data telegram");
        else
            sprintf( LRN_Bit_text,"Teach-in telegram");
        // ------------------------------
        
        switch (device.func)
        {
            case 0x02:
                log_DEBUG("[EnOcean] FUNC: 02 Temperature Sensors");
                switch (device.type)
                {
                case 0x01:
                    log_DEBUG("[EnOcean] TYPE: 01 Temperature Sensor Range -40°C to 0°C");
                    temperature = enDecodeTemperature(-40,0,255,0,(int)data[3]);
                    break;
                case 0x02:
                    log_DEBUG("[EnOcean] TYPE: 02 Temperature Sensor Range -30°C to +10°C");
                    temperature = enDecodeTemperature(-30,10,255,0,(int)data[3]);
                    break;
                case 0x03:
                    log_DEBUG("[EnOcean] TYPE: 03 Temperature Sensor Range -20°C to +20°C");
                    temperature = enDecodeTemperature(-20,20,255,0,(int)data[3]);
                    break;
                case 0x04:
                    log_DEBUG("[EnOcean] TYPE: 04 Temperature Sensor Range -10°C to +30°C");
                    temperature = enDecodeTemperature(-10,30,255,0,(int)data[3]);
                    break;
                case 0x05:
                    log_DEBUG("[EnOcean] TYPE: 05 Temperature Sensor Range 0°C to +40°C");
                    temperature = enDecodeTemperature(0,40,255,0,(int)data[3]);
                    break;
                case 0x06:
                    log_DEBUG("[EnOcean] TYPE: 06 Temperature Sensor Range +10°C to +50°C");
                    temperature = enDecodeTemperature(10,50,255,0,(int)data[3]);
                    break;
                case 0x07:
                    log_DEBUG("[EnOcean] TYPE: 07 Temperature Sensor Range +20°C to +60°C");
                    temperature = enDecodeTemperature(20,60,255,0,(int)data[3]);
                    break;
                case 0x08:
                    log_DEBUG("[EnOcean] TYPE: 08 Temperature Sensor Range +30°C to +70°C");
                    temperature = enDecodeTemperature(30,70,255,0,(int)data[3]);
                    break;
                case 0x09:
                    log_DEBUG("[EnOcean] TYPE: 09 Temperature Sensor Range +40°C to +80°C");
                    temperature = enDecodeTemperature(40,80,255,0,(int)data[3]);
                    break;
                case 0x0A:
                    log_DEBUG("[EnOcean] TYPE: 0A Temperature Sensor Range +50°C to +90°C");
                    temperature = enDecodeTemperature(50,90,255,0,(int)data[3]);
                    break;
                case 0x0B:
                    log_DEBUG("[EnOcean] TYPE: 0B Temperature Sensor Range +60°C to +100°C");
                    temperature = enDecodeTemperature(60,100,255,0,(int)data[3]);
                    break;
                case 0x10:
                    log_DEBUG("[EnOcean] TYPE: 10 Temperature Sensor Range -60°C to +20°C");
                    temperature = enDecodeTemperature(-60,20,255,0,(int)data[3]);
                    break;
                case 0x11:
                    log_DEBUG("[EnOcean] TYPE: 11 Temperature Sensor Range -50°C to +30°C");
                    temperature = enDecodeTemperature(-50,30,255,0,(int)data[3]);
                    break;
                case 0x12:
                    log_DEBUG("[EnOcean] TYPE: 12 Temperature Sensor Range -40°C to +40°C");
                    temperature = enDecodeTemperature(-40,40,255,0,(int)data[3]);
                    break;
                case 0x13:
                    log_DEBUG("[EnOcean] TYPE: 13 Temperature Sensor Range -30°C to +50°C");
                    temperature = enDecodeTemperature(-30,50,255,0,(int)data[3]);
                    break;
                case 0x14:
                    log_DEBUG("[EnOcean] TYPE: 14 Temperature Sensor Range -20°C to +60°C");
                    temperature = enDecodeTemperature(-20,60,255,0,(int)data[3]);
                    break;
                case 0x15:
                    log_DEBUG("[EnOcean] TYPE: 15 Temperature Sensor Range -10°C to +70°C");
                    temperature = enDecodeTemperature(-10,70,255,0,(int)data[3]);
                    break;
                case 0x16:
                    log_DEBUG("[EnOcean] TYPE: 16 Temperature Sensor Range 0°C to +80°C");
                    temperature = enDecodeTemperature(0,80,255,0,(int)data[3]);
                    break;
                case 0x17:
                    log_DEBUG("[EnOcean] TYPE: 17 Temperature Sensor Range +10°C to +90°C");
                    temperature = enDecodeTemperature(10,90,255,0,(int)data[3]);
                    break;
                case 0x18:
                    log_DEBUG("[EnOcean] TYPE: 18 Temperature Sensor Range +20°C to +100°C");
                    temperature = enDecodeTemperature(20,100,255,0,(int)data[3]);
                    break;
                case 0x19:
                    log_DEBUG("[EnOcean] TYPE: 19 Temperature Sensor Range +30°C to +110°C");
                    temperature = enDecodeTemperature(30,110,255,0,(int)data[3]);
                    break;
                case 0x1A:
                    log_DEBUG("[EnOcean] TYPE: 1A Temperature Sensor Range +40°C to +120°C");
                    temperature = enDecodeTemperature(40,120,255,0,(int)data[3]);
                    break;
                case 0x1B:
                    log_DEBUG("[EnOcean] TYPE: 1B Temperature Sensor Range +50°C to +130°C");
                    temperature = enDecodeTemperature(50,130,255,0,(int)data[3]);
                    break;
                case 0x20:
                    log_DEBUG("[EnOcean] TYPE: 20 10 Bit Temperature Sensor Range -10°C to +41.2°C");
                    temperature = enDecodeTemperature10bit(-10,41.2,1023,0,data[2],data[3]);
                    break;
                case 0x30:
                    log_DEBUG("[EnOcean] TYPE: 30 10 Bit Temperature Sensor Range -40°C to +62.3°C");
                    temperature = enDecodeTemperature10bit(-40,62.3,1023,0,data[2],data[3]);
                    break;
                default:
                    log_DEBUG("[EnOcean] TYPE: Not Supported");
                    break;
            }
                mysql_insert("UPDATE devices SET last_update=NOW(),home_data1=%.2f WHERE dc_id=%d; \
                INSERT INTO weather (dc_id,datetime,temperature) VALUES ( %d, NOW(), %.2f);",temperature,device.dc_id,device.dc_id,temperature);
                log_DEBUG("\n\n [EnOcean] \n Packetype: A5 Telegram  \n id1: %02hhX  \n id2: %02hhX \n id3: %02hhX  \n id4: %02hhX \n Learn Button: %s \n temperature: %.2f \n",id1,id2,id3,id4,LRN_Bit_text,temperature);
                break;
            case 0x04:
                log_DEBUG("[EnOcean] FUNC: 04 Temperature and Humidity Sensor");
                switch (device.type)
                {
                case 0x01:
                    log_DEBUG("[EnOcean] TYPE: 01 Range 0°C to +40°C and 0% to 100%");
                    temperature = enDecodeTemperature(0,40,0,250,(int)data[3]);
                    humidity = (int)enDecodeTemperature(0,100,0,250,(int)data[2]);
                    break;
                case 0x02:
                    log_DEBUG("[EnOcean] TYPE: 02 Range -20°C to +60°C and 0% to 100%");
                    temperature = enDecodeTemperature(-20,60,0,250,(int)data[3]);
                    humidity = (int)enDecodeTemperature(0,100,0,250,(int)data[2]);
                    break;
                case 0x03:
                    log_DEBUG("[EnOcean] TYPE: 03 Range -20°C to +60°C 10bit-measurement and 0% to 100%");
                    temperature = enDecodeTemperature10bit(-20,60,0,1023,data[2],data[3]);
                    humidity = (int)enDecodeTemperature(0,100,0,255,(int)data[1]);
                    break;
                default:
                    log_DEBUG("[EnOcean] TYPE: Not Supported");
                    break;
            }
                mysql_insert("UPDATE devices SET last_update=NOW(),home_data1=%.2f,home_data2=%d WHERE dc_id=%d; \
                INSERT INTO weather (dc_id,datetime,temperature,humidity) VALUES (%d,NOW(),%.2f,%d);",temperature,humidity,device.dc_id,device.dc_id,temperature,humidity);
                log_DEBUG("\n\n [EnOcean] \n Packetype: A5 Telegram  \n id1: %02hhX  \n id2: %02hhX \n id3: %02hhX  \n id4: %02hhX \n Learn Button: %s \n temperature: %.2f \n humidity: %d \n",id1,id2,id3,id4,LRN_Bit_text,temperature,humidity);
                break;
            case 0x05:
                log_DEBUG("[EnOcean] FUNC: 05 Barometric Sensor");
                switch (device.type)
                {
                case 0x01:
                    log_DEBUG("[EnOcean] TYPE: 01 Range 500 to 1150 hPa");
                    break;
                default:
                    log_DEBUG("[EnOcean] TYPE: Not Supported");
                    break;
                }
                break;
            case 0x06:
                log_DEBUG("[EnOcean] FUNC: 06 Light Sensor");
                switch (device.type)
                {
                case 0x02:
                    log_DEBUG("[EnOcean] TYPE: Range 0lx to 1.020lx");
                    break;
                case 0x03:
                    log_DEBUG("[EnOcean] TYPE: 10-bit measurement (1-Lux resolution) with range 0lx to 1000lx");
                    break;
                default:
                    log_DEBUG("[EnOcean] TYPE: Not Supported");
                    break;
            }
                break;
            default:
                log_DEBUG("[EnOcean] RORG: Not Supported \r\n");
                break;
        }
    }
    return true;
}


bool decodeEnoceanRadio(char* data)
{
    if(data == NULL) return false;
    
    log_DEBUG("[EnOcean] byte 1: %02x",data[0]);
    
    switch (data[0])
    {
        case 0xD5:
            enMessage_0XD5(data);
            break;
        case 0xA5:
            enMessage_0XA5(data);
            break;
        default:
            log_DEBUG("[EnOcean] RORG: Not Supported \r\n");
            break;
    }
    return true;
}