<?php

function db_list() {

	if ( isset( $_SESSION['current_db'] ) )
		unset( $_SESSION['current_db'] );

	$tpl = class_init('PHPTAL');
	class_call_method($tpl, 'setPhpCodeDestination', PHPTAL_CODE_DESTINATION);
	class_call_method($tpl, 'setTemplateRepository', PHPTAL_TEMPLATE_REPOSITORY);

	$db = func_call( 'db_create' );

	$q = 'SELECT * FROM information_schema.SCHEMATA';
	$res = func_call('db_query', $db, $q);

	$databases = array();
	while ( $row = class_call_method( $res, 'fetchRow', MDB2_FETCHMODE_ASSOC ) ) {
		$row['url_db'] = $GLOBALS['_INDEX'] . '?p=db&opt=tbl_list&db=' . $row['schema_name'];
		$databases[] = $row;
	}

	class_call_method($tpl, 'set', 'databases', $databases);
	class_call_method($tpl, 'setTemplate', 'db_list.html');

	return class_call_method($tpl, 'execute');

}

?>