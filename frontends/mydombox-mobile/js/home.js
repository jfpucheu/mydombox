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
					var homelist = "";
					if(selector == '#home_list')
					{					
						homelist += thermostat_list(selector); // add thermostat before devices
					}
					$.each(data, function(index, value) {
                            if(! value.dc_logo){
                                value.dc_logo="mdb_nologo.png";
                            };	
							switch(value.int_id)
							{
							case '1':
								switch(value.packettype)
								{
								case '52':
									homelist += liste_type_52(selector, value);				
								break;
								case '55':
									homelist += liste_type_55(selector, value)	;							
								break;
								case '56':
									homelist += liste_type_56(selector, value)	;				
								break;
								case '11':
									homelist += liste_type_11(selector, value)	;				
								break;
								case '14':
									homelist += liste_type_14(selector, value)	;				
								break;
								case '1A':
									homelist += liste_type_1A(selector, value)	;				
								break;									
								case '5A':
									homelist += liste_type_5A(selector, value)	;				
								break;
								case '40':
									homelist += liste_type_40(selector, value)	;				
								break;	
								case 'ERDF':
									homelist += liste_type_ERDF(selector, value)	;				
								break;		
								case '1W28':
									homelist += liste_type_1W48(selector, value)	;				
								break;		
								case 'WP':
									homelist += liste_type_WP(selector, value)	;				
								break;								
								default:
									console.log('type not supported')
								break;
								}
							break;
							case '4':	
								switch(value.packettype)
								{
								case 'A5':
									homelist += liste_type_40(selector, value);	
								break;
								case 'D5':
									homelist += liste_type_dore(selector, value);	
								break;											
								default:
									console.log('type not supported')
								break;
								}
							break;
							default:
								console.log('int not supported for device ' + value.dc_id)
							break;
							}							
						});

				$(selector).html(homelist).listview('refresh');
				},
			});
}

function liste_type_52(selector, value){
		var listelement = '	 <li> \
							<a href="#" id="bt-weather-dialog"  dc_id='+ value.dc_id+'> \
							<img src="css/images/'+ value.dc_logo +'" class="ui-li-thumb"> \
							<h2>'+ value.dc_name +'</h2> \
							<p class="ui-li-aside">'+ value.home_data1 +' &ordm </p> \
							<p class="ui-li-aside2">'+Math.round(value.home_data2)+'% </p> \
							</a></li> '; 
	return listelement;
}

function liste_type_55(selector, value){

	value.home_data2=value.home_data2 / 10 ;
	
		var listelement = '	 <li> \
							<a href="#"   id="bt-weather-dialog"  dc_id='+ value.dc_id+'> \
							<img src="css/images/weather55.png" class="ui-li-thumb"> \
							<h2>'+ value.dc_name +'</h2> \
							<p class="ui-li-aside">'+ value.home_data2 +' mm</p>\
							</a></li> '; 
	return listelement;
}

function liste_type_56(selector, value){
		var listelement = '	 <li> \
							<a href="#"   id="bt-weather-dialog"  dc_id='+ value.dc_id+'> \
							<img src="css/images/weather56.png" class="ui-li-thumb"> \
							<h2>'+ value.dc_name +'</h2> \
							<p class="ui-li-aside">'+Math.round(value.home_data2)+' km/H </p> \
							<p class="ui-li-aside2">'+Math.round(value.home_data1)+' &ordm </p> \
							</a></li> ';
	return listelement;							
}

function liste_type_11(selector, value){
		var listelement = '	 <li> \
							<a href="#"   id="bt-lm-dialog"  dc_id='+ value.dc_id+'> \
							<img src="css/images/'+ value.dc_logo +'" class="ui-li-thumb"> \
							<h2>'+ value.dc_name +'</h2> \
							<p class="ui-li-aside">'+ value.device_mode +'</p>\
							</a></li> ';
	return listelement;	
}

function liste_type_14(selector, value){
		var listelement = '	 <li> \
							<a href="#"   id="bt-lm-dialog"  dc_id='+ value.dc_id+'> \
							<img src="css/images/'+ value.dc_logo +'" class="ui-li-thumb"> \
							<h2>'+ value.dc_name +'</h2> \
							<p class="ui-li-aside">'+ value.device_mode +'</p>\
							</a></li> ';
	return listelement;
}

