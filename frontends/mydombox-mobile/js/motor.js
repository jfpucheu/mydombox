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

//Fonction d'affichage des scenario
function program_display(dc_id){
	$("#program_list").empty();
	
	var action = "program";
	var dataString = 'action='+ action +'&dc_id='+ dc_id;

		$.ajax({
			type: "POST",
			url: "fct/fct_light.php", 
			data: dataString, 
			dataType: 'json',
				success: function(data){
					$.each(data, function(index, value) {				
						switch (value.sch_day) { // Swich Case pour Afficher le jour de la semaine en fonction du sc_day
						    case "1":
						        day = "Lundi";
						        break;
						    case "2":
						        day = "Mardi";
						        break;
						    case "3":
						        day = "Mercredi";
						        break;
						    case "4":
						        day = "Jeudi";
						        break;
						    case "5":
						        day = "Vendredi";
						        break;
						    case "6":
						        day = "Samedi"
						        break;
						    case "7":
						        day = "Dimanche";
						        break;
						    default:
						    	day = "Journee";
						}
						$('#program_list').append('<li day='+ day +' data-icon="gear" sch_id='+ value.sch_id + ' sc_day='+ value.sch_day +' time='+ value.sch_time +' action='+ value.sch_action +'><a href="#">Time: '+ value.sch_time +'&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Action: '+value.sch_action+'</a></li>');

					});
					$('#program_list').append('<li data-icon="plus" sch_id="new" time="12:00" action="" ><a href="#" style="text-align: left;">New Program</a></li>');
					$("#program_list").listview({
						autodividers: true,
						autodividersSelector: function (li) {
							var out = li.attr("day");
							return out;
						}
						}).listview('refresh');
				}
			});
}

$(document).on('pagebeforeshow', '#motor-dialog', function(){ 
	motor_display(localStorage.dc_id);
	program_display(localStorage.dc_id);
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
