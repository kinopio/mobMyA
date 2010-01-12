<?php
/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

function tpl_create() {

	$tpl = class_init('PHPTAL');

	class_call_method($tpl, 'setPhpCodeDestination', PHPTAL_CODE_DESTINATION);
	class_call_method($tpl, 'setTemplateRepository', PHPTAL_TEMPLATE_REPOSITORY);

	return $tpl;
}

?>
