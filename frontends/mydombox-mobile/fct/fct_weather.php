<?php 
include"../inc/db.php";

if(isset($_POST["action"]))      $action=$_POST["action"];
else      $action="";
if(isset($_POST["dc_id"]))      $dc_id=$_POST["dc_id"];
else      $dc_id="";

switch($action)
{

    case 'display';
		WH_DISPLAY();
		break;	
    case 'graph';
		WH_GRAPH();
		break;	
}

/*
 * Funstion: WH_DISPLAY
 * variables: dc_id
 * comment: Display weather Data as Json
 * End:
 */
function WH_DISPLAY(){

	global $dc_id;
	
	$order ="SELECT devices.dc_id, devices.packettype, weather.datetime AS datetime, devices.dc_name AS name,
			weather.temperature AS temperature, 
			weather.humidity AS humidity,
			weather.rainrate /100 AS rainrate, 
			weather.raintotal /10 AS raintotal,
			weather.winddirection AS winddirection, 
			weather.av_speed AS av_speed
			FROM weather 
			INNER JOIN devices USING (dc_id)
			WHERE devices.dc_id=$dc_id ORDER BY id DESC LIMIT 1;";


	$result = mysql_query($order);
	$jsonData = array();

	while ($array = mysql_fetch_assoc($result)) {
		$jsonData[] = $array;
	}
	echo json_encode($jsonData);
}



function WH_GRAPH(){

	global $dc_id;

	$order = "SELECT dc_id, packettype FROM devices  WHERE dc_id=$dc_id LIMIT 1;";

	$result = mysql_query($order);
	$row = mysql_fetch_array($result);

	//packet Type 52
	if( $row['packettype']== 52) {
		$order2 = " SELECT datetime,temperature,humidity
		FROM weather 
		WHERE dc_id=$dc_id AND datetime > DATE_SUB(NOW(), INTERVAL 24 HOUR);";
		
		$result2 = mysql_query($order2);
		$jsonData = array();
	
		while ($row = mysql_fetch_array($result2)) {
			$jsonData[]=array($row['datetime'],floatval($row['temperature']),intval($row['humidity']));
		}	
	}
	else {
	}
	//packet Type 55
	if( $row['packettype']== 55) {
		$order2 = "SELECT DATE(datetime) AS data_time, (MAX(raintotal) - MIN(raintotal)) AS data 
		FROM weather 
		WHERE dc_id = $dc_id AND datetime  >= DATE_SUB(CURDATE(), INTERVAL 7 DAY) GROUP BY data_time;";
		
		$result2 = mysql_query($order2);
		$jsonData = array();
	
		while ($row = mysql_fetch_array($result2)) {
			$jsonData[]=array($row['data_time'],floatval($row['data']));
		}
	}
	else {
	}
	echo json_encode($jsonData);
}


?>
