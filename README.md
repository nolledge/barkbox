# Barkbox

A small ioT project to log and cope with the barking of my dog when she is alone.


## Setup

This projece uses an ESP8266 NodeMCU microcontroller with WIFI capabilities and a KY-037 sound detection sensor module
to detect barking and to send it to an Eclipse Mosquitto (MQTT message broker) instance that runs on a server alongside an influxdb.

