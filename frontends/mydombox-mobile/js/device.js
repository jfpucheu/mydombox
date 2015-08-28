//Fonction affichage light status
function device_list(){

	var action="list";
	var dataString = 'action='+ action;
	
	$.ajax({
		type: "POST",
		url: "fct/fct_device.php",
			data: dataString, 
			dataType: 'json',
				success: function(data){
					var devicelist = "";
					var devicelistnew = "";
					$.each(data, function(index, value) {
						if ( value.new==1){
							devicelistnew +='	<li> \
												<a data-role="button" id="bt-config-dialog"  dc_id='+ value.dc_id+'> \
												<h2>'+ value.dc_name +'</h2> \
												<p class="ui-li-aside">'+ value.packetdescription +'</p>\
												</a></li> ';
						}else{
							devicelist +='	<li> \
												<a data-role="button" id="bt-config-dialog"  dc_id='+ value.dc_id+'> \
												<h2>'+ value.dc_name +'</h2> \
												<p class="ui-li-aside">'+ value.packetdescription +'</p>\
												</a></li> ';
						}	
						
					});
					$('#device-list-new').html(devicelistnew).listview('refresh');
					$('#device-list').html(devicelist).listview('refresh');
				}
		});
		
};

//Fonction requette init device
function device_init(){

	var dc_id = $("#dc_id").val();
	var action="init";
	var dataString = 'action='+ action+'&dc_id='+ dc_id;
	
		$.ajax({
		type: "POST",
		url: "fct/fct_device.php",
			data: dataString, 
				success: function(data){  
					//console.log(data); 
					if (data == 0){
			
					}
					else {
						alert("ERROR DC_WS001: Probleme send Webservice Request");
					}
				},
				error: function() {
				alert("ERROR DC_DV001: Error Updating Device Informations in DB");
				}
		});	
};

//Fonction requette init device
function device_record(mode){

	var action="record";
	var dataString = 'action='+ action+'&mode='+ mode;
	
		$.ajax({
		type: "POST",
		url: "fct/fct_device.php",
			data: dataString, 
				success: function(data){  
					$('#record_mode').val(data).slider('refresh');
				},
		});	
};

//Fonction requette clear device
function device_clear(){

	var action="clear";
	var dataString = 'action='+ action;
	
		$.ajax({
		type: "POST",
		url: "fct/fct_device.php",
			data: dataString, 
				success: function(data){  
					//console.log(data); 
					if (data == 0){
						$('#device-list-new').empty();
						device_list();
					}
					else {
						alert("ERROR DC_WS001: Probleme send Webservice Request");
					}
				},
				error: function() {
				alert("ERROR DC_DB005: Error Clearing Device autoddetected in DB");
				}
		});	
};

