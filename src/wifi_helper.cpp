#include "wifi_helper.h"
#include "secrets.h"

namespace WifiHelper
{
    /* Your WiFi Credentials */
    const char *ssid = WIFI_USER;       // SSID
    const char *password = WIFI_PWD; // Password

    void WiFiGotIP(WiFiEvent_t event, WiFiEventInfo_t info)
    {
    } // void WiFiGotIP(WiFiEvent_t event, WiFiEventInfo_t info)

    void setupWiFi()
    {
        // Connect WiFi
        debugpln("---------- Start WiFi Connect ----------");
        //LcdDisplay::drawWiFiSignal(0);

        // Auto reconnect is set true as default
        // To set auto connect off, use the following function
        WiFi.setAutoReconnect(true);

        WiFi.onEvent(WiFiEvent);
        WiFi.onEvent(WiFiGotIP, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_GOT_IP);
        WiFi.onEvent(WiFiStationDisconnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED);

        debugpln(F("Connect to WiFi"));

        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid, password);
        if (WiFi.waitForConnectResult() != WL_CONNECTED)
        {
            debugpln("WiFi Failed!\n");
            return;
        }
        // debugp("IP Address: ");
        // debugpln(WiFi.localIP());
        // debugp("RRSI: ");
        // debugpln(WiFi.RSSI());
        debugpln("---------- End WiFi Connect ----------");

    } // void setupWiFi()

    void wifiInfo()
    {
        debugp("Is Connected: ");
        debugpln(WiFi.isConnected());
        debugp("Local IP: ");
        debugpln(WiFi.localIP());
        debugp("MAC Address: ");
        debugpln(WiFi.macAddress());
        debugp("Network ID: ");
        debugpln(WiFi.networkID());
        debugp("Get Sleep: ");
        debugpln(WiFi.getSleep());
        debugp("Get Status Bits: ");
        debugpln(WiFi.getStatusBits());
        debugp("getTxPower:");
        debugpln(WiFi.getTxPower());
        debugp("Get Auto Reconnect: ");
        debugpln(WiFi.getAutoReconnect());
        debugp("Get Mode: ");
        debugpln(WiFi.getMode());
        debugp("Get Host Name: ");
        debugpln(WiFi.getHostname());
        debugp("Gateway IP: ");
        debugpln(WiFi.gatewayIP());
        debugp("DNS IP: ");
        debugpln(WiFi.dnsIP());
        debugp("WiFi Status: ");
        debugpln(WiFi.status());
    } // void wifiInfo()

    void ScanWiFINetworks()
    {
        debugpln("Scan start");

        // WiFi.scanNetworks will return the number of networks found.
        int n = WiFi.scanNetworks();
        debugpln("Scan done");
        if (n == 0)
        {
            debugpln("no networks found");
        }
        else
        {
            debugp(n);
            debugpln(" networks found");
            debugpln("Nr | SSID | RSSI | CH | Encryption");
            for (int i = 0; i < n; ++i)
            {
                // Print SSID and RSSI for each network found
                debugpf("%2d", i + 1);
                debugp(" | ");
                debugpf("%-32.32s", WiFi.SSID(i).c_str());
                debugp(" | ");
                debugpf("%4d", WiFi.RSSI(i));
                debugp(" | ");
                debugpf("%2d", WiFi.channel(i));
                debugp(" | ");
                switch (WiFi.encryptionType(i))
                {
                case WIFI_AUTH_OPEN:
                    debugp("open");
                    break;
                case WIFI_AUTH_WEP:
                    debugp("WEP");
                    break;
                case WIFI_AUTH_WPA_PSK:
                    debugp("WPA");
                    break;
                case WIFI_AUTH_WPA2_PSK:
                    debugp("WPA2");
                    break;
                case WIFI_AUTH_WPA_WPA2_PSK:
                    debugp("WPA+WPA2");
                    break;
                case WIFI_AUTH_WPA2_ENTERPRISE:
                    debugp("WPA2-EAP");
                    break;
                case WIFI_AUTH_WPA3_PSK:
                    debugp("WPA3");
                    break;
                case WIFI_AUTH_WPA2_WPA3_PSK:
                    debugp("WPA2+WPA3");
                    break;
                case WIFI_AUTH_WAPI_PSK:
                    debugp("WAPI");
                    break;
                default:
                    debugp("unknown");
                }
                debugpln();
                delay(10);
            }
        }
    } // void ScanWiFINetworks()

    void WiFiEvent(WiFiEvent_t event)
    {
        //debugpf("[WiFi-event] event: %d\n", event);

        switch (event)
        {
        case ARDUINO_EVENT_WIFI_READY:
            debugpln("WiFi interface ready");
            break;
        case ARDUINO_EVENT_WIFI_SCAN_DONE:
            debugpln("Completed scan for access points");
            break;
        case ARDUINO_EVENT_WIFI_STA_START:
            debugpln("WiFi client started");
            break;
        case ARDUINO_EVENT_WIFI_STA_STOP:
            debugpln("WiFi clients stopped");
            break;
        case ARDUINO_EVENT_WIFI_STA_CONNECTED:
            debugpln("Connected to access point");
            break;
        case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
            debugpln("Disconnected from WiFi access point");
            break;
        case ARDUINO_EVENT_WIFI_STA_AUTHMODE_CHANGE:
            debugpln("Authentication mode of access point has changed");
            break;
        case ARDUINO_EVENT_WIFI_STA_GOT_IP:
            debugp("Obtained IP address: ");
            debugpln(WiFi.localIP());
            debugp("WiFi Signal Strength: ");
            debugpln(WiFi.RSSI());
            //LcdDisplay::drawWiFiSignal(WiFi.RSSI());

            break;
        case ARDUINO_EVENT_WIFI_STA_LOST_IP:
            debugpln("Lost IP address and IP address is reset to 0");
            break;
        case ARDUINO_EVENT_WPS_ER_SUCCESS:
            debugpln("WiFi Protected Setup (WPS): succeeded in enrollee mode");
            break;
        case ARDUINO_EVENT_WPS_ER_FAILED:
            debugpln("WiFi Protected Setup (WPS): failed in enrollee mode");
            break;
        case ARDUINO_EVENT_WPS_ER_TIMEOUT:
            debugpln("WiFi Protected Setup (WPS): timeout in enrollee mode");
            break;
        case ARDUINO_EVENT_WPS_ER_PIN:
            debugpln("WiFi Protected Setup (WPS): pin code in enrollee mode");
            break;
        case ARDUINO_EVENT_WIFI_AP_START:
            debugpln("WiFi access point started");
            break;
        case ARDUINO_EVENT_WIFI_AP_STOP:
            debugpln("WiFi access point  stopped");
            break;
        case ARDUINO_EVENT_WIFI_AP_STACONNECTED:
            debugpln("Client connected");
            break;
        case ARDUINO_EVENT_WIFI_AP_STADISCONNECTED:
            debugpln("Client disconnected");
            break;
        case ARDUINO_EVENT_WIFI_AP_STAIPASSIGNED:
            debugpln("Assigned IP address to client");
            break;
        case ARDUINO_EVENT_WIFI_AP_PROBEREQRECVED:
            debugpln("Received probe request");
            break;
        case ARDUINO_EVENT_WIFI_AP_GOT_IP6:
            debugpln("AP IPv6 is preferred");
            break;
        case ARDUINO_EVENT_WIFI_STA_GOT_IP6:
            debugpln("STA IPv6 is preferred");
            break;
        case ARDUINO_EVENT_ETH_GOT_IP6:
            debugpln("Ethernet IPv6 is preferred");
            break;
        case ARDUINO_EVENT_ETH_START:
            debugpln("Ethernet started");
            break;
        case ARDUINO_EVENT_ETH_STOP:
            debugpln("Ethernet stopped");
            break;
        case ARDUINO_EVENT_ETH_CONNECTED:
            debugpln("Ethernet connected");
            break;
        case ARDUINO_EVENT_ETH_DISCONNECTED:
            debugpln("Ethernet disconnected");
            break;
        case ARDUINO_EVENT_ETH_GOT_IP:
            debugpln("Obtained IP address");
            break;
        default:
            break;
        }
    } // void WiFiEvent(WiFiEvent_t event)

    void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info)
    {
        debugpln("Disconnected from WiFi access point");
        debugp("WiFi lost connection. Reason: ");
        debugpln(info.wifi_sta_disconnected.reason);
        debugpln("Trying to Reconnect");
        //WiFi.begin(ssid, password);
        //LcdDisplay::drawWiFiSignal(WiFi.RSSI());
    } // void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info)


} // namespace WifiHelper