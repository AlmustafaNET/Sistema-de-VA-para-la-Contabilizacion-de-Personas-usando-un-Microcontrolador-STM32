# Sistema de Visión Artificial para la Contabilización de Personas usando un Microcontrolador STM32

El siguiente código pertenece al Trabajo de Fin de Máster (TFM), realizado para el Máster en Inteligencia Artificial de la **Universidad Internacional de La Rioja (UNIR)**.

*Realizado por:*  **Dany López. 2019**

##  Contenido:

-  **TestImagenComputador**:  Programa que se conecta a la tarjeta electrónica por medio de la Red Ethernet, para leer el correcto funcionamiento de la imagen adquirida.

> Compilación:  Linux x64 Bits , Qt  5.12

> $ qmake

> $ make 

> $ ./TestImagenComputador

-  **ContadorPersonas**: Programa desarrollado en lenguaje C. Lee el archivo "videos/personas001.mp4" y procesa el archivo con el algoritmo de detección de personas. En el archivo "videos/output.mp4" se puede ver la salida del programa contando las personas que pasan.
> Compilación: Linux x64 Bits, CMake v2.8. Utiliza Opencv v4.1.0

> $ cmake --build . --target all 

> $ ./ContadorPersonas

- **STM32/ContadorPersonas**: Programa escrito en lenguaje C para el microcontrolador. Se utiliza una tarjeta de desarrollo *STM32 NUCLEO-F767ZI*. 
> Archivo de configuración STM32CubeMX v5.0:  ContadorPersonas.ioc

> IDE de Programación: Atollic TrueSTUDIO® for STM32 9.3

- **InterfazCamara**: Proyecto entero realizado en KiCAD para la elaboración de la tarjeta electrónica que sirve como interfaz entre la cámara *OV7670* y el *STM32 NUCLEO-F767ZI*. Este pryecto, incluye el esquemático, PCB y los archivos GERBER.
