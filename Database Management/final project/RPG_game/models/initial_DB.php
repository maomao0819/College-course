<?php
	require_once dirname(__FILE__) . "/db_check.php";
	require_once dirname(__FILE__) . "/delete_login_info_cookie.php";
	$conn = db_check();
	$drop_taqble_sql = "DROP TABLE BATTLE";
  	mysqli_query($conn, $drop_taqble_sql);
  	$drop_taqble_sql = "DROP TABLE MONSTER";
  	mysqli_query($conn, $drop_taqble_sql);
  	$drop_taqble_sql = "DROP TABLE SKILLUSED";
  	mysqli_query($conn, $drop_taqble_sql);
  	$drop_taqble_sql = "DROP TABLE SKILL";
  	mysqli_query($conn, $drop_taqble_sql);
  	$drop_taqble_sql = "DROP TABLE CHARACTER_TABLE";
  	mysqli_query($conn, $drop_taqble_sql);
  	$drop_taqble_sql = "DROP TABLE EXPLEVEL";
  	mysqli_query($conn, $drop_taqble_sql);
  	$drop_taqble_sql = "DROP TABLE CLASS";
  	mysqli_query($conn, $drop_taqble_sql);
  	$drop_taqble_sql = "DROP TABLE ACCOUNT";
  	mysqli_query($conn, $drop_taqble_sql);
	$drop_taqble_sql = "DROP TABLE user_account";
  	mysqli_query($conn, $drop_taqble_sql);
  	
  	$create_sql =
  	  	"CREATE TABLE user_account (
		id INT(10) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
		email VARCHAR(60) NOT NULL,
		username VARCHAR(40) NOT NULL,
		password VARCHAR(40) NOT NULL,
		reg_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP);";
	mysqli_query($conn, $create_sql);
	$sql = "CREATE TABLE IF NOT EXISTS ACCOUNT ( -- 帳號，一個帳號可能有多個玩家角色
		    Account_ID int NOT NULL, -- 帳號編號(PK)
		    Real_Name varchar(200) NOT NULL, -- 真人名稱
		    Age int,
		    Sex enum('male','female'),
		    Country varchar(200) NOT NULL,
		    Email varchar(200) NOT NULL,
		    Username varchar(200) NOT NULL UNIQUE, -- 帳號帳號
		    Password varchar(200) NOT NULL, -- 帳號密碼
		    PRIMARY KEY (Account_ID));";
	mysqli_query($conn, $sql);
	$sql = "CREATE TABLE IF NOT EXISTS CLASS ( -- 職業，玩家角色種類或怪物種類都有
		    Class_ID int NOT NULL, -- 職業編號(PK)
		    Class_Name varchar(200) NOT NULL, -- 職業名稱
		    Base_Damage int NOT NULL, -- 職業基礎攻擊
		    Base_Defense int NOT NULL, -- 職業基礎防禦
		    Base_Health int NOT NULL, -- 職業基礎血量
		    Base_Speed int NOT NULL, -- 職業基礎速度
		    PRIMARY KEY (Class_ID));";
	mysqli_query($conn, $sql);
	$sql = "CREATE TABLE IF NOT EXISTS EXPLEVEL ( -- 玩家角色經驗值換算成等級的總表
		    Experience int NOT NULL,
		    Level int NOT NULL,
		    PRIMARY KEY (Experience));";
	mysqli_query($conn, $sql);
	$sql = "CREATE TABLE IF NOT EXISTS CHARACTER_TABLE (-- 玩家角色
		    Character_ID int NOT NULL, -- 角色編號(PK)
		    Character_Name varchar(200) NOT NULL UNIQUE, -- 角色名字，不可重複
		    Account int NOT NULL, -- 角色的帳號編號
		    Class int NOT NULL, -- 角色的職業編號
		    Exp int,
		    PRIMARY KEY (Character_ID),
		    FOREIGN KEY (Account) REFERENCES ACCOUNT(Account_ID),
		    FOREIGN KEY (Class) REFERENCES CLASS(Class_ID),
		    FOREIGN KEY (Exp) REFERENCES EXPLEVEL(Experience));";
	mysqli_query($conn, $sql);
	$sql = "CREATE TABLE IF NOT EXISTS SKILL ( -- 技能
		    Skill_ID int NOT NULL, -- 技能編號(PK)
		    Skill_Name varchar(200) NOT NULL, -- 技能名稱
		    Class int NOT NULL, -- 用技能的職業
		    Level_limit int, -- 等級限制
		    Mana_Cost int NOT NULL, -- 魔力花費
		    Damage int NOT NULL, -- 造成傷害
		    CD int NOT NULL, 
		    PRIMARY KEY (Skill_ID),
		    FOREIGN KEY (Class) REFERENCES CLASS(Class_ID));";
	mysqli_query($conn, $sql);
	$sql = "CREATE TABLE IF NOT EXISTS SKILLUSED ( -- 當作我們資料庫的Works_on就對了
		    Skill int NOT NULL, -- 技能編號(PK)
		    Char_ID int NOT NULL, -- 玩家角色編號(PK)
		    Times_used int, -- 本角色用此技能次數
		    PRIMARY KEY (Skill,Char_ID),
		    FOREIGN KEY (Skill) REFERENCES SKILL(Skill_ID),
		    FOREIGN KEY (Char_ID) REFERENCES CHARACTER_TABLE(Character_ID));";
	mysqli_query($conn, $sql);
	$sql = "CREATE TABLE IF NOT EXISTS MONSTER ( -- 怪物，每隻遊戲內產出的皆分開記
		    Monster_ID int NOT NULL, -- 帳號編號(PK)
		    Class int NOT NULL, -- 怪物種類
		    Defeat_Exp int NOT NULL, -- 擊退玩家能獲得的經驗值
		    Defeat_Date DATE, -- 擊退日期
		    Defeated_By int, -- 擊退本怪物的玩家角色的編號
		    PRIMARY KEY (Monster_ID),
		    FOREIGN KEY (Class) REFERENCES CLASS(Class_ID),
		    FOREIGN KEY (Defeated_By) REFERENCES CHARACTER_TABLE(Character_ID));";
	mysqli_query($conn, $sql);
	$sql = "CREATE TABLE IF NOT EXISTS BATTLE (
		    Battle_ID int NOT NULL, -- 戰鬥編號(PK)
		    Battle_Date DATE NOT NULL, -- 戰鬥發生的日期
		    Stage_ID int NOT NULL, -- 場地編號
		    Winner_ID int NOT NULL, -- 贏家玩家角色的編號
		    Loser_ID int NOT NULL,  -- 輸家玩家角色的編號
		    PRIMARY KEY (Battle_ID),
		    FOREIGN KEY (Winner_ID) REFERENCES CHARACTER_TABLE(Character_ID),
		    FOREIGN KEY (Loser_ID) REFERENCES CHARACTER_TABLE(Character_ID));";
	mysqli_query($conn, $sql);
	$sql = "INSERT INTO ACCOUNT (Account_ID, Real_Name, Age, Sex, Country, Email , Username, Password) VALUES
			(1, 'John Smith', 22, 'male','Taiwan','john_smith@gmail.com','ABCDEF', 'ABCDEF'),
			(2,  'Dona Huber',1,'female','US','dona_huber@gmail.com', 'ugvuv', 'ovioj'),
			(3,  'Roy Hise', 99,'male','Taiwan','roy_hise@gmail.com', 'apple', 'pen'),
			(4,   'Peter Goad', 87,'male','Canada','peter_goad@gmail.com', 'Active','QAQ'),
			(5, 'Sarah Thomas', 66,'female','French','sarah_thomas@gmail.com', 'W', 'jpg'),
			(6, 'Edna William',123, 'female','Japan', 'edna_william@gmail.com', '$2y$10$mfM','e.jpg');";
	mysqli_query($conn, $sql);
	$sql = "INSERT INTO CLASS (Class_ID, Class_Name, Base_Damage, Base_Defense, Base_Health , Base_Speed) VALUES
			(1, 'Mage', 5, 15,5,5),
			(2, 'Warrior', 5, 5,15,5),
			(3, 'Archer', 5, 5,5,10),
			(4, 'Rouge', 5, 5,5,15),
			(5, 'Pirate', 10, 5,10,5),
			(6, 'Slime', 1, 1,1,1),
			(7, 'Snail', 2, 2,2,2),
			(8, 'Mushroom', 5, 5,5,5),
			(9, 'Pig', 5, 5,5,5),
			(10, 'Demon', 105, 105,105,105),
			(11, 'Treant', 5, 5,5,5),
			(12, 'Mono', 5, 5,5,5);";
	mysqli_query($conn, $sql);
	$sql = "INSERT INTO EXPLEVEL(Experience , Level) VALUES
			(0, 1),
			(1, 1),
			(2, 1),
			(3, 1),
			(4, 1),
			(5, 1),
			(6, 1),
			(7, 1),
			(8, 1),
			(9, 1),
			(10, 2),
			(11, 2),
			(12, 2),
			(13, 2),
			(14, 2),
			(15, 2),
			(16, 2),
			(17, 2),
			(18, 2),
			(19, 2),
			(20, 3),
			(21, 3),
			(22, 3),
			(23, 3),
			(24, 3),
			(25, 3),
			(26, 3),
			(27, 3),
			(28, 3),
			(29, 3),
			(30, 4),
			(31, 4),
			(32, 4),
			(33, 4),
			(34, 4),
			(35, 4),
			(36, 4),
			(37, 4),
			(38, 4),
			(39, 4),
			(40, 5),
			(41, 5),
			(42, 5),
			(43, 5),
			(44, 5),
			(45, 5),
			(46, 5),
			(47, 5),
			(48, 5),
			(49, 5),
			(50, 6),
			(51, 6),
			(52, 6),
			(53, 6),
			(54, 6),
			(55, 6),
			(56, 6),
			(57, 6),
			(58, 6),
			(59, 6),
			(60, 7),
			(61, 7),
			(62, 7),
			(63, 7),
			(64, 7),
			(65, 7),
			(66, 7),
			(67, 7),
			(68, 7),
			(69, 7),
			(70, 8),
			(71, 8),
			(72, 8),
			(73, 8),
			(74, 8),
			(75, 8),
			(76, 8),
			(77, 8),
			(78, 8),
			(79, 8),
			(80, 9),
			(81, 9),
			(82, 9),
			(83, 9),
			(84, 9),
			(85, 9),
			(86, 9),
			(87, 9),
			(88, 9),
			(89, 9),
			(90, 10),
			(91, 10),
			(92, 10),
			(93, 10),
			(94, 10),
			(95, 10),
			(96, 10),
			(97, 10),
			(98, 10),
			(99, 10),
			(100, 11);";
	mysqli_query($conn, $sql);
	$sql = "INSERT INTO CHARACTER_TABLE (Character_ID,Character_Name, Account, Class,Exp) VALUES
			(1, 'tom',1,1,31),
			(2, 'tim',1,1,21),
			(3, 'fred',2,1,11),
			(4, 'john',2,2,41),
			(5, 'henry',4,2,31),
			(6, 'tina',5,2,21),
			(7, 'timmy',6,2,1),
			(8, 'timmy2',4,2,1),
			(9, 'abc',2,3,1),
			(10, 'def',1,3,1),
			(11, 'Winni',3,3,1),
			(12, 'ijk',2,3,44),
			(13, 'bbc',1,4,41),
			(14, 'mmd',2,4,31),
			(15, 'Tzuyu',3,4,1),
			(16, 'wtf',2,5,21),
			(17, 'Jason',3,5,31),
			(18, 'apple',4,5,41);";
	mysqli_query($conn, $sql);
	$sql = "INSERT INTO SKILL (Skill_ID, Skill_Name , Class, Level_limit, Mana_Cost , Damage, CD) VALUES
			(1, 'Freeze', 1, 1,2,5, 3),
			(2, 'Fireball', 1, 2,10,10, 4),
			(3, 'Zap', 1, 3,20,10, 4),
			(4, 'Slash', 2, 5,5,15, 6),
			(5, 'Bash', 2, 5,10,5,3),
			(6, 'Strike', 2, 1,1,1,1),
			(7, 'DualShot', 3, 2,2,2,2),
			(8, 'Target', 3, 5,5,5,3),
			(9, 'FlameArrow', 3, 5,5,5,3),
			(10, 'CannonBall', 5, 105,105,105,45),
			(11, 'Stab', 5, 5,5,5,3),
			(12, 'Shot', 5, 5,5,5,3),
			(13, 'Sneak', 4, 5,5,5,3),
			(14, 'Dash', 4, 5,5,5,3),
			(15, 'Stab', 4, 5,5,5,3);";
	mysqli_query($conn, $sql);
	$sql = "INSERT INTO SKILLUSED(Skill, Char_ID , Times_used) VALUES
			(1,1,3),
			(2,1,1),
			(3,1,9),
			(1,2,3),
			(2,2,1000),
			(3,2,9),
			(1,3,3),
			(2,3,6),
			(3,3,9),
			(4,4,2),
			(5,4,11),
			(6,4,9),
			(4,5,4),
			(5,5,66),
			(6,5,1),
			(4,6,0),
			(5,6,0),
			(6,6,6),
			(4,7,6),
			(5,7,4),
			(6,7,3),
			(4,8,2),
			(5,8,1),
			(6,8,0),
			(7,9,2),
			(8,9,1),
			(9,9,0),
			(7,10,2),
			(8,10,1),
			(9,10,0),
			(7,11,2),
			(8,11,1),
			(9,11,0),
			(7,12,2),
			(8,12,1),
			(9,12,0),
			(10,13,2),
			(11,13,1),
			(12,13,0),
			(10,14,2),
			(11,14,1),
			(12,14,0),
			(10,15,2),
			(11,15,1),
			(12,15,0),
			(13,16,2),
			(14,16,1),
			(15,16,0),
			(13,17,2),
			(14,17,1),
			(15,17,0),
			(13,18,2),
			(14,18,1),
			(15,18,0);";
	mysqli_query($conn, $sql);
	$sql = "INSERT INTO MONSTER(Monster_ID, Class  , Defeat_Exp,Defeat_Date,Defeated_By ) VALUES
			(1,6,1,'2015/12/17',1),
			(2,7,1,'2015/12/17',1),
			(3,8,1,'2015/12/17',2),
			(4,11,1,'2015/12/18',1),
			(5,6,1,'2015/12/17',3),
			(6,6,2,'2015/12/17',3),
			(7,6,2,'2015/12/18',4),
			(8,6,2,'2015/12/18',5),
			(9,6,1,'2015/12/17',6),
			(10,6,1,'2015/12/18',6),
			(11,7,0,'2015/12/17',6),
			(12,9,0,'2015/12/19',7),
			(13,6,0,'2015/12/17',8),
			(14,6,1,'2015/12/19',8),
			(15,9,1,'2015/12/17',9),
			(16,9,0,'2015/12/19',10),
			(17,9,0,'2015/12/17',11),
			(18,6,3,'2015/12/17',12),
			(19,6,3,'2015/12/19',13),
			(20,7,3,'2015/12/17',14),
			(21,7,5,'2015/12/19',14),
			(22,6,5,'2015/12/17',15),
			(23,6,1,'2015/12/19',16),
			(24,7,0,'2015/12/17',16),
			(25,6,1,'2015/12/19',16),
			(26,7,1,'2015/12/17',17);";
	mysqli_query($conn, $sql);
	$sql = "INSERT INTO BATTLE(Battle_ID , Battle_Date  , Stage_ID,Winner_ID,Loser_ID ) VALUES
			(1,'2015/12/17',5,1,12),
			(2,'2015/12/17',5,1,11),
			(3,'2015/12/17',5,1,14),
			(4,'2015/12/17',5,13,1),
			(5,'2015/12/18',5,1,16),
			(6,'2015/12/18',5,12,1),
			(7,'2015/12/18',5,2,5),
			(8,'2015/12/18',5,1,5),
			(9,'2015/12/17',5,1,7),
			(10,'2015/12/19',5,1,8),
			(11,'2015/12/19',5,1,12),
			(12,'2015/12/17',5,2,12),
			(13,'2015/12/19',5,14,2),
			(14,'2015/12/17',5,15,2),
			(15,'2015/12/19',5,1,2);";
	mysqli_query($conn, $sql);
  	$email = "11@11";
  	$username = "11";
  	$password = md5("11", false);
  	$initail_sql = "INSERT INTO user_account (email, username, password) VALUES ('$email', '$username', '$password')";
  	mysqli_query($conn, $initail_sql);
  	delete_login_info_cookie();
  	setcookie("initial_DB", true, time() + 3600, "/");
  	header("Location: ../views/login.php");
	exit();