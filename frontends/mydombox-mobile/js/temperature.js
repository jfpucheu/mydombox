
//Fonction Affichage des scenarios
function thermostat_scenario_list(th_id){
	
	var action = "list";
	var sc_id = $(this).attr("sc_id");
	var dataString =  'action='+ action +'&th_id='+ th_id;
	//alert(sc_id);
	$('#select-scenario option').remove();
	$('#select-scenario').append($("<option></option>").attr("value","no").text("-- No Scenario Selected --"));
	
		$.ajax({
			type: "POST",
			url: "fct/fct_scenario.php", 
			data: dataString, 
			dataType: 'json',
				success: function(data){
					$.each(data, function(index, value) {
						$('#select-scenario').append($("<option></option>").attr("value",value.sc_id).text(value.sc_name)); 
						});

				}
			});
};

//Fonction Affichage des thermostats
function thermostat_display(th_id){
	var action="display";
	var dataString = 'action='+ action+'&th_id='+ th_id;
	
	thermostat_scenario_list();
	
	$.ajax({
		type: "POST",
		url: "fct/fct_thermostat.php",
			data: dataString, 
			dataType: 'json',
				success: function(data){
					$.each(data, function(index, value) {
						$("#th_id").val(value.th_id);
						$("#sensor_list").val(value.sensor_id).attr('selected','selected').selectmenu('refresh');
						$("#recept_list").val(value.recept_id).attr('selected','selected').selectmenu('refresh');
						$("#th_name").val(value.th_name);
						$("#th_use").val(value.th_use).flipswitch('refresh');
						$("#th_mode").val(value.th_mode).flipswitch('refresh');
						$("#tp_set").val(value.tp_set).slider('refresh');
						$("#select-scenario").val(value.sc_id).selectmenu('refresh');
						$("#select-scenario").val(value.sc_id).attr('selected','selected').selectmenu('refresh');
						$("#select-scenario").val(value.sc_id).prop('selected',true).selectmenu('refresh');
					});
					
					if($("#th_mode").val()=="auto")
					{
						$("div#manual-config").hide();
						$("div#auto-config").show();
						$("#select-scenario").selectmenu('refresh');
					}
					else if ($("#th_mode").val()=="manual"){
						$("div#manual-config").show();
						$("div#auto-config").hide();
					}
				}
		});		
};

//Fonction updade des thermostats
function thermostat_update(){
	var action="update";
	var th_id = $("#th_id").val();
	var th_use = $("#th_use").val();
	var th_mode = $("#th_mode").val();
	var tp_set = $("#tp_set").val();
	var sc_id = $("#select-scenario option:selected").val();
	
	var dataString = 'action='+ action+'&th_id='+ th_id +'&th_use='+ th_use +'&th_mode='+ th_mode+'&tp_set='+ tp_set+'&sc_id='+ sc_id;

	$.ajax({
		type: $('form').attr('method'),
		url: "fct/fct_thermostat.php",
			data: dataString, 
			async: true,
				success: function(data){
					history.back();
				}
		});		
};

//Fonction creation d'un thermostat
function thermostat_new(){
	var action="new";
	var dataString = 'action='+ action;

	$.ajax({
		type: $('form').attr('method'),
		url: "fct/fct_thermostat.php",
			data: dataString, 
			async: true,
				success: function(data){
					if (data == 0){
						$('#thermostat_list').empty(); //empty for list updated
						thermostat_list('#thermostat_list');
                    }
					else if (data == 1){
						alert("A thermostat is not yet finished to configure");
					}
					else{
						alert("An error as occured creating thermostat");
					}
				},
				error: function(){
					alert("An error as occured creating thermostat");
				}
		});		
};

//Fonction delete d'un thermostat
function thermostat_delete(){
	var action="delete";
	var th_id = $("#th_id").val();

	var dataString = 'action='+ action+'&th_id='+ th_id;

	$.ajax({
		type: $('form').attr('method'),
		url: "fct/fct_thermostat.php",
			data: dataString, 
			async: true,
				success: function(data){
				
						$('#thermostat_list').empty(); //empty for list updated
						thermostat_list('#thermostat_list');
						history.back(1);
				}
		});		
};

//Fonction updade des thermostats settings
function thermostat_settings(){
	var action="settings";
	var th_id = $("#th_id").val();
	var th_name = $("#th_name").val();
	var sensor_id = $("#sensor_list option:selected").val();
	var recept_id = $("#recept_list option:selected").val();
	
	var dataString = 'action='+ action+'&th_id='+ th_id +'&th_name='+ th_name +'&sensor_id='+ sensor_id+'&recept_id='+ recept_id;

	$.ajax({
		type: $('form').attr('method'),
		url: "fct/fct_thermostat.php",
			data: dataString, 
			async: true,
				success: function(data){
					history.back();
				}
		});		
};

//Fonction Affichage des devices pour faire un thermostat
function thermostat_devices_list(){
	
	var action = "list-devices";
	var dataString =  'action='+ action;
    
	$('#sensor_list option').remove();
	$('#sensor_list').append($("<option></option>").attr("value","no").text("-- No Device Selected --"));

	$('#recept_list option').remove();
	$('#recept_list').append($("<option></option>").attr("value","no").text("-- No Device Selected --"));
		
		$.ajax({
			type: "POST",
			url: "fct/fct_thermostat.php", 
			data: dataString, 
			dataType: 'json',
				success: function(data){
					$.each(data, function(index, value) {
						if(value.com == 'tx' && (value.packettype == '40' || value.packettype == '50' || value.packettype == '51' || value.packettype == '52' || value.packettype == '1W28')){
							$('#sensor_list').append($("<option></option>").attr("value",value.dc_id).text(value.dc_name)); 
						}else if( value.packettype == '40' || value.packettype == '11'){
							$('#recept_list').append($("<option></option>").attr("value",value.dc_id).text(value.dc_name)); 						
						}
						
					});
				}
			});
};


