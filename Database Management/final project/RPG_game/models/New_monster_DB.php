<?php
	require_once dirname(__FILE__) . "/db_check.php";
	$conn = db_check();
  	$insert_new_monster_sql =
  	  	"INSERT INTO MONSTER(Monster_ID, Class ,Defeat_Exp) SELECT COUNT(Monster_ID)+(1),Class_ID,(10) FROM `class`,`monster` WHERE Class_Name = 'Slime'";
	mysqli_query($conn, $insert_new_monster_sql);
  	setcookie("New_monster_DB", true, time() + 3600, "/");
  	header("Location: ../views/RPG/New_monster_result.php");
	exit();