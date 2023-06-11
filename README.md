# Dispensador de comida dependiente

Proyecto casero destinado a generar un dispensador de comida con un ESP32 pero con la necesidad de que un agente externo (vía MQTT) nos indique cuando se debe dispensar.

La idea es que un algoritmo externo (por ejemplo NodeRed) nos indique a través de un mensaje MQTT cuando es la [próxima comida](https://es.wikipedia.org/wiki/Marca_temporal), el nº de dosis que debemos dosificar y la duración de cada dosis.
***

## Funcionamiento del dispensador

Nada más encenderse, el dispensador se conecta a una conexión WiFi y a un servidor MQTT. Posteriormente se suscribe al topic `/taixmiguel/pets/automaticDispenser_<id device>/state` donde espera un payload como el siguiente:
```
{
    "nextEatTime": 1672531200,
    "nextEatDoses": 2,
    "timeDoses": 1000
}
```
* `nextEatTime` se corresponde con una marca temporal que indica la próxima comida.
* `nextEatDoses` se corresponde con el nº de dosis que se tienen que dispensar.
* `timeDoses` es la duración (en milisegundos) de una dosis.
