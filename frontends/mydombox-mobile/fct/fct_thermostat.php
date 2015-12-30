<?php 
include"../inc/db.php";

if(isset($_POST["action"]))      $action=$_POST["action"];
else      $action="";
if(isset($_POST["th_id"]))      $th_id=$_POST["th_id"];
else      $th_id="";
if(isset($_POST["th_use"]))      $th_use=$_POST["th_use"];
else      $th_use="";
if(isset($_POST["th_mode"]))      $th_mode=$_POST["th_mode"];
else      $th_mode="";
if(isset($_POST["tp_set"]))      $tp_set=$_POST["tp_set"];
else      $tp_set="";
if(isset($_POST["sc_id"]))      $sc_id=$_POST["sc_id"];
else      $sc_id="";
if(isset($_POST["th_name"]))      $th_name=$_POST["th_name"];
else      $th_name="";
if(isset($_POST["sensor_id"]))      $sensor_id=$_POST["sensor_id"];
else	$sensor_id="";
if(isset($_POST["recept_id"]))      $recept_id=$_POST["recept_id"];
else      $recept_id="";

switch($action)
{
    case 'list';
		TH_LIST();
		break;
    case 'update';
		TH_UPDATE();
		break;
    case 'settings';
		TH_SETTINGS();
		break;
    case 'display';
		TH_DISPLAY();
		break;
	case 'list-devices';
		TH_LIST_DEVICES();
		break;
	case 'new';
		TH_NEW();
		break;
	case 'delete';
		TH_DELETE();
		break;		
}

/*
 * Funstion: TH_LIST
 * variables: 
 * comment: Display Thermostats as Json
 * End:
 */
function TH_LIST(){

	$dw = date( "w", time() );
	if ($dw == 0)	$dw = 7;

	$order = "SELECT sc_id,th_id,th_name,th_use,th_mode,tp_set, home_screen,
	(SELECT scenario.tp_prog from scenario WHERE ((sc_day= '$dw') OR (sc_day= 0)) AND (sc_periode_start < CURRENT_TIME) AND ( CURRENT_TIME < sc_periode_stop) AND thermostat.sc_id=scenario.sc_id ) AS tp_prog 
	FROM thermostat;"; 

	$result = mysql_query($order);
	$jsonData = array();

	while ($array = mysql_fetch_assoc($result)) {
		$jsonData[] = $array;
	}
	echo json_encode($jsonData);
}

/*
 * Funstion: TH_UPDATE
 * variables: 
 * comment: Update thermostat informations
 * End:
 */
function TH_UPDATE(){

	
	global $th_id;
	global $th_use;
	global $th_mode;
	global $tp_set;
	global $sc_id;

	$order = "UPDATE thermostat SET th_use='$th_use', th_mode='$th_mode', tp_set='$tp_set',sc_id='$sc_id' WHERE th_id='$th_id';";
	
	$result = mysql_query($order);
	
	if($result) {
		echo 0;
	} else {
		echo 1;
	}
}

/*
 * Funstion: TH_SETTINGS
 * variables: 
 * comment: Update thermostat settings informations
 * End:
 */
function TH_SETTINGS(){

	global $th_id;
	global $th_name;
	global $sensor_id;
	global $recept_id;

	if ($sensor_id == "" || $recept_id == ""){
		echo 2;
		exit;
	}
	
	$order = "UPDATE thermostat set th_name='$th_name',sensor_id='$sensor_id',recept_id='$recept_id' WHERE th_id='$th_id';";
	
	$result = mysql_query($order);
	
	if($result) {
		echo 0;
	} else {
		echo 1;
	}
}

/*
 * Funstion: TH_DISPLAY
 * variables: 
 * comment: Display Thermostats as Json
 * End:
 */

function TH_DISPLAY(){
	
	global $th_id;
	
	$order = "SELECT * FROM thermostat where th_id='$th_id';";
	$result = mysql_query($order);
	$jsonData = array();

	while ($array = mysql_fetch_assoc($result)) {
		$jsonData[] = $array;
	}
	echo json_encode($jsonData);
}

/*
 * Funstion: TH_SETUP
 * variables: 
 * comment: Display Thermostats as Json
 * End:
 */

function TH_LIST_DEVICES(){
	
	$order = "SELECT dc_id,packettype,dc_name,com FROM devices WHERE packettype IN('40','50','51','52','1W28') AND deleted=0;";
	$result = mysql_query($order);
	$jsonData = array();

	while ($array = mysql_fetch_assoc($result)) {
		$jsonData[] = $array;
	}
	echo json_encode($jsonData);
}

/*
 * Funstion: TH_NEW
 * variables: 
 * comment: Créate new thermostat
 * End:
 */
function TH_NEW(){
		
	$order = "INSERT INTO thermostat (th_id,sensor_id,recept_id,th_name,th_use,th_mode,tp_set,sc_id,home_screen) SELECT (SELECT MAX(th_id)+1 FROM thermostat) as th_id,0,0,'New Thermostat','off','manual',18,0,'1';";
	
	$result = mysql_query($order);
	
	if($result) {
		echo 0;
	} else {
		echo 1;
	}

}	
/*
 * Funstion: TH_DELETE
 * variables: th_id
 * comment: delete thermostat from database
 * End:
 */
function TH_DELETE(){
	
	global $th_id;
	global $sensor_id;
	global $recept_id;

	if ($th_id == ""){
		echo 2;
		exit;
	}
	
	$order = "DELETE FROM thermostat WHERE th_id='$th_id'";
	$result = mysql_query($order);
	$order = "DELETE FROM scenario_info WHERE th_id='$th_id'";
	$result2 = mysql_query($order);
	
	if($result and $result2) {
		echo 0;
	}
	else {
		echo 1;
	}
}

?>
