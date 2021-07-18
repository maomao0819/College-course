<?php
	require_once dirname(__FILE__) . "/include/head.php";
?>
<ul 
	class="nav justify-content-end" 
	style="background-color: white"
>
	<button 
		class="btn-outline-dark btn" 
		onclick="window.location = '/HW3/views/registration.php'"
	>
		<b>註冊</b>
	</button>
	<button 
		class="btn-outline-dark btn" 
		onclick="window.location = '/HW3/views/login.php'"
	>
		<b>登入</b>
	</button>
	<button 
		class="btn-outline-dark btn" 
		onclick="window.location = '/HW3/models/initial_DB.php'"
	>
		<b>初始化</b>
	</button>
</ul>