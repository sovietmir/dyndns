<?php
/*
 *
 *
 */
date_default_timezone_set('Europe/Athens');
class __log {
  var $filename;
  var $dir;
  var $what; //what_to_log
  var $num_of_days_to_log;
  var $error_message;
  function __construct($dir="./tmp/",$filename="log.txt",$num_of_days_to_log=5){
    $this->set_filename($filename);
    $this->set_dir($dir);
    $this->set_what();
    $this->num_of_days_to_log = $num_of_days_to_log;
    $this->error_message="";
  }
  
  function get_filename(){return $this->filename;}
  function get_dir(){return $this->dir;}
  function get_what(){return $this->what;}
  function get_num_of_days_to_log(){return $this->num_of_days_to_log;}

  
  function set_filename($value){
    // na figoun oloi oi xaraktires ektos apo 0-9 kai latinikous
    $what_to_remove = "/[^0-9a-zA-Z.\ _]/i";
    $value = preg_replace($what_to_remove,"",$value);
    $trans = array(" " => "_", "-" => "_","\t"=>"_","\\"=>"_","\n"=>"_","'"=>"","\""=>"","\r"=>"_");
    $this->filename = strtr($value, $trans);
  }
  function set_dir($dir){
    $this->dir = "";
    if(!is_dir($dir)){
      if(!mkdir($dir)){
        $this->error_message = "Cannot create directory: ".$dir;
        return false;
      }
    }
    $this->dir = $dir;
    return true;
  }  
  function set_what($value=null){ // removes enters
    if($value===null){
      $this->what = "";
    }
    else {
      $trans = array("\n"=>" ","\r"=>" ");
      $this->what .= strtr($value, $trans);
    }
  }
  
  function get_date(){
    list($usec, $sec) = explode(" ", microtime());
    date_default_timezone_set('Europe/Athens');
    return date("Y-m-d H:i:s").".".$usec;
  }  
  function get_ip(){
    return (isset($_SERVER["REMOTE_ADDR"]))?$_SERVER["REMOTE_ADDR"]:"";
  }  
  function get_full_filename(){
    $filename = $this->dir.$this->filename;
    return $filename;
  }
  
  function maintain_logfile(){
    if($file = file($this->get_full_filename())){
      $log = array();
      foreach ($file as $i => $line){
        $tmp = explode(" ",trim($line),2);
        $log[$tmp[0]][] = trim($line);       
      }
      $log = array_slice($log,(count($log)-5),5);
      $to_save = array();
      foreach ($log as $value){
        foreach ($value as $v){
          $to_save[] = $v;    
        }
      }     
      $handle = @fopen($this->get_full_filename(), "w");
      fwrite($handle, implode("\n",$to_save)."\n");
      fclose($handle);    
    }
  }  
  
  function save_append(){
    if($this->get_what()!=""){
      $handle = @fopen($this->get_full_filename(), "a");
      if($handle){
    //  if(fwrite($handle, $this->get_date()."\t".$this->get_ip()."\t".$this->get_what()."\n")){
        if(fwrite($handle, $this->get_date()."\t".$this->get_what()."\n")){
          $this->set_what();
        }
        else {
          $this->error_message = "Cannot write into file ".$this->get_full_filename();
        }
        fclose($handle);
      }
      return true;
    }
    return false;
  }
}

?>