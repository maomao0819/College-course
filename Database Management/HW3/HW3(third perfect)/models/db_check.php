<?php
	// create DB's connection first, and then input servername、username、password
	function db_check() 
	{
		$servername = "localhost";
		$username = "root";
		$password = "";
		$conn = new mysqli($servername, $username, $password);
		if ($conn->connect_error) 
			die("Connection failed: " . $conn->connect_error);
		$dbname = "user";
		$conn = new mysqli($servername, $username, $password, $dbname);
		if ($conn->connect_error) 
			die("Connection failed: " . $conn->connect_error);
		// return connection's information
		return $conn = new mysqli($servername, $username, $password, $dbname);
	}