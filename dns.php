<?php
/**
 * On the external server, a Domain Name System (named-bind) allows updates 
 * from localhost for configured zones (domains). Additionally, the external 
 * server has an Apache web server with PHP that serves URIs ip.php and dns.php. 
 * The ip.php script returns the IP of the request, while dns.php (this script) 
 * accepts a parameter named 'ip' in the request. It checks the value of the 
 * 'ip' parameter with the request's IP and, based on the configuration stored 
 * in $CFG->zones (defined in the conf/zones.ini file), creates a text file with 
 * appropriate nsupdate commands and executes the nsupdate command with the 
 * argument being that file.
 * 
 */
include_once("common.inc");
if(Common::ie("ip",$_REQUEST)==Common::ie("REMOTE_ADDR",$_SERVER)){
  $ip = Common::ie("ip",$_REQUEST);
  $timestamp = Common::ie("timestamp",$_REQUEST);
  $signature = Common::ie("signature",$_REQUEST);
  
  if((time() - $timestamp)>3610) {
    header('HTTP/1.1 401 Unauthorized');
    die('Invalid timestamp');
  }

  $signature_expected = base64_encode(hash_hmac('sha256', $timestamp.$ip, $CFG->privateKey, true));
  
  if (!hash_equals($signature, $signature_expected)) {
    header('HTTP/1.1 401 Unauthorized');
    die('Invalid signature');
  }

  $dir = $CFG->real_path."/tmp/";
  $filename = "nsupdate";
  $handle = fopen($dir.$filename,"w");
  if (!$handle) { print "Can't open ".$dir.$filename.""; }
  else {
    $data = "server localhost\n";
    $data .= "debug true\n";
    foreach($CFG->zones AS $key=>$zone){
      $domain = Common::ie("domain", $zone, $key);
      if($domain!=""){
        $data .= "zone ".$domain.".\n";
        foreach(Common::ie("subdomains", $zone, array()) AS $subdomain){
          $data .= "update delete ".$subdomain.".".$domain.". A\n";
          $data .= "update add ".$subdomain.".".$domain.". 300 IN A ".$ip."\n";
        }
        if(Common::ie("setDomain", $zone)=="true"){
          $data .= "update delete ".$domain.". A\n";
          $data .= "update add ".$domain.". 300 IN A ".$ip."\n";
        }
        $data .= "send\n";
      } 
    }

    if (fwrite($handle, $data) === false) { die("Can't write ".$dir.$filename."");  }
    else {
      $command = $CFG->nsupdate." -v ".$dir.$filename;
      $CFG->log("executing commmand: ".$command,0);
      $response = "";
      $fp = popen($command, "r");
      while(!feof($fp)) {
        $response .= fread($fp, 1024); 
      }
      fclose($fp);
      $CFG->log("nsupdate responded ".$response,0);
      //Handle the response, i.e., catch the error response or success
      if(preg_match("/status: NOERROR/", $response))
        print "ok";
      else 
        print "Nok. ".$response;
    }
  }
}