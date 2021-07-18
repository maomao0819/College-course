<?php
	require_once dirname(__FILE__) . "/db_check.php";
	$conn = db_check();
  $upgrade_sql =
  	  	"SELECT Class_Name 
  	  	 FROM class
  	  	 WHERE Class_ID = (SELECT Monster_ID 
  	  	 				           FROM monster 
  	  	 				           WHERE Defeat_Exp = 1)";
	mysqli_query($conn, $upgrade_sql);
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

  // mysql_connect("127.0.0.1", "root", "");
  // mysql_select_db("user");
  // mysql_query($upgrade_sql);

  setcookie("upgrade_DB", true, time() + 3600, "/");
  header("Location: ../views/RPG/upgrade_result.php");
	exit();