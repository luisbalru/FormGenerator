<?php

class generaFormulario{
  private $iFields = array();
  private $formulario;

  public function makeFormulario($title, $action, $inputFields, $bText = "Submit",
                                $method = "POST")
  {
    $this->formulario = new Formulario($title,$action,$inputFields,$bText,$method);
    echo $this->formulario->getHTML();
  }

  // new text field
  public function addText($label, $name, $value = "")
  {
    $this->iFields[] = new InputField($label, InputFieldType::TEXT, $name, $value);
  }

  // new textarea
  public function addTextarea($label, $name, $value = "")
  {
    $this->iFields[] = new InputField($label, InputFieldType::TEXTAREA, $name, $value);
  }

  // new radio list
  public function addRadio($label, $name, $itemList=array(), $value = "")
  {
    $this->iFields[] = new InputField($label, InputFieldType::RADIO, $name, $value, $itemList);
  }

  // new checkbox list
  public function addCheckbox($label, $name, $itemList=array(), $value = "")
  {
    $this->iFields[] = new InputField($label, InputFieldType::CHECKBOX, $name, $value, $itemList);
  }

  // new select list
  public function addSelect($label, $name, $itemList=array(), $value = "")
  {
    $this->iFields[] = new InputField($label, InputFieldType::SELECT, $name, $value,$itemList);
  }

  public function getInputFields()
  {
    return $this->iFields;
  }
}

class Formulario{
  private $title;
  private $action;
  private $method;
  private $inputFields = array();
  private $bText = "Submit";

  public function __construct($title, $action, $inputFields, $buttonText = "Submit", $method = "POST")
  {
    $this->title = $title;
    $this->action = $action;
    $this->inputFields = $inputFields;
    $this->bText = $buttonText;
    $this->method = $method;
  }

  public function getHTML()
  {
    $salida = '<h1>'.$this->title.'</h1> <br>';
    $salida .= '<form action="'.$this->action.'" method="'.$this->method.'"> <br>'."\n \t";

    foreach($this->inputFields as $key => $val){
      $salida .= $val->getHTML();
    }

    $salida .= '<input type="submit" value="'.$this->bText.'"/> <br>'."\n \t";
    $salida .= '</form>';
    return $salida;
  }
}

class InputField{

  private $label;
  private $name;
  private $type;
  private $value; // selected value for select, radio, checkbox
  private $placeholder = "";
  private $description;
  private $isDisabled = false;
  private $isMultiSelectable = false;
  private $itemList = array();
  private $selectedItems = array();
  private $pleaseSelectEnabled = true;


  public function __construct($label, $type, $name, $value = "", $itemList=array(),
                              $selectedItems = array(), $pleaseSelectEnabled = true) {
    $this->title = $label;
    $this->type = $type;
    $this->name = $name;
    $this->itemList = $itemList;
    $this->selectedItems = $selectedItems;
    $this->pleaseSelectEnabled = $pleaseSelectEnabled;
  }


  public function getHtml(){
    $result = "";
    $result .= $this->getFieldHtmlByType($this->type);
    return $result;
  }

  private function getFieldHtmlByType($type){
   $result = "";
   if($this->isInput($type)) {
     $result .= $this->getCommonLabelForField();
     $result .= '<input value="'.$this->value.'" name="'.$this->name.'" id="'.$this->name.'" type="'.$type.'"/> <br>'."\n \t";
     $result .= $this->getCommonDescriptionForField();
   }
   else if($this->isTextarea($type)) {
     $result .= $this->getCommonLabelForField();
     $result .= '<textarea id="'.$this->name.'" name="'.$this->name.'" rows="7"> </textarea> <br>'."\n \t";
     $result .= $this->getCommonDescriptionForField();
   }
   else if ($this->isCheckboxOrRadio($type)) {
     $result .= $this->addValueToSelectedItems($this->value);
     $result .= '<section class="row">'."\n \t";
     $result .= '<section class="col-md-12">'."\n \t";
     $result .= $this->getCommonLabelForField();
     $result .= $this->getCommonDescriptionForField();
     $result .= '</section>'."\n \t";
     $result .= '</section>'."\n \t";
     $result .= '<section class="row">'."\n \t";
     $result .= '<section class="col-md-12">'."\n \t";
     $result .= $this->getCheckboxOrRadioOptions($type);
     $result .= '</section>'."\n \t";
     $result .= '</section>'."\n \t";
   }
   else if($this->isSelect($type)) {
     $this->addValueToSelectedItems($this->value);
     $result .= $this->getCommonLabelForField();
     $result .= '<select name="'.$this->name.'"'.'>'."\n \t";
     $result .= $this->getSelectOptions();
     $result .= '</select>'."\n \t";
     $result .= $this->getCommonDescriptionForField();
   }
   return $result;
 }
 //add label
 private function getCommonLabelForField() {
   return '<label class="control-label" for="'.$this->name.'">'.$this->title.'</label>'."\n \t";
 }
 // add description below input field
 private function getCommonDescriptionforField() {
   if(strlen($this->description) > 0) {
     return '<span id="'.$this->name.'-help" class="help-block">'.$this->description.'</span>'."\n \t";
   }
 }
 // if value is set, and field requires selectedItems add value to selected items
 private function addValueToSelectedItems($value){
   if(strlen($value) > 0) {
     $this->selectedItems[] = $value;
   }
 }
 // add <option>'s to select
 private function getSelectOptions() {
   $result = "";
   if($this->pleaseSelectEnabled) {
     $result .= '<option value="null"> -- Please Select --</option>';
   }
   foreach($this->itemList as $key => $val) {
     $selectedText = "";
     if(in_array($key, $this->selectedItems)) {
       $selectedText = 'selected="selected"';
     }
     $result .= '<option value="'.$key.'" '.$selectedText.'>'.$val.'</option>'."\n \t";
   }
   return $result;
 }
 //get items for checkbox or radio
 private function getCheckboxOrRadioOptions($type) {
   $result = "";
   foreach($this->itemList as $key => $val) {
     $selectedText = "";
     if(in_array($key, $this->selectedItems)) {
       $selectedText = 'checked="checked"';
     }
     $result .= '<section class="'.$type.'">'."\n \t";
     $result .= '<label>'."\n \t";
     $result .= '<input type="'.$type.'" value="'.$key.'" name="'.$this->name.'"/>'.$val."\n \t";
     $result .= '</label>'."\n \t";
     $result .= '</section>'."\n \t";
   }
   return $result;
 }
 private function isInput($type) {
   $result = false;
   if( !strcmp($type, InputFieldType::TEXT)) {
     $result = true;
   }
   return $result;
 }
 private function isCheckboxOrRadio($type) {
   $result = false;
   if( !strcmp($type, InputFieldType::RADIO) ||
       !strcmp($type, InputFieldType::CHECKBOX)
     ) {
     $result = true;
   }
   return $result;
 }
 private function isCheckbox($type) {
   $result = false;
   if(!strcmp($type, InputFieldType::CHECKBOX))
	$result=true;
   
   return $result;
 }
 private function isTextarea($type) {
   $result = false;
   if(!strcmp($type, InputFieldType::TEXTAREA))
	$result=true;
   
   return $result;
 }
 private function isSelect($type) {
   return (!strcmp($type, InputFieldType::SELECT));
 }
 private function getDisableOption() {
   return ($this->isDisabled ? ' disabled' : '');
 }
}


abstract class InputFieldType {
  //HTML input constants
	const TEXT = "text";
  const RADIO = "radio";
	const CHECKBOX = "checkbox";
  const TEXTAREA = "textarea";
	const SELECT = "select";
}




?>
