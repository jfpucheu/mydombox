$(function() {
    FastClick.attach(document.body);
});


function icones_list(selector,action){
	var dataString = 'action='+ action ;
	
		$.ajax({
			type: "POST",
			url: "fct/fct_screen.php", 
			dataType: 'json',
			data: dataString, 
				success: function(data){
					$.each(data, function(index, value) {

							switch(value.packettype)
							{
							case '52':
								liste_type_52(selector, value);				
							break;
							case '55':
								liste_type_55(selector, value)	;							
							break;
							case '56':
								liste_type_56(selector, value)	;				
							break;
							case '11':
								liste_type_11(selector, value)	;				
							break;
							case '14':
								liste_type_14(selector, value)	;				
							break;
							case '1A':
								liste_type_1A(selector, value)	;				
							break;									
							case '5A':
								liste_type_5A(selector, value)	;				
							break;
							case '40':
								liste_type_40(selector, value)	;				
							break;	
							case 'ERDF':
								liste_type_ERDF(selector, value)	;				
							break;		
							case '1W28':
								liste_type_1W48(selector, value)	;				
							break;		
							case 'WP':
								liste_type_WP(selector, value)	;				
							break;								
							default:
								console.log('type not supported')
							break;
							}
						});
				$(selector).listview('refresh');
				}
			});
}

function liste_type_52(selector, value){
	$(selector).append('	<li> \
							<a data-role="button" id="bt-weather-dialog"  dc_id='+ value.dc_id+'> \
							<img src="css/images/weather52.png"/> \
							<h2>'+ value.dc_name +'</h2> \
							<p class="ui-li-aside">'+ value.home_data1 +' &ordm </p> \
							<p class="ui-li-aside2">'+Math.round(value.home_data2)+'% </p> \
							</a></li> '); 
}

function liste_type_55(selector, value){

	value.home_data2=value.home_data2 / 10 ;
	
	$(selector).append('	<li> \
							<a data-role="button" id="bt-weather-dialog"  dc_id='+ value.dc_id+'> \
							<img src="css/images/weather55.png"/> \
							<h2>'+ value.dc_name +'</h2> \
							<p class="ui-li-aside">'+ value.home_data2 +' mm</p>\
							</a></li> '); 
}

function liste_type_56(selector, value){
	$(selector).append('	<li> \
							<a data-role="button" id="bt-weather-dialog"  dc_id='+ value.dc_id+'> \
							<img src="css/images/weather56.png"/> \
							<h2>'+ value.dc_name +'</h2> \
							<p class="ui-li-aside">'+Math.round(value.home_data2)+' km/H </p> \
							<p class="ui-li-aside2">'+Math.round(value.home_data1)+' &ordm </p> \
							</a></li> ');							
}

function liste_type_11(selector, value){
	$(selector).append('	<li> \
							<a data-role="button" id="bt-light-dialog"  dc_id='+ value.dc_id+'> \
							<img src="css/images/mdb_light.png"/> \
							<h2>'+ value.dc_name +'</h2> \
							<p class="ui-li-aside">'+ value.device_mode +'</p>\
							</a></li> ');
}

function liste_type_14(selector, value){
	$(selector).append('	<li> \
							<a data-role="button" id="bt-light-dialog"  dc_id='+ value.dc_id+'> \
							<img src="css/images/mdb_chroma.png"/> \
							<h2>'+ value.dc_name +'</h2> \
							<p class="ui-li-aside">'+ value.device_mode +'</p>\
							</a></li> ');
}

function liste_type_1A(selector, value){
	$(selector).append('	<li> \
							<a data-role="button" id="bt-motor-dialog"  dc_id='+ value.dc_id+'> \
							<img src="css/images/mdb_volet.png"/> \
							<h2>'+ value.dc_name +'</h2> \
							</a></li> ');
}

function liste_type_5A(selector, value){
	$(selector).append('	<li> \
							<a data-role="button" id="bt-energy-dialog"  dc_id='+ value.dc_id+'> \
							<img src="css/images/mdb_elec.png"/> \
							<h2>'+ value.dc_name +'</h2> \
							<p class="ui-li-aside">'+ Math.round(value.home_data1) +' W</p>\
							</a></li> '); 
}

function liste_type_40(selector, value){
	$(selector).append('	<li> \
							<a data-role="button" id="bt-temperature-dialog"  dc_id='+ value.dc_id+'> \
							<img src="css/images/mdb_thermometre.png"/> \
							<h2>'+ value.dc_name +'</h2> \
							<p class="ui-li-aside">'+ value.home_data1 +' &ordm</p>\
							</a></li> '); 												
}

