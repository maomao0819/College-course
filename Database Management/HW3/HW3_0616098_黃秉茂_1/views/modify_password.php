<?php
	$is_loggin = isset($_COOKIE["login"]);
	if (!$is_loggin)
	{
		require_once dirname(__FILE__) . "/login_status.php";
	}
	else
	{
		require_once dirname(__FILE__) . "/include/head.php";
		require_once dirname(__FILE__) . "/modify_password_nav.php";
	}
	
?>
<!-- 修改密碼頁的部分 -->
<script type = "text/javascript" src = "./include/js/modify_password_form_submit.js"></script>
<div>
	<form 
		id = "form2" 
		onsubmit = "return false" 
		action = "/HW3_0616098_黃秉茂/models/modify_password_check.php"
	>
		<div>
			<br>
			<br>
			<br>
			<label>
				<p class="label-txt">
					<b>Old password: </b>
				</p>
					<input 
						id="old_password"
						name="old_password"
						type="password"
						class = "input" 
						required = ""
					>
				<div class = "line-box">
					<div class = "line"></div>
				</div>
			</label>
		</div>
		<div>
			<label>
				<p class="label-txt">
					<b>New password: </b>
				</p>
					<input 
						id = "new_password" 
						name = "new_password" 
						type = "password"
						class = "input" 
						required = ""
					>
				<div class = "line-box">
					<div class="line"></div>
				</div>
			</label>
		</div>
		<div>
			<label>
				<p class = "label-txt">
					<b>Confirm new password: </b>
				</p>
				<input 
					id = "new_passwordConfirm" 
					name = "new_passwordConfirm"
					type = "password" 
					class = "input" 
					required = ""
				>
				<div class = "line-box">
					<div class = "line"></div>
				</div>
			</label>
		</div>
		<button name= "submit_modify_password" type="submit"> 
			<b>submit_modify_password</b>
		</button>
	</form>
</div>
<script>modify_password_form_submit()</script>