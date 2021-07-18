<?php
	$is_loggin = isset($_COOKIE["login"]);
	if (!$is_loggin)
		require_once dirname(__FILE__) . "/login_nav.php";
	else
	{
		require_once dirname(__FILE__) . "/login_status.php";
		require_once dirname(__FILE__) . "/logged_in_nav.php";
		require_once $_SERVER["DOCUMENT_ROOT"] . "/RPG_game/models/db_check.php";
	}
?>
	<html>
		<head>
			<title>Resume</title>
			<meta charset="utf-8">
			<meta name="viewport" content="width=device-width, initial-scale=1">
			<!-- Website Link -->
			<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css">
			<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
			<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/js/bootstrap.min.js"></script>
			
			<!-- External File -->
			<script type="text/javascript" src="./include/js/event.js"></script>
			<link rel="stylesheet" type="text/css" href="./include/css/style.css">
		</head>
		<body>
			<hr>
			<!-- Popover Navigation Bar -->
			<div id = "local-link">
				<ul class="nevigate">
    				<li class="nevigate"><a href = "/RPG_game/views/RPG/search_opponent.php" class="nevigate active">search opponent</a></li>
    				<li class="nevigate"><a href = "/RPG_game/views/RPG/upgrade.php"  class="nevigate">upgrade</a></li>
    				<li class="nevigate"><a href = "/RPG_game/views/RPG/My_skill.php"  class="nevigate">My skill</a></li>
    				<li class="nevigate"><a href = "/RPG_game/views/RPG/crusade_against_the_monster.php"  class="nevigate">Crusade against the monster</a></li>
    				<li class="nevigate"><a href = "/RPG_game/views/RPG/New_monster.php"  class="nevigate">New monster</a></li>
  				</ul>
			</div>
			<hr>
			<!-- Profile -->
			<div id = "title" class = "parallax" style = "text-align: center; line-height:230px;">
				<br>
				<h1 style = "line-height: 15px; font-size: 100px; color: white; ">
					<?php 
						if (isset($_COOKIE["username"]))
						{
							echo "<strong> Welcome to RPG world !! <br><br><br><br><br><br> The great king, <b>" . $_COOKIE["username"] . "</b></strong>"; 
						}
						else
							echo "<br><br><br><strong> Welcome to RPG world !! </strong>";
					?>
				</h1>
				<br>
			</div>
			<hr>
			<!-- SCROOL TOP BOTTON -->
			<button onclick = "topFunction()" id = "TopBotton" title = "Go to top">Top</button>
			<script>
				//Get the button
				var topbutton = document.getElementById("TopBotton");
			</script>
			<!-- Bootstrap Carousel -->
			<div class="bg_pink">
				<div class="container" align="center"> 
				  	<div id="RPG_Carousel" class="carousel slide" data-ride="carousel" style="width:960px; height:540px;">
				    	<!-- Indicators -->
				    	<ol class="carousel-indicators">
				      		<li data-target="#RPG_Carousel" data-slide-to="0" class="active"></li>
				      		<li data-target="#RPG_Carousel" data-slide-to="1"></li>
				      		<li data-target="#RPG_Carousel" data-slide-to="2"></li>
				      		<li data-target="#RPG_Carousel" data-slide-to="3"></li>
				    	</ol>
				    	<!-- Wrapper for slides -->
				    	<div class="carousel-inner" role="listbox" style="width:100%;">
				      		<div class="item active">
				        		<img src="./include/image/rpg1.jpg">
				      		</div>
				      		<div class="item">
				        		<img src="./include/image/rpg2.jpg">
				     		</div>
				      		<div class="item">
				        		<img src="./include/image/rpg3.jpg">
				     		</div>
				     		<div class="item">
				        		<img src="./include/image/rpg4.jpg">
				     		</div>
				    	</div>
				    	<!-- Left and right controls -->
				    	<a class="left carousel-control" href="#RPG_Carousel" data-slide="prev">
				    	  	<span class="glyphicon glyphicon-chevron-left"></span>
				      		<span class="sr-only">Previous</span>
				    	</a>
				    	<a class="right carousel-control" href="#RPG_Carousel" data-slide="next">
				      		<span class="glyphicon glyphicon-chevron-right"></span>
				      		<span class="sr-only">Next</span>
				    	</a>
				  	</div>
				</div>
			</div>
		</body>
	</html>