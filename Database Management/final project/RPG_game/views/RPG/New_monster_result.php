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
			action = "/RPG_game/models/New_monster_DB.php" 
		>
			<h3 align="center">NEW MONSTER</h3>   		  
			<br><br>
			<h4 align="center" style="color:blue;">The new monster has been generated!</h4>
			</button>  			
		</form>			
	</div>
</div>