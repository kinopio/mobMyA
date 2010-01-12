<?php

function col_list() {

	$db = func_call( 'db_create' );

	if ( isset( $_REQUEST['tbl'] ) )
		$_SESSION['current_tbl'] = mysql_escape_string( trim( urldecode( $_REQUEST['tbl'] ) ) );

	if ( !isset( $_SESSION['current_db'] ) ) {
		header('Location: ' . $GLOBALS['_INDEX'] . '?p=db_list');
		exit;
	}

	if ( !isset( $_SESSION['current_tbl'] ) ) {
		header('Location: ' . $GLOBALS['_INDEX'] . '?p=tbl_list');
		exit;
	}

	$page['url_db_list'] = $GLOBALS['_INDEX'] . '?p=db&opt=db_list';
	$page['lbl_db_list'] = _('Back to the database list');

	$page['url_tbl_list'] = $GLOBALS['_INDEX'] . '?p=db&opt=tbl_list';
	$page['lbl_tbl_list'] = _('Back to the table list');

	$tpl = class_init('PHPTAL');
	class_call_method($tpl, 'setPhpCodeDestination', PHPTAL_CODE_DESTINATION);
	class_call_method($tpl, 'setTemplateRepository', PHPTAL_TEMPLATE_REPOSITORY);

	$q = 'SELECT * FROM information_schema.COLUMNS WHERE information_schema.COLUMNS.TABLE_SCHEMA = "' . $_SESSION['current_db'] . '" AND information_schema.COLUMNS.TABLE_NAME = "' . $_SESSION['current_tbl'] . '"';
	$res = func_call('db_query', $db, $q);

	$cols = array();
	while ( $row = class_call_method( $res, 'fetchRow', MDB2_FETCHMODE_ASSOC ) ) {
		$row['url_db'] = $GLOBALS['_INDEX'] . '?p=db&opt=col_list&table=' . $row['table_name'];
		$cols[] = $row;
	}

	class_call_method($tpl, 'set', 'page', $page);
	class_call_method($tpl, 'set', 'cols', $cols);
	class_call_method($tpl, 'setTemplate', 'col_list.html');

	return class_call_method($tpl, 'execute');

}

?>