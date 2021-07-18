<?php
	require_once dirname(__FILE__) . "/include/head.php";
	require_once dirname(__FILE__) . "/change_password_nav.php";
?>
<!-- 註冊頁的部分 -->
<div>
	<form 
		id = "form2" 
		onsubmit = "return false" 
		action = "/HW3/models/change_password_check.php"
	>
		<div>
			<label>
				<p class="label-txt">
					<b>Old password: </b>
				</p>
					<input 
						id="old_password"
						name="old_password"
						type="password"
						class = "input" 
						required = ""
					>
				<div class = "line-box">
					<div class = "line"></div>
				</div>
			</label>
		</div>
		<div>
			<label>
				<p class="label-txt">
					<b>New password: </b>
				</p>
					<input 
						id = "new_password" 
						name = "new_password" 
						type = "password"
						class = "input" 
						required = ""
					>
				<div class = "line-box">
					<div class="line"></div>
				</div>
			</label>
		</div>
		<div>
			<label>
				<p class = "label-txt">
					<b>Confirm new password: </b>
				</p>
				<input 
					id = "new_passwordConfirm" 
					name = "new_passwordConfirm"
					type = "password" 
					class = "input" 
					required = ""
				>
				<div class = "line-box">
					<div class = "line"></div>
				</div>
			</label>
		</div>
		<button>submit_change_password</button>
	</form>
</div>

<script>
$("#form2").submit(function(e) 
{
	if ($("#new_password").val() !== $("#new_passwordConfirm").val()) 
	{
		Swal.fire(
		{
			icon: 'warning',
			title: 'Oops...',
			text: 'Please confirm your password again'
		});
		return;
	}
	else if ($("#new_password").val() == $("#old_password").val()) 
	{
    	Swal.fire(
		{
			icon: 'warning',
			title: 'Oops...',
			html: 'New password is same as the old one. <br> Please input another new password!'
		});
    	return;
	} 
	else 
	{
		var params = 
		{
			old_password: $('#old_password').val(),
			new_password: $('#new_password').val(),
		};
		var query = jQuery.param(params);
		var form2 = $(this);
		var url = form2.attr('action');
		// 以Ajax的方式發送到後端，將表單的內容插入到網址裡 -> 加到網址後面 -> 透過POST發送到後端 -> 進行驗證
		// 以Ajax的方式將表單的內容以網址query的方式傳入到 /models/registration_check.php，等待結果回傳。
		$.ajax
		({
			type: "POST",
			url: url + '?' + query,
			// 等待/models/registration_check.php echo的結果
			success: function(data) 
			{
				if (data.includes('passward is incorrect')) 
				{
					Swal.fire
					({
						icon: 'warning',
						title: 'Oops...',
						html:data
					});
				}
				if (data.includes('Change the password successfully')) 
				{
					Swal.fire
					({
						icon: 'success',
						title: 'OK',
						text: 'Change the password successfully',
						allowOutsideClick: false,
						showCancelButton: false,
					}).then((result) => 
					{
						if (result.value) 
							window.location = '/HW3/views/index.php'
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