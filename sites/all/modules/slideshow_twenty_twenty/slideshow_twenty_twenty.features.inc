<?php
/**
 * @file
 * slideshow_twenty_twenty.features.inc
 */

/**
 * Implements hook_views_api().
 */
function slideshow_twenty_twenty_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function slideshow_twenty_twenty_image_default_styles() {
  $styles = array();

  // Exported image style: twenty.
  $styles['twenty'] = array(
    'name' => 'twenty',
    'label' => 'Twenty',
    'effects' => array(
      1 => array(
        'label' => 'Escalar y recortar',
        'help' => 'Escalar y recortar mantendrán la relación de proporciones de la imagen original y se desechará lo que sobre por el lado mayor. Esto es especialmente útil para crear miniaturas perfectamente cuadradas sin deformar la imagen.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 970,
          'height' => 350,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function slideshow_twenty_twenty_node_info() {
  $items = array(
    'twenty' => array(
      'name' => t('Twenty'),
      'base' => 'node_content',
      'description' => t('Es el slideshow de Twenty Twenty.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
