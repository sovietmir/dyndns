<?php
include_once("common/generic.inc");
include_once("common/log.inc");
include_once("common/Common.inc");

$CFG = new _generic();

$CFG->tmp_dir = "./tmp";
$CFG->logger = new __log($CFG->tmp_dir."/","dyndns.log");


$tmp = explode("/",$_SERVER['SCRIPT_FILENAME']); array_pop($tmp);
$CFG->real_path = implode("/",$tmp);

$CFG->nsupdate = "/usr/bin/nsupdate";
$CFG->server = "dyndns.elru.gr";

$CFG->privateKey = "zppk+asSat7bOcS2WoZiQNH+2QGRxNYiJj8cSqeLHvI=";

$CFG->zones = array(
  array(
    "domain"=>"elru.gr",
    "subdomains"=>array(
      "temp","teivos","mixgrill","judi","photo","ftp","teivoscms","checkpoints","thesiseap","maridora","kostas-maridora-book","exelixis",
      "teletraffic","ehlja","torrelay","fek","openjscad","vipr","olena-rabota","95a","khusainov","audiopedia"
    )
  ),
  array(
    "domain"=>"creajob.com",
    "setDomain"=>"true",
    "subdomains"=>array(
      "www"
    )
  ),
  array(
    "domain"=>"aslanidisalexios.gr",
    "setDomain"=>"true",
    "subdomains"=>array(
      "www"
    )
  ),
  array(
    "domain"=>"nmsecurity.gr",
    "setDomain"=>"true",
    "subdomains"=>array(
      "www", "www2"
    )
  ),
);