<?php
	// 驗證有沒有登入的資訊
	require_once dirname(__FILE__) . "/include/head.php";
	$time = $_SERVER['REQUEST_TIME'];
	// 設定30min(1800sec)為timeout
	$timeout_duration = 1800;  
	$is_login = isset($_COOKIE["login"]);
	// 沒有登入的資訊 or timeout
	$is_timeout = ($time - $_COOKIE['LAST_ACTIVITY']) > $timeout_duration;
	if (!$is_login || $is_timeout) 
	{
		// 傳送到login.php確保沒有登入資訊的人進不了blog.php
		header("Location: ./login.php");
		exit();
	}
?>