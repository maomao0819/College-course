<?php
	require_once dirname(__FILE__) . "/login_nav.php";
?>
<!-- 註冊頁的部分 -->
<script type = "text/javascript" src = "./include/js/registration_form_submit.js"></script>
<div>
	<form 
		id = "form" 
		onsubmit = "return false" 
		action = "/HW3/models/registration_check.php"
	>
		<div>
			<label>
				<p class="label-txt">
					<b>EMAIL: </b>
				</p>
					<input 
						id = "email" 
						name = "email" 
						type = "email" 
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
					<b>Username: </b>
				</p>
					<input 
						id = "username" 
						name = "username" 
						type = "text" 
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
					<b>Password: </b>
				</p>
				<input 
					id = "passwordInput" 
					name = "passwordInput"
					type = "password" 
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
				<p class = "label-txt">
					<b>Confirm password: </b>
				</p>
			<input 
				id = "passwordConfirm" 
				name = "passwordConfirm" 
				type = "password" 
				class = "input" 
				autocomplete = "Off" 
				required = ""
			>
				<div class = "line-box">
					<div class="line"></div>
				</div>
			</label>
		</div>
		<button>submit</button>
	</form>
</div>
<script>registration_form_submit()</script>
<!-- 最後進到/models/registration_check.php -->