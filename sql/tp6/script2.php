<?php 

include("utils.php");

?>

<!DOCTYPE html PUBLIC "-//W3C//Dtd html 4.0 Transitional//EN">
<html>
	<head>
		<meta HTTP-EQUIV="CONTENT-TYPE" content="text/html; charset=UTF-8">
		<meta name="AUthOR" content="Parmentier Laurent">
		<meta name="DESCRIPTION" content="script php postgres">
		<meta name="KEYWORDS" content="Parmentier Laurent, informatique, ENSICAEN, 2A INFO">
		<title>script2</title>
	</head>
  <body>
	<h1>Requêtes sur la base clinique</h1>
<!-- modifier l'url de l'action par votre url -->
<form action="http://www.ecole.ensicaen.fr/~parmentier/BDD/script3.php">

<?php 

$query=pg_query($dbconn, "SELECT tablename FROM pg_tables WHERE schemaname='parmentier' AND tablename NOT LIKE 'pg%'");
echo(aff_select($query, "tablename", 0));

?>

<input type="submit" name="send" value="execute" />

</form>
 </body>
</html>
