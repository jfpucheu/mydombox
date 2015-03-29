function motor_display(dc_id){

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
						default:

						break;
						}
					});
				}
		});
		
};

$(document).on('pagebeforeshow', '#motor-dialog', function(){ 
	motor_display(localStorage.dc_id);
});

$(document).on('pageinit', '#index', function(){      
    $(document).on('click', '#bt-motor-dialog', function(e){ 
		//alert("toto");
        // store some data
        if(typeof(Storage)!=="undefined") {
			var dc_id = $(this).attr("dc_id");
              localStorage.dc_id=dc_id;         
        }
        // Change page
        $.mobile.changePage("#motor-dialog",{transition: 'pop', role: 'dialog'});
    });   
});



// Confirm device on Popup confirm device click
$(document).ready(function(){
	$("#RFY_up").on('click', function (){
		light_update("up");
	});
	$("#RFY_stop").on('click', function (){
		light_update("stop");
	});
	$("#RFY_down").on('click', function (){
		light_update("down");
	});	
});
