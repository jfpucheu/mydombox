
//Fonction listage des scenario
function scenario_list(th_id){
	
	var action = "list";
	var dataString =  'action='+ action +'&th_id='+ th_id;
	
	$('#select-scenario-edit option').remove();
	$('#select-scenario-edit').append($("<option></option>").attr("value","no").text("-- No Scenario Selected --"));
	
		$.ajax({
			type: "POST",
			url: "fct/fct_scenario.php", 
			data: dataString, 
			dataType: 'json',
				success: function(data){
					$.each(data, function(index, value) {
						$('#select-scenario-edit').append($("<option></option>").attr("value",value.sc_id).attr("type",value.sc_type).text(value.sc_name)); 
						});
				}
			});
}

//Fonction d'affichage des scenario
function scenario_display(){
	$("#actionList").empty();
	var day;
	var action = "display";
	var sc_id= $("#select-scenario-edit option:selected").attr('value');
	var sc_type= $("#select-scenario-edit option:selected").attr('type');

	// hide day button id dail scenario
	if (sc_type == 'weekly') {
		$('#day_select').show();
		localStorage.sc_type ='weekly';    
	}
	else
	{
		$('#day_select').hide();
		localStorage.sc_type ='daily'; 		
	}	
	
	// hide add slot button if no scenario selected ok new option selected.
	if (sc_id == 'no') {
		$('#del_scenario').hide();
		$('#actionList').hide();
		$('#new_scenario').show();
	}
	else
	{
		$('#del_scenario').show();
		$('#actionList').show();
		$('#new_scenario').hide();		
	}
	
	var dataString = 'action='+ action +'&sc_id='+ sc_id;
		$.ajax({
			type: "POST",
			url: "fct/fct_scenario.php", 
			data: dataString, 
			dataType: 'json',
				success: function(data){
					$.each(data, function(index, value) {				
						switch (value.sc_day) { // Swich Case pour Afficher le jour de la semaine en fonction du sc_day
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
						$('#actionList').append('<li day='+ day +' data-icon="gear" pg_id='+ value.pg_id + ' sc_day='+ value.sc_day +' start='+ value.start +' stop='+ value.stop +' tp_prog='+ value.tp_prog +'><a href="#">De '+ value.start +' a '+ value.stop+'&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="temperature">'+value.tp_prog+' &ordm;C</span></a></li>');

					});
					$('#actionList').append('<li data-icon="plus" pg_id="new" start="00:00" stop="00:00" tp_prog="20" ><a href="#" style="text-align: center;">Add new Periode</a></li>');
					$("#actionList").listview({
						autodividers: true,
						autodividersSelector: function (li) {
							var out = li.attr("day");
							return out;
						}
						}).listview('refresh');
				}
			});
}

// Affichage des scenario sur changement du scenario
$(document).on('pagebeforeshow', '#scenario', function(){ 
	scenario_list(localStorage.th_id);
	$("#select-scenario-edit").change(scenario_display);
});


$(document).ready(function(){

	// Affichage du popup pour modification periode sur scenario
	$('#actionList').on('click', 'li', function (){
		var pg_id = $(this).attr("pg_id");
		var start = $(this).attr("start");
		var stop = $(this).attr("stop");
		var sc_day = $(this).attr("sc_day");
		var tp_prog = $(this).attr("tp_prog");
		
		$("#pg_id").val(pg_id);
		$("#start_time").val(start);
		$("#stop_time").val(stop);
		$("#tp_prog").val(tp_prog);		
		$("#sc_day").val(sc_day).selectmenu('refresh');	

		$("#delete_periode").show();	
		$("div#sc_form").popup( "open" );	
	});

	// Affichage du popup scenario sur click
	$("#open_popup_scenario").click(function() {
		$("div#sc_new").popup( "open" );
	});
	
	// Affichage Popup Suppression d'un scenario
	$("#del_scenario_button").click(function() {
		$("div#sc_del").popup( "open" );
	});
	// Affichage Popup duplication d'un jour de scenario
	$("#copy_day_button").click(function() {
		$("div#sc_dup").popup( "open" );
	});

	//Post de la copy d'un jour de scenario
	$("#sc_copy").click(function() {
		/* VALUES */
		var action="copy";
		var sc_id = $("#select-scenario-edit").val();
		var sc_day_ori = $("#sc_day_ori").val();
		var sc_day_dest = $("#sc_day_dest").val();
				
		/* DATASTRING */
		var dataString = 'action='+ action+'&sc_id='+ sc_id +'&sc_day_ori='+ sc_day_ori +'&sc_day_dest='+ sc_day_dest;
		$.ajax({
		type: "POST",
		url: "fct/fct_scenario.php",
			data: dataString,
				success: function(data){  
					if (data == 0){
						scenario_display();
                    }
					else if (data == 1){
						alert("Probleme Copying Day");
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
	
	//Post de l'update du scenario
	$("#update_periode").click(function() {
		/* VALUES */
		var action="update";
		var sc_id = $("#select-scenario-edit").val();
		var pg_id = $("#pg_id").val();
		var start_time = $("#start_time").val();
		var stop_time = $("#stop_time").val();
		var tp_prog = $("#tp_prog").val();
		
		if (localStorage.sc_type == 'weekly')
		{
			var sc_day = $("#sc_day").val();
		}
		else
		{
			var sc_day = 0;	
		}
		/* DATASTRING */
		var dataString = 'action='+ action+'&sc_id='+ sc_id +'&pg_id='+ pg_id +'&start_time='+ start_time +'&stop_time='+ stop_time +'&tp_prog='+ tp_prog +'&sc_day='+ sc_day;
							$.ajax({
		type: "POST",
		url: "fct/fct_scenario.php",
			data: dataString,
				success: function(data){  
					if (data == 0){
						scenario_display();
                    }
					else if (data == 1){
						alert("Time Slot not Available, Please Correct !");
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
	
	//Post du delete d'une periode du scenario
	$("#delete_periode").click(function() {
		/* VALUES */
		var action = "delete-pg";
		var pg_id = $("#pg_id").val();
		/* DATASTRING */
		var dataString = 'action='+ action +'&pg_id='+ pg_id;
							$.ajax({
		type: "POST",
		url: "fct/fct_scenario.php",
			data: dataString,
				success: function(data){  
					console.log(data); 
					if (data == 0){
						scenario_display();
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

	//Post de l'ajout d'un nouveau scenario
	$("#add_scenario").click(function() {
		/* VALUES */
		var action="new";
		var th_id = localStorage.th_id
		var sc_name = $("#sc_name").val();
		var sc_type = $("#sc_type").val();
		/* DATASTRING */
		var dataString = 'action='+ action+'&th_id='+ th_id +'&sc_name='+ sc_name +'&sc_type='+ sc_type;
		$.ajax({
			type: "POST",
			url: "fct/fct_scenario.php",
				data: dataString,
					success: function(data){  
						//console.log(data); 
						if (data == 0){
							scenario_list();
						}
						else if(data ==1){
							alert("Scenario Name Already use ! Please change it !");
						}
						else {
							alert("ERROR: Creating Scenario!");
						}
					},
					error: function() {
					alert("ERROR: Creating Scenario!");
					}
			});
	});

	//Post de la suppression d'un scenario
	$("#sc_del_confirm").click(function() {
		/* VALUES */
		var action="delete";
		var sc_id = $("#select-scenario-edit").val();
		/* DATASTRING */
		var dataString = 'action='+ action +'&sc_id='+ sc_id;
		$.ajax({
			type: "POST",
			url: "fct/fct_scenario.php",
				data: dataString,
					success: function(data){   
						if (data == 0){
							$("#select-scenario-edit option:eq(0)").prop("selected",true);
							$("#select-scenario-edit").change();
						}
						else {
							alert("ERROR: Deleting Scenario!");
						}
					},
					error: function() {
					alert("ERROR: Deleting= Scenario!");
					}
		});
	});  	

});

