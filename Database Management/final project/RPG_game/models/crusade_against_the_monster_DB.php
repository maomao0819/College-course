<?php
	require_once dirname(__FILE__) . "/db_check.php";
	$conn = db_check();
  	$crusade_against_the_monster_sql =
  	  	"UPDATE MONSTER,CHARACTER_TABLE 
		 SET Defeat_Date=CURRENT_DATE(),Defeated_By=1,Exp=Exp+Defeat_Exp 
		 WHERE Monster_ID=25 AND Character_ID=1;";
	mysqli_query($conn, $crusade_against_the_monster_sql);
  	setcookie("crusade_against_the_monster_DB", true, time() + 3600, "/");
  	// header("Location: ../views/index.php");
  	header("Location: ../views/RPG/crusade_against_the_monster_result.php");
	exit();