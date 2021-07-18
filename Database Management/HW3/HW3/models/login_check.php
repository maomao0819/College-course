<?php
require_once dirname(__FILE__)."/db_check.php";
// 是否為從表單的"submit"button發送來的
// 確保請求是從表單的"GET"方法，並由按鈕
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
// 名稱密碼都要對上 -> 註冊session資訊 -> 保存它的login, Id, username, 最後登入時間(timeout機制)
function checkData($username, $password, $conn) 
{
  $sql = "SELECT id, username, password FROM user_account WHERE username = '$username' AND password = '$password'";
  $result = mysqli_query($conn, $sql);
  // 以mysqli_num_rows()回傳的數字來評斷是否登入成功。
  // 沒有回傳結果的話
  if(mysqli_num_rows($result) == 0) 
  {
    echo "Username or password error";
    // 網址的結尾會多帶error=帳號密碼錯誤
    header("Location: /HW3/views/login.php?error=username or password error");   
  }
  // 登入成功 -> login, Id, username, 最後登入時間寫入session -> 作為user登入的確認
  // 將使用者的登入資訊寫入到SESSION中，作為登入認證使用。
  else 
  {
    $row = mysqli_fetch_assoc($result);
    echo "Login successfully";
    // $_SESSION['login'] = true;
    // $_SESSION['id'] = $row['id'];
    // $_SESSION['username'] = $row['username'];
    // $_SESSION['LAST_ACTIVITY'] = $_SERVER['REQUEST_TIME'];
    setcookie( "login", true, time()+3600, "/");
    setcookie( "id", $row['id'], time()+3600, "/");
    setcookie( "username", $row['username'], time()+3600, "/");
    setcookie( "password", $row['password'], time()+3600, "/");
    setcookie( "LAST_ACTIVITY", $_SERVER['REQUEST_TIME'], time()+3600, "/");
    // 登入成功 -> 進入blog頁面
    header("Location: /HW3/views/index.php");
  }
}
$conn->close();