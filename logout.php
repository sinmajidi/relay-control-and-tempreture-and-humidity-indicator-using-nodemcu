<?php
    if($_SERVER['REQUEST_METHOD'] == "POST" and isset($_POST['logout']))
    {
        func();
    }
    function func()
    {
        
// set the expiration date to one hour ago
setcookie("user", "", time() -(86400 * 30), '/');
header("Location:/");
   
    }
?>