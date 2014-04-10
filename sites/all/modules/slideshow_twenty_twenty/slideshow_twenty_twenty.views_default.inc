<?php
/**
 * @file
 * slideshow_twenty_twenty.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function slideshow_twenty_twenty_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'slideshow_twenty';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Slideshow Twenty';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Slideshow Twenty';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'más';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Aplicar';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Reiniciar';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Ordenar por';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Campo: Contenido: Título */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Campo: Contenido: Imagen Twenty */
  $handler->display->display_options['fields']['field_imagen_twenty']['id'] = 'field_imagen_twenty';
  $handler->display->display_options['fields']['field_imagen_twenty']['table'] = 'field_data_field_imagen_twenty';
  $handler->display->display_options['fields']['field_imagen_twenty']['field'] = 'field_imagen_twenty';
  $handler->display->display_options['fields']['field_imagen_twenty']['label'] = '';
  $handler->display->display_options['fields']['field_imagen_twenty']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_imagen_twenty']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_imagen_twenty']['type'] = 'twentytwenty';
  $handler->display->display_options['fields']['field_imagen_twenty']['settings'] = array(
    'image_style' => 'twenty',
    'default_offset_pct' => '0.8',
  );
  $handler->display->display_options['fields']['field_imagen_twenty']['delta_offset'] = '0';
  /* Criterio de ordenación: Contenido: Fecha del envío */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Criterios de filtrado: Contenido: Publicado */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Criterios de filtrado: Contenido: Tipo */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'twenty' => 'twenty',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $translatables['slideshow_twenty'] = array(
    t('Master'),
    t('Slideshow Twenty'),
    t('más'),
    t('Aplicar'),
    t('Reiniciar'),
    t('Ordenar por'),
    t('Asc'),
    t('Desc'),
    t('Block'),
  );
  $export['slideshow_twenty'] = $view;

  return $export;
}
