<?php

function db_create() {

	$dsn = 'mysql://' . $_SESSION['db']['username'] . ':' . $_SESSION['db']['password'] . '@' . $_SESSION['db']['hostname'] . ':' . $_SESSION['db']['port'];

// 	$db = class_init('MDB2');
// 	class_call_method($db, 'connect', $dsn);

	$db = MDB2::connect($dsn);

	if (PEAR::isError($db))
		die($db->getMessage());

	return $db;
}

?>