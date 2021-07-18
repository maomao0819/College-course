<?php
require_once dirname(__FILE__) . "/include/head.php";
require_once dirname(__FILE__) . "/login_nav.php";
?>
<!-- 註冊頁的部分 -->
<div>
  <form 
    id="form" 
    onsubmit="return false" 
    action="/php_project_demo/models/registration_check.php"
  >
    <div>
      <label>
        <p class="label-txt"><b>請輸入EMAIL</b></p>
        <input 
          id="email" 
          type="email" 
          class="input" 
          required=""
        >
        <div class="line-box">
          <div class="line"></div>
        </div>
      </label>
    </div>
    <div>
      <label>
        <p class="label-txt"><b>請輸入使用者名稱</b></p>
        <input 
          id="username" 
          type="text" 
          class="input" 
          required=""
        >
        <div class="line-box">
          <div class="line"></div>
        </div>
      </label>
    </div>
    <div>
      <label>
        <p class="label-txt"><b>請輸入密碼</b></p>
        <input 
          id="passwordInput" 
          type="password" 
          class="input" 
          required=""
        >
        <div class="line-box">
          <div class="line"></div>
        </div>
      </label>
    </div>
    <div>
      <label>
        <p class="label-txt"><b>再確認一次密碼</b></p>
        <input 
          id="passwordConfirm" 
          type="password" 
          class="input" 
          autocomplete="Off" 
          required=""
        >
        <div class="line-box">
          <div class="line"></div>
        </div>
      </label>
    </div>
    <button>submit</button>
  </form>
</div>

<script>
$("#form").submit(function(e) {
  if ($("#passwordInput").val() !== $("#passwordConfirm").val()) {
    Swal.fire({
      icon: 'warning',
      title: 'Oops...',
      text: '請再確認一次密碼',
    });
    return;
  } else {
    var params = {
      email: $('#email').val(),
      username: $('#username').val(),
      // 密碼經過md5加密(此md5加密方法為外部js，在/views/include/資料夾下)
      password: md5($('#passwordInput').val()),
    };
    var query = jQuery.param(params);
    var form = $(this);
    var url = form.attr('action');
    // 以Ajax的方式發送到後端，將表單的內容插入到網址裡 -> 加到網址後面 -> 透過POST發送到後端 -> 進行驗證
    // 以Ajax的方式將表單的內容以網址query的方式傳入到 /models/registration_check.php，等待結果回傳。
    $.ajax({
      type: "POST",
      url: url + '?' + query,
      // 等待/models/registration_check.php echo的結果
      success: function(data) {
        if (data.includes('已註冊過')) {
          Swal.fire({
            icon: 'warning',
            title: 'Oops...',
            html:data,
          });
        }
        if (data.includes('資料新增成功')) {
          Swal.fire({
            icon: 'success',
            title: 'OK',
            text: '資料新增成功',
            allowOutsideClick: false,
            showCancelButton: false,
          }).then((result) => {
            if (result.value) {
              window.location = '/php_project_demo/views/login.php'
            }
          })
        }
      }
    });
    // 避免真的發送表單造成頁面重整
    e.preventDefault(); // avoid to execute the actual submit of the form.
  }
});
</script>
<!-- 最後進到/models/registration_check.php -->