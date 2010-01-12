<?php

function login() {

	$tpl = class_init('PHPTAL');
	class_call_method($tpl, 'setPhpCodeDestination', PHPTAL_CODE_DESTINATION);
	class_call_method($tpl, 'setTemplateRepository', PHPTAL_TEMPLATE_REPOSITORY);

	$data = array( 'hostname' => array( 'label' => _('hostname'), 'default' => 'localhost' ),
				   'port' => array( 'label' => _('hostname'), 'default' => 3306 ),
				   'username' => array( 'label' => _('username'), 'default' => '' ),
				   'password' => array( 'label' => _('password'), 'default' => '' ),
				 );

	$page_data['form_action'] = INDEX . '?p=login';

	if ( isset( $_REQUEST['connect'] ) ) {
		$dsn = 'mysql://' . $_REQUEST['username'] . ':' . $_REQUEST['password'] . '@' . $_REQUEST['hostname'] . ':' . $_REQUEST['port'];
		$db = class_init('MDB2');
		class_call_method($db, 'connect', $dsn);

		if (PEAR::isError($db))
			die($db->getMessage(). ' - ' . $db->getDebugInfo());

		$_SESSION['db']['init'] = true;
		$_SESSION['db']['hostname'] = $_REQUEST['hostname'];
		$_SESSION['db']['port'] = $_REQUEST['port'];
		$_SESSION['db']['username'] = $_REQUEST['username'];
		$_SESSION['db']['password'] = $_REQUEST['password'];

		header('Location: ' . INDEX . '?p=db');
	}

	class_call_method($tpl, 'set', 'data', $data);
	class_call_method($tpl, 'set', 'page_data', $page_data);
	class_call_method($tpl, 'setTemplate', 'login.html');

	return class_call_method($tpl, 'execute');

}

?>