// Device Display champs
function affichage_champs(int_id,packettype){

if (int_id == 4 ){

	$("div#div_address").hide();
    $("div#div_id1").show();
	$("div#div_id2").show();
	$("div#div_id3").show();
	$("div#div_id4").show();
	$("div#div_groupcode").hide();
	$("div#div_housecode").hide();
	$("div#div_unitcode").hide();

}
else
{
    if(packettype == 10)
    {
		$("div#div_address").hide();
        $("div#div_id1").hide();
		$("div#div_id2").hide();
		$("div#div_id3").hide();
		$("div#div_id4").hide();
		$("div#div_groupcode").hide();
		$("div#div_housecode").show();
		$("div#div_unitcode").show();
    }
    else if(packettype == 11)
    {
		$("div#div_address").hide();
        $("div#div_id1").show();
		$("div#div_id2").show();
		$("div#div_id3").show();
		$("div#div_id4").show();
		$("div#div_groupcode").hide();
		$("div#div_housecode").hide();
		$("div#div_unitcode").show();
    }
	else if(packettype == 14 || packettype == '1A')
    {
		$("div#div_address").hide();
        $("div#div_id1").show();
		$("div#div_id2").show();
		$("div#div_id3").show();
		$("div#div_id4").hide();
		$("div#div_groupcode").hide();
		$("div#div_housecode").hide();
		$("div#div_unitcode").show();
    }
	else if(packettype == 40 || ( packettype >= 50 && packettype <= 59) || packettype == '5A')
    {
		$("div#div_address").hide();
        $("div#div_id1").show();
		$("div#div_id2").show();
		$("div#div_id3").hide();
		$("div#div_id4").hide();
		$("div#div_groupcode").hide();
		$("div#div_housecode").hide();
		$("div#div_unitcode").hide();
    }
	else if(packettype == 41)
    {
		$("div#div_address").hide();
        $("div#div_id1").hide();
		$("div#div_id2").hide();
		$("div#div_id3").hide();
		$("div#div_id4").hide();
		$("div#div_groupcode").hide();
		$("div#div_housecode").hide();
		$("div#div_unitcode").show();
    }
	else if(packettype == '1W28' || packettype == 'ERDF')
    {
		$("div#div_address").show();
        $("div#div_id1").hide();
		$("div#div_id2").hide();
		$("div#div_id3").hide();
		$("div#div_id4").hide();
		$("div#div_groupcode").hide();
		$("div#div_housecode").hide();
		$("div#div_unitcode").hide();
    }	
	else if(packettype == 'WP')
    {
		$("div#div_address").show();
        $("div#div_id1").hide();
		$("div#div_id2").hide();
		$("div#div_id3").hide();
		$("div#div_id4").hide();
		$("div#div_groupcode").hide();
		$("div#div_housecode").hide();
		$("div#div_unitcode").show();
    }	
	else {
		$("div#div_address").hide();
        $("div#div_id1").hide();
		$("div#div_id2").hide();
		$("div#div_id3").hide();
		$("div#div_id4").hide();
		$("div#div_groupcode").hide();
		$("div#div_housecode").hide();
		$("div#div_unitcode").hide();		
	}	
}

}

//Fonction listage interfaces disponibles
function device_int(){
	
	var action = "list-int";
	var dataString =  'action='+ action;

	$('#device_int option').remove();
	$('#device_int').append($("<option></option>").val(0).text("-- No Interface Selected --"));

		$.ajax({
			type: "POST",
			url: "fct/fct_device.php", 
			data: dataString, 
			dataType: 'json',
				success: function(data){
					$.each(data, function(index, value) {
						$('#device_int').append($("<option></option>").val(value.int_id).text(value.int_name)); 
					});
				}
			});
};

//Fonction listage device type disponibles
function device_type(int_id,selected){

	var action = "list-type";
	var dataString =  'action='+ action +'&int_id='+ int_id;

	$('#device_type option').remove();
	$('#device_type').append($("<option></option>").val(0).text("-- No Device Selected --"));

		$.ajax({
			type: "POST",
			url: "fct/fct_device.php", 
			data: dataString, 
			dataType: 'json',
				success: function(data){
					$.each(data, function(index, value) {	
						if (selected == value.type_id){
							$('#device_type').append($("<option></option>").prop('selected', true).val(value.type_id).text(value.subdescription)); 
						}
						else {
							$('#device_type').append($("<option></option>").val(value.type_id).text(value.subdescription));
    					}
    					$('#device_type').selectmenu('refresh', true);	
					});
				}
			});
		
};

//Fonction affichage devices
function device_display(dc_id){
	
	var action="display";
	var dataString = 'action='+ action+'&dc_id='+ dc_id;
	
	$.ajax({
		type: "POST",
		url: "fct/fct_device.php",
			data: dataString, 
			dataType: 'json',
				success: function(data){
					$.each(data, function(index, value) {
						$("#device_name span").html(value.dc_name);
						$("#dc_id").val(value.dc_id);
						$("#device_int option[value="+value.int_id+"]").prop('selected', true);
						$("#device_int").selectmenu('disable', true);
						$("#device_int").selectmenu('refresh', true);
						device_type(value.int_id,value.type_id);
						$("#dc_name").val(value.dc_name);
						$("#address").val(value.address);
						$("#id1").val(value.id1);
						$("#id2").val(value.id2);
						$("#id3").val(value.id3);
						$("#id4").val(value.id4);
						$("#groupcode").val(value.groupcode);
						$("#housecode").val(value.housecode);
						$("#unitcode").val(value.unitcode);
						$("#com").val(value.com).slider('refresh');
						$("#cloud").val(value.iss_status).slider('refresh');	
						$("#cloud_id").val(value.iss_stream);						
							//if ( $("#cloud").val() == 1){
							//	$("#div_cloud_name").show();
							//}else{
							//	$("#div_cloud_name").hide();  
							//}			
						affichage_champs(value.int_id,value.packettype);
						if(value.new == 1){
							$("#confirm-device").show();
						}else{
							$("#confirm-device").hide();
						}
					});
				}
		});	
};

