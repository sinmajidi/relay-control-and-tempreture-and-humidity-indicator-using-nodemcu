<?php
session_start();

?>
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="stylesheet" type="text/css" href="login_style.css">
</head>
<body>

<form action="login_check.php" method="post">
  <div class="container">
    <h1>ورود</h1>
  
    <hr>

    <label for="username"><b>نام کاربری</b></label>
    <input type="text" placeholder="نام کاربری" name="username" id="username" required>

    <label for="psw"><b> رمز ورود</b></label>
    <input type="password" placeholder="رمز ورود" name="psw" id="psw" required>

    
    <hr>
    

    <button type="submit" class="registerbtn">ورود </button>
  </div>
  
 
</form>

</body>
</html>
