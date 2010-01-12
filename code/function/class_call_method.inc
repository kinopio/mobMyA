<?php

function class_call_method( &$obj, $method ) {

	$args = func_get_args();

	if ( !method_exists( $obj, $method ) )
		return false;

	unset( $args[0] );
	unset( $args[1] );

	return call_user_func_array( array( $obj, $method ), $args );
}

?>