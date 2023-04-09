<?php
#[AllowDynamicProperties]
class _generic {
  public $debug = true;
  public $debug_level = 2;
  public $cache = false;
  public $error_messages= array();
  
  function __construct(){
  }
  function log($value,$debug_level=0){
    if($this->debug_level>=$debug_level){
      if(!$this->write_log($value)){
        list($usec, $sec) = explode(" ", microtime());
        date_default_timezone_set('Europe/Athens');
        print date("Y-m-d H:i:s").".".$usec." ".getmypid()." ".$value."\n";
      }
    }
  }
  function write_log($message_to_log){
    if(isset($this->logger) and is_object($this->logger) and ($this->logger instanceof __log)){
      $this->logger->set_what(getmypid()." ".$message_to_log);
      return $this->logger->save_append();   
    }
    $this->error_messages[] = $this->pfl(__FILE__,__LINE__,__FUNCTION__,__CLASS__)." No logger is set, so cannot write the message_to_log: ".$message_to_log;
    return false;
  }
  function write_debug_log($message_to_log){
    if($this->debug===true){
      return $this->write_log($message_to_log);
    }
    return true;
  }  
  function print_message($message, $debug_message=""){
    print $message;
    if($this->debug===true){
      print "<pre>".$debug_message."</pre>";
    }
  }
  /*
   * prefix for logger. componets a standart prefix for looger
   * 
   * $file string
   * $line int
   * $function string
   * $class string
   * return string the prefix used for logger
   */
  function pfl($file, $line, $function="", $class=""){
    if(isset($this->PHP_DIR)){
      $file =  preg_replace("@".$this->PHP_DIR."/@","",$file);
    }
    return $file.(($class!="")?" ".$class."->":"").(($function!="")?(($class=="")?" ":"").$function."()":"")."[".$line."]:";  
  }
  function cacheget($name, $cache_time_sec=0, $prefix_for_logger=""){
    if(ie("cache", $this, false) and $cache_time_sec>0){
      if(file_exists($this->tmp_dir."/cache/".$name)){
        $this->log($prefix_for_logger." ".$this->pfl(__FILE__,__LINE__,__FUNCTION__,__CLASS__).": ".$cache, 2);
        if(filemtime($this->tmp_dir."/cache/".$name)>(time()-$cache_time_sec)){
          include_once($this->tmp_dir."/cache/".$name);
          return true;
        }
      }
    }
    return false;  
  }
  function cacheit($name, $data, $cache_time_sec=0){
    if(ie("cache", $this, false) and $cache_time_sec>0){
//This file is query cache for the query ".$hole_query." its cache time is ".$cache_time_sec."sec
      $towrite = "<?php
/**
* This file is generic cache, its cache time is ".$cache_time_sec."sec
* Cached on ".date("Y-m-d H:i:s")."
*/
?>
".$data."
";
      include_once("common/Saver.inc");
      Saver::write_to_file($this->tmp_dir."/cache/",$name, $towrite); 
    }
  }
}
