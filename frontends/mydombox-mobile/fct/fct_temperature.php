<?php 
include"../inc/db.php";

if(isset($_POST["action"]))      $action=$_POST["action"];
else      $action="";
if(isset($_POST["dc_id"]))      $dc_id=$_POST["dc_id"];
else      $dc_id="";

switch($action)
{

    case 'display';
		TP_DISPLAY();
		break;
    case 'graph';
		TP_GRAPH();
		break;		
}


/*
 * Funstion: TP_DISPLAY
 * variables: 
 * comment: Display Temperature  as Json
 * End:
 */
function TP_DISPLAY(){

	global $dc_id;

	$order = "SELECT dc_id, packettype FROM devices  WHERE dc_id=$dc_id LIMIT 1;";

	$result = mysql_query($order);
	$row = mysql_fetch_array($result);

	// Packet Type 40 :
	if( $row['packettype']== 40 ) { 
		$order2 = "SELECT devices.dc_id, devices.dc_name as name, temperature.datetime, temperature.temperature from temperature 
		INNER JOIN devices USING (dc_id)
		WHERE dc_id=$dc_id order by id desc limit 1;";
	}
	// Packet Type 1W28 :
	elseif( $row['packettype']== '1W28' ) { 
		$order2 = "SELECT devices.dc_id, devices.dc_name as name, temperature.datetime, temperature.temperature from temperature 
		INNER JOIN devices USING (dc_id)
		WHERE dc_id=$dc_id order by id desc limit 1;";
	}
	//packet Type 52
	elseif( $row['packettype']== 52) { 
		$order2 = "SELECT devices.dc_id, weather.datetime AS datetime, devices.dc_name AS name, weather.temperature AS temperature
		FROM weather  
		INNER JOIN devices USING (dc_id) 
		WHERE packettype=52 AND dc_id=$dc_id ORDER BY id DESC limit 1 ;";
	} 
	// Packet Type A5 :
	elseif( $row['packettype']== 'A5' ) { 
		$order2 = "SELECT devices.dc_id, weather.datetime AS datetime, devices.dc_name AS name, weather.temperature AS temperature
		FROM weather  
		INNER JOIN devices USING (dc_id) 
		WHERE packettype='A5' AND dc_id=$dc_id ORDER BY id DESC limit 1 ;";
	}
	else {
	}

	$result2 = mysql_query($order2);
	$jsonData = array();

	while ($array = mysql_fetch_assoc($result2)) {
		$jsonData[] = $array;
	}
	echo json_encode($jsonData);
}

function TP_GRAPH(){

	global $dc_id;

	$order = "SELECT dc_id, packettype FROM devices  WHERE dc_id=$dc_id LIMIT 1;";

	$result = mysql_query($order);
	$row = mysql_fetch_array($result);

	// Packet Type 40 :
	if( $row['packettype']== 40 ) { 
		$order2 = " SELECT  datetime,temperature
		FROM temperature 
		WHERE dc_id=$dc_id AND datetime > DATE_SUB(NOW(), INTERVAL 24 HOUR);";
	}
	// Packet Type 1W28 :
	elseif( $row['packettype']== '1W28' ) { 
		$order2 = " SELECT  datetime,temperature
		FROM temperature 
		WHERE dc_id=$dc_id AND datetime > DATE_SUB(NOW(), INTERVAL 24 HOUR);";
	}
	//packet Type 52
	elseif( $row['packettype']== 52) {
		$order2 = " SELECT  datetime,temperature
		FROM weather 
		WHERE dc_id=$dc_id AND datetime > DATE_SUB(NOW(), INTERVAL 24 HOUR);";
	}
		//packet Type A5
	elseif( $row['packettype']== 'A5') {
		$order2 = " SELECT  datetime,temperature
		FROM weather 
		WHERE dc_id=$dc_id AND datetime > DATE_SUB(NOW(), INTERVAL 24 HOUR);";
	}
	else {
	}

	$result2 = mysql_query($order2);
	$jsonData = array();
	
	while ($row = mysql_fetch_array($result2)) {
		$jsonData[]=array($row['datetime'],floatval($row['temperature']));
	}
	echo json_encode($jsonData);
}

?>
