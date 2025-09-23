#if !defined(WIFI_HELPER)
#define WIFI_HELPER

#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiClient.h>
#include <HTTPClient.h>

#include "globals.h"
//#include "timeHelper.h"
//#include "hardware.h"

namespace WifiHelper
{

    // Function Declaration
    void WiFiGotIP(WiFiEvent_t event, WiFiEventInfo_t info);
    void setupWiFi();
    void wifiInfo();
    void ScanWiFINetworks();
    void WiFiEvent(WiFiEvent_t event);
    void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info);


} // namespace WifiHelper

#endif // WIFI_HELPER
