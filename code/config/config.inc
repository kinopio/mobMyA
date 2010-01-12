<?php

/* DEFINES */
define('PAGE_PATH', ROOT_PATH . 'page/');
define('FUNC_PATH', ROOT_PATH . 'function/');

define('PHPTAL_CODE_DESTINATION', ROOT_PATH . 'cache/');
define('PHPTAL_TEMPLATE_REPOSITORY', ROOT_PATH . 'layout/');

define('INDEX', 'index.php');

define('DEFAULT_PAGE', 'db');

/* INCLUDES */
require_once FUNC_PATH . '/class_init.inc';
require_once FUNC_PATH . '/class_call_method.inc';
require_once FUNC_PATH . '/func_call.inc';

?>