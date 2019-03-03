<?php
    session_start();
    define('DB_SERVER', 'localhost');
    define('DB_USERNAME', 'root');
    define('DB_PASSWORD', '');
    define('DB_DATABASE', 'database');
    $db = mysqli_connect(DB_SERVER,DB_USERNAME,DB_PASSWORD,DB_DATABASE);
    if ($db->connect_error) {
       die("Connection failed: " . $db->connect_error);
    }
    if(isset($_POST['temperature']) && isset($_POST['humidity'])){
        if($_POST['temperature'] != "" && $_POST['humidity'] != ""){
            $temp = $_POST['temperature'];
            $humi = $_POST['humidity'];
            $sql_store = "INSERT into templog (temperature, humidity) VALUES ('$temp', '$humi')";
            $sql = mysqli_query($db, $sql_store) or die(mysqli_error($db));
        }
        else{
            echo("You need to enter data!");
        }
    }
    
?>





<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>DummyData</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" type="text/css" media="screen" href="main.css">
    <script src="main.js"></script>
</head>
<body>
    <h1> Temp&Humi Data </h1>
    <form action="dummyDataPost.php" method="POST">
        <input type="text" name="temperature" value="" placeholder="Temperature">
        <input type="text" name="humidity" value="" placeholder="Humidity">
        <input type="submit" name="submit" value="Submit">

    </form>
</body>
</html>