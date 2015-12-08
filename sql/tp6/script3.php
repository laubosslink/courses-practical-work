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
<form action="http://www.ecole.ensicaen.fr/~parmentier/BDD/script4.php">
<input type="hidden" name="tablename" value="<?php echo($_GET['tablename']); ?>" />

<?php 

$query=pg_query($dbconn, "SELECT a.attname
FROM pg_attribute as a, pg_class as c
WHERE c.relname='".$_GET['tablename']."'
AND pg_get_userbyid(c.relowner)='parmentier'
AND a.attrelid=c.relfilenode
AND a.attname NOT IN ('cmax','xmax','cmin','xmin','oid','ctid','tableoid');
");

for($i=0; $i<pg_num_rows($query); $i++)
{
	echo "<input type=\"checkbox\" name=\"col[" . pg_fetch_result($query,$i,0) . "]\" checked=\"checked\" />";
	echo pg_fetch_result($query,$i,0);
	echo "<br />";
}
?>

<a href="script2.php">Retour au choix d'une table</a><br />
<input type="submit" name="send" value="execute" />

</form>
 </body>
</html>
