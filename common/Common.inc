<?php
ini_set('include_path',get_include_path().PATH_SEPARATOR .'../'.PATH_SEPARATOR .'../common/');
/**
 * @author Khusainov Iskander
 *
 */
class Common {
  /**
   * ie = if exists
   * @param unknown_type $what
   * @param unknown_type $from
   * @param unknown_type $default
   * @param unknown_type $pattern
   */
  public static function ie($what, $from=array(), $default="", $pattern="{value}"){ 
    $r = "";
    $value = $default;
    if(is_object($from) and isset($from->{$what})){
      if(is_string($from->{$what})) {
        if($from->{$what}!="") $value = $from->{$what};
      }
      else $value = $from->{$what};
      //$from = self::obj2array($from);
    }
    else if(is_array($from) and isset($from[$what])){
      if(is_string($from[$what])) {
        if($from[$what]!="") $value = $from[$what];
      }
      else $value = $from[$what];
    }
    if($value!="" and is_string($value)) $r = strtr($pattern,array("{value}"=>$value));
    else $r = $value;
    return $r;
  }
  /**
   * conver an object into array
   * @param object $obj
   * @return array()
   */
   public static function obj2array($obj) {
    $out = array();
    if(is_array($obj) or is_object($obj)){
      foreach ($obj as $key => $val) {
        switch(true) {
          case is_object($val): case is_array($val):
            $out[$key] = self::obj2array($val);
            break;
          default:
            $out[$key] = $val;
        }
      }
    }
    return $out;
  }
  /**
   * 
   * @return Ambigous <multitype:, multitype:NULL >
   */
  public static function myarray_merge(){
    $r = array();
    if(func_num_args()>=2){
      $a = func_get_arg(0);
      for($i=1; $i<func_num_args();$i++){
        $b = func_get_arg($i);
        $r = array_merge($a, $b);
        foreach ($a as $key => $value) {
          if(is_array($value) and is_array(ie($key,$b))){
            $r[$key] = self::myarray_merge($value, $b[$key]);
          }
        }
        $a = $r;
      }
    }
    return $r;
  }
  /**
   * query escape
   * @param string $value
   * @return string mysql escaped string
   */
  public static function qe($value){
    //  return mysql_escape_string(unescape($value))  ;
    //return mysql_escape_string($value);
    if(is_array($value)) 
      return array_map(__METHOD__, $value);
    
    if(!empty($value) && is_string($value)) { 
      return str_replace(array('\\', "\0", "\n", "\r", "'", '"', "\x1a"), array('\\\\', '\\0', '\\n', '\\r', "\\'", '\\"', '\\Z'), $value); 
    }
    return $value; 
  }
  /**
   * convert greek, cyrillic (russian) text into latin one
   * @param string $string
   * @return string
   */
  public static function to_latin($string){
    $trans = array(
        "Α" => "A","Ά" => "A","α" => "a","ά" => "a",
        "Β" => "V","β" => "v",
        "Γ" => "G","γ" => "g",
        "Δ" => "D","δ" => "d",
        "Ε" => "E","Έ" => "E","ε" => "e","έ" => "e",
        "Ζ" => "Z","ζ" => "z",
        "Η" => "I","Ή" => "I","η" => "i","ή" => "i",
        "Θ" => "Th","θ" => "th",
        "Ι" => "I","Ί" => "I","Ϊ" => "I","ι" => "i","ί" => "i","ϊ" => "i","ΐ" => "i",
        "Κ" => "K","κ" => "k",
        "Λ" => "L","λ" => "l",
        "Μ" => "M","μ" => "m",
        "Ν" => "N","ν" => "n",
        "Ξ" => "Ks","ξ" => "ks",
        "Ο" => "O","Ό" => "O","ο" => "o","ό" => "o",
        "Π" => "P","π" => "p",
        "Ρ" => "R","ρ" => "r",
        "Σ" => "S","σ" => "s","ς" => "s",
        "Τ" => "T","τ" => "t",
        "Υ" => "Y","Ύ" => "Y","Ϋ" => "Y","υ" => "y","ύ" => "y","ϋ" => "y","ΰ" => "y",
        "Φ" => "F","φ" => "f",
        "Χ" => "X","χ" => "x",
        "Ψ" => "Ps","ψ" => "ps",
        "Ω" => "W","Ώ" => "W","ω" => "w","ώ" => "w"
    );
    $string = strtr($string, $trans);
    $trans = array(
        "А" => "A","а" => "a",
        "Б" => "B","б" => "b",
        "В" => "V","в" => "v",
        "Г" => "G","г" => "g",
        "Д" => "D","д" => "d",
        "Е" => "E","е" => "e",
        "Ё" => "Jo","ё" => "jo",
        "Ж" => "Zh","ж" => "zh",
        "З" => "Z","з" => "z",
        "И" => "I","и" => "i",
        "Й" => "J","й" => "j",
        "К" => "K","к" => "k",
        "Л" => "L","л" => "l",
        "М" => "M","м" => "m",
        "Н" => "N","н" => "n",
        "О" => "O","о" => "o",
        "П" => "P","п" => "p",
        "Р" => "R","р" => "r",
        "С" => "S","с" => "s",
        "Т" => "T","т" => "t",
        "У" => "U","у" => "u",
        "Ф" => "F","ф" => "f",
        "Х" => "X","х" => "x",
        "Ц" => "C","ц" => "c",
        "Ч" => "Ch","ч" => "ch",
        "Ш" => "Sh","ш" => "sh",
        "Щ" => "Shch","щ" => "shch",
        "Ъ" => "`","ъ" => "`",
        "Ы" => "Y","ы" => "y",
        "Ь" => "'","ь" => "'",
        "Э" => "Eh","э" => "eh",
        "Ю" => "Ju","ю" => "ju",
        "Я" => "Ja","я" => "ja",
    );
    $string = strtr($string, $trans);
    return $string;
  }
  
