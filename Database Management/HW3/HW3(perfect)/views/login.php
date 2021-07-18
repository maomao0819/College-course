<?php
	// login的頁面
	require_once dirname(__FILE__) . "/login_nav.php";
	// 只要到登入頁面，會清空使用者狀態，讓他要重新登入才能看到後面的結果
	// 釋放COOKIE所保留的使用者登入資訊
	// 不同於/views/registration.php ajax的方式，這裡是實作傳統的表單發送介接後端的方式，發送方法為"GET"，不需等待回傳，且需頁面跳轉。
	require_once dirname(__FILE__)."/../models/delete_login_info_cookie.php";
	delete_login_info_cookie();
    setcookie( "initial_DB", "", time() - 3600, "/HW3");
?>
<script type = "text/javascript" src = "./include/js/login.js"></script>
<link rel = "stylesheet" type = "text/css" href = "./include/css/login.css">
<div class = "container">
	<div class = "wrapper">
		<form
			id = "form"
			class = "form-signin"
			method = "get"  
			action = "/HW3/models/login_check.php" 
		>       
			<h3 class = "form-signin-heading">Login</h3>
			<!-- PO文部分，較傳統的發送到後端的方式，傳統的php方式將結果印出到前端，POST -> 回傳到表單 -> 回傳頁面 -> 重新整理，重新load一次頁面 -> 生成新資料， 非用Ajex -->
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
				class = "btn btn-lg btn-primary btn-block"  
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