//Fonction updade des devices
function device_update(){
	var action="update";
	var dc_id = $("#dc_id").val();
	var type_id= $("#device_type option:selected").val();
	var dc_name = $("#dc_name").val();
	var address = $("#address").val();
	var id1 = $("#id1").val();
	var id2 = $("#id2").val();
	var id3 = $("#id3").val();
	var id4 = $("#id4").val();
	var groupcode = $("#groupcode").val();
	var housecode = $("#housecode").val();
	var unitcode = $("#unitcode").val();
	
	var com = $("#com").val();

	var cloud = $("#cloud").val();
	var cloud_id = $("#cloud_id").val();
	
	var dataString = 'action='+ action+'&type_id='+ type_id +'&dc_id='+ dc_id +'&dc_name='+ dc_name +'&address='+ address+ '&id1='+ id1+'&id2='+ id2+'&id3='+ id3+'&id4='+ id4+'&groupcode='+ groupcode+'&housecode='+ housecode+'&unitcode='+ unitcode+'&com='+ com+'&cloud='+ cloud+'&cloud_id='+ cloud_id;

	$.ajax({
		type: "POST",
		url: "fct/fct_device.php",
			data: dataString, 
			async: true,
				success: function(data){
					if (data == 0){
						history.back();
					}
					else {
						alert("ERROR DC_DV001: Error Updating Device Informations in DB");
					}
				}
		});		
};

//Fonction delete des devices
function device_delete(){
	var action="delete";
	var dc_id = $("#dc_id").val();
	
	var dataString = 'action='+ action+'&dc_id='+ dc_id;

	$.ajax({
		type: "POST",
		url: "fct/fct_device.php",
			data: dataString, 
			async: true,
				success: function(data){
					if (data == 0){
						history.back();
					}
					else {
						alert("ERROR DC_DV002: Error deleting Device in DB");
					}
				}
		});		
};

//Fonction new device
function device_new(){
	var action="new";
	
	var type_id= $("#device_type option:selected").val();
	//var packettype= $("#device_type option:selected").attr('packettype');
	//alert( "type id:" + type_id + "packettype:" +packettype);
	var dc_name = $("#dc_name").val();
	var address = $("#address").val();
	var id1 = $("#id1").val();
	var id2 = $("#id2").val();
	var id3 = $("#id3").val();
	var id4 = $("#id4").val();
	var groupcode = $("#groupcode").val();
	var housecode = $("#housecode").val();
	var unitcode = $("#unitcode").val();
	
	var com = $("#com").val();
	
	var dataString = 'action='+ action+'&type_id='+ type_id +'&dc_name='+ dc_name +'&address='+ address +'&id1='+ id1+'&id2='+ id2+'&id3='+ id3+'&id4='+ id4+'&groupcode='+ groupcode+'&housecode='+ housecode+'&unitcode='+ unitcode+'&com='+ com;

	$.ajax({
		type: "POST",
		url: "fct/fct_device.php",
			data: dataString, 
			async: true,
				success: function(data){
					if (data == 0){
						history.back();
					}
					else {
						alert("ERROR DC_DV003: Error Creation Device in DB");
					}
				}
		});		
};

