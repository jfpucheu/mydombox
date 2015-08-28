<?php 
include"../inc/db.php";

if(isset($_POST["action"]))      $action=$_POST["action"];
else      $action="";

switch($action)
{
	case 'home_screen';
		HOME_SCREEN();
		break;
	case 'temperature_screen';
		TEMPERATURE_SCREEN();
		break;
	case 'light_screen';
		LIGHT_SCREEN();
		break;
	case 'energy_screen';
		ENERGY_SCREEN();
		break;
	case 'weather_screen';
		WEATHER_SCREEN();
		break;
	case 'windore_screen';
		WINDORE_SCREEN();
		break;		
}

/*
 * Funstion: HOME_SCREEN
 * variables: 
 * comment: Display homescreen Device List as Json
 * End:
 */
function HOME_SCREEN(){

	$order = "SELECT dc_id,dc_name,last_update,int_id,packettype,subtype,home_data1,home_data2,home_data3,device_mode FROM devices LEFT JOIN state USING (dc_id) WHERE deleted=0 AND home_screen=1 AND com='tx' AND new=0;"; 

	$result = mysql_query($order);
	$jsonData = array();

	while ($array = mysql_fetch_assoc($result)) {
		$jsonData[] = $array;
	}
	echo json_encode($jsonData);
}

/*
 * Funstion: TEMPERATURE_SCREEN
 * variables: 
 * comment: Display temperature_screen Device List as Json
 * End:
 */
function TEMPERATURE_SCREEN(){

	$order = "SELECT dc_id,dc_name,last_update,int_id,packettype,subtype,home_data1,home_data2,home_data3 FROM devices WHERE deleted=0 AND com='tx' AND new=0 AND int_id IN (1,4) AND packettype IN ('40','52','1W28','A5');"; 

	$result = mysql_query($order);
	$jsonData = array();

	while ($array = mysql_fetch_assoc($result)) {
		$jsonData[] = $array;
	}
	echo json_encode($jsonData);
}

/*
 * Funstion: LIGHT_SCREEN
 * variables: 
 * comment: Display light_screen Device List as Json
 * End:
 */
function LIGHT_SCREEN(){

	$order = "SELECT dc_id,dc_name,last_update,int_id,packettype,subtype,device_mode FROM devices LEFT JOIN state USING (dc_id) WHERE deleted=0 AND com='tx' AND new=0 AND packettype IN ('11','14','WP');"; 

	$result = mysql_query($order);
	$jsonData = array();

	while ($array = mysql_fetch_assoc($result)) {
		$jsonData[] = $array;
	}
	echo json_encode($jsonData);
}

/*
 * Funstion: ENERGY_SCREEN
 * variables: 
 * comment: Display energy_screen Device List as Json
 * End:
 */
function ENERGY_SCREEN(){

	$order = "SELECT dc_id,dc_name,last_update,int_id,packettype,subtype,home_data1,home_data2,home_data3 FROM devices WHERE deleted=0 AND com='tx' AND new=0 AND packettype IN ('5A','ERDF');"; 

	$result = mysql_query($order);
	$jsonData = array();

	while ($array = mysql_fetch_assoc($result)) {
		$jsonData[] = $array;
	}
	echo json_encode($jsonData);
}

/*
 * Funstion: WEATHER_SCREEN
 * variables: 
 * comment: Display weather_screen Device List as Json
 * End:
 */
function WEATHER_SCREEN(){

	$order = "SELECT dc_id,dc_name,last_update,int_id,packettype,subtype,home_data1,home_data2,home_data3 FROM devices WHERE deleted=0 AND com='tx' AND new=0 AND packettype IN ('52','55','56');"; 

	$result = mysql_query($order);
	$jsonData = array();

	while ($array = mysql_fetch_assoc($result)) {
		$jsonData[] = $array;
	}
	echo json_encode($jsonData);
}

/*
 * Funstion: WINDORE_SCREEN
 * variables: 
 * comment: Display windore_screen Device List as Json
 * End:
 */
function WINDORE_SCREEN(){

	$order = $order = "SELECT dc_id,dc_name,last_update,int_id,packettype,subtype,device_mode FROM devices LEFT JOIN state USING (dc_id) WHERE deleted=0 AND com='tx' AND new=0 AND packettype IN ('D5','1A');"; 

	$result = mysql_query($order);
	$jsonData = array();

	while ($array = mysql_fetch_assoc($result)) {
		$jsonData[] = $array;
	}
	echo json_encode($jsonData);
}

?>