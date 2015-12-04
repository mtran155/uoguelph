function weeklyRanking(msg){
	schedule(msg[0].week);
	var title = "<H3 style = \"font-family: Serif\" align=\"center\"><strong>WEEK " + msg[0].week + " " + msg[0].position + " RANKINGS</strong></H3>"
	document.getElementById('table').innerHTML = title;
	
	var table = document.createElement("TABLE");
	table.className = "sortable CSSTableGenerator";
	table.id = "newTable";
	table.border = "2px";
	table.cellSpacing = "5px";
	table.cellPadding = "5px";
	table.width = "100%"
	
	var tHead = document.createElement("THEAD");
	var tBody = document.createElement("TBODY");
	var row, cell;
	var i, j;
	
	var header = new Array();

	header[0] = "Ranking" 
	header[1] = "Team"
	header[2] = "Name"
	header[3] = "Projected Points"
	
	var stats = new Array();

	for(i=0; i < msg.length; i++){
	    stats[i] = new Array((i+1), msg[i].team, msg[i].name, msg[i].points);
	}
	
	table.appendChild(tHead);
	table.appendChild(tBody);

	row = document.createElement("TR");
	tHead.appendChild(row);

	for(i=0; i<header.length; i++){
		cell = document.createElement("TD");
		cell.innerHTML = header[i];
		row.appendChild(cell);
	}

	for(i=0; i<stats.length; i++){
		row = document.createElement("TR");
		tBody.appendChild(row);
		for(j=0; j<stats[i].length;j++){
			cell = document.createElement("TD");
			cell.align = "center";
			cell.innerHTML = stats[i][j];
			row.appendChild(cell);
		}
	}

	var d = document.getElementById("table");
	d.appendChild(table);
	
	var sortTab = document.getElementById("newTable");
	sorttable.makeSortable(sortTab);
}

function QB_Projeciton(msg){
	schedule(msg[0].week);
	
	var title = "<H3 style = \"font-family: Serif\" align=\"center\"><strong>WEEK " + msg[0].week + " " + msg[0].position + " RANKINGS</strong></H3>"
	document.getElementById('table').innerHTML = title;

	var table = document.createElement("TABLE");
	table.className = "sortable CSSTableGenerator";
	table.id = "newTable";
	table.border = "2px";
	table.cellSpacing = "5px";
	table.cellPadding = "5px";
	table.width = "100%"

	var tHead = document.createElement("THEAD");
	var tBody = document.createElement("TBODY");
	var row, cell;
	var i, j;

	var header = new Array();

	header[0] = "Player" 
	header[1] = "Team"
	header[2] = "Pass Comp"
	header[3] = "Pass Att"
	header[4] = "Pass Comp %"
	header[5] = "Pass Yds"
	header[6] = "Pass Td"
	header[7] = "Pass Int"
	header[8] = "Rush Yds"
	header[9] = "Rush TD"

	var stats = new Array();

	for(i=0; i < msg.length; i++){
		var result = ((msg[i].passCmp/msg[i].passAtt)*100);
	    result = result.toFixed(2);

		stats[i] = new Array(msg[i].name, msg[i].team, msg[i].passCmp, msg[i].passAtt, result + "%",  msg[i].passYds, msg[i].passTD,
							 msg[i].passInt, msg[i].rushYds, msg[i].rushTD);
	}

	table.appendChild(tHead);
	table.appendChild(tBody);

	row = document.createElement("TR");
	tHead.appendChild(row);

	for(i=0; i<header.length; i++){
		cell = document.createElement("TD");
		cell.innerHTML = header[i];
		row.appendChild(cell);
	}

	for(i=0; i<stats.length; i++){
		row = document.createElement("TR");
		tBody.appendChild(row);
		for(j=0; j<stats[i].length;j++){
			cell = document.createElement("TD");
			cell.align = "center";
			cell.innerHTML = stats[i][j];
			row.appendChild(cell);
		}
	}

	var d = document.getElementById("table");
	d.appendChild(table);

	var sortTab = document.getElementById("newTable");
	sorttable.makeSortable(sortTab);
    
}

