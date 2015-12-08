<?php
// Connexion au serveur
$dbconn=pg_connect("host=postgres dbname=clinique user=parmentier password=louloute") or die ("Connexion Impossible".pg_last_error());

function aff_select($res,$nom,$col)
{
 echo "<select name='" . $nom . "'>";
 for($i=0;$i<pg_num_rows($res);$i++)
   echo "<option>" . pg_fetch_result($res,$i,$col) . "</option>";
 echo "</select>";
}

function aff_check_box($res,$nom,$col)
{

  for($i=0;$i<pg_num_rows($res);$i++)
    {
      echo "<input type='checkbox' name='" . $nom . "[]'";
      echo " value='" . pg_fetch_result($res,$i,$col) . "' checked>"  ;
      echo pg_fetch_result($res,$i,$col) . "<br>";
    }
}

function aff_table($res)
{
 echo "<table border=\"1px\" witdh='50%'>";
echo "<tr>";
for($i=0;$i<pg_num_fields($res);$i++)
  echo "<th>".pg_field_name($res,$i)."</th>";
echo "</tr>";

for($i=0;$i<pg_num_rows($res);$i++)
  {
    echo "<tr>";
    for($j=0;$j<pg_num_fields($res);$j++)
      {
	if (pg_field_type($res,$j) =="bytea")
	{
	 $table=pg_field_table($res,0);
	 echo "<td><img width='60%' src='photo.php?table=" . $table . "&id=" . pg_field_name($res,0). "&valeur=" . pg_fetch_result($res,$i,0) . "&champ=" . pg_field_name($res,$j) . "'></td>";
	}
	else echo "<td>".pg_fetch_result($res,$i,$j)."</td>";
      }
    echo "</tr>";
  }
echo "</table>";
}
?>
