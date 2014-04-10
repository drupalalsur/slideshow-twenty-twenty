<?php
// 

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Allows the profile to alter the site configuration form.
 */
function alsur_form_install_configure_form_alter(&$form, $form_state) {
    $form['site_information']['site_name']['#default_value'] = 'Drupal al Sur';
    $form['site_information']['site_mail']['#default_value'] = 'yo@localhost.com';
    $form['admin_account']['account']['name']['#default_value'] = 'drupal';
    $form['admin_account']['account']['mail']['#default_value'] = 'yo@localhost.com';
    $form['server_settings']['site_default_country']['#default_value'] = 'UY';
    $form['server_settings']['date_default_timezone']['#default_value'] = 'America/Montevideo';
    $form['update_notifications']['#access'] = FALSE;
    //$form['update_notifications']['update_status_module']['#default_value'] = array(1);
    $form['#submit'][] = '_alsur_profile_install_configure_form_submit';
}

/**
* Allow profile to pre-select the language, skipping the selection.
*/
function spanish_profile_details() {
  $details['language'] = "es";
  // Set timezone for date_timezone.module.
  // Set timezone for date_timezone.module.
  $details['date_format_short'] = 'd/m/Y - H:i';
  $details['date_format_medium'] = 'D, d/m/Y - H:i';
  $details['date_format_long'] = 'l, j F, Y - H:i';
  $details['site_default_country'] = "UY";

    // Alter configuration form.
  $details['site_name'] = $_SERVER['SERVER_NAME'];
  $details['site_mail'] = "webmaster@" . $_SERVER['SERVER_NAME'];
  $details['name'] = "drupal";
  $details['pass'] = "drupal";
  $details['mail'] = "webmaster@" . $_SERVER['SERVER_NAME'];
 }
/**
 * Forms API submit for the site configuration form.
 */
function _alsur_profile_install_configure_form_submit($form, &$form_state) {
  global $user;
  $sql_file = dirname(__FILE__).'/alsur.sql';
  $count = _alsur_profile_import_sql($sql_file);
  drupal_set_message("¡Termino la instalación del perfíl! Importadas $count queries.");
  drupal_set_message("Por seguridad elimina el archivo $sql_file, o mueve el directorio del perfil fuera del servidor.");

  variable_set('site_name', $form_state['values']['site_name']);
  variable_set('site_mail', $form_state['values']['site_mail']);
  variable_set('date_default_timezone', $form_state['values']['date_default_timezone']);
  variable_set('site_default_country', $form_state['values']['site_default_country']);

  variable_del('file_temporary_path');
  file_directory_temp();
 
  // Enable update.module if this option was selected.
  if ($form_state['values']['update_status_module'][1]) {
    module_enable(array('update'), FALSE);

    // Add the site maintenance account's email address to the list of
    // addresses to be notified when updates are available, if selected.
    if ($form_state['values']['update_status_module'][2]) {
      variable_set('update_notify_emails', array($form_state['values']['account']['mail']));
    }
  }

  // We precreated user 1 with placeholder values. Let's save the real values.
  $account = user_load(1);
  $merge_data = array('init' => $form_state['values']['account']['mail'], 'roles' => !empty($account->roles) ? $account->roles : array(), 'status' => 1);
  user_save($account, array_merge($form_state['values']['account'], $merge_data));
  // Load global $user and perform final login tasks.
  $user = user_load(1);
  user_login_finalize();

  if (isset($form_state['values']['clean_url'])) {
    variable_set('clean_url', $form_state['values']['clean_url']);
  }

  // Record when this install ran.
  variable_set('install_time', $_SERVER['REQUEST_TIME']);

  $form_state['build_info']['args'][0]['parameters']['profile'] = 'standard';
  drupal_goto();
}

function _alsur_profile_import_sql($filename){
  global $databases;
  if (@mysql_connect($databases['default']['default']['host'], $databases['default']['default']['username'], $databases['default']['default']['password'])){
    mysql_select_db($databases['default']['default']['database']);
    $buffer='';
    $count=0;
    $handle = @fopen($filename, "r");
    if ($handle) {
      while (!feof($handle)) {
        $line = fgets($handle);
        $buffer.=$line;
        if(preg_match('|;$|', $line)){
          $count++;
          mysql_query(_alsur_profile_prefixTables($buffer));
          $buffer='';
        }
      }
      fclose($handle);
    }
    mysql_close();
  }
  return $count;
}

function _alsur_profile_prefixTables($sql) {
  global $databases;
  $prefix = $databases['default']['default']['prefix'];
  if (is_array($prefix)) {
    $defaultPrefix = isset($prefix['default']) ? $prefix['default'] : '';
    unset($prefix['default']);
    $prefixes = $prefix;
  } else {
    $defaultPrefix = $prefix;
    $prefixes = array();
  }	
  // Replace specific table prefixes first.
  foreach ($prefixes as $key => $val) {
    $sql = strtr($sql, array('prefixalsur_' . $key  => $val . $key));
  }
  // Then replace remaining tables with the default prefix.
  return strtr($sql, array('prefixalsur_' => $defaultPrefix ));
}
