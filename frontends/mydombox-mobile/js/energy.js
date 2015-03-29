//Fonction affichage energy status
function energy_display(dc_id){

	var action="display";
	var dataString = 'action='+ action+'&dc_id='+ dc_id;
	
	$.ajax({
		type: "POST",
		url: "fct/fct_energy.php",
			data: dataString, 
			dataType: 'json',
				success: function(data){
					$.each(data, function(index, value) {
						$("#device_energy_name span").html(value.name);
						$("#energy_update span").html(value.datetime);
						$("#energy_instant span").html(value.instant);
						$("#energy_total span").html(value.total);						
					});
				}
		});
		
};

//Fonction affichage temperature
function energy_graph(dc_id){

	var action="graph";
	var dataString = 'action='+ action+'&dc_id='+ dc_id;
	$('#energy_chartdiv').empty();	
	$("#energy_spinner").show();
	$.ajax({
		type: "POST",
		url: "fct/fct_energy.php",
			data: dataString, 
			dataType: 'json',
				success: function(data){
					tmp_plot = $.jqplot ('energy_chartdiv',[ data ],{
						title:'Energy',
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
				$("#energy_spinner").hide();
				}
		});
	$(window).resize(function() {
	      tmp_plot.replot( { resetAxes: true } );
	});
};

function affichage_champs_edf(subtype){
    if(subtype == 01)
    {
		$("div#energy_edf_iinst").show();
        $("div#energy_edf_iinst1").hide();
		$("div#energy_edf_iinst2").hide();
		$("div#energy_edf_iinst3").hide();
		$("div#energy_edf_imax").show();
		$("div#energy_edf_imax1").hide();
		$("div#energy_edf_imax2").hide();
		$("div#energy_edf_imax3").hide();
		$("div#energy_edf_pmax").hide();
		$("div#energy_edf_adir1").hide();
		$("div#energy_edf_adir2").hide();
		$("div#energy_edf_adir3").hide();		
	}
    else if(subtype == 03)
	{
		$("div#energy_edf_iinst").hide();
        $("div#energy_edf_iinst1").show();
		$("div#energy_edf_iinst2").show();
		$("div#energy_edf_iinst3").show();
		$("div#energy_edf_imax").hide();
		$("div#energy_edf_imax1").show();
		$("div#energy_edf_imax2").show();
		$("div#energy_edf_imax3").show();
		$("div#energy_edf_pmax").show();
		$("div#energy_edf_adir1").show();
		$("div#energy_edf_adir2").show();
		$("div#energy_edf_adir3").show();		
	}
	else
	{
		$("div#energy_edf_iinst").hide();
        $("div#energy_edf_iinst1").hide();
		$("div#energy_edf_iinst2").hide();
		$("div#energy_edf_iinst3").hide();
		$("div#energy_edf_imax").hide();
		$("div#energy_edf_imax1").hide();
		$("div#energy_edf_imax2").hide();
		$("div#energy_edf_imax3").hide();
		$("div#energy_edf_pmax").hide();
		$("div#energy_edf_adir1").hide();
		$("div#energy_edf_adir2").hide();
		$("div#energy_edf_adir3").hide();
	}
}
	
//Fonction affichage energy status
function energy_display_edf(dc_id){

	var action="display_edf";
	var dataString = 'action='+ action+'&dc_id='+ dc_id;
	
	$.ajax({
		type: "POST",
		url: "fct/fct_energy.php",
			data: dataString, 
			dataType: 'json',
				success: function(data){
					$.each(data, function(index, value) {
						$("#device_energy_edf_name span").html(value.name);
						$("#energy_edf_update span").html(value.datetime);
						$("#energy_edf_optarif span").html(value.optarif);
						$("#energy_edf_isousc span").html(value.isousc);
						$("#energy_edf_hchp span").html(value.hchp);	
						$("#energy_edf_hchc span").html(value.hchc);	
						$("#energy_edf_ptec span").html(value.ptec);	
						$("#energy_edf_iinst span").html(value.iinst);	
						$("#energy_edf_iinst1 span").html(value.iinst1);	
						$("#energy_edf_iinst2 span").html(value.iinst2);	
						$("#energy_edf_iinst3 span").html(value.iinst3);
						$("#energy_edf_imax span").html(value.imax);	
						$("#energy_edf_imax1 span").html(value.imax1);	
						$("#energy_edf_imax2 span").html(value.imax2);	
						$("#energy_edf_imax3 span").html(value.imax3);	
						$("#energy_edf_pmax span").html(value.pmax);	
						$("#energy_edf_hphc span").html(value.hphc);	
						$("#energy_edf_motdetat span").html(value.motdetat);	
						$("#energy_edf_ppot span").html(value.ppot);	
						$("#energy_edf_adps span").html(value.adps);
						$("#energy_edf_adir1 span").html(value.adir1);
						$("#energy_edf_adir2 span").html(value.adir2);
						$("#energy_edf_adir3 span").html(value.adir3);
						affichage_champs_edf(value.subtype);
					});
				}
		});
		
};

$(document).on('pageinit', '#index', function(){      
    $(document).on('click', '#bt-energy-dialog', function(e){ 
        // store some data
        if(typeof(Storage)!=="undefined") {
			var dc_id = $(this).attr("dc_id");
              localStorage.dc_id=dc_id;         
        }
        // Change page
        $.mobile.changePage("#energy-dialog",{transition: 'pop', role: 'dialog'});
    });   
	
    $(document).on('click', '#bt-energy-edf-dialog', function(e){ 
        // store some data
        if(typeof(Storage)!=="undefined") {
			var dc_id = $(this).attr("dc_id");
              localStorage.dc_id=dc_id;         
        }
        // Change page
        $.mobile.changePage("#energy-edf-dialog",{transition: 'pop', role: 'dialog'});
    });   
});

$(document).on('pageshow', '#energy-dialog', function(){ 
	energy_display(localStorage.dc_id);
	energy_graph(localStorage.dc_id);     
});

$(document).on('pagebeforeshow', '#energy-edf-dialog', function(){ 
	energy_display_edf(localStorage.dc_id);     
});