<?php
  require_once dirname(__FILE__). "/login_status.php";
  require_once dirname(__FILE__) . "/include/head.php";
  require_once dirname(__FILE__). "/blog_nav.php";
  require_once $_SERVER["DOCUMENT_ROOT"]. "/HW3/models/db_check.php";
  //$conn = db_check();
  //$article_sql = "SELECT id, title, content, username, img, reg_date FROM user_article ORDER BY id DESC;";
?>
<html>
    <head>
      <title>Resume</title>
      <meta charset="utf-8">
      <meta name="viewport" content="width=device-width, initial-scale=1">
      <!-- Website Link -->
      <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css">
      <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
      <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/js/bootstrap.min.js"></script>
      
      <!-- External File -->
      <script type="text/javascript" src="./include/js/event.js"></script>
      <link rel="stylesheet" type="text/css" href="./include/css/mystyle.css">
    </head>
    <body>

      <!-- reference 彈出視窗 -->
      <div>
            <button type="button" id="watchmore" onclick = "recover()" style="color: white; width: 100%; height: 60px; background-color: #8888FF; font-size: 20px;">
              Watch More!
            </button>
            <div id="hidecontent" style="display: none; width: 80%;background: lightyellow; margin-left: 150px; ">
                <h4 align="center" style="width: 100%; height: 40px; background-color: orange"><b>Reference</b></h4>
                <span>progress bar:</span>
                <br>&nbsp;&nbsp;&nbsp;&nbsp;
                <a href="https://getbootstrap.com/docs/4.0/components/progress/" target="_blank">
          <span>https://getbootstrap.com/docs/4.0/components/progress/</span>
          <a href="https://stackoverflow.com/questions/23414333/thinner-bootstrap-progress-bars/" target="_blank">
            <span>https://stackoverflow.com/questions/23414333/thinner-bootstrap-progress-bars</span>
          </a>
          <br>&nbsp;&nbsp;&nbsp;&nbsp;
          <a href="https://https://www.w3schools.com/bootstrap/bootstrap_progressbars.asp" target="_blank">
            <span>https://www.w3schools.com/bootstrap/bootstrap_progressbars.asp</span>
          </a>
          <br>
          <span>CSS:</span>
          <br>&nbsp;&nbsp;&nbsp;&nbsp;
          <a href="https://www.codecademy.com/courses/learn-css/lessons/css-setup-selectors/exercises/intro-to-css" target="_blank">
            <span>https://www.codecademy.com/courses/learn-css/lessons/css-setup-selectors/exercises/intro-to-css</span>
          </a>
          <br>&nbsp;&nbsp;&nbsp;&nbsp;
          <span>circle image:</span>
          <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
          <a href="https://www.w3schools.com/css/css3_images.asp" target="_blank">
            <span>https://www.w3schools.com/css/css3_images.asp</span>
          </a>
          <br>
          <span>HTML:</span>
          <br>&nbsp;&nbsp;&nbsp;&nbsp;
          <a href="https://www.codecademy.com/learn/learn-html" target="_blank">
            <span>https://www.codecademy.com/learn/learn-html</span>
          </a>
          <br>
          <span>resume:</span>
          <br>&nbsp;&nbsp;&nbsp;&nbsp;
          <a href="https://www.cakeresume.com/resumes" target="_blank">
            <span>https://www.cakeresume.com/resumes</span>
          </a>
          <br>
          <span>Grid-View:</span>
          <br>&nbsp;&nbsp;&nbsp;&nbsp;
          <a href="https://www.w3schools.com/css/css_rwd_grid.asp" target="_blank">
            <span>https://www.w3schools.com/css/css_rwd_grid.asp</span>
          </a>
          <br>
          <span>Popover:</span>
          <br>&nbsp;&nbsp;&nbsp;&nbsp;
          <a href="https://www.w3schools.com/bootstrap/bootstrap_popover.asp" target="_blank">
            <span>https://www.w3schools.com/bootstrap/bootstrap_popover.asp</span>
          </a>
          <br>
          <span>Bootstrap Carousel:</span>
          <br>&nbsp;&nbsp;&nbsp;&nbsp;
          <a href="https://www.w3schools.com/bootstrap/bootstrap_carousel.asp" target="_blank">
            <span>https://www.w3schools.com/bootstrap/bootstrap_carousel.asp</span>
          </a>
          <br>
          <span>scroll top button:</span>
          <br>&nbsp;&nbsp;&nbsp;&nbsp;
          <a href="https://www.w3schools.com/howto/howto_js_scroll_to_top.asp" target="_blank">
            <span>https://www.w3schools.com/howto/howto_js_scroll_to_top.asp</span>
          </a>
          <br>
          <span>mouse event:</span>
          <br>&nbsp;&nbsp;&nbsp;&nbsp;
          <a href="https://www.w3schools.com/jsref/event_onmouseout.asp" target="_blank">
            <span>https://www.w3schools.com/jsref/event_onmouseout.asp</span>
          </a>
          <h5 style="width: 100%; height: 20px; background-color: white"></h5>
            </div>
        </div>

      <!-- Profile -->
      <div id = "title" class = "bg_blue" style = "text-align: center;">
        <br>
        <!-- img & mouse event-->
        <img align="center" src = "./include/image/me.jpg" class="img-circle title" width="160px" height="240px" title = "My portrait" onmouseover="bigger(this)" onmouseout="smaller(this)">
        <h1 style = "line-height: 15px;"><strong>黃秉茂 Jason Huang</strong></h1>
        <span>Computer Science & Finance  • Taipei City  • Taiwan</span>
        <br>
        <span style="display: inline-block; line-height: 0px;">
          <img src = "./include/image/phone.png" width="20px" height="20px" class = "title" onmouseover="bigger(this)" onmouseout="smaller(this)">
          (+886) 976-967-859
          &nbsp;     
          <img src = "./include/image/Gmail_Icon.png" width="20px" height="20px" class = "title" onmouseover="bigger(this)" onmouseout="smaller(this)">
          maomao0819.cs06@nctu.edu.tw
        </span>
        <p>Curiosity about everything & Willing to self-learning</p>
      </div>

      <!-- SCROOL TOP BOTTON -->
      <button onclick = "topFunction()" id = "TopBotton" title = "Go to top">Top</button>
      <script>
        //Get the button
        var topbutton = document.getElementById("TopBotton");
      </script>

      <!-- Popover Navigation Bar -->
      <div id = "local-link">
        <ul class="nevigate">
            <li class="nevigate">
              <a href = "#title" class="nevigate active">profile</a>
            </li>
            <li class="nevigate">
              <a href = "#education" title="Bachelor of Science" data-toggle="popover" data-trigger="hover" data-placement="top" data-content="Bachelor of Business Administration" class="nevigate">education</a>
            </li>
            <li class="nevigate">
              <a href = "#working experience" title="Tutor" data-toggle="popover" data-trigger="hover" data-placement="top" data-content="茗松" class="nevigate">working experience</a>
            </li>
            <li class="nevigate">
              <a href = "#extracurricular activities" title="Student Union of Department" data-toggle="popover" data-trigger="hover" data-placement="top" data-content="Cake Club" class="nevigate">extracurricular activities</a>
            </li>
            <li class="nevigate">
              <a href = "#sk" title="Programming" data-toggle="popover" data-trigger="hover" data-placement="top" data-content="Language" class="nevigate">skills</a>
            </li>
            <li class="nevigate">
              <a href = "#portfolio" title="title" data-toggle="popover" data-trigger="hover" data-placement="right" data-content="Breakout Game" class="nevigate">portfolio</a>
            </li>
            <li class="nevigate"><a href = "#contact"  class="nevigate">contact</a></li>
          </ul>
      </div>

      <!-- parallax-background -->
      <div class="parallax">
          <h2 class="hobby">My Hobby</h2>
      </div>

      <!-- Bootstrap Carousel -->
      <div class="container" align="center"> 
          <div id="Hobby_Carousel" class="carousel slide" data-ride="carousel" style="width:400px; height:400px;">
            <!-- Indicators -->
            <ol class="carousel-indicators">
                <li data-target="#Hobby_Carousel" data-slide-to="0" class="active"></li>
                <li data-target="#Hobby_Carousel" data-slide-to="1"></li>
                <li data-target="#Hobby_Carousel" data-slide-to="2"></li>
                <li data-target="#Hobby_Carousel" data-slide-to="3"></li>
            </ol>
            <!-- Wrapper for slides -->
            <div class="carousel-inner" role="listbox" style="width:100%;">
                <div class="item active">
                  <img src="./include/image/music_icon.jpg">
                </div>
                <div class="item">
                  <img src="./include/image/movie_icon.jpg">
              </div>
                <div class="item">
                  <img src="./include/image/YT.png">
              </div>
              <div class="item">
                  <img src="./include/image/game_icon.png">
              </div>
            </div>
            <!-- Left and right controls -->
            <a class="left carousel-control" href="#Hobby_Carousel" data-slide="prev">
                <span class="glyphicon glyphicon-chevron-left"></span>
                <span class="sr-only">Previous</span>
            </a>
            <a class="right carousel-control" href="#Hobby_Carousel" data-slide="next">
                <span class="glyphicon glyphicon-chevron-right"></span>
                <span class="sr-only">Next</span>
            </a>
          </div>
      </div>

      <!-- Layout -->
      <div class="col-6 bg_pink">
      <!-- EDUCATION PART -->
        <div id = "education">
          <!-- create black rectangle -->
          <div class="rec">
            <span class="rec">EDUCATION</span>
          </div>

          <hr>
          <h3 align = "left" style = "display: inline;">Bachelor of Science, National Chiao Tung University</h3>
          <span class="date">Sep 2017 - Present</span>
          <ul>
            <li>
              <h4 style="display: inline;">Major:</h4>
              <span> Computer Science(Current GPA: 3.97)</span>
            </li>
            <li>
              <h4 style="display: inline;">Programing Coursework:</h4>
              <span> Data Structure, Algorithm, Network, Formal Language, Compiler</span>
            </li>
            <li>
              <h4 style="display: inline;">Math Coursework:</h4>
              <span> Calculus, Linear Algebra, Probability, Statistic, Discrete Mathematics</span>
            </li>
            <li>
              <h4 style="display: inline;">Electric Coursework:</h4>
              <span> Digital Circuit Design, Computer Organization, Microprocessor System Lab</span>
            </li>
          </ul>
          <br>
          <h3 align = "left" style = "display: inline;">Bachelor of Business Administration, National Chiao Tung University</h3>
          <span class="date">Sep 2017 - Present</span>
          <ul>
            <li>
              <h4 style="display: inline;">Major:</h4>
              <span> Information Management and Finance</span>
            </li>
            <li>
              <h4 style="display: inline;">Finance Coursework:</h4>
              <span> Accounting, Investment, Principles of Economics, Financial Management</span>
            </li>
          </ul>
          <br>
        </div>

        <!-- WORKING EXPERIENCE PART -->
        <div id = "working experience">
          <h2 class="blue_text" style="display: inline-block; line-height: 0px;">     
            <img src = "./include/image/job.png" width="30px" height="30px">
            WORKING EXPERIENCE
          </h2>
          <hr>
          <h3>Tutor, part-time</h3>
          <ul>
            <li>
              <span style = "float:left;">English Tutor for four High School Seniors to take <strong>General Scholastic Ability Test</strong></span>
              <span class="date">Sep 2018 - Jan 2019</span>
            </li>
            <li>
              <span style = "float:left;">Physics Tutor for a High School Freshman studying at Taipei First Girls High School, who <strong>got 3rd place</strong> on physics in class with my assistance</span>
              <span class="date">Sep 2019 - Jan 2020</span>
            </li>
            <li>
              Practiced explaining notions clearly and logically
            </li>
          </ul>
          <br>
          <h3 align = "left" style = "display: inline;">茗松, Server, Student Cafeteria, part-time</h3>
          <span class="date">Mar 2018 - Jan 2020</span>
          <ul>
            <li>Familiarize the environment of workplace</li>
            <li>Assisted customers to order meals and managed the quality of service and food</li>
            <li>Supported operation in kitchen</li>
          </ul>
          <br>
        </div>
      </div>

      <!-- EXTRACURRICULAR ACTIVITIES PART -->
      <div class = "col-6 ea bg_pink">
        <div id = "extracurricular activities">
          <h2 class="blue_text" style="display: inline-block; line-height: 0px;">     
            <img src = "./include/image/ea.png" width="20px" height="20px">
            EXTRACURRICULAR ACTIVITIES
          </h2>
          <hr>
          <h3 align = "left" style = "display: inline;">Public Relations Department, Student Union of Department of Computer Science</h3>
          <!-- <em> -->
          <span style = "float:right;"><em>Jul 2018 - Jun 2019</em></span>
          <ul>
            <li>
              Public relation - Contacting enterprises and alumni actively to maintain relationship
            </li>
            <li>
              <!-- <i> -->
              Sourced for <strong>sponsorships</strong> from enterprises – Total value <strong><i>$6,000</i></strong>
            </li>
            <li>
              <!-- <u> -->
              Directed to invite alumni and persuading people to share their story and useful tips - <strong><u>Papacode</u></strong>
            </li>
            <li>
              Project assisting and organizing activity - Christmas ball of <strong>four departments</strong>
            </li>
            <li>
              <!-- <font> -->
              Arranged business visiting - <font color="red"><strong><u>Google</u></strong></font>
            </li>
          </ul>
          <br>
          <br>
          <h3 align = "left" style = "display: inline;">Procurement Section and Education Section, Cake Club</h3>
          <span style = "float:right;"><em>Jul 2019 - Present</em></span>
          <ul>
            <li>
              Project organizing assistant - Cake making, selling, and teaching
            </li>
            <li>
              Checking and purchasing materials, equipments, and ingredients
            </li>
            <li>
              Improving skills in team management and organization
            </li>
          </ul>
          <br>
          <br>
          <h3 align = "left" style = "display: inline;">Activities Section, Inheriting Project</h3>
          <span style = "float:right;"><em>Jun 2018 - Jan 2019</em></span>
          <ul>
            <li>
              <strong>Directed student recruitment</strong>
            </li>
            <li>
              Organized a welcome party and activities for freshmen
            </li>
          </ul>
          <br>
          <br>
          <h3 align = "left" style = "display: inline;">Activities Section, YanPing High School Alumni Association</h3>
          <span style = "float:right;"><em>Sep 2017 - Jun 2018</em></span>
          <ul>
            <li>
              Feedback - Stall selling at alma mater
            </li>
            <li>
              Project coordinating - Uniform Day
            </li>
            <li>
              Public relation assistant - Christmas ball of <strong>four high school alumni associations</strong>
            </li>
            <li>
              Project organizing - Orientation of high-school juniors at NCTU and NTHU
            </li>
          </ul>
        </div>
      </div>

      <!-- SKILL -->
      <div class="bg_purple">
        <h2 id = "sk" class="blue_text" style="display: inline-block; line-height: 0px;">     
          <img src = "./include/image/skill.jpg" width="20px" height="20px">
          SKILL
        </h2>
        <hr>

        <!-- Programming -->
        <div class="col-6 bg_purple">
          <h3>Programming:</h3>

          <!-- <progress> progress bar -->
          <p class = "skill" style = "line-height: 0px;">C/C++: CPE Collegiate Programming Examination</p>
          <span class = "skill"></span>
                <progress class = "skill" value="70" max="100"></progress>
              <p class = "skill" style = "line-height: 0px;">Matlab</p>
              <span class = "skill"></span>
              <progress class = "skill" value="50" max="100"></progress>
              <p class = "skill" style = "line-height: 0px;">Labview: CLAD</p>
              <span class = "skill"></span>
              <progress class = "skill" value="40" max="100"></progress>
              <p class = "skill" style = "line-height: 0px;">Blockly</p>
              <span class = "skill"></span>
              <progress class = "skill" value="50" max="100"></progress>
              <p class = "skill" style = "line-height: 0px;">Git</p>
              <span class = "skill"></span>
              <progress class = "skill" value="30" max="100"></progress>
              <p class = "skill" style = "line-height: 0px;">HTML</p>
              <span class = "skill"></span>
              <progress class = "skill" value="30" max="100"></progress>
              <br><br>
            </div>

            <!-- Language -->
            <div class="col-6 bg_purple">
              <div class="container">
              <h3>Language:</h3>
              <p class = "skill" style = "line-height: 0px;">Chinese</p>

              <!-- bootstrap progressbars -->
              <div class="progress" box-shadow= "none">
                <div div class="progress-bar progress-bar-success progress-bar-striped active" role="progressbar" aria-valuenow="95" aria-valuemin="0" aria-valuemax="100" style="width:95%">
                  Native
                </div>
              </div>
              <p class = "skill " style = "line-height: 0px;">English: GEPT High-Intermediate L/R</p>
              <div class="progress">
                <div div class="progress-bar progress-bar-info progress-bar-striped active" role="progressbar" aria-valuenow="70" aria-valuemin="0" aria-valuemax="100" style="width:70%">
                Advanced
                </div>
              </div>
              <p class = "skill " style = "line-height: 0px;">Japanese</p>
              <div class="progress">
                <div div class="progress-bar progress-bar-warning progress-bar-striped active" role="progressbar" aria-valuenow="45" aria-valuemin="0" aria-valuemax="100" style="width:45%">
                  Immediate
                </div>
              </div>
              <p class = "skill " style = "line-height: 0px;">Korean</p>
              <div class="progress">
                <div div class="progress-bar progress-bar-danger progress-bar-striped active" role="progressbar" aria-valuenow="10" aria-valuemin="0" aria-valuemax="100" style="width:10%">
                  Elementary
                </div>
              </div>
          </div>
        </div>
      </div>

      <!-- PORFOLIO -->
      <div id = "portfolio" class="col-6 bg_green">
        <h2 class="blue_text" style="display: inline-block; line-height: 0px;"> PORTFOLIO </h2>
        <hr>
        <h3>Breakout Game:  Click the image to Play!</h3>
        &nbsp;&nbsp;&nbsp;&nbsp;
        <a align="center" href="./include/breakgame/breakout.html" target="_blank"><img align="center" src = "./include/image/mywork.jpg" ></a>
      </div>

      <!-- CONTACT -->
      <div id = "contact" class="col-6 contact bg_green">
        <br><br><br><br><br>
        <form>
              <h2>Contact me !</h2>
              <section class="company's name ">
                &nbsp;&nbsp;&nbsp;&nbsp;
                  <label for="company's name">What is your company's name?</label>
              <input type="text" name="company's name" id="company's name">
              </section>
              <section class="your name">
                &nbsp;&nbsp;&nbsp;&nbsp;
                  <label for="name">What is your name?</label>
              <input type="text" name="name" id="name">
              </section>
              <section class="your phone number">
                &nbsp;&nbsp;&nbsp;&nbsp;
                <label for="phone number">What is your phone number?</label>
              <input type="text" name="phone number" id="phone number">
              </section>
            <section class="wage">
              &nbsp;&nbsp;&nbsp;&nbsp;
                  <label for="amount">How much would you willing to pay for my salary a month?</label>
                  <input type="number" name="amount" id="amount">
              </section>
              <section class="satisfy">
                &nbsp;&nbsp;&nbsp;&nbsp;
                <label for="doneness" padding>Does my CV catch your eyes?</label>
                <br>
                &nbsp;&nbsp;&nbsp;&nbsp;
                <span>NOPE</span>
                &nbsp;
                <input style = "width:30%; display: inline;" type="range" name="doneness" id="doneness" value="6" min="1" max="11">
                <span>OFCOURSE!</span>
              </section>
              <section class="part">
                &nbsp;&nbsp;&nbsp;&nbsp;
                  <span>Which parts do I catch your eyes?</span>
                  <br>
                  &nbsp;&nbsp;&nbsp;&nbsp;
                  <input type="checkbox" name="part" id="EDUCATION" value="EDUCATION">
                  <label for="EDUCATION">EDUCATION</label>
                  <input type="checkbox" name="part" id="WORKING EXPERIENCE" value="WORKING EXPERIENCE">
                  <label for="WORKING EXPERIENCE">WORKING EXPERIENCE</label>
                  <input type="checkbox" name="part" id="EXTRACURRICULAR ACTIVITIES" value="EXTRACURRICULAR ACTIVITIES">
                  <label for="EXTRACURRICULAR ACTIVITIES">EXTRACURRICULAR ACTIVITIES</label>
                  <input type="checkbox" name="part" id="SKILL" value="SKILL">
                  <label for="SKILL">SKILL</label>
                  <br>&nbsp;&nbsp;&nbsp;&nbsp;
                  <input type="checkbox" name="part" id="PORTFOLIO" value="PORTFOLIO">
                  <label for="PORTFOLIO">PORTFOLIO</label>
              </section>
              <section class="week-choice">
                &nbsp;&nbsp;&nbsp;&nbsp;
            <label for="week">Which day can I reply to your invitation?</label>
                  <select id="week" name="week">
                    <option value="Monday">Monday</option>
                    <option value="Tueday">Tuesday</option>
                    <option value="Wednesday">Wednesday</option>
                    <option value="Thursday">Thursday</option>
                    <option value="Friday">Friday</option>
                    <option value="Saturday">Saturday</option>
                    <option value="Sunday">Sunday</option>
                </select>
              </section>
            </form>
            <br><br><br><br>
      </div>
    </body>
  </html>