<?php
	require_once dirname(__FILE__)."/db_check.php";
	$query = 
	[
		'old_password' => htmlspecialchars($_GET["old_password"]),
		'new_password' => htmlspecialchars($_GET["new_password"])
	];
	$conn = db_check();
	updateData(md5($query['old_password'], false), md5($query['new_password'], false), $conn);
	function updateData($old_password, $new_password, $conn) 
	{
		if ($old_password == $_COOKIE["password"])
		{
			$id = $_COOKIE["id"];
			$sql = "UPDATE user_account SET password = '$new_password' WHERE id = '$id'";
			if (mysqli_query($conn, $sql)) 
			{
				echo "Modify the password successfully!";
				setcookie("password", $new_password, time() + 3600, "/");
			}
			else 
				echo "Error: " . $sql . "<br>" . $conn->error;
		}
		else
			echo "Old passward is incorrect";
	}
	$conn->close();