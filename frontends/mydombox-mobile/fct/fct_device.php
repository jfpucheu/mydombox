<?php 
include"../inc/db.php";

if(isset($_POST["action"]))      $action=$_POST["action"];
else      $action="";
if(isset($_POST["mode"]))      $mode=$_POST["mode"];
else      $mode="";
if(isset($_POST["int_id"]))      $int_id=$_POST["int_id"];
else      $int_id="";
if(isset($_POST["dc_id"]))      $dc_id=$_POST["dc_id"];
else      $dc_id="";
if(isset($_POST["dc_name"]))      $dc_name=$_POST["dc_name"];
else      $dc_name="";
if(isset($_POST["type_id"]))      $type_id=$_POST["type_id"];
else      $type_id="";
if(isset($_POST["address"]))      $address=$_POST["address"];
else      $address="";
if(isset($_POST["id1"]))      $id1=$_POST["id1"];
else      $id1="";
if(isset($_POST["id2"]))      $id2=$_POST["id2"];
else      $id2="";
if(isset($_POST["id3"]))      $id3=$_POST["id3"];
else      $id3="";
if(isset($_POST["id4"]))      $id4=$_POST["id4"];
else      $id4="";
if(isset($_POST["com"]))      $com=$_POST["com"];
else      $com="";
if(isset($_POST["reverse"]))      $reverse=$_POST["reverse"];
else      $reverse="";
if(isset($_POST["unitcode"]))      $unitcode=$_POST["unitcode"];
else      $unitcode="";
if(isset($_POST["groupcode"]))      $groupcode=$_POST["groupcode"];
else      $groupcode="";
if(isset($_POST["housecode"]))      $housecode=$_POST["housecode"];
else      $housecode="";
if(isset($_POST["cloud"]))      $cloud=$_POST["cloud"];
else      $cloud="";
if(isset($_POST["cloud_id"]))      $cloud_id=$_POST["cloud_id"];
else      $cloud_id="";
if(isset($_POST["dc_logo"]))      $dc_logo=$_POST["dc_logo"];
else     $dc_logo="";

switch($action)
{

	case 'list';
		DC_LIST();
		break;
    case 'display';
		DC_DISPLAY();
		break;	
    case 'init';
		DC_INIT();
		break;
    case 'record';
		DC_RECORD();
		break;
    case 'update';
		DC_UPDATE();
		break;	
    case 'new';
		DC_NEW();
		break;			
    case 'confirm';
		DC_CONFIRM();
		break;
    case 'list-int';
		DC_LIST_INT();
		break;	
    case 'list-type';
		DC_LIST_TYPE();
		break;	
    case 'delete';
		DC_DELETE();
		break;
    case 'clear';
		DC_CLEAR();
		break;		
}

/*
 * Funstion: DC_LIST
 * variables: 
 * comment: Display Device List as Json
 * End:
 */
function DC_LIST(){

	$order = "SELECT * FROM devices LEFT JOIN type USING (packettype,subtype,type) WHERE devices.deleted=0;"; 
	//$order = "SELECT * FROM devices WHERE devices.deleted=0;";


	$result = mysql_query($order);
	$jsonData = array();

	while ($array = mysql_fetch_assoc($result)) {
		$jsonData[] = $array;
	}
	echo json_encode($jsonData);
}


/*
 * Funstion: DC_DISPLAY
 * variables: dc_id
 * comment: Display Device information as Json
 * End:
 */
function DC_DISPLAY(){

	global $dc_id;

	$order = "SELECT * FROM devices LEFT JOIN type USING (int_id,packettype,subtype,type) where dc_id='$dc_id';";


	$result = mysql_query($order);
	$jsonData = array();

	while ($array = mysql_fetch_assoc($result)) {
		$jsonData[] = $array;
	}
	echo json_encode($jsonData);
}

/*
 * Funstion: DC_INIT
 * variables: dc_id
 * comment: Send Init message to device via webservice
 * End:
 */
function DC_INIT(){

	global $dc_id;

	$order = "SELECT dc_name FROM devices WHERE dc_id=$dc_id;";

	$result = mysql_query($order);
	$row = mysql_fetch_array($result);

	//sending init
	$wsorder = 'init';
	
	require_once '../inc/mydombox.php';
	$client = new mydombox();

	$input = new initDevice();
	$input->DeviceID = $dc_id;
	$input->Order = $wsorder;

	try{
	   $response=$client->initDevice($input);
		//echo $response->DeviceID;
		//echo $response->Order;
	}
	catch (Exception $e){
	   echo $e->getMessage();
	}
	
	if ($response->Order == 'init') {
		echo 0;
	} else {
		echo 1;
	}
}

/*
 * Funstion: DC_RECORD
 * variables: dc_id, action
 * comment: Send record action (learn_on/ learn_off / learn_state)
 * End:
 */
function DC_RECORD(){

    global $mode;
	//sending init
	
	require_once '../inc/mydombox.php';
	$client = new mydombox();

	$input = new initDevice();
	$input->DeviceID = 0;
	$input->Order = $mode;

	try{
	   $response=$client->initDevice($input);
		//echo $response->DeviceID;
		//echo $response->Order;
	}
	catch (Exception $e){
	   echo $e->getMessage();
	}

	echo $response->Order;
}

/*
 * Funstion: DC_UPDATE
 * variables: dc_name id1 id2 id3 id4 unitcode groupcode housecode com dc_id
 * comment: Update Devices informations
 * End:
 */
