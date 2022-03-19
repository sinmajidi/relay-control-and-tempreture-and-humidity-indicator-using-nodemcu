<?php
include_once('connection_temp.php');
$tbl_name = "temp_control";
    if(!empty($_POST['temp']) && !empty($_POST['humidity']))
    {
    	$temp = $_POST['temp'];
    	$humidity = $_POST['humidity'];
        echo "ok".$temp;
        echo "ok".$humidity;
        $sql = "UPDATE $tbl_name SET temp=$temp,humidity=$humidity WHERE id=1";
        if (mysqli_query($conn_temp, $sql)) {
     header("Location: /panel.php", true,  303); 
  } else {
    echo "Error updating record: " . mysqli_error($conn_temp);
  }
        mysqli_close($conn_temp);
	}


	
?>