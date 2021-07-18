<nav 
  class="sticky-top navbar-dark bg-dark" 
  style="width:100%; position: absolute; z-index: 10; background-color: #000000"
>
  <div style="width: 100%">
    <div 
      align="right" 
      style="color:#f6f6f6"
    >
      <?php echo "Hello  <b>" . $_SESSION['username'] . "</b>&nbsp;&nbsp;&nbsp;" ?>
      <button class="btn" onclick="
        Swal.fire({
        icon: 'warning',
        title: 'warning',
        text: 'Are you sure to log out?',
        showCancelButton: true,
        }).then((result) => 
        {
          if (result.value) 
            window.location = '/HW3/views/login.php'
        })"
      >
      <b>登出</b></button>
      <button 
        class="btn" 
        onclick="window.location = '/HW3/views/change_password.php'"
      >
        <b>修改密碼</b>
      </button>
    </div>
  </div>
</nav>