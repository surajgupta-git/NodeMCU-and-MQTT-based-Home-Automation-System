MQTT-web-client
======================

## A websockets based MQTT Client for your browser.

This client runs on any modern browser, which supports websockets.
You can use it to publish and subscribe at the same time.

See it in action at []()


## Localhost / Local network

You can also use this client to connect to a broker on your local machine ("localhost") or any machine in your local network which is reachable from the machine which your browser runs on.

## MQTT Broker

This web client works perfectly with the [HiveMQ MQTT broker](https://www.hivemq.com/hivemq/ "HiveMQ MQTT Broker") with enabled websockets.

If you don’t like to use a self hosted (or locally running) HiveMQ, you can use the [public MQTT broker](http://www.hivemq.com/showcase/public-mqtt-broker/ "Public MQTT Server") from the [MQTTDashboard](http://www.mqttdashboard.com/ "MQTT Dashboard").

* Host: **broker.mqttdashboard.com**
* Websockets port: **8000**

## Why another MQTT Client

We needed a quick and simple way to develop and test our applications which use MQTT over websockets, so we sat down for a few hours and built this client which also works for your local development machine.


