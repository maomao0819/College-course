window.addEventListener("load", function() {
	var canvas = document.getElementById("myCanvas");
	var ctx = canvas.getContext("2d");
	var ballRadius = 10;
	var ball_x = canvas.width/2;
	var ball_y = canvas.height-30;
	var ball_dx = 2;
	var ball_dy = -2;
	var paddleHeight = 10;
	var paddleWidth = 75;
	var paddleX = (canvas.width-paddleWidth)/2;
	var rightPressed = false;
	var leftPressed = false;
	var upPressed = false;
	var downPressed = false;
	var plusPressed = false;
	var minusPressed = false;
	var num8Pressed = false;
	var num2Pressed = false;
	// define the bricks
	var brickRowCount = 6;
	var brickColumnCount = 3;
	var brickWidth = 75;
	var brickHeight = 20;
	var brickOffsetTop = 30;
	var brickOffsetLeft = 30;
	//bricks interval
	var brickPadding_x = 10;
	var brickPadding_y = 8;
	
	var score = 0;
	var lives = 3;
	var speed = 1;
	
	var bricks = [];
	for(var c = 0; c< brickColumnCount; c++) 
	{
	  bricks[c] = [];
	  for(var r = 0; r < brickRowCount; r++) 
	  {
		  if((c + r) % 2)
			bricks[c][r] = { x: 0, y: 0, status: 3 };
		  else
			bricks[c][r] = { x: 0, y: 0, status: 2 };
	  }
	}

	document.addEventListener("keydown", keyDownHandler, false);
	document.addEventListener("keyup", keyUpHandler, false);
	document.addEventListener("mousemove", mouseMoveHandler, false);

	//when you press 'left', 'right', 'up', 'num8', 'plus', 'down', 'num2', or 'minus'
	function keyDownHandler(e) 
	{
	  if(e.keyCode == 39) 
		rightPressed = true;
	  else if(e.keyCode == 37) 
		leftPressed = true;
	  else if(e.keyCode == 107)
		plusPressed = true;
	  else if(e.keyCode == 109) 
		minusPressed = true;
	  else if(e.keyCode == 104)
		num8Pressed = true;
	  else if(e.keyCode == 98) 
		num2Pressed = true;
	  else if(e.keyCode == 38)
		upPressed = true;
	  else if(e.keyCode == 40)
		downPressed = true;
	}
	function keyUpHandler(e) 
	{
	  if(e.keyCode == 39) 
		rightPressed = false;
	  else if(e.keyCode == 37) 
		leftPressed = false;
	  else if(e.keyCode == 107)
		plusPressed = false;
	  else if(e.keyCode == 109) 
		minusPressed = false;
	  else if(e.keyCode == 104)
		num8Pressed = false;
	  else if(e.keyCode == 98) 
		num2Pressed = false;
	  else if(e.keyCode == 38)
		upPressed = false;
	  else if(e.keyCode == 40)
		downPressed = false;
	}
	function mouseMoveHandler(e) 
	{
	  var relativeX = e.clientX - canvas.offsetLeft;
	  if(relativeX > 0 && relativeX < canvas.width) 
		paddleX = relativeX - paddleWidth/2;
	}
	function brick_collisionDetection() 
	{
	  for(var c=0; c<brickColumnCount; c++) 
	  {
		for(var r=0; r<brickRowCount; r++) 
		{
		  var b = bricks[c][r];
		  if(b.status > 0) 
		  {
			//碰撞判定較精準
			if((((b.x + 0.5 * brickWidth) - ball_x) * ((b.x + 0.5 * brickWidth) - ball_x) < (0.5 * brickWidth + ballRadius) * (0.5 * brickWidth + ballRadius)) && (((b.y + 0.5 * brickHeight) - ball_y) * ((b.y + 0.5 * brickHeight) - ball_y) < (0.5 * brickHeight + ballRadius) * (0.5 * brickHeight + ballRadius)))
			{
			  ball_dy = -ball_dy;
			  b.status--;
			  bricks[c][r].status = b.status;
			  // speed will multiply 1.1 when score increases
			  if(b.status == 0)
			  {
				score++;
				ball_dx *= 1.1;
				ball_dy *= 1.1;
			  }
			  if(score == brickRowCount * brickColumnCount) 
			  {
				alert("YOU WIN, CONGRATULATIONS!");
				document.location.reload();
			  }
			}
		  }
		}
	  }
	}

	function drawBall() 
	{
	  ctx.beginPath();
	  ctx.arc(ball_x, ball_y, ballRadius, 0, Math.PI*2);
	  ctx.fillStyle = "red";
	  ctx.fill();
	  ctx.closePath();
	}
	function drawPaddle() 
	{
	  ctx.beginPath();
	  ctx.rect(paddleX, canvas.height-paddleHeight-10, paddleWidth, paddleHeight);
	  ctx.fillStyle = "black";
	  ctx.fill();
	  ctx.closePath();
	}
	function drawBricks() 
	{
	  for(var c = 0; c < brickColumnCount; c++) 
	  {
		for(var r = 0; r < brickRowCount; r++) 
		{
		  if(bricks[c][r].status > 0) 
		  {
			var brickX = (r*(brickWidth+brickPadding_x))+brickOffsetLeft;
			var brickY = (c*(brickHeight+brickPadding_y))+brickOffsetTop;
			bricks[c][r].x = brickX;
			if(score == 17)
				bricks[c][r].x += 5;
			bricks[c][r].y = brickY;
			ctx.beginPath();
			ctx.rect(brickX, brickY, brickWidth, brickHeight);
			if(bricks[c][r].status == 3)
				ctx.fillStyle = "#009588";
			else if(bricks[c][r].status == 2)
				ctx.fillStyle = "#0095AA";
			else if(bricks[c][r].status == 1)
				ctx.fillStyle = "#0095CC";
			ctx.fill();
			ctx.closePath();
		  }
		}
	  }
	}
	function drawScore() 
	{
	  ctx.font = "20px Arial";
	  ctx.fillStyle = "#0095DD";
	  ctx.fillText("Score: "+score, 8, 20);
							  //start,length
	}
	function drawLives() 
	{
	  ctx.font = "16px Arial";
	  ctx.fillStyle = "#0095DD";
	  ctx.fillText("Lives: " + lives, canvas.width - 65, 20);
	}
	
	function reborn_setting()
	{
		ball_x = canvas.width / 2;
		ball_y = canvas.height - 30;
		paddleX = (canvas.width - paddleWidth) / 2;
		ballRadius = 10;
	}
	
	function draw() 
	{
	  ctx.clearRect(0, 0, canvas.width, canvas.height);
	  drawBricks();
	  drawBall();
	  drawPaddle();
	  drawScore();
	  drawLives();
	  brick_collisionDetection();

	  if(ball_x + ball_dx > canvas.width-ballRadius || ball_x + ball_dx < ballRadius) 
		ball_dx = -ball_dx;
	
	  if(ball_y + ball_dy < ballRadius) 
		ball_dy = -ball_dy;
	 
	  else if(ball_y + ball_dy > canvas.height - ballRadius - 10 - paddleHeight) 
	  {
		if(ball_x > paddleX && ball_x < paddleX + paddleWidth) 
		{
		  ball_dy = -ball_dy;
		  //ball will become smaller when hits the paddle
		  ballRadius *= 0.95;
		}
		else 
		{
		  lives--;
		  if(lives == 0) 
		  {
			alert("GAME OVER");
			document.location.reload();
		  }
		  else 
		  {
			reborn_setting();
			//the less the lives are, the faster the ball is.
			ball_dx = 7-2*lives;
			ball_dy = -7+2*lives;
		  }
		}
	  }

	  if(rightPressed && paddleX < canvas.width - paddleWidth) 
		paddleX += 3;
	  
	  else if(leftPressed && paddleX > 0) 
		paddleX -= 3;
	  // speed will multiply 1.2 when you press 'up', or 'num8' 
	  if(upPressed || num8Pressed)
	  {
		  ball_dx *= 1.2;
		  ball_dy *= 1.2;
	  }
	  // speed will multiply 0.8 when you press 'down', or 'num2'
	  else if(downPressed || num2Pressed)
	  {
		  ball_dx *= 0.8;
		  ball_dy *= 0.8;
	  }
	  //'plus' maks the ball become larger
	  if(plusPressed && ballRadius <21) 
		ballRadius *= 1.1;
	  //'minus' maks the ball become smaller
	  else if(minusPressed && ballRadius <21) 
		ballRadius *= 0.9;
	
	  ball_x += ball_dx;
	  ball_y += ball_dy;
	  
	  requestAnimationFrame(draw);

	}

	draw();
	//setInterval(draw, 100);
});