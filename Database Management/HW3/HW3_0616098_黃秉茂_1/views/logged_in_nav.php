<?php
	require_once dirname(__FILE__). "/include/head.php";
?>

	<div style = "width: 100%">
		<div 
			align = "left" 
			style = "color:green"
		>
			<?php echo "Welcome! Dear Mr./Mrs.<b>" . $_COOKIE["username"] . "</b>&nbsp;~&nbsp;&nbsp;" ?>
			<button 
				class = "btn" 
				onclick = 
					"Swal.fire
					({
						icon: 'warning',
						title: 'warning',
						text: 'Are you sure to log out?',
						showCancelButton: true,
					}).then((result) => 
					{
						if (result.value) 
							window.location = '/HW3_0616098_黃秉茂/views/login.php'
					})"
			>
				<b>登出</b>
			</button>
			<button 
				class = "btn" 
				onclick = "window.location = '/HW3_0616098_黃秉茂/views/modify_password.php'"
			>
				<b>修改密碼</b>
			</button>
			<button 
				class = "btn" 
				onclick = "window.location = '/HW3_0616098_黃秉茂/models/initial_DB.php'"
			>
				<b>初始化</b>
			</button>
		</div>
	</div>
