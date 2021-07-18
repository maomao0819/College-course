<?php
	require_once dirname(__FILE__) . "/db_check.php";
	require_once dirname(__FILE__) . "/delete_login_info_cookie.php";
	$conn = db_check();
	$drop_taqble_sql = "DROP TABLE user_account";
  	mysqli_query($conn, $drop_taqble_sql);
  	$create_sql =
  	  	"CREATE TABLE user_account (
		id INT(10) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
		email VARCHAR(60) NOT NULL,
		username VARCHAR(40) NOT NULL,
		password VARCHAR(40) NOT NULL,
		reg_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP);";
	mysqli_query($conn, $create_sql);
  	$email = "11@11";
  	$username = "11";
  	$password = md5("11", false);
  	$initail_sql = "INSERT INTO user_account (email, username, password) VALUES ('$email', '$username', '$password')";
  	mysqli_query($conn, $initail_sql);
  	delete_login_info_cookie();
  	setcookie("initial_DB", true, time() + 3600, "/HW3");
  	header("Location: ../views/login.php");
	exit();