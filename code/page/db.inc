<?php

function db() {

	$sub = ( isset( $_REQUEST['opt'] ) ? $_REQUEST['opt'] : '' );

	switch ( $sub ) {
		default:
		case 'db_list':
			require_once PAGE_PATH . 'db_list.inc';
			return db_list();
			break;
		case 'tbl_list':
			require_once PAGE_PATH . 'tbl_list.inc';
			return tbl_list();
			break;
		case 'col_list':
			require_once PAGE_PATH . 'col_list.inc';
			return col_list();
			break;
		case 'row_list':
			require_once PAGE_PATH . 'row_list.inc';
			return row_list();
			break;
		case 'idx_list':
			require_once PAGE_PATH . 'idx_list.inc';
			return idx_list();
			break;
	}

}

?>