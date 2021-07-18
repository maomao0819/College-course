<?php
	// check user, email是否被註冊過
	// 引入/db_check.php 檔案做資料庫的確認
	require_once dirname(__FILE__)."/db_check.php";
	$query = 
	[
		// htmlspecialchars() :避免使用者夾雜html的非法輸入
		// $_GET()取得網址所帶的query 註: 網址query
		'old_password' => htmlspecialchars($_GET["old_password"]),
		'new_password' => htmlspecialchars($_GET["new_password"])
	];
	// 取得資料庫連線資訊 註:此function在db_check.php內
	$conn = db_check();
	updateData(md5($query['old_password'], false), md5($query['new_password'], false), $conn);
	// 將參數帶入DB看回傳結果
	function updateData($old_password, $new_password, $conn) 
	{
		if ($old_password == $_COOKIE["password"])
		{
			$id = $_COOKIE["id"];
			$sql = "UPDATE user_account SET password = '$new_password' WHERE id = '$id'";
			if (mysqli_query($conn, $sql)) 
			{
				echo "Change the password successfully!";
				setcookie("password", $new_password, time() + 3600, "/HW3");
			}
			else 
				echo "Error: " . $sql . "<br>" . $conn->error;
		}
		else
			echo "Old passward is incorrect";
	}
	// 終止連線以免資源浪費
	// 在程式最末段終止DB連線 (保持良好的設計習慣記得在做完資料庫的連線使用後關閉連線，釋放資源)
	$conn->close();