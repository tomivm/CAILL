# CAILL 
CAILL un sistema (software y hardware libre) de control de condiciones  en invernaderos/indoor capaz de adaptar un ambiente apto para cultivo de hortalizas, flores y plantas aromaticas. 
Consiste en crear un entorno para que una planta pueda desarrollarse de la manera más óptima usando las nuevas y viejas tecnoloogias. teniendo como trafondo formar una comunidad de cultivadores, tecnicos, profesores, biologos y la habilidad de todo aquel que quiera sumarse! se trata de compartir.


En Nuestra primera version, Hidroponica y wifi utilizamos una simple tarjeta NodeMcu programada en la ide de Arduino. Esta es nuestro cerebro  y tambien se encarga de la conexion wifi, lo unico que necesitamos para programarla es un micro usb.
 Los programas, placas y diagramas de conexion estan aqui. Un poco de efuerzo y colaboracion en equipo nos hara tener unos ricos frutos para compartir entre amigos y familia, Todo de autocultivo :).

Con un poco de ezfuerzo vamos a poder entender como conectar los modulos y hasta hacer las placas necesarias para adaptaciones y si no, por un poco de dinero te las enviamos.

interactuamos con CAILL mediante un menu de 3 botones y un display(OLED 64*128), en el podemos editar la etapa vigente, las horas de luz para cada etapa,cuantos riegos y de cuanto tiempo, T° y HR deseadas o seleccionar el perfil de la planta que queremos.Tambien podremos confijurar el reloj de tiempo real DS3231 que incluiremos para tener la hora correcta, sin importar los cortes de luz.

Para el manejo de la lampara, bomba de agua o cualquier otro dispositivo de corriente alterna, desarrollamos un controlador sin relays mecanicos para aumentar la vida util!

Controlamos la temperatura y humedad con un sensor DHT22 o DHT11 segun conveniencias u oportunidades del usuario. Dependiendo estos valores se controlara la velocidad de intraccion y extraccion de los coolers(Puedes editar los parametros deseados desde el menu) Estas mediciones pueden ser enviados al celular :).
