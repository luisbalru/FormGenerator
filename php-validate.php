<!DOCTYPE HTML>  
<html>
	<head>
		<style>
		.error {color: #FF0000;}
		</style>
	</head>
	<body>  

		<?php
		// definición de las variables
		$nameErr = $emailErr = $genderErr = $websiteErr = "";
		$name = $email = $gender = $comment = $website = "";

		if ($_SERVER["REQUEST_METHOD"] == "POST") {
		  if (empty($_POST["name"])) {
		    $nameErr = "Debes poner el nombre";
		  } else {
		    $name = test_input($_POST["name"]);
		    // comprueba si el nombre tiene sólo letras y espacios
		    if (!preg_match("/^[a-zA-Z ]*$/",$name)) {
		      $nameErr = "Sólo letras y espacios";
		    }
		  }
		  
		  if (empty($_POST["email"])) {
		    $emailErr = "Debes poner el email";
		  } else {
		    $email = test_input($_POST["email"]);
		    // comprueba si el email está bien definido
		    if (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
		      $emailErr = "Email no válido";
		    }
		  }
		    
		  if (empty($_POST["website"])) {
		    $website = "";
		  } else {
		    $website = test_input($_POST["website"]);
		    // comprueba si la sintaxis de la URL es válida
		    if (!filter_var($website,FILTER_VALIDATE_URL)) {
		      $websiteErr = "URL no válida";
		    }
		  }

		  if (empty($_POST["comment"])) {
		    $comment = "";
		  } else {
		    $comment = test_input($_POST["comment"]);
		  }

		  if (empty($_POST["gender"])) {
		    $genderErr = "Elige el género";
		  } else {
		    $gender = test_input($_POST["gender"]);
		  }
		}

		function test_input($data) {
		  $data = trim($data);
		  $data = stripslashes($data);
		  $data = htmlspecialchars($data);
		  return $data;
		}
		?>

		<h2>Validación de un Formulario PHP</h2>
		<p><span class="error">* campo obligatorio</span></p>
		<form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">  
		  Nombre: <input type="text" name="name" value="<?php echo $name;?>">
		  <span class="error">* <?php echo $nameErr;?></span>
		  <br><br>
		  E-mail: <input type="text" name="email" value="<?php echo $email;?>">
		  <span class="error">* <?php echo $emailErr;?></span>
		  <br><br>
		  Página web: <input type="text" name="website" value="<?php echo $website;?>">
		  <span class="error"><?php echo $websiteErr;?></span>
		  <br><br>
		  Comentarios: <textarea name="comment" rows="5" cols="40"><?php echo $comment;?></textarea>
		  <br><br>
		  Género:
		  <input type="radio" name="gender" <?php if (isset($gender) && $gender=="female") echo "checked";?> value="female">Femenino
		  <input type="radio" name="gender" <?php if (isset($gender) && $gender=="male") echo "checked";?> value="male">Masculino
		  <input type="radio" name="gender" <?php if (isset($gender) && $gender=="other") echo "checked";?> value="other">Otro
		  <span class="error">* <?php echo $genderErr;?></span>
		  <br><br>
		  <input type="submit" name="submit" value="Submit">  
		</form>


	</body>
</html>