  public static function strip_html($document){
    $search = array (
      "'<script[^>]*?>.*?</script>'si",  // Strip out javascript
      "'<style[^>]*?>.*?</style>'si",  // Strip out style
      "'<[\/\!]*?[^<>]*?>'si",  // Strip out html tags
      "'([\r\n])[\s]+'",  // Strip out white space
      "'&(quot|#34);'i",  // Replace html entities
      "'&(amp|#38);'i",
      "'&(lt|#60);'i",
      "'&(gt|#62);'i",
      "'&(nbsp|#160);'i",
      "'&(iexcl|#161);'i",
      "'&(cent|#162);'i",
      "'&(pound|#163);'i",
      "'&(copy|#169);'i"
      //"'&#(\d+);'e" // evaluate as phpnull
    );
    $replace = array (
      "",
      "",
      "",
      "\\1",
      "\"",
      "&",
      "<",
      ">",
      " ",
      chr(161),
      chr(162),
      chr(163),
      chr(169),
      "chr(\\1)"
    );
    $text = preg_replace ($search, $replace, $document);
    return $text;
  }
  
  public static function hex2rgb($color){ //color is like #ffffff
  	$r = array("r"=>0,"g"=>0,"b"=>0);
  	// $hexcode is the six digit hex colour code we want to convert
  	$r["r"] = hexdec(substr($color,1,2));
  	$r["g"] = hexdec(substr($color,3,2));
  	$r["b"] = hexdec(substr($color,5,2));
  	return $r;
  }
  public static function rgb2hex($color){ //color is like array("r"=>0,"g"=>0,"b"=>0);
  	return "#".sprintf("%02X",round($color["r"])).sprintf("%02X",round($color["g"])).sprintf("%02X",round($color["b"]));
  }
  public static function rgb2hsl($color){ //color is like #ffffff
  	$r = array("h"=>0,"s"=>0,"l"=>0);
  	$rgb = self::hex2rgb($color);
  	$rgb["r"] = $rgb["r"]/255;
  	$rgb["g"] = $rgb["g"]/255;
  	$rgb["b"] = $rgb["b"]/255;
  
  	$var_min = min($rgb["r"],$rgb["g"],$rgb["b"]);
  	$var_max = max($rgb["r"],$rgb["g"],$rgb["b"]);
  	$del_max = $var_max - $var_min;
  
  	$r["l"] = ($var_max + $var_min) / 2;
  	if ($del_max == 0) {
  		$r["h"] = 0;
  		$r["s"] = 0;
  	}
  	else {
  		if ($r["l"] < 0.5) $r["s"] = $del_max / ($var_max + $var_min);
  		else $r["s"] = $del_max / (2 - $var_max - $var_min);
  		$del_r = ((($var_max - $rgb["r"]) / 6) + ($del_max / 2)) / $del_max;
  		$del_g = ((($var_max - $rgb["g"]) / 6) + ($del_max / 2)) / $del_max;
  		$del_b = ((($var_max - $rgb["b"]) / 6) + ($del_max / 2)) / $del_max;
  		if ($rgb["r"] == $var_max) $r["h"]= $del_b - $del_g;
  		elseif ($rgb["g"] == $var_max) $r["h"] = (1 / 3) + $del_r - $del_b;
  		elseif ($rgb["b"] == $var_max) $r["h"] = (2 / 3) + $del_g - $del_r;
  
  		if ($r["h"] < 0) $r["h"] += 1;
  		if ($h > 1) $r["h"] -= 1;
  	}
  	return $r;
  }
  public static function hsl2rgb($hsl){ //$hsl is like array("h"=>0,"s"=>0,"l"=>0);
  	$r = array("r"=>0,"g"=>0,"b"=>0);
  	if ($hsl["s"] == 0) {
  		$r["r"] = $hsl["l"] * 255;
  		$r["g"] = $hsl["l"] * 255;
  		$r["b"] = $hsl["l"] * 255;
  	}
  	else {
  		if ($hsl["l"] < 0.5) $var_2 = $hsl["l"] * (1 + $hsl["s"]);
  		else $var_2 = ($hsl["l"] + $hsl["s"]) - ($hsl["s"] * $hsl["l"]);
  
  		$var_1 = 2 * $hsl["l"] - $var_2;
  		$r["r"] = 255 * self::hue_2_rgb($var_1,$var_2,$hsl["h"] + (1 / 3));
  		$r["g"] = 255 * self::hue_2_rgb($var_1,$var_2,$hsl["h"]);
  		$r["b"] = 255 * self::hue_2_rgb($var_1,$var_2,$hsl["h"] - (1 / 3));
  	}
  	return rgb2hex($r);
  }
  public static function hue_2_rgb($v1,$v2,$vh) {
  	if ($vh < 0) $vh += 1;
  	if ($vh > 1) $vh -= 1;
  	if ((6 * $vh) < 1) return ($v1 + ($v2 - $v1) * 6 * $vh);
  	if ((2 * $vh) < 1) return ($v2);
  	if ((3 * $vh) < 2) return ($v1 + ($v2 - $v1) * ((2 / 3 - $vh) * 6));
  	return ($v1);
  }

