//Fonction d'affichage des scenario
function program_display(dc_id){
	$("#program_list").empty();
	
	var action = "display";
	var dataString = 'action='+ action +'&dc_id='+ dc_id;

		$.ajax({
			type: "POST",
			url: "fct/fct_scheduler.php", 
			data: dataString, 
			dataType: 'json',
				success: function(data){
					$.each(data, function(index, value) {				
						switch (value.sch_day) { // Swich Case pour Afficher le jour de la semaine en fonction du sc_day
					    	case "0":
					        	day = "All";
					        break;
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
						$('#program_list').append('<li day='+ day +' data-icon="gear" sch_id='+ value.sch_id + ' sch_day='+ value.sch_day +' sch_time='+ value.sch_time +' sch_action='+ value.sch_action +'><a href="#">'+ value.sch_time +'&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; '+value.sch_action+'</a></li>');

					});
					$('#program_list').append('<li data-icon="plus" sch_id="new" sch_time="12:00" action="" ><a href="#" style="text-align: center;">Add Action</a></li>');
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

function action_list(packettype){
	
	$('#sch_action').html('');
	$("#sch_action").empty();
	switch (packettype) { // Swich Case pour Afficher le jour de la semaine en fonction du sc_day
    	case "1A":
        	var myArray = ["up", "down", "stop"];
        break;
	    case "11":
	        var myArray = ["on", "off"];
        break;
	    case "14":
	        var myArray = ["on", "off"];
	    break;
	    default:
	    	var myArray = [];
	}		
	$('#sch_action').append('<option sch_action="Action" disabled="disabled">Action</option>');
	for (var i = 0; i < myArray.length; i++) {
		$('#sch_action').append('<option sch_action='+ myArray[i]+'>'+ myArray[i] +'</option>');
	}
}

//Post de l'update de l'action
$(document).ready(function(){
	$("#update_action").click(function() {

		var action="update";
		var dc_id = $("#dc_id").val();
		var sch_id = $("#sch_id").val();
		var sch_day = $("#sch_day").val();
		var sch_time = $("#sch_time").val();
		var sch_action = $("#sch_action").val();

		/* DATASTRING */
		var dataString = 'action='+ action+'&dc_id='+ dc_id +'&sch_id='+ sch_id +'&sch_day='+ sch_day +'&sch_time='+ sch_time +'&sch_action='+ sch_action;
		$.ajax({
		type: "POST",
		url: "fct/fct_scheduler.php",
			data: dataString,
				success: function(data){  
					if (data == 0){
						program_display(dc_id);
	                }
					else{
						alert("Error updating rows !");
					}
				},
				error: function() {
				alert("ERROR: Updating !");
				}
		});
	});
	
	//Post de la suppression d'une action
	$("#delete_action").click(function() {
		/* VALUES */
		var action="delete";
		var dc_id = $("#dc_id").val();
		var sch_id = $("#sch_id").val();
		/* DATASTRING */
		var dataString = 'action='+ action +'&sch_id='+ sch_id;
		$.ajax({
			type: "POST",
			url: "fct/fct_scheduler.php",
				data: dataString,
					success: function(data){   
						if (data == 0){
							program_display(dc_id);
						}
						else {
							alert("ERROR: Deleting Action!");
						}
					},
					error: function() {
						alert("ERROR: Deleting Action!");
					}
		});
	}); 
});