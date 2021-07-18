<?php
	require_once dirname(__FILE__) . "/db_check.php";
	$conn = db_check();
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
	mysqli_query($conn, $my_skill_sql);
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

  // mysql_connect("127.0.0.1", "root", "");
  // mysql_select_db("user");
  // mysql_query($my_skill_sql);

  setcookie("My_skill_DB", true, time() + 3600, "/");
  header("Location: ../views/RPG/My_skill_result.php");
	exit();