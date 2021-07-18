<?php
	require_once dirname(__FILE__) . "/include/head.php";
?>
<ul 
	class = "justify-content-front" 
	style = "background-color: gray"
>
	<button 
		class = "btn" 
		onclick = "window.location = '/HW3_0616098_黃秉茂/views/registration.php'"
	>
		<b>註冊</b>
	</button>
	<button 
		class = "btn" 
		onclick = "window.location = '/HW3_0616098_黃秉茂/views/login.php'"
	>
		<b>登入</b>
	</button>
	<button 
		class = "btn" 
		onclick = "window.location = '/HW3_0616098_黃秉茂/models/initial_DB.php'"
	>
		<b>初始化</b>
	</button>
</ul>