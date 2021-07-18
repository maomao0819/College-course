<?php
// 驗證有沒有登入的資訊
require_once dirname(__FILE__) . "/include/head.php";
$time = $_SERVER['REQUEST_TIME'];
$timeout_duration = 1800;  // 設定30分鐘為timeout
// 沒有登入的資訊or timeout
if (!isset($_SESSION['login']) || ($time - $_SESSION['LAST_ACTIVITY']) > $timeout_duration) {
	// 傳送到login.php確保沒有登入資訊的人進不了blog.php
  header("Location: ./login.php");
  exit();
}
?>