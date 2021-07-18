<?php
	// login的頁面
	require_once dirname(__FILE__) . "/../modify_password_nav.php";
	// 只要到登入頁面，會清空使用者狀態，讓他要重新登入才能看到後面的結果
	// 釋放COOKIE所保留的使用者登入資訊
?>
<?php
	require '/RPG_game/models/search_opponent_DB.php';
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
			print "$r[0]\n" ;
?>
<link rel = "stylesheet" type = "text/css" href = "./../include/css/login.css">
<div class = "container">
	<div class = "wrapper">
		<form
			id = "form"
			method = "get"  
			action = "/RPG_game/models/search_opponent_DB.php" 
		>       
			<h3 align="center">SEARCH OPPONENT</h3>   		  
			<button 
				class = "btn btn-primary btn-block"  
				name = "submit" 
				value = "Login" 
				type = "submit"
				onclick= "<?php
	require 'DB.php';
	require '/RPG_game/models/search_opponent_DB.php';
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
			print "$r[0]\n" ;
?>"
			>
				<b>SUBMIT</b>
			</button>  			
		</form>			
	</div>
</div>