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
			action = "/RPG_game/models/My_skill_DB.php" 
		>
			<h3 align="center">MY SKILL</h3>   		  
			<br><br>
			<?php
				$my_skill_sql =
  	  				"SELECT skill.Skill_Name,skill.Level_limit,explevel.Level AS player_level
         			 FROM `skill`,`character_table`,`explevel`
         			 WHERE skill.Class=character_table.Class
           			   AND character_table.Exp=explevel.Experience
           			   AND character_table.Character_Name='tom'
           			   AND (NOT EXISTS (SELECT * 
                            			FROM skillused 
                            			WHERE skillused.Skill=Skill.Skill_ID
                              			  AND character_table.Character_ID=skillused.Char_ID));";
  	  	 		// require 'DB.php';
				// $d = DB::connect('oci8://acct1:pass12@www.host.com/dbname') ;
				// if (DB::isError($d)) { die("cannot connect -" . $d->getMessage());}
				// $d->setErrorHandling(PEAR_ERROR_DIE);
				// $q = $d->query("SELECT skill.Skill_Name,skill.Level_limit,explevel.Level AS player_level
				//        FROM `skill`,`character_table`,`explevel`
				//        WHERE skill.Class=character_table.Class
				//          AND character_table.Exp=explevel.Experience
				//          AND character_table.Character_Name='tom'
				//          AND (NOT EXISTS (SELECT * 
				//                           FROM skillused 
				//                           WHERE skillused.Skill=Skill.Skill_ID
				//                             AND character_table.Character_ID=skillused.Char_ID));" ) ;
				// while ($r = $q->fetchRow()) 
				//   $result = "$r[0]\n" ;
                $skill = ["Freeze", "Fireball", "Zap"];
				// mysql_connect("127.0.0.1", "root", "");
				// mysql_select_db("user");
				// mysql_query($my_skill_sql);
                foreach ($skill as &$value)
                	echo "<h4 align=\"center\" style=\"color:blue;\">$value</h4>";
			?>
			</button>  			
		</form>	
	</div>
</div>