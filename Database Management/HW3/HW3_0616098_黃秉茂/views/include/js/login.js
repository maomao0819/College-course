function getUrlVars_error()
{
	if(getUrlVars()['error']) 
	{
		Swal.fire
		({
			icon: 'warning',
			title: 'Oops...',
			text: decodeURIComponent(getUrlVars()['error'])
		});
	}
}
//用來取得網址所帶的參數，如果登入失敗 server會將網址帶上"?error=帳號密碼錯誤"，"getUrlVars()"會根據回傳內容顯示跳窗。
function getUrlVars()
{
	var vars = [], hash;
	var hashes = window.location.href.slice(window.location.href.indexOf('?') + 1).split('&');
	for(var i = 0; i < hashes.length; i++)
	{
		hash = hashes[i].split('=');
		vars.push(hash[0]);
		vars[hash[0]] = hash[1];
	}
	return vars;
}
