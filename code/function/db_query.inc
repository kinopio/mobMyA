<?php

function db_query( &$db, $q ) {

	$res = class_call_method( $db, 'query', $q );

	if (PEAR::isError($db))
		die($db->getMessage());

	return $res;
}

?>