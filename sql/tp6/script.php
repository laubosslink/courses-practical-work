<?php 

include("utils.php");

?>
<!DOCTYPE html PUBLIC "-//W3C//Dtd html 4.0 Transitional//EN">
<html>
	<head>
		<meta HTTP-EQUIV="CONTENT-TYPE" content="text/html; charset=UTF-8">
		<meta name="AUthOR" content="Parmentier laurent">
		<meta name="DESCRIPTION" content="script php postgres">
		<meta name="KEYWORDS" content="Parmentier Laurent, informatique, ENSICAEN, 2A INFO">
		<title>script</title>
	</head>
  <body>
		<?php 
			$req=$_GET["req"];
			if (!isset($req) || empty($req) || substr_compare("SELECT", trim($req), 0, 6, true))  
     			 {
				echo "</body></html>";
				return;
			}
			echo "<center><h1>Votre requête : " . $req . "</h1>";
			$dbconn=pg_connect("host=postgres dbname=clinique user=parmentier password=louloute") or die ("Connexion Impossible".pg_last_error());
			$query=pg_query($dbconn,$req);
			if(!$query)
  		{
   			 die ("Erreur dans la requete : " .$req);
  		}

			echo "<table border=\"1px\" witdh='50%'>";
			echo "<tr>";
			for($i=0;$i<pg_num_fields($query);$i++)
  			echo "<th>".pg_field_name($query,$i)."</th>";
			echo "</tr>";

			for($i=0;$i<pg_num_rows($query);$i++)
 			 {
   		 	echo "<tr>";
    		for($j=0;$j<pg_num_fields($query);$j++)
      	{
					if (pg_field_type($query,$j) =="bytea")
					{
	 					$table=pg_field_table($query,0);
	 					echo "<td><img width='60%' src='photo.php?table=" . $table . "&id=" . pg_field_name($query,0). "&valeur=" . pg_fetch_result($query,$i,0) . "&champ=" . pg_field_name($query,$j) . "'></td>";
					}
					else echo "<td>".pg_fetch_result($query,$i,$j)."</td>";
      	}
    		echo "</tr>";
  		 }
			echo "</table>";
			pg_free_result($query);
			pg_close($dbconn);
			?>
			<a href="formulaire.html"> Retour au formulaire</a><br/>
		</center>
	</body>
</html>
