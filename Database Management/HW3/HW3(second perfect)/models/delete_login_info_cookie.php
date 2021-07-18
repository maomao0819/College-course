<?php
	function delete_login_info_cookie() 
	{
		setcookie( "login", "", time() - 3600, "/HW3");
		setcookie( "id", "", time() - 3600, "/HW3");
		setcookie( "username", "", time() - 3600, "/HW3");
		setcookie( "password", "", time() - 3600, "/HW3");
		setcookie( "LAST_ACTIVITY", "", time() - 3600, "/HW3");
	}