<?php
	function db_check() 
	{
		$servername = "localhost";
		$username = "root";
		$password = "";
		// create DB's connection first, and then input servername、username、password
		$conn_server = new mysqli($servername, $username, $password);
		if ($conn_server->connect_error) 
			die("Connection failed: " . $conn_server->connect_error);
		$DBname = "user";
		$conn_DB = new mysqli($servername, $username, $password, $DBname);
		if ($conn_DB->connect_error) 
			die("Connection failed: " . $conn_DB->connect_error);
		// return connection's information
		return $conn_DB;
	}