function liste_type_ERDF(selector, value){
	switch(value.subtype)
	{
	case '01':
		$(selector).append('	<li> \
									<a data-role="button" id="bt-energy-edf-dialog"  dc_id='+ value.dc_id+'> \
									<img src="css/images/mdb_elec.png"/> \
									<h2>'+ value.dc_name +'</h2> \
									<p class="ui-li-aside">'+ Math.round(value.home_data1) +' W</p>\
									</a></li> '); 														
	break;
	case '03':
		$(selector).append('	<li> \
									<a data-role="button" id="bt-energy-edf-dialog"  dc_id='+ value.dc_id+'> \
									<img src="css/images/mdb_elec.png"/> \
									<h2>'+ value.dc_name +'</h2> \
									<p class="ui-li-aside">'+Math.round(value.home_data1)+','+Math.round(value.home_data2)+','+Math.round(value.home_data3)+' W</p>\
									</a></li> '); 																
	break;;								
	default:
		console.log('type not supported')
	break;
	}
}

function liste_type_1W48(selector, value){
	$(selector).append('	<li> \
							<a data-role="button" id="bt-temperature-dialog"  dc_id='+ value.dc_id+'> \
							<img src="css/images/mdb_thermometre.png"/> \
							<h2>'+ value.dc_name +'</h2> \
							<p class="ui-li-aside">'+ value.home_data1 +' &ordm</p>\
							</a></li> '); 												
}

function liste_type_WP(selector, value){
	$(selector).append('	<li> \
							<a data-role="button" id="bt-light-dialog"  dc_id='+ value.dc_id+'> \
							<img src="css/images/mdb_light.png"/> \
							<h2>'+ value.dc_name +'</h2> \
							<p class="ui-li-aside">'+ value.device_mode +'</p>\
							</a></li> ');
}

//Fonction listage des thermostat
function thermostat_list(selector){

	if(selector == '#thermostat_list')
	{
		$(selector).append('<li> \
							<a data-role="button" id="bt-thermostat-new"> \
							<img src="css/images/toolbar/mdb_nav_plus.png"/> \
							<h3> New Thermostat</h3> \
							</a></li> '); 	
	}

	var action = "list";
	var dataString = 'action='+ action ;
		$.ajax({
			type: "POST",
			url: "fct/fct_thermostat.php", 
			data: dataString, 
			dataType: 'json',
				success: function(data){
					$.each(data, function(index, value) {
						if((selector=='#home_list' && value.home_screen==1) || (selector!='#home_list')) // verification for dispalying or homescreen or not
						{
							if (value.th_mode== 'auto')
							{
								$(selector).append('	<li> \
																<a data-role="button" id="bt-thermostat" th_id='+ value.th_id+'> \
																<img src="css/images/mdb_thermostat.png"/> \
																<h2>'+ value.th_name +'</h2> \
																<p class="ui-li-aside">'+ value.tp_prog +' &ordm;</p> \
																<p class="ui-li-aside2">A</p> \
																</a></li> '); 												
							}
							else if (value.th_mode== 'manual')
							{
								$(selector).append('	<li> \
																<a data-role="button" id="bt-thermostat" th_id='+ value.th_id+'> \
																<img src="css/images/mdb_thermostat.png"/> \
																<h2>'+ value.th_name +'</h2> \
																<p class="ui-li-aside">'+ value.tp_set +' &ordm;</p> \
																<p class="ui-li-aside2">M</p> \
																</a></li> '); 	
							}
						}
					});
				
					$(selector).listview('refresh');
				}
			});
}



// Refresh la page index apres qu'elle ait été caché.
//$(document).on("pagehide", '#index', function(event) {
//    $(event.target).remove();
//});


$(document).on('pageinit', '#index',  function(){
	$('#home_list').empty(); //empty for list updated
	thermostat_list('#home_list');
	icones_list('#home_list','home_screen');
});

$(document).on('pageinit', '#thermostat',  function(){
	thermostat_list('#thermostat_list');
	icones_list('#temperature_list','temperature_screen');
});

$(document).on('pageinit', '#light',  function(){
	icones_list('#light_list','light_screen');
});

$(document).on('pageinit', '#energy',  function(){
	icones_list('#energy_list','energy_screen');
});

$(document).on('pageinit', '#weather',  function(){
	icones_list('#weather_list','weather_screen');	
});

// test refresh on click
$(document).on('click', '#home', function(e){ 
	$('#home_list').empty(); //empty for list updated
	thermostat_list('#home_list');
	icones_list('#home_list','home_screen');	
});   

$(document).bind( "mobileinit", function(event) {
    $.extend($.mobile.zoom, {locked:true,enabled:false});
});



