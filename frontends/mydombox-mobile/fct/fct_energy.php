<?php 
include"../inc/db.php";

if(isset($_POST["action"]))      $action=$_POST["action"];
else      $action="";
if(isset($_POST["dc_id"]))      $dc_id=$_POST["dc_id"];
else      $dc_id="";

switch($action)
{

    case 'display';
		EN_DISPLAY();
		break;
    case 'graph';
		EN_GRAPH();
		break;		
    case 'display_edf';
		EN_EDF_DISPLAY();
		break;	
}

/*
 * Funstion: EN_DISPLAY
 * variables: dc_id
 * comment: Display Energy Data as Json
 * End:
 */
function EN_DISPLAY(){

	global $dc_id;
	
	$order = "SELECT devices.dc_name AS name, energy.datetime, energy.instant, energy.total FROM energy 
	INNER JOIN devices USING (dc_id)
	WHERE dc_id=$dc_id ORDER BY id DESC limit 1;";

	$result = mysql_query($order);
	$jsonData = array();

	while ($array = mysql_fetch_assoc($result)) {
		$jsonData[] = $array;
	}
	echo json_encode($jsonData);
}

function EN_GRAPH(){

	global $dc_id;
	
	$order = "SELECT datetime, instant FROM energy
	WHERE dc_id=$dc_id AND datetime > DATE_SUB(NOW(), INTERVAL 24 HOUR);";

	$result = mysql_query($order);
	$jsonData = array();
	
	while ($row = mysql_fetch_array($result)) {
		$jsonData[]=array($row['datetime'],floatval($row['instant']));
	}
	echo json_encode($jsonData);
}


/*
 * Funstion: EN_EDF_DISPLAY
 * variables: dc_id
 * comment: Display Energy Data as Json
 * End:
 */
function EN_EDF_DISPLAY(){

	global $dc_id;
	
	$order = "SELECT devices.dc_name AS name,  devices.subtype, energy_edf.* FROM energy_edf
	INNER JOIN devices USING (dc_id)
	WHERE dc_id=$dc_id ORDER BY id DESC limit 1;";

	$result = mysql_query($order);
	$jsonData = array();

	while ($array = mysql_fetch_assoc($result)) {
		$jsonData[] = $array;
	}
	echo json_encode($jsonData);
}

?>
