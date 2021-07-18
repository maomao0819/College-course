$(document).ready(function () {
  $("button").click(function () {
    $("#details").is(":visible") ? $("#details").fadeOut() : $("#details").fadeIn();
  });
});