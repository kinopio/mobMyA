<?php

function idx_list() {

	if ( !isset( $_SESSION['current_db'] ) ) {
		header('Location: ' . $GLOBALS['_INDEX'] . '?p=db&opt=db_list');
		exit;
	}

	if ( isset( $_REQUEST['tbl'] ) )
		$_SESSION['current_tbl'] = mysql_escape_string( trim( urldecode( $_REQUEST['tbl'] ) ) );

	if ( !isset( $_SESSION['current_tbl'] ) ) {
		header('Location: ' . $GLOBALS['_INDEX'] . '?p=db&opt=tbl_list');
		exit;
	}

	$page['url_db_list'] = $GLOBALS['_INDEX'] . '?p=db&opt=db_list';
	$page['lbl_db_list'] = _('Back to the database list');
	$page['url_tbl_list'] = $GLOBALS['_INDEX'] . '?p=db&opt=tbl_list';
	$page['lbl_tbl_list'] = _('Back to the table list');

	$tpl = class_init('PHPTAL');
	class_call_method($tpl, 'setPhpCodeDestination', PHPTAL_CODE_DESTINATION);
	class_call_method($tpl, 'setTemplateRepository', PHPTAL_TEMPLATE_REPOSITORY);

	$db0 = func_call( 'db_create' );

	$q = 'SELECT * FROM information_schema.STATISTICS WHERE information_schema.STATISTICS.TABLE_SCHEMA = "' . $_SESSION['current_db'] . '" AND information_schema.STATISTICS.TABLE_NAME = "' . $_SESSION['current_tbl'] . '"';
	$res0 = func_call('db_query', $db0, $q);

	$indexes = array();
	while ( $row0 = class_call_method( $res0, 'fetchRow', MDB2_FETCHMODE_ASSOC ) ) {
		
		$row0['unique'] = ( $row0['not_unique'] ? 'not unique' : 'unique' );

		$indexes[] = $row0;
	}

	class_call_method($tpl, 'set', 'page', $page);
	class_call_method($tpl, 'set', 'indexes', $indexes);
	class_call_method($tpl, 'setTemplate', 'idx_list.html');

	return class_call_method($tpl, 'execute');

}

?>