function DC_UPDATE(){

	
	global $dc_name;
	global $type_id;
	global $address;
	global $id1;
	global $id2;
	global $id3;
	global $id4;
	global $unitcode;
	global $groupcode;
	global $housecode;
	global $com;
    global $reverse;
	global $cloud;
	global $cloud_id;
	global $dc_id;
    global $dc_logo;
	
/*
	$order = "UPDATE devices SET
		dc_name='$dc_name',
		address='$address',
		id1='$id1',
		id2='$id2',
		id3='$id3',
		id4='$id4',
		unitcode='$unitcode',
		groupcode='$groupcode',
		housecode='$housecode',
		com='$com',
		iss_status='$cloud',
		iss_stream='$cloud_id'
		WHERE
		dc_id='$dc_id'";
*/

	$order = "UPDATE devices SET
		dc_name='$dc_name',
		packettype = (select packettype FROM type WHERE type_id = '$type_id'),
		subtype = (select subtype FROM type WHERE type_id = '$type_id'),
		type = (select type FROM type WHERE type_id = '$type_id'),
		address='$address',
		id1='$id1',
		id2='$id2',
		id3='$id3',
		id4='$id4',
		unitcode='$unitcode',
		groupcode='$groupcode',
		housecode='$housecode',
		com='$com',
        reverse='$reverse',
		iss_status='$cloud',
		iss_stream='$cloud_id',
        dc_logo='$dc_logo'
		WHERE
		dc_id='$dc_id'";

	$result = mysql_query($order);
	
	if($result) {
		echo 0;
	} else {
		echo 1;
	}
}

/*
 * Funstion: DC_NEW
 * variables: dc_name id1 id2 id3 id4 unitcode groupcode housecode com dc_id
 * comment: Add new device
 * End:
 */
function DC_NEW(){

	global $dc_name;
	global $int_id;
	global $type_id;	
	global $address;
	global $id1;
	global $id2;
	global $id3;
	global $id4;
	global $unitcode;
	global $groupcode;
	global $housecode;
	global $type_id;
	
	$order = "INSERT INTO devices (dc_id,packettype,subtype,type,int_id,dc_name,last_update,address,id1,id2,id3,id4,unitcode,groupcode,housecode,new) 
	SELECT (SELECT IFNULL(MAX(dc_id),0)+1 FROM devices)as dc_id,
	(SELECT packettype FROM type WHERE type_id = '$type_id'),
	(SELECT subtype FROM type WHERE type_id = '$type_id'),
	(SELECT type FROM type WHERE type_id = '$type_id'),
	(SELECT int_id FROM type WHERE type_id = '$type_id'),
	'$dc_name',
	NOW(),
	'$address',
	'$id1',
	'$id2',
	'$id3',
	'$id4',
	'$unitcode',
	'$groupcode',
	'$housecode',0;";
	
	//echo $order;
	
	$result = mysql_query($order);
	
	
	if($result) {
		echo 0;
	} else {
		echo 1;
	}
}
/*
 * Funstion: DC_CONFIRM
 * variables: dc_id
 * comment: Confirm Devices
 * End:
 */
function DC_CONFIRM(){

	global $dc_id;
	

	$order = "UPDATE devices SET new=0 WHERE dc_id='$dc_id'";

	$result = mysql_query($order);
	
	if($result) {
		echo 0;
	} else {
		echo 1;
	}
}

/*
 * Funstion: DC_LIST_INT
 * variables: nothing
 * comment: Display Interfaces List type as Json
 * End:
 */

function DC_LIST_INT(){

	$order = "SELECT DISTINCT int_id,int_name FROM interfaces;"; 

	$result = mysql_query($order);
	$jsonData = array();

	while ($array = mysql_fetch_assoc($result)) {
		$jsonData[] = $array;
	}
	echo json_encode($jsonData);
}

/*
 * Funstion: DC_LIST_TYPE
 * variables: nothing
 * comment: Display Device List type as Json
 * End:
 */
function DC_LIST_TYPE(){

	global $int_id;

	$order = "SELECT DISTINCT type_id,packettype,subtype,type,subdescription FROM type WHERE int_id='$int_id';"; 

	$result = mysql_query($order);
	$jsonData = array();

	while ($array = mysql_fetch_assoc($result)) {
		$jsonData[] = $array;
	}
	echo json_encode($jsonData);
}

/*
 * Funstion: DC_DELETE
 * variables: dc_id
 * comment: Delete device;
 * End:
 */
function DC_DELETE(){

	global $dc_id;
	
	$order = "DELETE FROM devices WHERE dc_id='$dc_id';";
	$result = mysql_query($order);
	
	$order = "DELETE FROM energy where dc_id='$dc_id';";
	$result = mysql_query($order);
	
	$order = "DELETE FROM energy_edf where dc_id='$dc_id';";
	$result = mysql_query($order);
	
	$order = "DELETE FROM lighting where dc_id='$dc_id';";
	$result = mysql_query($order);
	
	$order = "DELETE FROM temperature where dc_id='$dc_id'; DELETE FROM weather where dc_id='$dc_id';";
	$result = mysql_query($order);
	
	$order = "DELETE FROM weather where dc_id='$dc_id';";
	$result = mysql_query($order);
	
	
	if($result) {
		echo 0;
	} else {
		echo 1;
	}
}

function DC_CLEAR(){

	$order = "DELETE FROM devices WHERE new=1;";
	$result = mysql_query($order);
	
	if($result) {
		echo 0;
	} else {
		echo 1;
	}
}

?>