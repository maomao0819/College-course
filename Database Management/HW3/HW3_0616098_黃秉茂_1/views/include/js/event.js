// recover hide content
function recover() 
{
	$("#hidecontent").is(":visible") ? $("#hidecontent").fadeOut() : $("#hidecontent").fadeIn();
}

// image bigger
function bigger(t)
{
	t.width *= 1.2;
	t.height *= 1.2;
}

// image smaller
function smaller(t)
{
	t.width /= 1.2;
	t.height /= 1.2;
}

// popover
$(document).ready
(
	function()
	{
		$('[data-toggle="popover"]').popover();   
	}
);

// SCROOL TOP BOTTON 
// When the user scrolls down 20px from the top of the document, show the button
window.onscroll = function() 
{
	scrollFunction()
};

function scrollFunction() 
{
  	if (document.body.scrollTop > 300 || document.documentElement.scrollTop > 300)
    	topbutton.style.display = "block";
  	else 
    	topbutton.style.display = "none";
}
// When the user clicks on the button, scroll to the top of the document
function topFunction() {
  	document.body.scrollTop = 0;
  	document.documentElement.scrollTop = 0;
}
