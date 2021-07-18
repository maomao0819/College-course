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
			<!-- Profile -->
			<div id = "title"  style = "text-align: center; line-height:230px;">
				<br>
				<h1 style = "line-height: 30px; color: black; ">
					<?php
							require dirname(__FILE__) . '/../models/.php';
							$d = DB::connect('oci8://acct1:pass12@www.host.com/dbname') ;
							if (DB::isError($d)) { die("cannot connect -" . $d->getMessage());}
							$d->setErrorHandling(PEAR_ERROR_DIE);
							$q = $d->query("SELECT Character_Name 
  	  	 									FROM CHARACTER_TABLE 
  	  	 									WHERE Account = (SELECT A2.Account_ID 
  	  	 				  									 FROM account A2, account A1 
  	  	 				  									 WHERE A2.Country = (SELECT A1.Country 
  	  	 				  					  									 WHERE A1.Real_Name = 'John Smith')
  	  	 				  					AND A2.Account_ID != A1.Account_ID);" ) ;
							while ($r = $q->fetchRow()) 
							echo "$r[0]\n" ;
					?>
				</h1>
				<br>
			</div>
			<hr>
		</body>
	</html>