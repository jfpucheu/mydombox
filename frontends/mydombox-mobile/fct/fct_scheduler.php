<?php 
include"../inc/db.php";

if(isset($_POST["action"]))      $action=$_POST["action"];
else      $action="";
if(isset($_POST["dc_id"]))      $dc_id=$_POST["dc_id"];
else      $dc_id="";
if(isset($_POST["sch_id"]))      $sch_id=$_POST["sch_id"];
else      $sch_id="";
if(isset($_POST["sch_day"]))      $sch_day=$_POST["sch_day"];
else      $sch_day="";
if(isset($_POST["sch_time"]))      $sch_time=$_POST["sch_time"];
else      $sch_time="";
if(isset($_POST["sch_action"]))      $sch_action=$_POST["sch_action"];
else      $sch_action="";


switch($action)
{
    case 'display';
		DISPLAY_PROGRAM();
		break;
    case 'update';
		PROGRAM_UPDATE();
		break;
	case 'delete';
		PROGRAM_DELETE();
		break;				
}


/*
 * Funstion: DISPLAY_PROGRAM
 * variables: dc_id
 * comment: Display Light Program as json
 * End:
 */
function DISPLAY_PROGRAM(){
	
	global $dc_id;

	$order = "SELECT sch_id,sch_day,TIME_FORMAT(sch_time,'%H:%i') AS sch_time,sch_action FROM scheduler WHERE dc_id='$dc_id' ORDER BY sch_time;";

	$result = mysql_query($order);

	$jsonData = array();

	while ($array = mysql_fetch_array($result)) {
		$jsonData[] = $array;
	}
	echo json_encode($jsonData);
}

/*
 * Funstion: PROGRAM_UPDATE
 * variables: dc_id, sch_id, sch_day, sch_time, sch_action
 * comment: Update Programation
 * End:
 */
 
function PROGRAM_UPDATE(){
	
	global $dc_id, $sch_id, $sch_day, $sch_time, $sch_action;
	
	if ( $sch_id == "new") {
		$order = "INSERT INTO scheduler (dc_id,sch_day,sch_time,sch_action) VALUES ('$dc_id','$sch_day','$sch_time','$sch_action');";	 
	} else {   
		$order = "UPDATE scheduler SET sch_day='$sch_day',sch_time='$sch_time',sch_action='$sch_action' WHERE sch_id='$sch_id';";
	}
	
	$result = mysql_query($order);
	if($result) {
		echo 0;
	} else {
		echo 1;
	}
}

/*
 * Funstion: PROGRAM_DELETE
 * variables: sch_id, 
 * comment: Delete programation
 * End:
 */
function PROGRAM_DELETE(){
	
	global $sch_id;
	
	$order = "DELETE FROM scheduler WHERE sch_id='$sch_id';";
	$result = mysql_query($order);
	
	if($result) {
		echo 0;
	} else {
		echo 1;
	}
}
?>
