<?php
	// 進入點login的頁面
	require_once dirname(__FILE__)."/login_nav.php";
	// 只要到登入頁面，會清空使用者狀態，讓他要重新登入才能看到後面的結果
	// 釋放SESSION所保留的使用者登入資訊
	// 不同於/views/registration.php ajax的方式，這裡是實作傳統的表單發送介接後端的方式，發送方法為"GET"，不需等待回傳，且需頁面跳轉。
	// unset($_SESSION['login']);
	// unset($_SESSION['id']);
	// unset($_SESSION['username']);
	setcookie( "login", "", time()-3600, "/");
	setcookie( "id", "", time()-3600, "/");
	setcookie( "username", "", time()-3600, "/");
	setcookie( "password", "", time()-3600, "/");
    setcookie( "LAST_ACTIVITY", "", time()-3600, "/");
?>

<div class="container">
	<div class="wrapper">
		<form
			id="form"
			class="form-signin"
			method="get"  
			action="/HW3/models/login_check.php" 
		>       
			<h3 class="form-signin-heading">Login</h3>
			<!-- PO文部分，較傳統的發送到後端的方式，傳統的php方式將結果印出到前端，POST -> 回傳到表單 -> 回傳頁面 -> 重新整理，重新load一次頁面 -> 生成新資料， 非用Ajex -->
			<input
				id="username"
				name="username" 
				type="text" 
				class="form-control" 
				placeholder="Username" 
				required=""
			>
			<input
				id="password"
				name="password"  
				type="password" 
				class="form-control" 
				placeholder="Password" 
				required=""
			>     		  
			<button 
				class="btn btn-lg btn-primary btn-block"  
				name="submit" 
				value="Login" 
				type="submit"
			><b>登入</b></button>  			
		</form>			
	</div>
</div>

<script>
if(getUrlVars()['error']) {
	Swal.fire({
			icon: 'warning',
			title: 'Oops...',
			text: decodeURIComponent(getUrlVars()['error']),
	});
}

//用來取得網址所帶的參數，如果登入失敗 server會將網址帶上"?error=帳號密碼錯誤"，"getUrlVars()"會根據回傳內容顯示跳窗。
function getUrlVars()
{
	var vars = [], hash;
	var hashes = window.location.href.slice(window.location.href.indexOf('?') + 1).split('&');
	for(var i = 0; i < hashes.length; i++)
	{
		hash = hashes[i].split('=');
		vars.push(hash[0]);
		vars[hash[0]] = hash[1];
	}
	return vars;
}
</script>

<style>
.wrapper {    
	margin-top: 80px;
	margin-bottom: 20px;
}

.form-signin {
	max-width: 420px;
	padding: 30px 38px 66px;
	margin: 0 auto;
	background-color: #eee;
}

.form-signin-heading {
	text-align:center;
	margin-bottom: 30px;
}

.form-control {
	position: relative;
	font-size: 16px;
	height: auto;
	padding: 10px;
}

input[type="text"] {
	margin-bottom: 0px;
	border-bottom-left-radius: 0;
	border-bottom-right-radius: 0;
}

input[type="password"] {
	margin-bottom: 20px;
	border-top-left-radius: 0;
	border-top-right-radius: 0;
}
</style>