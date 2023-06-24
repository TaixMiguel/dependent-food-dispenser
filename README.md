# Dispensador de comida dependiente

Proyecto casero destinado a generar un dispensador de comida con un ESP32, pero con la necesidad de que un agente externo (vía MQTT) nos indique cuando se debe dispensar.

La idea es que un algoritmo externo (programado por ejemplo en NodeRed) nos indique a través de un mensaje MQTT cuando es la [próxima comida](https://es.wikipedia.org/wiki/Marca_temporal), el n.º de dosis que debemos dosificar y la duración de cada dosis.
***

## Funcionamiento del dispensador

Nada más encenderse, el dispensador se conecta a una conexión WiFi y a un servidor MQTT. Posteriormente, se suscribe al topic `/taixmiguel/pets/automaticDispenser_<id device>/state` donde espera un payload como el siguiente:
```
{
    "nextEatTime": 1672531200,
    "nextEatDoses": 2,
    "timeDoses": 1000
}
```
* `nextEatTime` se corresponde con una marca temporal que indica la próxima comida.
* `nextEatDoses` se corresponde con el n.º de dosis que se tienen que dispensar.
* `timeDoses` es la duración (en milisegundos) de una dosis.

Para el caso en el que no se haya definido la variable asociada al pin del motor, el dispositivo se reinicia.

## Configuración del dispositivo (Preferences)
* `wifi_ssid` y `wifi_pass` almacenan el SSID y la contraseña del router WiFi al que se conecta el dispositivo.
* `mqtt_server` establece la IP del servidor MQTT. `mqtt_client`, `mqtt_user` y `mqtt_pass` establecen la configuración asociada al cliente y usuario del servidor MQTT. El puerto preestablecido es el 1883.
* `pin_dispenser_motor` almacena el identificador del pin asociado al motor encargado de dispensar comida.
* `sw_battery` activa el control de una batería externa y `pin_battery` especifica el pin asociado a la batería.
***

## Próximas funcionalidades
### Release 0.1.0 (fecha no confirmada)
* Aviso MQTT cuando la comida sea dispensada.
* Despliegue automático de la versión a través de CI.
### Release 0.1.1 (fecha no confirmada)
* Control de no inicio cuando no se puede conectar con el servidor MQTT, similar al control cuando no se ha parametrizado el pin del motor.
### Release 0.2.0 (fecha no confirmada)
* Integración con Home Assistant.
* Actualización automática vía OTA.
