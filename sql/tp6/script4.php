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
<?php 

$query_string="SELECT ";

$i = 0;
$last_i = count($_GET['col'])-1;

foreach($_GET['col'] as $col_name => $col_val){
	if($last_i != $i){
		$query_string .= $col_name . ", ";
	} else {
		$query_string .= $col_name . " ";
	}

	$i++;
}

$query_string .= "FROM " . $_GET['tablename'];

$query=pg_query($dbconn, $query_string);

echo(aff_table($query));

?>

<a href="script2.php">Retour au choix des colonnes de la table</a><br />
<a href="script3.php?tablename=<?php echo($_GET['tablename']); ?>">Retour au choix d'une table</a><br />

 </body>
</html>