function WR_Projeciton(msg){
	schedule(msg[0].week);
	
	var title = "<H3 style = \"font-family: Serif\" align=\"center\"><strong>WEEK " + msg[0].week + " " + msg[0].position + " RANKINGS</strong></H3>"
   	document.getElementById('table').innerHTML = title;

   	var table = document.createElement("TABLE");
   	table.className = "sortable CSSTableGenerator";
   	table.id = "newTable";
   	table.border = "2px";
   	table.cellSpacing = "5px";
   	table.cellPadding = "5px";
   	table.width = "100%"

   	var tHead = document.createElement("THEAD");
   	var tBody = document.createElement("TBODY");
   	var row, cell;
   	var i, j;

   	var header = new Array();

   	header[0] = "Player" 
   	header[1] = "Team"
   	header[2] = "Receptions"
   	header[3] = "Reception Yds"
   	header[4] = "Reception TD"
   	header[5] = "Rush Att"
   	header[6] = "Rush Yds"
   	header[7] = "Rush TD"

   	var stats = new Array();

   	for(i=0; i < msg.length; i++){
   		stats[i] = new Array(msg[i].name, msg[i].team, msg[i].receptions, msg[i].recYds, msg[i].recTD, msg[i].rushAtt,
   							 msg[i].rushYds, msg[i].rushTD);
   	}

   	table.appendChild(tHead);
   	table.appendChild(tBody);

   	row = document.createElement("TR");
   	tHead.appendChild(row);

   	for(i=0; i<header.length; i++){
   		cell = document.createElement("TD");
   		cell.innerHTML = header[i];
   		row.appendChild(cell);
   	}

   	for(i=0; i<stats.length; i++){
   		row = document.createElement("TR");
   		tBody.appendChild(row);
   		for(j=0; j<stats[i].length;j++){
   			cell = document.createElement("TD");
   			cell.align = "center";
   			cell.innerHTML = stats[i][j];
   			row.appendChild(cell);
   		}
   	}

   	var d = document.getElementById("table");
   	d.appendChild(table);

   	var sortTab = document.getElementById("newTable");
   	sorttable.makeSortable(sortTab);
}

function K_Projection(msg){
	schedule(msg[0].week);
	
	var title = "<H3 style = \"font-family: Serif\" align=\"center\"><strong>WEEK " + msg[0].week + " " + msg[0].position + " RANKINGS</strong></H3>"
	document.getElementById('table').innerHTML = title;

	var table = document.createElement("TABLE");
	table.className = "sortable CSSTableGenerator";
	table.id = "newTable";
	table.border = "2px";
	table.cellSpacing = "5px";
	table.cellPadding = "5px";
	table.width = "100%"

	var tHead = document.createElement("THEAD");
	var tBody = document.createElement("TBODY");
	var row, cell;
	var i, j;

	var header = new Array();

	header[0] = "Player" 
	header[1] = "Team"
	header[2] = "FG Att"
	header[3] = "FG Made"
	header[4] = "FG %"
	header[5] = "XP"

	var stats = new Array();

	for(i=0; i < msg.length; i++){
		var result = ((msg[i].fg/msg[i].fgAtt)*100);
		result = result.toFixed(2);

		stats[i] = new Array(msg[i].name, msg[i].team, msg[i].fgAtt, msg[i].fg, result + "%", msg[i].xp);
	}

	table.appendChild(tHead);
	table.appendChild(tBody);

	row = document.createElement("TR");
	tHead.appendChild(row);

	for(i=0; i<header.length; i++){
		cell = document.createElement("TD");
		cell.innerHTML = header[i];
		row.appendChild(cell);
	}

	for(i=0; i<stats.length; i++){
		row = document.createElement("TR");
		tBody.appendChild(row);
		for(j=0; j<stats[i].length;j++){
			cell = document.createElement("TD");
			cell.align = "center";
			cell.innerHTML = stats[i][j];
			row.appendChild(cell);
		}
	}

	var d = document.getElementById("table");
	d.appendChild(table);

	var sortTab = document.getElementById("newTable");
	sorttable.makeSortable(sortTab);
}

function DEF_Projection(msg){
	schedule(msg[0].week);
	   
	var title = "<H3 style = \"font-family: Serif\" align=\"center\"><strong>WEEK " + msg[0].week + " " + msg[0].position + " RANKINGS</strong></H3>"
	document.getElementById('table').innerHTML = title;

	var table = document.createElement("TABLE");
	table.className = "sortable CSSTableGenerator";
	table.id = "newTable";
	table.border = "2px";
	table.cellSpacing = "5px";
	table.cellPadding = "5px";
	table.width = "100%"

	var tHead = document.createElement("THEAD");
	var tBody = document.createElement("TBODY");
	var row, cell;
	var i, j;

	var header = new Array();

	header[0] = "Team" 
	header[1] = "Interceptions"
	header[2] = "Sacks"
	header[3] = "Forced Fumble"
	header[4] = "Fumble Recovery"
	header[5] = "DEF Touchdowns"
	header[6] = "Return Touchdowns"
	header[7] = "Safety"
	header[8] = "Points Allowed"
	header[9] = "Yards Allowed"

	var stats = new Array();

	for(i=0; i < msg.length; i++){
		stats[i] = new Array(msg[i].name, msg[i].defInt, msg[i].defSack , msg[i].defFF, msg[i].defFR,  msg[i].defTD, msg[i].defRetTD,
							 msg[i].defSafety, msg[i].defPA, msg[i].defYdsAllowed);
	}

	table.appendChild(tHead);
	table.appendChild(tBody);

	row = document.createElement("TR");
	tHead.appendChild(row);

	for(i=0; i<header.length; i++){
		cell = document.createElement("TD");
		cell.innerHTML = header[i];
		row.appendChild(cell);
	}

	for(i=0; i<stats.length; i++){
		row = document.createElement("TR");
		tBody.appendChild(row);
		for(j=0; j<stats[i].length;j++){
			cell = document.createElement("TD");
			cell.align = "center";
			cell.innerHTML = stats[i][j];
			row.appendChild(cell);
		}
	}

	var d = document.getElementById("table");
	d.appendChild(table);

	var sortTab = document.getElementById("newTable");
	sorttable.makeSortable(sortTab);
}

