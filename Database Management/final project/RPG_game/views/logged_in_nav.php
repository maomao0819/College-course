<?php
	require_once dirname(__FILE__). "/include/head.php";
?>

	<div style = "width: 100%">
		<div 
			align = "left" 
			style = "color:brown"
		>
			<?php echo "Welcome! The great king, <b>" . $_COOKIE["username"] . "</b>&nbsp;~&nbsp;&nbsp;" ?>
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
							window.location = '/RPG_game/views/login.php'
					})"
			>
				<b>登出</b>
			</button>
			<button 
				class = "btn" 
				onclick = "window.location = '/RPG_game/views/modify_password.php'"
			>
				<b>修改密碼</b>
			</button>
			<button 
				class = "btn" 
				onclick = "window.location = '/RPG_game/models/initial_DB.php'"
			>
				<b>初始化</b>
			</button>
		</div>
	</div>
