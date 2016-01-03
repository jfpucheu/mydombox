//Fonction affichage light status
function lm_device_display(dc_id){

	var action="display";
	var dataString = 'action='+ action+'&dc_id='+ dc_id;
	
	$.ajax({
		type: "POST",
		url: "fct/fct_light_motor.php",
			data: dataString, 
			dataType: 'json',
				success: function(data){
					$.each(data, function(index, value) {
						$("#light-motor-name span").html(value.name);
						$("#dc_id").val(value.dc_id);
						$("#packettype").val(value.packettype);
						
						switch(value.packettype)
						{
						case '11':
							$("#light_mode").val(value.mode).flipswitch('refresh');
							$("div#light_swich").show();
							$("div#light_mode").hide();
							$("div#light_speed").hide();
							$("div#light_dim").hide();
							$("div#motor_control").hide();	
							$("div#colorpicker").hide();
						break;
						case '14':
							$("div#light_swich").hide();
							$("div#light_mode").show();
							$("div#light_speed").show();
							$("div#light_dim").show();
							$("div#motor_control").hide();	
							$("div#colorpicker").show();								
						break;
						case '1A':
							$("div#light_swich").hide();
							$("div#light_mode").hide();
							$("div#light_speed").hide();
							$("div#light_dim").hide();
							$("div#motor_control").show();
							$("div#colorpicker").hide();
								
						break;							
						default:
							console.log('type not supported')
						break;
						}
					});
				}
		});
		
};

//Fonction d'update  status
function send_order(mode){

	var dc_id= $("#dc_id").val();
	var action="update";
	var dataString = 'action='+ action+'&dc_id='+ dc_id+ '&mode='+mode;
	
	$.ajax({
		type: "POST",
		url: "fct/fct_light_motor.php",
			data: dataString, 
				success: function(data){  
					//console.log(data); 
					if (data == 0){
			
					}
					else if(data ==1){
						//alert("ERROR LM_WS001: Probleme send Webservice Request");
					}
					else {
						alert("ERROR LM_DB001: Error Updating Status in DB");
					}
				},
				error: function() {
				alert("ERROR LM_PST_0001: E");
				}
	});
};

$(document).on('change','#light_mode',function(){ 
  send_order( $("#light_mode").val() ); 
});

$(document).on('pageinit', '#index', function(){      
    $(document).on('click', '#bt-lm-dialog', function(e){ 
		//alert("toto");
        // store some data
        if(typeof(Storage)!=="undefined") {
			var dc_id = $(this).attr("dc_id");
              localStorage.dc_id=dc_id;         
        }
        // Change page
        $.mobile.changePage("#light-motor-dialog",{transition: 'pop', role: 'dialog'});
    });   
});

$(document).on('pagebeforeshow', '#light-motor-dialog', function(){ 
	lm_device_display(localStorage.dc_id);
	program_display(localStorage.dc_id);     
});

// Confirm device on Popup confirm device click
$(document).ready(function(){
	$("#lighting5_On").on('click', function (){
		send_order("on");
	});
	$("#lighting5_Off").on('click', function (){
		send_order("off");
	});
	$("#lighting5_Mode").on('click', function (){
		send_order("on");
	});
	$("#lighting5_Light_down").on('click', function (){
		send_order("dim");
	});	
	$("#lighting5_Light_up").on('click', function (){
		send_order("bright");
	});	
	$("#lighting5_Speed_down").on('click', function (){
		send_order("color-");
	});	
	$("#lighting5_Speed_up").on('click', function (){
		send_order("color+");
	});	
	$("#RFY_up").on('click', function (){
		send_order("up");
	});
	$("#RFY_stop").on('click', function (){
		send_order("stop");
	});
	$("#RFY_down").on('click', function (){
		send_order("down");
	});
	
	//$('#colorpicker').farbtastic('#color');
	var newcolor = 0,oldcolor;
	var picker = $.farbtastic('#colorpicker');  //picker variable
	picker.setColor("#b6b6ff"); //set initial color

	
	picker.linkTo(onColorChange); //link to callback

	function onColorChange(color) {
		oldcolor = newcolor;
		newcolor = Math.round(picker.hsl[0]*(131-6))+6;
		
		if (Math.abs(newcolor - oldcolor) > 5){
			//alert('old:' + oldcolor + 'new:' + newcolor );
			$("#color").val(newcolor.toString(16));
			send_order(newcolor.toString(16));
		}
	}
	// Affichage du popup pour edition action  
	$('#program_list').on('click', 'li', function (){

		var dc_id = $("#dc_id").val();
		var packettype= $("#packettype").val();
		
		action_list(packettype);

		//get param from list delected
		var sch_id = $(this).attr("sch_id");
		var sch_day = $(this).attr("sch_day");
		var sch_time = $(this).attr("sch_time");
		var sch_action = $(this).attr("sch_action");	
			
		//set param in popup
		$("#sch_id").val(sch_id);
		if(sch_id=="new") 
		{
			sch_day=-1;
			sch_action="Action";
		}
		$("#sch_day").val(sch_day).selectmenu('refresh');
		$("#sch_time").val(sch_time);
		$("#sch_action").val(sch_action).selectmenu('refresh');
		
		$("#delete_periode").show();	
		$("div#popup_programmation").popup( "open" );	
	});

});


