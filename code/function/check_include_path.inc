<?php
/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

function check_include_path( $filename ) {

	if(stristr($_SERVER['SERVER_SOFTWARE'], 'Win32'))
		$slash = '\\';
	else
		$slash = '/';

	if ( strpos( $filename, $slash ) !== false ) {
		$dirs = array( rtrim( dirname( $filename ), $path ) );
	} else {
		$include_path = get_include_path();
		$dirs = explode( PATH_SEPARATOR, $include_path );
	}

	$filename = basename( $filename );
	
	foreach ( $dirs as $path ) {
		if ( file_exists( $path . $slash . $filename ) )
			return true;
	}

	return false;
}


?>
