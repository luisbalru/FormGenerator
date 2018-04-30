<?php
  require "./generaFormulario.inc";
  error_reporting(E_ALL);
  ini_set("display_errors", 1);
?>

<!DOCTYPE html>
<html>
  <head>
    <meta charset="UTF-8">
    <title>Prueba de generaFormulario</title>
  </head>

  <body>
    <section class="Pruebas">
      <?php
        $ciudades = array(1=>"Granada", 2=>"Madrid", 3=>"Barcelona");
        $ciudadesSeleccionadas = array();

        $Formulario = new generaFormulario();
        $Formulario->addText("Nombre", "nombre");
        $Formulario->addText("Apellidos", "apellidos", "Pon aquí tus apellidos");
	$Formulario->addText("Dirección", "address", "", "Otra forma");
        $Formulario->addTextarea("Descríbete","desc");
        $Formulario->addSelect("¿Cuál es tu ciudad favorita", "select1", $ciudades, "");
        $Formulario->addRadio("¿Y qué ciudad odias?","radio",$ciudades);
        $Formulario->addCheckbox("Elige ciudad", "check", $ciudades);
        $Formulario->makeFormulario("Formulario de prueba", "procesar.php", $Formulario->getInputFields());
      ?>
    </section>
  </body>
</html>
