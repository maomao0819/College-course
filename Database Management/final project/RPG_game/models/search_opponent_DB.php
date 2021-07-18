<?php
	require_once dirname(__FILE__) . "/db_check.php";
	$conn = db_check();
  $search_opponent_sql =
  	  	"SELECT Character_Name 
  	  	 FROM CHARACTER_TABLE 
  	  	 WHERE Account = (SELECT A2.Account_ID 
  	  	 				  FROM account A2, account A1 
  	  	 				  WHERE A2.Country = (SELECT A1.Country 
  	  	 				  					  WHERE A1.Real_Name = 'John Smith') 
  	  	 				  AND A2.Account_ID != A1.Account_ID)";
	mysqli_query($conn, $search_opponent_sql);
  // require 'DB.php';
  // $d = DB::connect('oci8://acct1:pass12@www.host.com/dbname') ;
  // if (DB::isError($d)) { die("cannot connect -" . $d->getMessage());}
  // $d->setErrorHandling(PEAR_ERROR_DIE);
  // $q = $d->query("SELECT Character_Name 
  //        FROM CHARACTER_TABLE 
  //        WHERE Account = (SELECT A2.Account_ID 
  //                 FROM account A2, account A1 
  //                 WHERE A2.Country = (SELECT A1.Country 
  //                             WHERE A1.Real_Name = 'John Smith') 
  //                 AND A2.Account_ID != A1.Account_ID)" ) ;
  // while ($r = $q->fetchRow()) 
  //   $result = "$r[0]\n" ;

  // mysql_connect("127.0.0.1", "root", "");
  // mysql_select_db("user");
  // mysql_query($search_opponent_sql);

  setcookie("search_opponent_DB", true, time() + 3600, "/");
  header("Location: ../views/RPG/search_opponent_result.php");
	exit();