//Fonction device confirmation
function device_confirm(){
	var action="confirm";
	var dc_id = $("#dc_id").val();
	
	var dataString = 'action='+ action+'&dc_id='+ dc_id;

	$.ajax({
		type: "POST",
		url: "fct/fct_device.php",
			data: dataString, 
			async: true,
				success: function(data){
					if (data == 0){
						$("#confirm-device").hide();
					}
					else {
						alert("ERROR DC_DB004: Error Updating Device confirmation in DB");
					}
				}
		});		
};

var auto_refresh_device_list;
//Affichage de la liste des devices sur ouverture de la page config-devices
$(document).on('pageinit', '#config-devices',  function(){
	device_record("learn_state");
	auto_refresh_device_list = setInterval(function () {
    	device_list();
  }, 3000);	
});       

//Passage du parametre dc_id au popup config device
$(document).on('pageinit', '#config-devices', function(){      
    $(document).on('click', '#bt-config-dialog', function(e){ 
        // store some data
        if(typeof(Storage)!=="undefined") {
			var dc_id = $(this).attr("dc_id");
              localStorage.dc_id=dc_id;         
        }
        // Change page
        $.mobile.changePage("#config-device-dialog",{transition: 'pop', role: 'dialog'});
    });   

    $(document).on('click', '#bt-config-dialog-clear', function(e){ 
        //post clear data
	device_clear();
    });   
    
	 // if new device button click, pass dc_id="new"
	 $(document).on('click', '#bt-config-dialog-new', function(e){ 
		// store some data
		if(typeof(Storage)!=="undefined") {
				var dc_id = "new";
		      localStorage.dc_id=dc_id;         
		}
		// Change page
		$.mobile.changePage("#config-device-dialog",{transition: 'pop', role: 'dialog'});
	});  
});

//Ouverture popup Config device et config device new
$(document).on('pagebeforeshow', '#config-device-dialog', function(){ 
	
	//clear cache
	$("#dc_id").val('');
	$("#dc_name").val('');
	$("#device_int option[value=0]").prop('selected', true);
	$("#device_int").selectmenu('enable', true);
	$("#device_int").selectmenu('refresh', true);	
	$('#device_type option').remove();
	$('#device_type').selectmenu('refresh', true);
	$("#address").val('');
	$("#id1").val('');
	$("#id2").val('');
	$("#id3").val('');
	$("#id4").val('');
	$("#groupcode").val('');
	$("#housecode").val('');
	$("#unitcode").val('');
	$("#cloud").val('');
	$("#cloud_id").val('');

	device_int();
	if (localStorage.dc_id!="new"){
		// verouiller modiff $("#div_device_type").hide()
		device_display(localStorage.dc_id);   
	}
});

//affichages des champs sur le type de device.
$(document).ready(function(){
	$('#device_int').change(function(){
		var int_id= $("#device_int option:selected").val();
		device_type(int_id);
	});
	$('#device_type').change(function(){
		affichage_champs( $("#device_int option:selected").val(),$("#device_type option:selected").attr('packettype'));
	});
	$('#record_mode').change(function(){
		device_record($('#record_mode').val());
	});
 });

//open Popup on Init device click and send ws request
$(document).ready(function(){
	$('#init-device').on('click', function (){
		setTimeout(function(){
		  //$("div#init-device-popup").popup();
		  $("div#init-device-popup").popup("open");
		}, 100);
		device_init();
		setTimeout(function(){
		  $("div#init-device-popup").popup("close");
		}, 4000);
	});
 });
 
// Creation ou update des infos devices sur click on save
$(document).ready(function(){
	$("#submit-device-config").on('click', function (){
		if (localStorage.dc_id=="new"){
			device_new();
		}else{
			device_update(); 
		}
	});
});

// Confirm device on Popup confirm device click
$(document).ready(function(){
	$("#confirm-device").on('click', function (){
		device_confirm();
	});
});
 
// Delete device on Popup confirm device click
$(document).ready(function(){
	$("#delete-device").on('click', function (){
		device_delete();
	});
});

//affichages Du cloud Name
/*$(document).ready(function(){
	$('#cloud').change(function(){
		
		if ( $("#cloud").val() == 1){
			$("#div_cloud_name").show();
		}else{
			$("#div_cloud_name").hide();  
		}
	});
 });
*/ 