  /**
   * translate date (from english) into gl locale
   *   currently support greek 
   * 
   * @param string $text
   * @param lang code $gl can be el
   * @param boolean $monthOnomastiki onomastiki ptosi for the month, default is geniki
   */
  public static function localeDate($text, $gl, $monthOnomastiki=false){
    if($gl=="el"){
      $map = array(
        "January"=>($monthOnomastiki)?"Ιανουάριος":"Ιανουαρίου",
        "February"=>($monthOnomastiki)?"Φεβρουάριος":"Φεβρουαρίου",
        "March"=>($monthOnomastiki)?"Μάρτιος":"Μαρτίου",
        "April"=>($monthOnomastiki)?"Απρίλιος":"Απριλίου",
        "May"=>($monthOnomastiki)?"Μάϊος":"Μαΐου",
        "June"=>($monthOnomastiki)?"Ιούνιος":"Ιουνίου",
        "July"=>($monthOnomastiki)?"Ιούλιος":"Ιουλίου",
        "August"=>($monthOnomastiki)?"Αύγουστος":"Αυγούστου",
        "September"=>($monthOnomastiki)?"Σεπτέμβριος":"Σεπτεμβρίου",
        "October"=>($monthOnomastiki)?"Οκτώβριος":"Οκτωβρίου",
        "November"=>($monthOnomastiki)?"Νοέμβριος":"Νοεμβρίου",
        "December"=>($monthOnomastiki)?"Δεκέμβριος":"Δεκεμβρίου",
          
        "Monday"=>"Δευτέρα",
        "Tuesday"=>"Τρίτη",
        "Wednesday"=>"Τετάρτη",
        "Thursday"=>"Πέμπτη",
        "Friday"=>"Παρασκευή",
        "Saturday"=>"Σάββατο",
        "Sunday"=>"Κυριακή"
      );
      $text = strtr($text, $map);
    }
    return $text;
  }
  
  /**
   * Null coalescing (in php version >7 it can be implemented with conditional assignment pperator: ??)
   * @param unknown $input
   * @param unknown $default
   */
  public static function nc($input, $default=""){
    return isset($input) ? $input : $default;
  }
}




/**
 * Functions Aliases 
 */

function ie($what, $from=array(), $default="", $pattern="{value}") {
  return Common::ie($what, $from, $default, $pattern);
}
function obj2array($obj) {
  return Common::obj2array($obj);
}
function qe($value) {
  return Common::qe($value);
}
function to_latin($string) {
  return Common::to_latin($string);
}
