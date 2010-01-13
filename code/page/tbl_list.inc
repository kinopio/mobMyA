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

	$db0 = func_call( 'db_create' );
	$db1 = func_call( 'db_create' );

	$q = 'SELECT * FROM information_schema.TABLES WHERE information_schema.TABLES.TABLE_SCHEMA = "' . $_SESSION['current_db'] . '"';
	$res0 = func_call('db_query', $db0, $q);

	$tables = array();
	while ( $row0 = class_call_method( $res0, 'fetchRow', MDB2_FETCHMODE_ASSOC ) ) {
		$row0['url_col'] = $GLOBALS['_INDEX'] . '?p=db&opt=col_list&tbl=' . $row0['table_name'];
		$row0['url_row'] = $GLOBALS['_INDEX'] . '?p=db&opt=row_list&tbl=' . $row0['table_name'];
		$row0['url_idx'] = $GLOBALS['_INDEX'] . '?p=db&opt=idx_list&tbl=' . $row0['table_name'];

		$q = 'SELECT * FROM information_schema.STATISTICS WHERE information_schema.STATISTICS.TABLE_SCHEMA = "' . $_SESSION['current_db'] . '" AND information_schema.STATISTICS.TABLE_NAME = "' . $row0['table_name'] . '"';
		$res1 = func_call('db_query', $db1, $q);

		$row0['indexes'] = array();
		while ( $row1 = class_call_method( $res1, 'fetchRow', MDB2_FETCHMODE_ASSOC ) ) {
			$row1['unique'] = ( $row1['not_unique'] ? 'not unique' : 'unique' );
			$row0['indexes'][] = $row1;
		}

		$tables[] = $row0;
	}

	class_call_method($tpl, 'set', 'page', $page);
	class_call_method($tpl, 'set', 'tables', $tables);
	class_call_method($tpl, 'setTemplate', 'tbl_list.html');

	return class_call_method($tpl, 'execute');

}

?>