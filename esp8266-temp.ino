#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <PubSubClient.h>

#define max_sleep_us 900000000ul        //15 * 60 * 1000000
#define max_wifi_cycles 16
#define max_read_cycles 10

#define wifi_ssid "wifi-ssid"
#define wifi_pass "wifi-pass"

#define mqtt_user "mqtt-user"
#define mqtt_pass "mqtt-pass"

const IPAddress ip(192,168,20,61);
const IPAddress gateway(192,168,20,1);
const IPAddress subnet(255,255,255,0);

const IPAddress mqtt_ip(192,168,10,1);
const int mqtt_port = 1883;

ADC_MODE(ADC_VCC);

void do_sleep(void)
{
    WiFi.disconnect(true);
    delay(10);

    ESP.deepSleep(max_sleep_us, WAKE_RF_DEFAULT);
    delay(1000);
}

float read_temperature(void)
{
    OneWire onewire(D1);
    DallasTemperature ds18b20(&onewire);

    float temperature;

    for (uint8_t attempt = 0; attempt < max_read_cycles; attempt++)
    {
        ds18b20.requestTemperatures();
        temperature = ds18b20.getTempCByIndex(0);

        if (temperature == 85.0 || temperature == (-127.0))
            delay(10);
        else
            break;
    }

    return temperature;
}

void pub_temperature(void)
{
    WiFiClient wifi_client;
    PubSubClient mqtt_client(mqtt_ip, mqtt_port, wifi_client);

    char mqtt_name[] = "iot-000";
    uint8_t client_id = WiFi.localIP()[3];
    uint16_t vcc = ESP.getVcc();

    sprintf(mqtt_name, "iot-%d", client_id);

    pinMode(D2, OUTPUT);
    digitalWrite(D2, HIGH);

    if (mqtt_client.connect(mqtt_name, mqtt_user, mqtt_pass))
    {
        char topic[64];
        char payload[20];

        sprintf(topic, "/state/iot/sensor/%d/temp_C", client_id);
        sprintf(payload, "%1.2f", read_temperature());
        mqtt_client.publish(topic, payload, true);

        sprintf(topic, "/state/iot/sensor/%d/voltage", client_id);
        sprintf(payload, "%1.2f", vcc / 1024.0f);
        mqtt_client.publish(topic, payload, true);

        sprintf(topic, "/state/iot/sensor/%d/millis", client_id);
        sprintf(payload, "%lu", millis());
        mqtt_client.publish(topic, payload, true);

        delay(750);
        mqtt_client.disconnect();
    }
}


void setup_wifi(void)
{
    uint8_t attempt = 0;

    delay(10);
    WiFi.persistent(false);
    WiFi.mode(WIFI_STA);
    WiFi.config(ip, gateway, subnet);
    WiFi.begin(wifi_ssid, wifi_pass);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);

        if (++attempt > max_wifi_cycles)
            do_sleep();
    }
}

void setup(void)
{
    setup_wifi();
    pub_temperature();
}

void loop(void)
{
    do_sleep();
}
