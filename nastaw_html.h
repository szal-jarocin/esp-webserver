const char nastaw_html[] PROGMEM = R"=====(
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
			
			#form1
			{
				float: left;
				padding-top: 10px;
				padding-bottom: 10px;
			}
			
			.ukryty1, .ukryty2, .ukryty3, .ukryty4, .ukryty5, .ukryty6, .ukryty7
			{
				display: none;
			}
			
			.pn_box:checked + .ukryty1, .wt_box:checked + .ukryty2, .sr_box:checked + .ukryty3, .cz_box:checked + .ukryty4, .pt_box:checked + .ukryty5, .sb_box:checked + .ukryty6, .nd_box:checked + .ukryty7
			{
				display: inline-block;
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
			function sprawdzaj()
			{
				var pn_od_var = document.formularz.pn_od.value; var pn_do_var = document.formularz.pn_do.value;
				var wt_od_var = document.formularz.wt_od.value; var wt_do_var = document.formularz.wt_do.value;
				var sr_od_var = document.formularz.sr_od.value; var sr_do_var = document.formularz.sr_do.value;
				var cz_od_var = document.formularz.cz_od.value; var cz_do_var = document.formularz.cz_do.value;
				var pt_od_var = document.formularz.pt_od.value; var pt_do_var = document.formularz.pt_do.value;
				var sb_od_var = document.formularz.sb_od.value; var sb_do_var = document.formularz.sb_do.value;
				var nd_od_var = document.formularz.nd_od.value; var nd_do_var = document.formularz.nd_do.value;
				
				if(document.formularz.pn_box.checked) document.getElementById("pn").value = 1;
				else document.getElementById("pn").value = 0;
				if(document.formularz.wt_box.checked) document.getElementById("wt").value = 1;
				else document.getElementById("wt").value = 0;
				if(document.formularz.sr_box.checked) document.getElementById("sr").value = 1;
				else document.getElementById("sr").value = 0;
				if(document.formularz.cz_box.checked) document.getElementById("cz").value = 1;
				else document.getElementById("cz").value = 0;
				if(document.formularz.pt_box.checked) document.getElementById("pt").value = 1;
				else document.getElementById("pt").value = 0;
				if(document.formularz.sb_box.checked) document.getElementById("sb").value = 1;
				else document.getElementById("sb").value = 0;
				if(document.formularz.nd_box.checked) document.getElementById("nd").value = 1;
				else document.getElementById("nd").value = 0;
				
				if((document.formularz.pn_box.checked&&pn_od_var>=pn_do_var)||(document.formularz.wt_box.checked&&wt_od_var>=wt_do_var)||(document.formularz.sr_box.checked&&sr_od_var>=sr_do_var)||(document.formularz.cz_box.checked&&cz_od_var>=cz_do_var)||(document.formularz.pt_box.checked&&pt_od_var>=pt_do_var)||(document.formularz.sb_box.checked&&sb_od_var>=sb_do_var)||(document.formularz.nd_box.checked&&nd_od_var>=nd_do_var))
				{
					alert("Godzina zakończenia nie może być wcześniejsza niż godzina rozpoczęcia!");
					return false;
				}
				else document.formularz.submit();
			}
			function stronaGlowna()
			{
				
			}
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
						<li><a href="http://192.168.104.104/">Główna</a></li>
						<li><a class="selected" href="nastaw_html">Harmonogram</a></li>
						
					</ul>
				</div>
				<div id="main">
					<h3>Harmonogram pracy</h3>
					<div id="form1">
						<form method="post"	action="http://192.168.104.104"  name=formularz>
						<input name="pn" id="pn" type="hidden" value="0">
						<input name="wt" id="wt" type="hidden" value="0">
						<input name="sr" id="sr" type="hidden" value="0">
						<input name="cz" id="cz" type="hidden" value="0">
						<input name="pt" id="pt" type="hidden" value="0">
						<input name="sb" id="sb" type="hidden" value="0">
						<input name="nd" id="nd" type="hidden" value="0">
						<input name="pn_box" class="pn_box" type="checkbox" value=""> Poniedziałek <div class="ukryty1"> od: <input name="pn_od" type="time"> do: <input name="pn_do" id="pn_do" type="time" min=pn_od></div><br>
						<input name="wt_box" class="wt_box" type="checkbox" value=""> Wtorek 		<div class="ukryty2"> od: <input name="wt_od" type="time"> do: <input name="wt_do" type="time" min=wt_od></div><br>
						<input name="sr_box" class="sr_box" type="checkbox" value=""> Środa 		<div class="ukryty3"> od: <input name="sr_od" type="time"> do: <input name="sr_do" type="time" min=sr_od></div><br>
						<input name="cz_box" class="cz_box" type="checkbox" value=""> Czwartek 	<div class="ukryty4"> od: <input name="cz_od" type="time"> do: <input name="cz_do" type="time" min=cz_od></div><br>
						<input name="pt_box" class="pt_box" type="checkbox" value=""> Piątek 		<div class="ukryty5"> od: <input name="pt_od" type="time"> do: <input name="pt_do" type="time" min=pt_od></div><br>
						<input name="sb_box" class="sb_box" type="checkbox" value=""> Sobota 		<div class="ukryty6"> od: <input name="sb_od" type="time"> do: <input name="sb_do" type="time" min=sb_od></div><br>
						<input name="nd_box" class="nd_box" type="checkbox" value=""> Niedziela 	<div class="ukryty7"> od: <input name="nd_od" type="time"> do: <input name="nd_do" type="time" min=nd_od></div><br>
						<input type="submit" id="submit" value="Potwierdź" onClick="return sprawdzaj();">
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
