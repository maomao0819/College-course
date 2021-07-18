<?php
// article.php的function要使用時，做實體化class類別 -> 使用class內的function
// 新增與刪除都是利用ArticleClass()內的方法。

require_once dirname(__FILE__) . '/article.php';
session_start();
// 實體化 article.php內的ArticleClass()
$article = new ArticleClass();
// 根據/views/write_article.php 78行的請求做資料新增
if (isset($_POST['writeArticle'])) {
  // 將使用者資訊塞入 註: 尚可在article.php內做使用者認證，加一層防護。
  $query = [
    'user_id' => $_SESSION['id'],
    'username' => $_SESSION['username'],
    'title' => htmlspecialchars($_POST['title']),
    'content' => htmlspecialchars($_POST['content']),
    'img' => $_POST['img']
  ];
  $result = $article->insertArticle($query);
  echo 'result'. $result;
  exit();
}

if (isset($_POST['deleteArticle'])) {
  $result = $article->deleteArticle($_POST['deleteArticle']);
  echo 'result'. $result;  
  exit();
}

if (isset($_POST['writeMessage'])) {
  $query = [
    'article_id' => htmlspecialchars($_POST['articleId']),
    'username' => htmlspecialchars($_POST['username']),
    'content' => htmlspecialchars($_POST['content']),
  ];
  $result = $article->insertMessage($query);
  echo $result;
  exit();
}

if (isset($_POST['deleteMessage'])) {
  $query = [
    'message_id' => htmlspecialchars($_POST['deleteMessage']),
    'username' => htmlspecialchars($_POST['username']),
  ];
  $result = $article->deleteMessage($query);
  echo 'result'. $result;  
  exit();
}