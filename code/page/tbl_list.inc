<?php

function tbl_list() {

	if ( isset( $_SESSION['current_tbl'] ) )
		unset( $_SESSION['current_tbl'] );

	if ( isset( $_REQUEST['db'] ) )
		$_SESSION['current_db'] = mysql_escape_string( trim( urldecode( $_REQUEST['db'] ) ) );

	if ( !isset( $_SESSION['current_db'] ) ) {
		header('Location: ' . $GLOBALS['_INDEX'] . '?p=db&opt=db_list');
		exit;
	}

	$page['url_db_list'] = $GLOBALS['_INDEX'] . '?p=db&opt=db_list';
	$page['lbl_db_list'] = _('Back to the database list');

	$tpl = class_init('PHPTAL');
	class_call_method($tpl, 'setPhpCodeDestination', PHPTAL_CODE_DESTINATION);
	class_call_method($tpl, 'setTemplateRepository', PHPTAL_TEMPLATE_REPOSITORY);

	$db = func_call( 'db_create' );

	$q = 'SELECT * FROM information_schema.TABLES WHERE information_schema.TABLES.TABLE_SCHEMA = "' . $_SESSION['current_db'] . '"';
	$res = func_call('db_query', $db, $q);

	$tables = array();
	while ( $row = class_call_method( $res, 'fetchRow', MDB2_FETCHMODE_ASSOC ) ) {
		$row['url_col'] = $GLOBALS['_INDEX'] . '?p=db&opt=col_list&tbl=' . $row['table_name'];
		$tables[] = $row;
	}

	class_call_method($tpl, 'set', 'page', $page);
	class_call_method($tpl, 'set', 'tables', $tables);
	class_call_method($tpl, 'setTemplate', 'tbl_list.html');

	return class_call_method($tpl, 'execute');

}

?>