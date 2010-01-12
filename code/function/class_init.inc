<?php

function class_init( $class ) {

	if ( !class_exists( $class ) )
		return false;

	$obj = new $class;

	return $obj;
}

?>