function scheduleHeader(msg){
    var i;
    
    document.getElementById('sched').innerHTML = "";
    
    for(i = 0; i < msg.length; i++){
	var awayTeam, homeTeam, day;
	awayTeam = teamLogo(msg[i].away);
	homeTeam = teamLogo(msg[i].home);
	day = Weekday(msg[i].gameDay);

	document.getElementById('sched').innerHTML += "<div class = \"col-lg-1\"><img src = \"img/" + awayTeam +"\" height = \"32\" width = \"32\"> " 
	+  msg[i].away + "<br>VS<br><img src = \"img/" + homeTeam +"\"height = \"32\" width = \"32\"> " + msg[i].home + "<br>" + day + " " + msg[i].gameTime+"</div>";
    }
}

function Weekday(msg){

	var res = msg.split("-");
	var d = new Date();

	d.setFullYear(res[0], res[1] - 1,res[2]);

	var days = ["Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"];
	var result = days[d.getDay()];


	return result;
}

function teamLogo(msg){
    var logo;
    
    if(msg == "ARI"){logo = "cardinals.png";}
    else if (msg == "ATL"){logo = "falcons.png";}
    else if (msg == "BAL"){logo = "ravens.png";}
    else if (msg == "BUF"){logo = "bills.png";}
    else if (msg == "CAR"){logo = "panthers.png";}
    else if (msg == "CHI"){logo = "bears.png";}
    else if (msg == "CIN"){logo = "bengals.png";}
    else if (msg == "CLE"){logo = "browns.png";}
    else if (msg == "DAL"){logo = "cowboys.png";}
    else if (msg == "DEN"){logo = "broncos.png";}
    else if (msg == "DET"){logo = "lions.png";}
    else if (msg == "GB"){logo = "packers.png";}
    else if (msg == "HOU"){logo = "texans.png";}
    else if (msg == "IND"){logo = "colts.png";}
    else if (msg == "JAC"){logo = "jags.png";}
    else if (msg == "KC"){logo = "cheifs.png";}
    else if (msg == "MIA"){logo = "dolphins.png";}
    else if (msg == "MIN"){logo = "vikings.png";}
    else if (msg == "NYG"){logo = "giants.png";}
    else if (msg == "NYJ"){logo = "jets.png";}
    else if (msg == "NE"){logo = "pats.png";}
    else if (msg == "NO"){logo = "saints.png";}
    else if (msg == "OAK"){logo = "raiders.png";}
    else if (msg == "PHI"){logo = "eagles.png";}
    else if (msg == "PIT"){logo = "steelers.png";}
    else if (msg == "SD"){logo = "chargers.png";}
    else if (msg == "SF"){logo = "niners.png";}
    else if (msg == "SEA"){logo = "seahawks.png";}
    else if (msg == "STL"){logo = "rams.png";}
    else if (msg == "TB"){logo = "bucs.png";}
    else if (msg == "TEN"){logo = "titans.png";}
    else if (msg == "WAS"){logo = "redskins.png";}    
    
    return logo; 
}



function ranking(position){
	var weekNum = $("select[name='week'] option:selected").text();
	
// 	console.log(weekNum);

	$.ajax({
		type: "GET",
		url: "/API",
		data: {service: "weekly-rankings/", rankingPos: position + "/", week: weekNum}
	})
	.done(function ( msg ){
		data = $.parseJSON(msg);
		weeklyRanking(data);
		console.log( "GET sent, received: " + msg );
	});
}

function projections(position){
	var weekNum = $("select[name='week'] option:selected").text();
/*	
	console.log(weekNum);*/

	$.ajax({
		type: "GET",
		url: "/API",
		data: {service: "weekly-projections/", projectionPos: position + "/", week: weekNum}
	})
	.done(function ( msg ){
		data = $.parseJSON(msg);
		if (data[0].position == "QB"){
		    QB_Projeciton(data);
		}
		else if (data[0].position == "WR" || data[0].position == "TE" || data[0].position == "RB") {
		    WR_Projeciton(data);
		}
		else if(data[0].position == "K"){
		    K_Projection(data);
		}
		else if(data[0].position == "DEF"){
		    DEF_Projection(data);
		}	
		
		console.log( "GET sent, received: " + msg );
	});
    
}

function schedule(week){
    var weekNum = week;
//     console.log("WEEK" + weekNum);
    
    $.ajax({
		type: "GET",
		url: "/API",
		data: {service: "schedule/", week: weekNum}
	})
	.done(function ( msg ){
		data = $.parseJSON(msg)
		scheduleHeader(data);
		console.log( "GET sent, received: " + msg );
	});
}