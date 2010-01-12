<?php

function func_call() {

	$args = func_get_args();

	if ( !function_exists( $args[0] ) ) {
		if ( file_exists( FUNC_PATH . $args[0] . '.inc' ) )
			require_once FUNC_PATH . $args[0] . '.inc';
		else
			return false;
	}

	$func_name = $args[0];
	unset( $args[0] );

	return call_user_func_array( $func_name, $args );
}

?>