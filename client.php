#!/php/bin/php
<?php
/**
 * cli stand alone php script, daemon style (runs for ever), that checks the IP, by hitting server/ip.php. 
 * If the IP have changed from the last time (or it is the first time) it hits the server/dns.ph, thus informing it of the current IP and asking to set it 
 * for the list of configured zones. 
 * 
 */
if (php_sapi_name() !== 'cli') {
  die("This script can only be run from the command line.".PHP_EOL);
}

include_once("common.inc");

print var_export($CFG, true).PHP_EOL;


if(Common::ie("privateKey", $CFG)=="") {
  $helpMsg = "The value of \$CFG->privateKey is not set.".PHP_EOL;
  $helpMsg .= "In order to set the private key, run the command `php privatekeyGeneration.php > ".ie("privateKeyFilename", $CFG)."`.".PHP_EOL;
  $helpMsg .= "Note that, you must share the ".ie("privateKeyFilename", $CFG)." file with the server — ".ie("server", $CFG).".".PHP_EOL;
  die($helpMsg);
}

$CFG->logger = null;
$sleep = 300;
$my_ip = "";
while(true){
  $ip_url = "http://".$CFG->server."/ip.php";
  $CFG->log("To obtain ip, hitting ".$ip_url,0);
  $ip = trim(implode("", file($ip_url)));
  if($ip!=""){
    $CFG->log("The ip is: ".$ip,0);
    if($ip!=$my_ip){
      if($my_ip=="") $CFG->log("First time",0);
      else $CFG->log("The ip chaneged from the previous time (previous ip: ".$myip.")",0);
  
      $timestamp = time();
      $signature = base64_encode(hash_hmac('sha256', $timestamp.$ip, $CFG->privateKey, true));

      $dns_url = "http://".$CFG->server."/dns.php?ip=".urlencode($ip)."&timestamp=".$timestamp."&signature=".urlencode($signature);
      $CFG->log("Updating dyndns by hiting ".$dns_url,0);
      $ok = trim(implode("",file($dns_url)));
      $CFG->log("Dyndns responded: ".$ok,0);
      if($ok=="ok"){
        $my_ip = $ip;
      }
    }
    else { $CFG->log("it was already updated",0);} 
  }else { $CFG->log("the ip is empty, may be some network problem? if this is not a network problem investigate the ".$ip_url,0);}
  $CFG->log("Sleep: ".$sleep."sec",0);
  sleep($sleep);  
}
