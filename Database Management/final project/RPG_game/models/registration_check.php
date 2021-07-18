<?php
	require_once dirname(__FILE__)."/db_check.php";
	$query = 
	[
		'email' => htmlspecialchars($_GET["email"]),
		'username' => htmlspecialchars($_GET["username"]),
		'password' => htmlspecialchars($_GET["password"])
	];
	// 取得資料庫連線資訊
	$conn = db_check();
  	insertData($query['email'], $query['username'], $query['password'], $conn);
	function insertData($email, $username, $password, $conn) 
	{
		$email_sql = "SELECT id FROM user_account WHERE email = '$email'";
		$username_sql = "SELECT id FROM user_account WHERE username = '$username'";
		$email_result = mysqli_query($conn, $email_sql);
		$username_result = mysqli_query($conn, $username_sql);
		if(mysqli_num_rows($email_result) > 0) 
		{
			echo "Email has been registered";
			echo '<br>';
		}
		if(mysqli_num_rows($username_result) > 0) 
			echo "Username has been registered";
		if(mysqli_num_rows($email_result) === 0 && mysqli_num_rows($username_result) === 0) 
		{
			$sql = "INSERT INTO user_account (email, username, password) VALUES ('$email', '$username', '$password')";
			if (mysqli_query($conn, $sql)) 
				echo "Add the data successfully";
			else 
			echo "Error: " . $sql . "<br>" . $conn->error;
		}
	}
	$conn->close();