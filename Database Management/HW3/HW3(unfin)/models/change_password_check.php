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
    'password' => htmlspecialchars($_GET["password"]),
    'old_password' => htmlspecialchars($_GET["old_password"]),
    'new_password' => htmlspecialchars($_GET["new_password"])
  ];
  $cookie_email = $query['email'];
  $cookie_username = $query['username'];
  $cookie_password = $query['new_password'];
  setcookie($cookie_email, $cookie_username, $cookie_password, time() + (86400 * 30), "/");
  // 取得資料庫連線資訊 註:此function在db_check.php內
  $conn = db_check();
  if ($query['old_password'] === $query['password'])
    updateData($query['email'], $query['username'], $query['password'], $conn);
  else
    echo "Old password is incorrect.";
  // 將參數帶入DB看回傳結果
  function updateData($email, $username, $password, $conn) 
  {
      $sql = "UPDATE user_account SET password = $password WHERE username = $username";
      if (mysqli_query($conn, $sql)) 
        echo "Change the password successfully";
      else 
        echo "Error: " . $sql . "<br>" . $conn->error;
  }
  // 終止連線以免資源浪費
  // 在程式最末段終止DB連線 (保持良好的設計習慣記得在做完資料庫的連線使用後關閉連線，釋放資源)
  $conn->close();
