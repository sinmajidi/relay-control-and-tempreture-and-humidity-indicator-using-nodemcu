<?php
$adminname=$_POST["username"];
$password=$_POST["psw"];
if ($adminname=="admin" && $password=="admin") 
{
            $cookie_name = "user";
            $cookie_value = "admin";
            setcookie($cookie_name, $cookie_value, time() + (86400 * 30), "/"); 
            header("Location: /panel.php", true,  303);
}
else
    echo '<script type="text/javascript">alert("نام کاربری یا کلمه عبور نادرست است.");window.location=\'index.php\';</script>';
?>