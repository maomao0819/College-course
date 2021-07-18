<?php
	// login的頁面
	require_once dirname(__FILE__) . "/login_nav.php";
	// 只要到登入頁面，會清空使用者狀態，讓他要重新登入才能看到後面的結果
	// 釋放COOKIE所保留的使用者登入資訊
	require_once dirname(__FILE__)."/../models/delete_login_info_cookie.php";
	delete_login_info_cookie();
    setcookie( "initial_DB", "", time() - 3600, "/");
?>
<script type = "text/javascript" src = "./include/js/login.js"></script>
<link rel = "stylesheet" type = "text/css" href = "./include/css/login.css">
<div class = "container">
	<div class = "wrapper">
		<form
			id = "form"
			method = "get"  
			action = "/RPG_game/models/login_check.php" 
		>       
			<h3 align="center">Login</h3>
			<input
				id = "username"
				name = "username" 
				type = "text" 
				class = "form-control" 
				placeholder = "Username" 
				required = ""
			>
			<input
				id = "password"
				name = "password"  
				type = "password" 
				class = "form-control" 
				placeholder = "Password" 
				required = ""
			>     		  
			<button 
				class = "btn btn-primary btn-block"  
				name = "submit" 
				value = "Login" 
				type = "submit"
			>
				<b>登入</b>
			</button>  			
		</form>			
	</div>
</div>
<script>getUrlVars_error()</script>