<?php
	// login的頁面
	require_once dirname(__FILE__) . "/../modify_password_nav.php";
	// 只要到登入頁面，會清空使用者狀態，讓他要重新登入才能看到後面的結果
	// 釋放COOKIE所保留的使用者登入資訊
?>
<link rel = "stylesheet" type = "text/css" href = "./../include/css/login.css">
<div class = "container">
	<div class = "wrapper">
		<form
			id = "form"
			method = "get"  
			action = "/RPG_game/models/upgrade_DB.php" 
		>
			<h3 align="center">UPGRADE</h3>   		  
			<br><br>
			<?php
				$upgrade_sql =
  	  				"SELECT Class_Name 
  	  	 			 FROM class
  	  	 			 WHERE Class_ID = (SELECT Monster_ID 
  	  	 				           	   FROM monster 
  	  	 				           	   WHERE Defeat_Exp = 1)";
  	  	 		// require 'DB.php';
			    // $d = DB::connect('oci8://acct1:pass12@www.host.com/dbname') ;
			    // if (DB::isError($d)) { die("cannot connect -" . $d->getMessage());}
			    // $d->setErrorHandling(PEAR_ERROR_DIE);
			    // $q = $d->query("SELECT Class_Name 
			    //                 FROM class
			    //                 WHERE Class_ID = (SELECT Monster_ID 
			    //                                   FROM monster 
			    //                                   WHERE Defeat_Exp = 1)" ) ;
			    // while ($r = $q->fetchRow()) 
			    //   $result = "$r[0]\n" ;
  	  	 		$monster_name = "slime";
			    // mysql_connect("127.0.0.1", "root", "");
			    // mysql_select_db("user");
			    // mysql_query($upgrade_sql);
                // foreach ($skill as &$value)
                // 	echo "<h4 align=\"center\" style=\"color:blue;\">$value</h4>";
                echo "<h4 align=\"center\" style=\"color:blue; \">You can crusade against the $monster_name to upgrade</h4>";
			?>
			</button>  			
		</form>	
	</div>
</div>