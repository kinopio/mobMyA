<?php

session_start();

define('ROOT_PATH', dirname(__FILE__) . '/');

require_once ROOT_PATH . 'config/config.inc';

if ( !func_call( 'check_include_path', 'MDB2.php' ) ) {
	echo 'Unable to find PEAR::MDB2 extension. Please install it (# pear install MDB2 MDB2#MySQL).';
	exit;
}

if ( !func_call( 'check_include_path', 'PHPTAL.php' ) ) {
	echo 'Unable to find the PHPTAL library. Please install it (# pear install http://phptal.org/latest.tar.gz).';
	exit;
}

if ( !is_dir( PHPTAL_CODE_DESTINATION ) ) {
	$created = @mkdir( PHPTAL_CODE_DESTINATION );
	if ( $created === false ) {
		echo 'Unable to create ' . PHPTAL_CODE_DESTINATION . ' directory. Please create it.';
		exit;
	}
}

if ( !is_writeable( PHPTAL_CODE_DESTINATION ) ) {
	echo 'Directory ' . PHPTAL_CODE_DESTINATION . ' is not writeable. Please update it.';
	exit;
}

require_once 'MDB2.php';
require_once 'PHPTAL.php';

if ( !isset( $_SESSION['db']['init'] ) ) {
	$page = 'login';
} else {
	if ( isset( $_REQUEST['p'] ) )
		$page = $_REQUEST['p'];
	else
		$page = DEFAULT_PAGE;
}

$tpl = func_call( 'tpl_create' );

switch ( $page ) {
	case 'login':
		require_once PAGE_PATH . 'login.inc';

		$html = login();
		break;
	case 'db':
		require_once PAGE_PATH . 'db.inc';
		$html = db();
		break;
}

class_call_method($tpl, 'set', 'body', $html);
class_call_method($tpl, 'setTemplate', 'index.html');

echo class_call_method($tpl, 'execute');

?>