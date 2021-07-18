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
			action = "/RPG_game/models/crusade_against_the_monster_DB.php" 
		>
			<h3 align="center">CRUSADE AGAINST THE MONSTER</h3>   		  
			<br><br>
			<?php
				$crusade_against_the_monster_sql =
  	  				"UPDATE MONSTER,CHARACTER_TABLE 
		 			 SET Defeat_Date=CURRENT_DATE(),Defeated_By=1,Exp=Exp+Defeat_Exp 
		 			 WHERE Monster_ID=25 AND Character_ID=1;";
  	  	 		// require 'DB.php';
				// $d = DB::connect('oci8://acct1:pass12@www.host.com/dbname') ;
				// if (DB::isError($d)) { die("cannot connect -" . $d->getMessage());}
				// $d->setErrorHandling(PEAR_ERROR_DIE);
				// $q = $d->query("UPDATE MONSTER,CHARACTER_TABLE 
		 		//  SET Defeat_Date=CURRENT_DATE(),Defeated_By=1,Exp=Exp+Defeat_Exp 
		 		//  WHERE Monster_ID=25 AND Character_ID=1;" ) ;
				// while ($r = $q->fetchRow()) 
				//   $result = "$r[0]\n" ;
		 		$monster = "slime";
				// mysql_connect("127.0.0.1", "root", "");
				// mysql_select_db("user");
				// mysql_query($crusade_against_the_monster_sql);
		 		echo "<h4 align=\"center\" style=\"color:blue; \">The $monster has been killed!</h4>";
			?>
 			
		</form>			
	</div>
</div>