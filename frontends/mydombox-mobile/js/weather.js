//Fonction affichage weather status
function weather_display(dc_id){

	var action="display";
	var dataString = 'action='+ action+'&dc_id='+ dc_id;
	
	$.ajax({
		type: "POST",
		url: "fct/fct_weather.php",
			data: dataString, 
			dataType: 'json',
				success: function(data){
					$.each(data, function(index, value) {
						$("#device_weather_name span").html(value.name);
						$("#weather_update span").html(value.datetime);
						$("#weather_temperature span").html(value.temperature);
						$("#weather_humidity span").html(value.humidity);
						$("#weather_rainrate span").html(value.rainrate);
						$("#weather_raintotal span").html(value.raintotal);
						$("#weather_winddirection span").html(value.winddirection);
						$("#weather_av_speed span").html(value.av_speed);		
						
						switch(value.packettype)
						{
						case '52':
							$("div#weather_temperature").show();
							$("div#weather_humidity").show();
							$("div#weather_rainrate").hide();
							$("div#weather_raintotal").hide();
							$("div#weather_winddirection").hide();
							$("div#weather_av_speed").hide();						
						break;
						case '55':
							$("div#weather_temperature").hide();
							$("div#weather_humidity").hide();
							$("div#weather_rainrate").show();
							$("div#weather_raintotal").show();
							$("div#weather_winddirection").hide();
							$("div#weather_av_speed").hide();						
						break;
						case '56':
							$("div#weather_temperature").hide();
							$("div#weather_humidity").hide();
							$("div#weather_rainrate").hide();
							$("div#weather_raintotal").hide();
							$("div#weather_winddirection").show();
							$("div#weather_av_speed").show();															
						break;								
						default:
							console.log('type not supported')
						break;
						}
						weather_graph(dc_id,value.packettype); 
		
					});
				}
		});
		
};//Fonction affichage temperature

function weather_graph(dc_id,packettype){

	var action="graph";
	var dataString = 'action='+ action+'&dc_id='+ dc_id;

	$('#weather_chartdiv').empty();
	$("#weather_spinner").show();
	$.ajax({
		type: "POST",
		url: "fct/fct_weather.php",
			data: dataString, 
			dataType: 'json',
				success: function(data){
					$('#weather_chartdiv').empty();
						switch(packettype)
						{
						case '52':
							wea_plot = $.jqplot ('weather_chartdiv',[ data ],{
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
						break;
						case '55':
							wea_plot = $.jqplot ('weather_chartdiv',[ data ],{
								title:'Pluviometrie (mm)',
								seriesDefaults: {
									renderer:$.jqplot.BarRenderer,
									rendererOptions: {
										barWidth: 40
										}
								},
								axes:{
									xaxis:{
										autoscale:true, 
										renderer:  $.jqplot.CategoryAxisRenderer,
										//tickInterval: "1 day",
										rendererOptions:{  
												tickOptions:{
												formatter: $.jqplot.DateTickFormatter,
												formatString:'%d/%m',
												showGridline: false
											}
										}
									},
									yaxis:{
										autoscale: true,
									},
								},
								series:[{lineWidth:4, markerOptions:{style:'circle'}}]
							});						
						break;
						case '56':
							$("div#weather_temperature").hide();
							$("div#weather_humidity").hide();
							$("div#weather_rainrate").hide();
							$("div#weather_raintotal").hide();
							$("div#weather_winddirection").show();
							$("div#weather_av_speed").show();															
						break;								
						default:
							console.log('type not supported')
						break;
						}
				 $("#weather_spinner").hide();
				}
		});
	$(window).resize(function() {
	      wea_plot.replot( { resetAxes: true } );
	});
};




$(document).on('pageinit', '#index', function(){      
    $(document).on('click', '#bt-weather-dialog', function(e){ 
		//alert("toto");
        // store some data
        if(typeof(Storage)!=="undefined") {
			var dc_id = $(this).attr("dc_id");
              localStorage.dc_id=dc_id;         
        }
        // Change page
        $.mobile.changePage("#weather-dialog",{transition: 'pop', role: 'dialog'});
    });   
});

$(document).on('pageshow', '#weather-dialog', function(){ 
	weather_display(localStorage.dc_id); 
});