function liste_type_1A(selector, value){
		var listelement = '	 <li> \
							<a href="#"   id="bt-lm-dialog"  dc_id='+ value.dc_id+'> \
							<img src="css/images/'+ value.dc_logo +'" class="ui-li-thumb"> \
							<h2>'+ value.dc_name +'</h2> \
							<p class="ui-li-aside">'+ value.device_mode +'</p>\
							</a></li> ';
	return listelement;
}

function liste_type_5A(selector, value){
		var listelement = '	 <li> \
							<a href="#"   id="bt-energy-dialog"  dc_id='+ value.dc_id+'> \
							<img src="css/images/'+ value.dc_logo +'" class="ui-li-thumb"> \
							<h2>'+ value.dc_name +'</h2> \
							<p class="ui-li-aside">'+ Math.round(value.home_data1) +' W</p>\
							</a></li> '; 
	return listelement;
}

function liste_type_40(selector, value){
		var listelement = '	 <li> \
							<a href="#"   id="bt-temperature-dialog"  dc_id='+ value.dc_id+'> \
							<img src="css/images/'+ value.dc_logo +'" class="ui-li-thumb"> \
							<h2>'+ value.dc_name +'</h2> \
							<p class="ui-li-aside">'+ value.home_data1 +' &ordm</p>\
							</a></li> ';
	return listelement;											
}

function liste_type_ERDF(selector, value){
	switch(value.subtype)
	{
	case '01':
		var listelement = '	 <li> \
									<a href="#"   id="bt-energy-edf-dialog"  dc_id='+ value.dc_id+'> \
									<img src="css/images/'+ value.dc_logo +'" class="ui-li-thumb"> \
									<h2>'+ value.dc_name +'</h2> \
									<p class="ui-li-aside">'+ Math.round(value.home_data1) +' W</p>\
									</a></li> '; 														
	break;
	case '03':
		var listelement = '	 <li> \
									<a href="#"   id="bt-energy-edf-dialog"  dc_id='+ value.dc_id+'> \
									<img src="css/images/'+ value.dc_logo +'" class="ui-li-thumb"> \
									<h2>'+ value.dc_name +'</h2> \
									<p class="ui-li-aside">'+Math.round(value.home_data1)+','+Math.round(value.home_data2)+','+Math.round(value.home_data3)+' W</p>\
									</a></li> '; 																
	break;;								
	default:
		console.log('type not supported')
	break;
	}
	return listelement;
}

function liste_type_1W48(selector, value){
		var listelement = '	 <li> \
							<a href="#"   id="bt-temperature-dialog"  dc_id='+ value.dc_id+'> \
							<img src="css/images/'+ value.dc_logo +'" class="ui-li-thumb"> \
							<h2>'+ value.dc_name +'</h2> \
							<p class="ui-li-aside">'+ value.home_data1 +' &ordm</p>\
							</a></li> ';
		return listelement;												
}

function liste_type_WP(selector, value){
		var listelement = '	 <li> \
							<a href="#"   id="bt-light-dialog"  dc_id='+ value.dc_id+'> \
							<img src="css/images/'+ value.dc_logo +'" class="ui-li-thumb"> \
							<h2>'+ value.dc_name +'</h2> \
							<p class="ui-li-aside">'+ value.device_mode +'</p>\
							</a></li> ';
		return listelement;
}

function liste_type_dore(selector, value){
	if (value.device_mode == 'open')
	{
		var listelement = '	 <li> \
							<a href="#"   id="bt-state-dialog"  dc_id='+ value.dc_id+'> \
							<img src="css/images/'+ value.dc_logo +'" class="ui-li-thumb"> \
							<h2>'+ value.dc_name +'</h2> \
							<p class="ui-li-aside">'+ value.device_mode +'</p>\
							</a></li> ';
	}
	else if (value.device_mode == 'closed')
	{
		var listelement = '	 <li> \
							<a href="#"   id="bt-state-dialog"  dc_id='+ value.dc_id+'> \
							<img src="css/images/'+ value.dc_logo +'" class="ui-li-thumb"> \
							<h2>'+ value.dc_name +'</h2> \
							<p class="ui-li-aside">'+ value.device_mode +'</p>\
							</a></li> ';
	}
		return listelement;
}

