<?php 
include_once('connection.php');
$tbl_name = "relay_control";
if (isset($_GET['switch_1'])){
    $switch1=$_GET['switch_1']; 
    }
else
    $switch1="0";

if (isset($_GET['switch_2'])){
    $switch2=$_GET['switch_2']; 
    }
else
    $switch2="0";

if (isset($_GET['switch_3'])){
    $switch3=$_GET['switch_3']; 
    }
else
    $switch3="0";
    
if (isset($_GET['switch_4'])){
    $switch4=$_GET['switch_4']; 
    }
else
    $switch4="0";
if (isset($_GET['switch_5'])){
    $switch5=$_GET['switch_5']; 
    }
else
    $switch5="0";
        
if (isset($_GET['switch_6'])){
    $switch6=$_GET['switch_6']; 
    }
else
    $switch6="0";
if (isset($_GET['switch_7'])){
    $switch7=$_GET['switch_7']; 
    }
else
    $switch7="0";
            
if (isset($_GET['switch_8'])){
    $switch8=$_GET['switch_8']; 
    }
else
    $switch8="0";

$sql = "UPDATE $tbl_name SET switch_1=$switch1,switch_2=$switch2,switch_3=$switch3,switch_4=$switch4,switch_5=$switch5,switch_6=$switch6,switch_7=$switch7,switch_8=$switch8 WHERE id=1";

if (mysqli_query($conn, $sql)) {
     header("Location: /panel.php", true,  303); 
  } else {
    echo "Error updating record: " . mysqli_error($conn);
  }
  
  mysqli_close($conn);
 
  
?>
