<?php
class getLightingStatus {
  public $DeviceID; // int
}

class getLightingStatusResponse {
  public $DeviceID; // int
  public $State; // string
  public $Dim; // int
}

class setLightingStatus {
  public $DeviceID; // int
  public $State; // string
  public $Dim; // int
}

class setLightingStatusResponse {
  public $DeviceID; // int
  public $State; // string
  public $Dim; // int
}

class initDevice {
  public $DeviceID; // int
  public $Order; // string
}

class initDeviceResponse {
  public $DeviceID; // int
  public $Order; // string
}


/**
 * mydombox class
 * 
 *  
 * 
 * @author    {author}
 * @copyright {copyright}
 * @package   {package}
 */
class mydombox extends SoapClient {

  private static $classmap = array(
                                    'getLightingStatus' => 'getLightingStatus',
                                    'getLightingStatusResponse' => 'getLightingStatusResponse',
                                    'setLightingStatus' => 'setLightingStatus',
                                    'setLightingStatusResponse' => 'setLightingStatusResponse',
                                    'initDevice' => 'initDevice',
                                    'initDeviceResponse' => 'initDeviceResponse',
                                   );

	public function mydombox($wsdl = "../inc/mydombox-2.0.wsdl", $options = array("location" => "http://192.168.64.15:8888/")) {
	//public function mydombox($wsdl = "../inc/mydombox-2.0.wsdl", $options = array("location" => "http://localhost:8888/")) {
    //public function mydombox($wsdl = "../inc/mydombox-2.0.wsdl", $options = array("location" => "http://localhost:8088/mockmydombox")) {
	foreach(self::$classmap as $key => $value) {
      if(!isset($options['classmap'][$key])) {
        $options['classmap'][$key] = $value;
      }
    }
    parent::__construct($wsdl, $options);
  }

  /**
   *  
   *
   * @param getLightingStatus $parameters
   * @return getLightingStatusResponse
   */
  public function getLightingStatus(getLightingStatus $parameters) {
    return $this->__soapCall('getLightingStatus', array($parameters),       array(
            'uri' => 'http://mydombox.com/mydombox/',
            'soapaction' => ''
           )
      );
  }

  /**
   *  
   *
   * @param setLightingStatus $parameters
   * @return setLightingStatusResponse
   */
  public function setLightingStatus(setLightingStatus $parameters) {
    return $this->__soapCall('setLightingStatus', array($parameters),       array(
            'uri' => 'http://mydombox.com/mydombox/',
            'soapaction' => ''
           )
      );
  }

  /**
   *  
   *
   * @param initDevice $parameters
   * @return initDeviceResponse
   */
  public function initDevice(initDevice $parameters) {
    return $this->__soapCall('initDevice', array($parameters),       array(
            'uri' => 'http://mydombox.com/mydombox/',
            'soapaction' => ''
           )
      );
  }

}

?>