//Fonction listage des thermostat
function thermostat_list(selector){

	var thlist = "";
	
	if(selector == '#thermostat_list')
	{		
			thlist += ' <li> \
						<a href="#"   id="bt-thermostat-new"> \
						<img src="css/images/toolbar/mdb_nav_plus.png" class="ui-li-thumb"> \
						<h2>New Thermostat</h2> \
						</a></li> '; 	
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
												thlist += '	 <li> \
																<a   id="bt-thermostat" th_id='+ value.th_id+'> \
																<img src="css/images/mdb_thermostat.png" class="ui-li-thumb"> \
																<h2>'+ value.th_name +'</h2> \
																<p class="ui-li-aside">'+ value.tp_prog +' &ordm;</p> \
																<p class="ui-li-aside2">A</p> \
																</a></li> '; 												
							}
							else if (value.th_mode== 'manual')
							{
												thlist += '	 <li> \
																<a   id="bt-thermostat" th_id='+ value.th_id+'> \
																<img src="css/images/mdb_thermostat.png" class="ui-li-thumb"> \
																<h2>'+ value.th_name +'</h2> \
																<p class="ui-li-aside">'+ value.tp_set +' &ordm;</p> \
																<p class="ui-li-aside2">M</p> \
																</a></li> '; 	
							}
						}
					});
					if(selector == '#thermostat_list')
					{
						$(selector).html(thlist).listview('refresh');
					}
				},
				async:false
			});
	return thlist;
}


// Home page
var auto_refresh_home;
$(document).on('pagebeforeshow', '#index',  function(){
	icones_list('#home_list','home_screen');
	auto_refresh_home = setInterval(function () {
    	icones_list('#home_list','home_screen');
  }, 3000);
});

$(document).on('pagehide', '#index',  function(){
  clearInterval(auto_refresh_home);
});

// Thermostat page
var auto_refresh_thermostat;
$(document).on('pagebeforeshow', '#thermostat',  function(){
	thermostat_list('#thermostat_list');
	icones_list('#temperature_list','temperature_screen');
	auto_refresh_thermostat = setInterval(function () {
		thermostat_list('#thermostat_list');
    	icones_list('#temperature_list','temperature_screen');
  }, 3000);
});

$(document).on('pagehide', '#thermostat_list',  function(){
  clearInterval(auto_refresh_thermostat);
});

// Lighting page
var auto_refresh_lighting;
$(document).on('pagebeforeshow', '#light',  function(){
	icones_list('#light_list','light_screen');
	auto_refresh_lighting = setInterval(function () {
    	icones_list('#light_list','light_screen');
  }, 3000);
});

$(document).on('pagehide', '#light',  function(){
  clearInterval(auto_refresh_lighting);
});

// Energy page
var auto_refresh_energy;
$(document).on('pagebeforeshow', '#energy',  function(){
	icones_list('#energy_list','energy_screen');
	auto_refresh_lighting = setInterval(function () {
    	icones_list('#energy_list','energy_screen');
  }, 3000);
});

$(document).on('pagehide', '#energy',  function(){
  clearInterval(auto_refresh_energy);
});


// Weather page
var auto_refresh_weather;
$(document).on('pagebeforeshow', '#weather',  function(){
	icones_list('#weather_list','weather_screen');
	auto_refresh_weather = setInterval(function () {
    	icones_list('#weather_list','weather_screen');
  }, 3000);
});

$(document).on('pagehide', '#weather',  function(){
  clearInterval(auto_refresh_weather);
});

// Windore page
var auto_refresh_windore;
$(document).on('pagebeforeshow', '#windore',  function(){
	icones_list('#windore_list','windore_screen');
	auto_refresh_windore = setInterval(function () {
    	icones_list('#windore_list','windore_screen');
  }, 3000);
});

$(document).on('pagehide', '#windore_list',  function(){
  clearInterval(auto_refresh_windore);
});

// test refresh on click
$(document).on('click', '#home', function(e){ 
	//$('#home_list').empty(); //empty for list updated
	//icones_list('#home_list','home_screen');
			
});   

$(document).bind( "mobileinit", function(event) {
    $.extend($.mobile.zoom, {locked:true,enabled:false});
});



