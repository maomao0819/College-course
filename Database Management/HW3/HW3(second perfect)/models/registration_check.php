<?php
	// check user, email是否被註冊過
	// 引入/db_check.php 檔案做資料庫的確認
	require_once dirname(__FILE__)."/db_check.php";
	$query = 
	[
		// htmlspecialchars() :避免使用者夾雜html的非法輸入
		// $_GET()取得網址所帶的query 註: 網址query
		'email' => htmlspecialchars($_GET["email"]),
		'username' => htmlspecialchars($_GET["username"]),
		'password' => htmlspecialchars($_GET["password"])
	];
	// 取得資料庫連線資訊 註:此function在db_check.php內
	$conn = db_check();
	// 將參數帶入function看回傳結果
  	insertData($query['email'], $query['username'], $query['password'], $conn);
	function insertData($email, $username, $password, $conn) 
	{
		$email_sql = "SELECT id FROM user_account WHERE email = '$email'";
		$username_sql = "SELECT id FROM user_account WHERE username = '$username'";
		$email_result = mysqli_query($conn, $email_sql);
		$username_result = mysqli_query($conn, $username_sql);
		// 以mysqli_num_rows()回傳的數字來評斷email、username有沒有被註冊過，如果數字大於0代表有被註冊過。
		if(mysqli_num_rows($email_result) > 0) 
		{
			echo "Email has been registered";
			echo '<br>';
		}
		if(mysqli_num_rows($username_result) > 0) 
			echo "Username has been registered";
		// 沒被註冊過 -> 把參數塞入DB中的user_account資料表內
		if(mysqli_num_rows($email_result) === 0 && mysqli_num_rows($username_result) === 0) 
		{
			$sql = "INSERT INTO user_account (email, username, password) VALUES ('$email', '$username', '$password')";
			if (mysqli_query($conn, $sql)) 
				echo "Add the data successfully";
			else 
			echo "Error: " . $sql . "<br>" . $conn->error;
		}
	}
	// 終止連線以免資源浪費
	// 在程式最末段終止DB連線 (保持良好的設計習慣記得在做完資料庫的連線使用後關閉連線，釋放資源)
	$conn->close();