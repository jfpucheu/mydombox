<?php 
include"../inc/db.php";

if(isset($_POST["action"]))      $action=$_POST["action"];
else      $action="";
if(isset($_POST["sc_id"]))      $sc_id=$_POST["sc_id"];
else      $sc_id="";
if(isset($_POST["pg_id"]))      $pg_id=$_POST["pg_id"];
else      $pg_id="";
if(isset($_POST["start_time"]))      $start_time=$_POST["start_time"];
else      $start_time="";
if(isset($_POST["stop_time"]))      $stop_time=$_POST["stop_time"];
else      $stop_time="";
if(isset($_POST["tp_prog"]))      $tp_prog=$_POST["tp_prog"];
else      $tp_prog="";
if(isset($_POST["th_id"]))      $th_id=$_POST["th_id"];
else      $th_id="";
if(isset($_POST["sc_name"]))      $sc_name=$_POST["sc_name"];
else      $sc_name="";
if(isset($_POST["sc_type"]))      $sc_type=$_POST["sc_type"];
else      $sc_type="";
if(isset($_POST["sc_day"]))      $sc_day=$_POST["sc_day"];
else      $sc_day="";
if(isset($_POST["sc_day_ori"]))      $sc_day_ori=$_POST["sc_day_ori"];
else      $sc_day_ori="";
if(isset($_POST["sc_day_dest"]))      $sc_day_dest=$_POST["sc_day_dest"];
else      $sc_day_dest="";


switch($action)
{
	case 'list';
		SC_LIST();
		break;
    case 'display';
		SC_DISPLAY();
		break;
    case 'new';
		SC_NEW();
		break;
    case 'update';
		SC_UPDATE();
		break;
    case 'copy';
		SC_COPY();
		break;
	case 'delete';
		SC_DELETE();
		break;
    case 'delete-pg';
		SC_DELETE_PG();
		break;			
}

/*
 * Funstion: SC_LIST
 * variables: th_id
 * comment: Display Scenario for thermostat as json
 * End:
 */
function SC_LIST(){

	global $th_id;

	$order = "SELECT sc_id,sc_type,sc_name FROM scenario_info WHERE th_id='$th_id';";
	$result = mysql_query($order);
	$jsonData = array();

	while ($array = mysql_fetch_assoc($result)) {
		$jsonData[] = $array;
	}
	echo json_encode($jsonData);
}

/*
 * Funstion: SC_DISPLAY
 * variables: sc_id
 * comment: Display Scenario as json
 * End:
 */
function SC_DISPLAY(){
	
	global $sc_id;

	$order = "SELECT pg_id,sc_id,sc_day,TIME_FORMAT(sc_periode_start,'%H:%i') AS start, TIME_FORMAT(sc_periode_stop,'%H:%i') AS stop,tp_prog FROM scenario
	WHERE sc_id='$sc_id' ORDER BY sc_day,sc_periode_start;";

	$result = mysql_query($order);

	$jsonData = array();

	while ($array = mysql_fetch_array($result)) {
		$jsonData[] = $array;
	}
	echo json_encode($jsonData);
}

/*
 * Funstion: SC_NEW
 * variables: th_id, sc_name, sc_type
 * comment: Add new scenario to thermostat
 * End:
 */
function SC_NEW(){

	global $th_id, $sc_name, $sc_type;
	
	$check_name = "SELECT * FROM scenario_info WHERE th_id='$th_id' AND sc_name='$sc_name';";

	$availability_result = mysql_query($check_name);
		
	if ( mysql_num_rows($availability_result) == 0 ){
		// Name Available, process  insert
		$order = "INSERT INTO scenario_info (th_id,sc_type,sc_name) VALUES ('$th_id','$sc_type','$sc_name');";	 
		$result = mysql_query($order);
		if($result) {
			echo 0;
		} else {
			echo 2;
		}
	} else {
	// Name Not Available
	echo 1;
	}	
}


/*
 * Funstion: SC_UPDATE
 * variables: sc_id, pg_id, start_time, stop_time, tp_prog
 * comment: Update Scenario
 * End:
 */
 
function SC_UPDATE(){
	
	global $sc_id, $pg_id, $start_time, $stop_time, $tp_prog, $sc_day;
	
	// if stop time = 00:00 change to 23:59:59
	if ( $stop_time == "00:00"){
	$stop_time = "23:59:59";
	}

	$check_availability = "SELECT * FROM scenario WHERE sc_id='$sc_id' AND sc_day='$sc_day' AND (('$start_time' between sc_periode_start AND sc_periode_stop) 
	OR ('$stop_time' between sc_periode_start AND sc_periode_stop) 
	OR ('$start_time' >= sc_periode_start AND '$stop_time' <= sc_periode_stop)
	OR ('$start_time' <= sc_periode_start AND '$stop_time' >= sc_periode_stop))
	AND ('$start_time' != sc_periode_stop) AND ('$stop_time' != sc_periode_start)
	AND ('$start_time' != sc_periode_start) AND ('$stop_time' != sc_periode_stop);";

	//echo $check_availability;

	$availability_result = mysql_query($check_availability);
	if ( mysql_num_rows($availability_result) == 0 ){
	// Timeslot Available, process update or insert
		if ( $pg_id == "new") {
			$order = "INSERT INTO scenario (sc_id,sc_day,sc_periode_start,sc_periode_stop,tp_prog) VALUES ('$sc_id','$sc_day','$start_time','$stop_time','$tp_prog');";	 
		} else {   
			$order = "UPDATE scenario SET sc_day='$sc_day',sc_periode_start='$start_time',sc_periode_stop='$stop_time',tp_prog='$tp_prog' WHERE pg_id='$pg_id';";
		}
	
		$result = mysql_query($order);
		if($result) {
			echo 0;
		} else {
			echo 2;
		}
	} else {
	// Timeslot Not Available
		echo 1;
	}	
}

/*
 * Funstion: SC_COPY
 * variables: $sc_id, $sc_day_ori, $sc_day_dest;
 * comment: Copy Scenario day
 * End:
 */
 
function SC_COPY(){
	
	global $sc_id, $sc_day_ori, $sc_day_dest;

	$order = "INSERT INTO scenario (sc_id, sc_day, sc_periode_start, sc_periode_stop,tp_prog) SELECT sc_id, '$sc_day_dest', sc_periode_start, sc_periode_stop, tp_prog FROM scenario WHERE sc_id='$sc_id' AND sc_day='$sc_day_ori';";
	$result = mysql_query($order);
	if($result) {
		echo 0;
	} else {
		echo 2;
	}	
}

/*
 * Funstion: SC_DELETE_PG
 * variables: pg_id, 
 * comment: Delete programation
 * End:
 */
function SC_DELETE_PG()
{
	global $pg_id;
	
	$order = "DELETE FROM scenario WHERE pg_id='$pg_id';";
	$result = mysql_query($order);
	if($result) {
		echo 0;
	} else {
		echo 2;
	}
}

/*
 * Funstion: SC_DELETE
 * variables: th_id, sc_name, sc_type
 * comment: Add new scenario to thermostat
 * End:
 */
function SC_DELETE(){

	global $sc_id;
	
	$order1 = "DELETE FROM scenario WHERE sc_id='$sc_id';";
	$order2 = "DELETE FROM scenario_info WHERE sc_id='$sc_id';";
	$result = mysql_query($order1);
		if($result) {
			$result2 = mysql_query($order2);
			if($result2) {
				echo 0;
			} else {
				echo 1;
			}
		} else {
			echo 1;
		}
}

?>
