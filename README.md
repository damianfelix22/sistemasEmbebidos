# Sistemas Embebidos 2022 - Proyecto Final
Este proyecto se trató sobre la automatización  mediante el protocolo de comunicación MQTT, utilizando una Raspberry Pi como broker MQTT y dos microcontroladores llamados ESP32 distribuidos que actuarian como clientes.
En la Raspberry Pi se ejecuta el bróker MQTT Mosquitto usado para la comunicación con  los diferentes microcontroladores donde se adquiere las señales de los diferentes sensores conectados a estos y Node-Red para enlazar y programar las acciones.

## Rama ESP32-1
Cuenta con un Sensor DHT22 que mide la temperatura y la humedad que es mostrada por la pantalla oled. A su vez estos valores de temperatura y humedad son publicados a través de MQTT al bróker para que los clientes suscriptos al tópico reciban esos valores.

## Rama ESP32-1
Tiene un módulo LDR que de acuerdo a la luz que incida prende o apaga un LED. Tambien cuenta con un módulo RGB que a través de node-Red con el nodo colour picker elegimos el color y éste le pasa al módulo RGB los parámetros para realizar la mezcla.
