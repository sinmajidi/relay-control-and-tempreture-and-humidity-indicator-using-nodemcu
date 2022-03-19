<?php
$cookie_name = "user";
if(!isset($_COOKIE[$cookie_name]))
header("Location: /", true,  303);
include_once('connection.php');
include_once('connection_temp.php');

$tbl_name = "relay_control";
$tbl_name_temp = "temp_control";
$sql = "SELECT * FROM $tbl_name";
$sql_temp = "SELECT * FROM $tbl_name_temp";
$result = mysqli_query($conn, $sql);
$result_temp = mysqli_query($conn_temp, $sql_temp);

$devices=[];
$devices_temp=[];
if (mysqli_num_rows($result) > 0) {
    // output data of each row
    while($row = mysqli_fetch_assoc($result)) {
        $devices =  $row;
    }
} 
if (mysqli_num_rows($result_temp) > 0) {
    // output data of each row
    while($row_temp = mysqli_fetch_assoc($result_temp)) {
        $devices_temp =  $row_temp;
    }
} 
mysqli_close($conn);
mysqli_close($conn_temp);

?>


<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="style.css">
    <title>اسیون هوشمند افرا</title>
</head>
<body>
<div class="grid">
    <div class="seprator">
<span><h2><b><i><strong>اتوماسیون هوشمند افرا</strong></i></b><br></h2></span>


<form action="server.php" method="get"> 
  <span>دستگاه شماره 1</span>
  <label class="switch switch-green">
    <input type="checkbox" name="switch_1" class="switch-input" value="1" <?=$devices["switch_1"] ? 'checked' :'' ?>>
    <span class="switch-label" data-on="On" data-off="Off"></span>
    <span class="switch-handle"></span>
  </label>
      <br>
      <span>دستگاه شماره 2</span>
      <label class="switch switch-green">
        <input type="checkbox" name="switch_2" class="switch-input" value="1" <?=$devices["switch_2"] ? 'checked' :'' ?>>
        <span class="switch-label" data-on="On" data-off="Off"></span>
        <span class="switch-handle"></span>
      </label>
      <br>
      <span>دستگاه شماره 3</span>
      <label class="switch switch-green">
        <input type="checkbox" name="switch_3" class="switch-input" value="1"<?=$devices["switch_3"] ? 'checked' :'' ?>>
        <span class="switch-label" data-on="On" data-off="Off"></span>
        <span class="switch-handle"></span>
      </label>
      <br>
      <span>دستگاه شماره 4</span>
      <label class="switch switch-green">
        <input type="checkbox" name="switch_4" class="switch-input" value="1"<?=$devices["switch_4"] ? 'checked' :'' ?>>
        <span class="switch-label" data-on="On" data-off="Off"></span>
        <span class="switch-handle"></span>
      </label>
      <br>
      <span>دستگاه شماره 5</span>
      <label class="switch switch-green">
        <input type="checkbox" name="switch_5" class="switch-input" value="1"<?=$devices["switch_5"] ? 'checked' :'' ?>>
        <span class="switch-label" data-on="On" data-off="Off"></span>
        <span class="switch-handle"></span>
      </label>
      <br>
      <span>دستگاه شماره 6</span>
      <label class="switch switch-green">
        <input type="checkbox" name="switch_6" class="switch-input" value="1"<?=$devices["switch_6"] ? 'checked' :'' ?>>
        <span class="switch-label" data-on="On" data-off="Off"></span>
        <span class="switch-handle"></span>
      </label>
      <br>
      <span>دستگاه شماره 7</span>
      <label class="switch switch-green">
        <input type="checkbox" name="switch_7" class="switch-input" value="1"<?=$devices["switch_7"] ? 'checked' :'' ?>>
        <span class="switch-label" data-on="On" data-off="Off"></span>
        <span class="switch-handle"></span>
      </label>
      <br>
      <span>دستگاه شماره 8</span>
      <label class="switch switch-green">
        <input type="checkbox" name="switch_8" class="switch-input" value="1"<?=$devices["switch_8"] ? 'checked' :'' ?>>
        <span class="switch-label" data-on="On" data-off="Off"></span>
        <span class="switch-handle"></span>
      </label>
      <br>
  <span>دما</span>
     <span> <?php
      echo $devices_temp["temp"]."C";
      ?></span> 
      <br>
      

<span>رطوبت</span>
      <span> <?php
      echo $devices_temp["humidity"]."%";
      ?></span> 
      <br>    

  <input class="submit" type="submit" value="ثبت">
</form>
<form action="logout.php" method="post">
    <input class="logout"type="submit" name="logout" value="خروج" />
</form>

 <br>  <br>  <br>  <br>  <br>  <br> 

    
</div>
</div>
</body>
</html>



<!-- <span>دستگاه شماره 1</span>
<input type="button" class="button button_on" name="switch1_on" value="روشن">
<input type="button" class="button button_off" name="switch1" value="خاموش">
<br>
<span>دستگاه شماره 2</span>
<input type="button" class="button button_on" name="switch2" value="روشن">
<input type="button" class="button button_off" name="switch2" value="خاموش">
<br>
<span>دستگاه شماره 3</span>
<input type="button" class="button button_on" name="switch3" value="روشن">
<input type="button" class="button button_off" name="switch3" value="خاموش">
<br>
<span>دستگاه شماره 4</span>
<input type="button" class="button button_on" name="switch4" value="روشن">
<input type="button" class="button button_off" name="switch4" value="خاموش">
<br>
<span>دستگاه شماره 5</span>
<input type="button" class="button button_on" name="switch5" value="روشن">
<input type="button" class="button button_off" name="switch5" value="خاموش">
<br>
<span>دستگاه شماره 6</span>
<input type="button" class="button button_on" name="switch6" value="روشن">
<input type="button" class="button button_off" name="switch6" value="خاموش">
<br>
<span>دستگاه شماره 7</span>
<input type="button" class="button button_on" name="switch7" value="روشن">
<input type="button" class="button button_off" name="switch7" value="خاموش">
<br>
<span>دستگاه شماره 8</span>
<input type="button" class="button button_on" name="switch8" value="روشن">
<input type="button" class="button button_off" name="switch8" value="خاموش"> -->
<!-- <input type="text" id="name" name="name"><br><br>-->