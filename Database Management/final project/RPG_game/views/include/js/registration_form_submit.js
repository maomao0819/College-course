function registration_form_submit ()
{
	$("#form").submit(function(e) 
	{
		if ($("#Password").val() !== $("#ConfirmPassword").val()) 
		{
			Swal.fire
			({
				icon: 'warning',
				title: 'Oops...',
				text: 'Please confirm your password again'
			});
			return;
		} 
		else 
		{
			var params = 
			{
				email: $('#email').val(),
				username: $('#username').val(),
				// 密碼經過md5加密(此md5加密方法為外部js，在/views/include/資料夾下)
				password: md5($('#Password').val()),
			};
			var query = jQuery.param(params);
			var form = $(this);
			var url = form.attr('action');
			// 以Ajax的方式發送到後端，將表單的內容插入到網址裡 -> 加到網址後面 -> 透過POST發送到後端 -> 進行驗證
			// 以Ajax的方式將表單的內容以網址query的方式傳入到 /models/registration_check.php，等待結果回傳。
			$.ajax
			({
				type: "POST",
				url: url + '?' + query,
				// 等待/models/registration_check.php echo的結果
				success: function(data) 
				{
					if (data.includes('has been registered')) 
					{
						Swal.fire
						({
							icon: 'warning',
							title: 'Oops...',
							html:data
						});
					}
					if (data.includes('Add the data successfully')) 
					{
						Swal.fire
						({
							icon: 'success',
							title: 'OK',
							text: 'Add the data successfully',
							allowOutsideClick: false,
							showCancelButton: false,
						}).then((result) => 
						{
							if (result.value) 
								window.location = '/RPG_game/views/login.php'
						})
					}
				}
			});
			// 避免真的發送表單造成頁面重整
			e.preventDefault(); // avoid to execute the actual submit of the form.
		}
	});
}