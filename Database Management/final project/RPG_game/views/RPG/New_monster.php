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
			<input
				id = "monster_name"
				name = "monster_name" 
				type = "text" 
				class = "form-control" 
				placeholder = "Monster_Name" 
				required = ""
			>   		  
			<button 
				class = "btn btn-primary btn-block"  
				name = "submit" 
				value = "Login" 
				type = "submit"
				onclick= "window.location.href='./../../models/New_monster_DB.php'"
			>
				<b>SUBMIT</b>
			</button>  			
		</form>			
	</div>
</div>