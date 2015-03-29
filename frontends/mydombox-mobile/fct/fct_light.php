<?php 
include"../inc/db.php";

if(isset($_POST["action"]))      $action=$_POST["action"];
else      $action="";
if(isset($_POST["dc_id"]))      $dc_id=$_POST["dc_id"];
else      $dc_id="";
if(isset($_POST["mode"]))      $mode=$_POST["mode"];
else      $mode="";

switch($action)
{
    case 'display';
		LI_DISPLAY();
		break;
    case 'update';
		LI_UPDATE();
		break;			
}


/*
 * Funstion: LI_DISPLAY
 * variables: dc_id
 * comment: Display Lighting Device as Json
 * End:
 */
function LI_DISPLAY(){

	global $dc_id;

	$order = "SELECT devices.dc_id, devices.dc_name AS name, state.device_mode AS mode, devices.packettype As packettype FROM state INNER JOIN devices USING (dc_id) WHERE dc_id=$dc_id;";
	
	$result = mysql_query($order);
	$jsonData = array();

	while ($array = mysql_fetch_assoc($result)) {
		$jsonData[] = $array;
	}
	echo json_encode($jsonData);
}

/*
 * Funstion: LI_UPDATE
 * variables: dc_id,mode
 * comment: Change light state
 * End:
 */
function LI_UPDATE(){

	global $mode,$dc_id;

	require_once '../inc/mydombox.php';
	$client = new mydombox();

	$input = new setLightingStatus();
	$input->DeviceID = $dc_id;
	$input->State = $mode;

	try{
	   $response=$client->setLightingStatus($input);
		//echo $response->DeviceID;
		//echo $response->State;
	}
	catch (Exception $e){
	   echo $e->getMessage();
	}

	if ($response->State ==  $mode) {
		if($mode == 'on') { 
			$order = "UPDATE state INNER JOIN devices USING (dc_id) SET state.device_mode='on', state.dim_level='0F' WHERE dc_id=$dc_id;";
			} 
		else { 
			$order = "UPDATE state INNER JOIN devices USING (dc_id) SET state.device_mode='off', state.dim_level='00' WHERE dc_id=$dc_id;";
			}
	
		$result = mysql_query($order);
		if($result) {
			echo 0;
		} else {
			echo 2;
		}
	}
	else
	{
	echo 1;
	}
	

}
?>
