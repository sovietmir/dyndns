<?php
include_once("common/generic.inc");
include_once("common/log.inc");
include_once("common/Common.inc");

$CFG = new _generic();

$CFG->tmp_dir = "./tmp";
$CFG->logger = new __log($CFG->tmp_dir."/","dyndns.log");


$tmp = explode("/",$_SERVER['SCRIPT_FILENAME']); array_pop($tmp);
$CFG->real_path = implode("/",$tmp);

$configuration = parse_ini_file("conf/config.ini");
foreach($configuration AS $key=>$value){
  $CFG->{$key} = $value;
}

//Load zones
$CFG->zonesINI = "conf/zones.ini";
$CFG->zones = parse_ini_file($CFG->zonesINI, true);

//Read privateKey
$CFG->privateKeyFilename = "conf/private.key";
$CFG->privateKey = file_get_contents($CFG->privateKeyFilename);