//Fonction affichage temperature
function temperature_display(dc_id){

	var action="display";
	var dataString = 'action='+ action+'&dc_id='+ dc_id;
	
	$.ajax({
		type: "POST",
		url: "fct/fct_temperature.php",
			data: dataString, 
			dataType: 'json',
				success: function(data){
					$.each(data, function(index, value) {
						$("#device_tp_name span").html(value.name);
						$("#last_update span").html(value.datetime);
						$("#last_temperature span").html(value.temperature);			
					});
				}
		});
};

//Fonction affichage temperature
function temperature_graph(dc_id){

	var action="graph";
	var dataString = 'action='+ action+'&dc_id='+ dc_id;
	$('#temperature_chartdiv').empty();
	$("#temperature_spinner").show();
	$.ajax({
		type: "POST",
		url: "fct/fct_temperature.php",
			data: dataString, 
			dataType: 'json',
				success: function(data){
					tmp_plot = $.jqplot ('temperature_chartdiv',[ data ],{
						title:'Temperature',
						seriesDefaults: {
							showMarker: false,
							rendererOptions: {
								smooth: true
								}
						},
						axes:{
							xaxis:{
								autoscale:true, 
								renderer:$.jqplot.DateAxisRenderer,
								tickOptions:{formatString:'%R'}
							},
							yaxis:{
								autoscale: true
							},
						}, 
						series:[{lineWidth:4, markerOptions:{style:'circle'}}]
						});
				$("#temperature_spinner").hide();
				}
		});
	$(window).resize(function() {
	      tmp_plot.replot( { resetAxes: true } );
	});
};


//***************************************************************************************************
//Change page to thermostat
//***************************************************************************************************


$(document).on('pageinit', '#index', function(){      
	$(document).on('click', '#bt-thermostat', function(){    
		// store some data
		if(typeof(Storage)!=="undefined") {
			var th_id = $(this).attr("th_id");
			  localStorage.th_id=th_id;         
		}
		// Change page
		$( "body" ).pagecontainer( "change","#thermostat-edit",{transition: 'pop'});
	});   
});

$(document).on('pageinit', '#thermostat', function(){      
	$(document).on('click', '#bt-thermostat', function(){    
		// store some data
		if(typeof(Storage)!=="undefined") {
			var th_id = $(this).attr("th_id");
			  localStorage.th_id=th_id;         
		}
		// Change page
		$( "body" ).pagecontainer( "change","#thermostat-edit",{transition: 'pop'});
	});  

	$(document).on('click', '#bt-thermostat-new', function(){    
		thermostat_new();
	});	
	
	
});

//$(document).on('pageinit', '#thermostat-edit', function(){   
$(document).on('pagebeforeshow', '#thermostat-edit', function(){ 
	//alert(localStorage.th_id);
	thermostat_devices_list();
	thermostat_display(localStorage.th_id);
})

//Submit Thermostat update
$(document).on('submit', '#thermostat-form', function(e){
    e.preventDefault();
    thermostat_update();
});

//Submit Thermostat edit update
$(document).on('submit', '#thermostat-setup', function(e){
    e.preventDefault();
    thermostat_settings();
});

// declenchement du popup sur click d'un device temperature
$(document).on('pageinit', '#index', function(){      
    $(document).on('click', '#bt-temperature-dialog', function(e){ 
        // store some data
        if(typeof(Storage)!=="undefined") {
			var dc_id = $(this).attr("dc_id");
              localStorage.dc_id=dc_id;         
        }
        // Change page
        $( "body" ).pagecontainer( "change","#temperature-dialog",{transition: 'pop', role: 'dialog'});
    });   
});


// recherche des infos sur ouberture du popup
$(document).on('pageshow', '#temperature-dialog', function(){ 
	temperature_display(localStorage.dc_id);
	temperature_graph(localStorage.dc_id);

});

//Change page to scenario editor
$(document).on('pageinit', '#thermostat-edit', function(){      
    $(document).on('click', '#sc-editor', function(){    
        // store some data

        // Change page
        $( "body" ).pagecontainer( "change","#scenario",{transition: 'pop',role: 'dialog'});
    });   
});


$(document).ready(function(){

	// Affichage du popup thermostat setup sur click
	$("#thermostat-setup").click(function() {
		$("div#th_setup").popup( "open" );
	});
	
	// Affichage Popup Suppression d'un thermostat
	$("#thermostat-delete").click(function() {
		$("div#thermostat-delete-confirm").popup( "open" );
	});
	
	// Suppression du thermostat sur confirmation
	$("#th_del_confirm").click(function() {
		thermostat_delete();
	});

	// display thermostat mode
	$('#th_mode').change(function(){
     //alert('Changed!')
		th_mode = $("#th_mode").val();
		
		if(th_mode=="auto")
		{
			$("div#manual-config").hide();
			$("div#auto-config").show();
			$("#select-scenario").selectmenu('refresh');
		}
		else if (th_mode=="manual"){
			$("div#manual-config").show();
			$("div#auto-config").hide();
		}
	});
});





	

