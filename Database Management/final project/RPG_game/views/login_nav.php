<?php
	require_once dirname(__FILE__) . "/include/head.php";
?>
<ul 
	class = "justify-content-front" 
	style = "background-color: gray"
>
	<button 
		class = "btn" 
		onclick = "window.location = '/RPG_game/views/registration.php'"
	>
		<b>註冊</b>
	</button>
	<button 
		class = "btn" 
		onclick = "window.location = '/RPG_game/views/login.php'"
	>
		<b>登入</b>
	</button>
	<button 
		class = "btn" 
		onclick = "window.location = '/RPG_game/models/initial_DB.php'"
	>
		<b>初始化</b>
	</button>
</ul>