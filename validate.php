<?php
include_once('connection.php');

$tbl_name = "relay_control";
$sql = "SELECT * FROM $tbl_name";
$result = mysqli_query($conn, $sql);

if (mysqli_num_rows($result) > 0) {
    while($row = mysqli_fetch_assoc($result)) {
        echo $row["switch_1"].$row["switch_2"].$row["switch_3"].$row["switch_4"].$row["switch_5"].$row["switch_6"].$row["switch_7"].$row["switch_8"];
    }
} else {
    echo "0 results";
}
mysqli_close($conn);
?>