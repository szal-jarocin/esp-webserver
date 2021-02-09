const char index_html[] PROGMEM = R"=====(
<!DOCTYPE html>
<meta charset="utf-8">
<html>
	<head>
		<title>Serwer zdalnie sterowanej platformy jezdnej</title>
		<style>
			body
			{
				background-color: #EEEEEE;
				font-family: Calibri, Arial, sans-serif;
			}
			
			a
			{
				text-decoration: none;
				color: red;
			}
			
			h1, h2, h3
			{
				margin: 0;
			}
			
			#container
			{
				background-color: white;
				width: 800px;
				margin-left: auto;
				margin-right: auto;
			}
			
			#header
			{
				background-color: #66CCFF;
				text-align: center;
				padding: 10px;
			}
			
			#content
			{
				padding: 10px 100px 10px 100px;
				overflow: hidden;
			}
			
			#nav
			{
				width: 200px;
				float: left;
			}
			
			#nav ul
			{
				list-style-type: none;
				padding: 0;
			}
			
			#nav .selected
			{
				font-weight: bold;
			}
			
			#main
			{
				width: 400px;
				float: right;
			}
			
			#txt
			{
				float: left;
				padding-top: 10px;
				padding-bottom: 10px;
			}
			
			#form1
			{
				float: left;
				padding: 10px;
			}
			
			#status
			{
				clear: both;
				padding-top: 10px;
				padding-bottom: 10px;
			}
			
			#footer
			{
				clear: both;
				padding: 10px;
				background-color: #999999;
				color: white;
				text-align: right;
			}
		</style>
		<script>
			function odbierzDate()
			{
				var d = new Date();
				var d_tyg = d.getDay();
				document.getElementById("d_tyg").value = d.getDay();
				if (d.getHours()<10) var d_h = "0" + d.getHours(); else var d_h = d.getHours();
				document.getElementById("d_h").value = d.getHours();
				if (d.getMinutes()<10) var d_m = "0" + d.getMinutes(); else var d_m = d.getMinutes();
				document.getElementById("d_m").value = d.getMinutes();
				if (d.getSeconds()<10) var d_s = "0" + d.getSeconds(); else var d_s = d.getSeconds();
				document.getElementById("d_s").value = d.getSeconds();
				document.getElementById("txt").innerHTML = d_h + ":" + d_m + ":" + d_s;
				var t = setTimeout(odbierzDate, 500);
				/*var flaga=0;
				if(d_s%2==0 && flaga==0)
				{
					Socket.send(d_h + ":" + d_m + ":" + d_s + ":" + t_tyg);
					flaga=1;
					//document.formularz.submit();
				}
				else flaga=0;
				if(d_s%20==0 && flaga==0)
				{
					document.formularz.submit();
				}*/
			}
			
			function uruchom()
			{
				document.getElementById("start").value=1;
			}
			
			function zatrzymaj()
			{
				document.getElementById("stop").value=1;
			}
			
			var Socket;
			function sprawdzStanPojazdu()
			{
				Socket = new WebSocket("ws://192.168.104.104:81/");
				Socket.onmessage = function(event)
				{
					if(event.data == "S") document.getElementById("stan_silnika").innerHTML = "Silnik pracuje";
					if(event.data == "s") document.getElementById("stan_silnika").innerHTML = "Silnik nie pracuje";
					if(event.data == "P") document.getElementById("stan_przeszkody").innerHTML = "Wykryto przeszkodę";
					if(event.data == "p") document.getElementById("stan_przeszkody").innerHTML = "Nie wykryto przeszkody";
					if(event.data == "t") document.formularz.submit();	
				}
			}
			//setTimeout(function()
			//{
			//	sprawdzStanPojazdu();
			//},500);
			
		</script>
	</head>
	<body onload="odbierzDate(); javascript:sprawdzStanPojazdu()">
		<div id="container">
			<div id="header">
				<h1>Serwer zdalnie sterowanej platformy jezdnej</h1>
			</div>
			<div id="content">
				<div id="nav">
					<h3>Nawigacja</h3>
					<ul>
						<li><a class="selected" href="http://192.168.104.104/">Główna</a></li>
						<li><a href="nastaw_html">Harmonogram</a></li>
						
					</ul>
				</div>
				<div id="main">
					<h3>Status</h3>
					<div id="time">
						<div id="txt"></div>
						<div id="form1">
							<form method="post" name="formularz">
							<INPUT id="d_tyg" name="d_tyg" type="hidden" value="">
							<INPUT id="d_h" name="d_h" type="hidden" value="">
							<INPUT id="d_m" name="d_m" type="hidden" value="">
							<INPUT id="d_s" name="d_s" type="hidden" value="">
							<INPUT type="submit" value="Synchronizuj">
							</form>
						</div>
					</div>
					<div id="status">
						<div id="stan_silnika">Silnik nie pracuje</div>
						<div id="stan_przeszkody">Nie znaleziono przeszkody</div>
						<form method="post" name="formularz2" if="formularz2">
						<input id="start" name="start" type="hidden" value="">
						<input id="stop" name="stop" type="hidden" value="">
						<input type="submit" onclick="uruchom();" value="Uruchom">
						<input type="submit" onclick="zatrzymaj();" value="Zatrzymaj">
						</form>
					</div>
				</div>
			</div>
			<div id="footer">
				Copyright &copy; 2019 Mateusz Szalkowski.
			<div>
		</div>
	</body>
</html>
)=====";
