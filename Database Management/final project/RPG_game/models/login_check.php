<?php
	require_once dirname(__FILE__)."/db_check.php";
	if (isset($_GET['submit']))
	{
		// 取得username和password
		$query = 
		[
			'username' => htmlspecialchars($_GET["username"]),
			'password' => htmlspecialchars($_GET["password"])
		];
		$conn = db_check();
		checkData($query['username'], md5($query['password'], false), $conn);
	}
	// 名稱密碼都要對上 -> 註冊COOKIE資訊
	function checkData($username, $password, $conn) 
	{
		$sql = "SELECT id, username, password FROM user_account WHERE username = '$username' AND password = '$password'";
		$result = mysqli_query($conn, $sql);
		if(mysqli_num_rows($result) == 0) 
		{
			echo "Username or password error";
			header("Location: /RPG_game/views/login.php?error=Username or password error");   
		}
		// 登入成功 -> login, id, username, 最後登入時間寫入cookie -> 作為user登入的確認
		else 
		{
			$row = mysqli_fetch_assoc($result);
			echo "Login successfully";
			// 用cookie保存它的login, id, username, password, 最後登入時間(timeout機制)
			setcookie("login", true, time() + 3600, "/");
			setcookie("id", $row['id'], time() + 3600, "/");
			setcookie("username", $row['username'], time() + 3600, "/");
			setcookie("password", $row['password'], time() + 3600, "/");
			setcookie("LAST_ACTIVITY", $_SERVER['REQUEST_TIME'], time() + 3600, "/");
			header("Location: /RPG_game/views/index.php");
		}
	}
	$conn->close();