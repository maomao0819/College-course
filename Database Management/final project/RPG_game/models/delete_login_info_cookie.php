<?php
	function delete_login_info_cookie() 
	{
		setcookie( "login", "", time() - 3600, "/");
		setcookie( "id", "", time() - 3600, "/");
		setcookie( "username", "", time() - 3600, "/");
		setcookie( "password", "", time() - 3600, "/");
		setcookie( "LAST_ACTIVITY", "", time() - 3600, "/");
	}