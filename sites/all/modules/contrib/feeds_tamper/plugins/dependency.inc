<?php
/**
* @file
* Dependency of field value on another field that returns a boolean value.
* If the dependent field is false or null, then blank output of current field.
*/
$plugin = array(
  'form'     => 'feeds_tamper_dependency_form',
  'callback' => 'feeds_tamper_dependency_callback',
  'name'     => 'Dependency',
  'multi'    => 'skip',
  'category' => 'Text',
);
function feeds_tamper_dependency_form($importer, $element_key, $settings) {
  $form = array();
  $replace = array();
  foreach (feeds_tamper_get_unique_source_list($importer) as $source) {
    $replace[] = '[' . $source . ']';
  }
  $form['text'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter controlling field (Select only one from the list of Available Dependant Fields)'),
    '#description' => t('Choose controlling field. If that field is false the output of the current field will be empty. Copy and paste one of the fields below into this text box.'),
    '#size' => 40,
    '#default_value' => isset($settings['text']) ? $settings['text'] : '',
  );
  $form['help'] = array(
    '#type' => 'fieldset',
    '#title' => t('Available Dependant Fields'),
    '#description'  => t('Choose one of these fields as the controlling field. If "false", the base field will produce a null output. Copy and paste one of the fields below into the text box above.'),
    '#collapsed' => FALSE,
    '#collapsible' => FALSE,
    '#value' => theme('item_list', array('items' => $replace)),
  );
  return $form;
}
function feeds_tamper_dependency_callback($result, $item_key, $element_key, &$field, $settings, $source) {
  $item = $result->items[$item_key];
  foreach ($item as $key => $value) {
    if ('[' . $key . ']' == $settings['text']) {
      $field_dependency = $value;
      break;
    }
  }
  $field = ($field_dependency == 'false' || !$field_dependency) ? "" : $field;
}
