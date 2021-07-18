<?php
	// 驗證有沒有登入的資訊
	require_once dirname(__FILE__) . "/include/head.php";
	$time = $_SERVER['REQUEST_TIME'];
	$timeout_duration = 1800;  // 設定30分鐘為timeout
	// 沒有登入的資訊or timeout
	$is_loggin = isset($_COOKIE["login"]);
	$is_timeout = ($time - $_COOKIE['LAST_ACTIVITY']) > $timeout_duration;
	if (!$is_loggin || $is_timeout) 
	{
		// 傳送到login.php確保沒有登入資訊的人進不了blog.php
		header("Location: ./login.php");
		exit();
	}
?>