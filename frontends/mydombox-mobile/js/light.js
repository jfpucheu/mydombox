//Fonction affichage light status
function light_display(dc_id){

	var action="display";
	var dataString = 'action='+ action+'&dc_id='+ dc_id;
	
	$.ajax({
		type: "POST",
		url: "fct/fct_light.php",
			data: dataString, 
			dataType: 'json',
				success: function(data){
					$.each(data, function(index, value) {
						$("#device_light_name span").html(value.name);
						$("#dc_id").val(value.dc_id);
						
						switch(value.packettype)
						{
						case '11':
							$("#light_mode").val(value.mode).slider('refresh');
							$("div#light_swich").show();
							$("div#light_mode").hide();
							$("div#light_speed").hide();
							$("div#light_dim").hide();	
							$("div#colorpicker").hide();	
						break;
						case '14':
							$("div#light_swich").hide();
							$("div#light_mode").show();
							$("div#light_speed").show();
							$("div#light_dim").show();	
							$("div#colorpicker").show();								
						break;								
						default:
							console.log('type not supported')
						break;
						}
					});
				}
		});
		
};

//Fonction d'update light status
function light_update(mode){

	var dc_id= $("#dc_id").val();
	var action="update";
	var dataString = 'action='+ action+'&dc_id='+ dc_id+ '&mode='+mode;
	
	$.ajax({
		type: "POST",
		url: "fct/fct_light.php",
			data: dataString, 
				success: function(data){  
					//console.log(data); 
					if (data == 0){
			
					}
					else if(data ==1){
						//alert("ERROR LI_WS001: Probleme send Webservice Request");
					}
					else {
						alert("ERROR LI_DB001: Error Updating Light Status in DB");
					}
				},
				error: function() {
				alert("ERROR LI_PST_0001: E");
				}
	});
};

$(document).on('change','#light_mode',function(){ 
  light_update( $("#light_mode").val() ); 
});

$(document).on('pageinit', '#index', function(){      
    $(document).on('click', '#bt-light-dialog', function(e){ 
		//alert("toto");
        // store some data
        if(typeof(Storage)!=="undefined") {
			var dc_id = $(this).attr("dc_id");
              localStorage.dc_id=dc_id;         
        }
        // Change page
        $.mobile.changePage("#light-dialog",{transition: 'pop', role: 'dialog'});
    });   
});

$(document).on('pagebeforeshow', '#light-dialog', function(){ 
	light_display(localStorage.dc_id);     
});

// Confirm device on Popup confirm device click
$(document).ready(function(){
	$("#lighting5_On").on('click', function (){
		light_update("On");
	});
	$("#lighting5_Off").on('click', function (){
		light_update("Off");
	});
	$("#lighting5_Mode").on('click', function (){
		light_update("On");
	});
	$("#lighting5_Light_down").on('click', function (){
		light_update("Dim");
	});	
	$("#lighting5_Light_up").on('click', function (){
		light_update("Bright");
	});	
	$("#lighting5_Speed_down").on('click', function (){
		light_update("Color-");
	});	
	$("#lighting5_Speed_up").on('click', function (){
		light_update("Color+");
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
			light_update(newcolor.toString(16));
		}
	}

});


