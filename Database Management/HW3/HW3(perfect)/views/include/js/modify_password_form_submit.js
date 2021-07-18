function modify_password_form_submit ()
{
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
			// 以Ajax的方式將表單的內容以網址query的方式傳入到 /models/modify_password_check.php，等待結果回傳。
			$.ajax
			({
				type: "POST",
				url: url + '?' + query,
				// 等待/models/modify_password_check.php echo的結果
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
					if (data.includes('Modify the password successfully')) 
					{
						Swal.fire
						({
							icon: 'success',
							title: 'OK',
							text: 'Modify the password successfully',
							allowOutsideClick: false,
							showCancelButton: false,
						}).then((result) => 
						{
							if (result.value) 
								window.location = '/HW3/views/login.php'
						})
					}
				}
			});
			// 避免真的發送表單造成頁面重整
			// avoid to execute the actual submit of the form.
			e.preventDefault(); 
		}
	});
}