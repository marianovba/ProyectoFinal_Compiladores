# Compilador de Transformación Musical Basado en Sonic Pi [Rocky Pi]

## Resumen
- Este proyecto tiene como objetivo desarrollar un compilador que transforme música de un género a otro utilizando Sonic Pi. La   relevancia de este compilador radica en su capacidad de automatizar el proceso de conversión musical, permitiendo a los usuarios generar variaciones estilísticas de piezas musicales.

## Motivación y Problema a Resolver
- **Descripción del problema:** La transformación de música entre géneros es un proceso manual complejo y subjetivo. Este compilador busca sistematizar la interpretación musical a través de reglas formales, generando nuevas versiones musicales basadas en características definidas.
- **Importancia:** La automatización de la conversión entre géneros permitirá a músicos y compositores explorar nuevas versiones de sus creaciones, facilitando la experimentación y la innovación en la música.
- **Casos de uso:** Apoyo para compositores (de todo nivel de experiencia), a crear versiones de una pieza musical en diferentes géneros, o para productores que buscan una solución rápida para adaptar música a distintos estilos.

## Objetivos del Proyecto
- **Objetivo 1:** Crear un analizador léxico y sintáctico capaz de interpretar código de Sonic Pi.
- **Objetivo 2:** Desarrollar un motor de transformación basado en reglas subjetivas musicales para delimitar las especificaciones de cada género.
- **Objetivo 3:** Pruebas de validación para la música transformada (ejecutable y escuchable)
- **Objetivo 4:** Ejecución de la música transformada

## Revisión del Estado del Arte
- **Compiladores similares:** En base a investigaciones previas, podemos identificar herramientas para la creación algorítmica de música, y no tanta competencia en la transformación de música.
- **Limitaciones de soluciones actuales:** Muchas soluciones actuales para producción de musica enfatizan la creación en base a patrones en vez de una transformación de género musical. Esto se debe ya que una transformacion es una herramientas mas de nicho.
- **Justificación del nuevo compilador:** La creación de un compilador que traduzca música entre géneros llena un vacio en herramientas disponibles para producción musical en Sonic Pi.

## Arquitectura y Diseño del Compilador
- **Diagrama de bloques:** 
  ![Diagrama_deBloques](/imgs/DiagramaBloques_Compiladores.drawio.png)
- **Explicación del flujo de datos:**
- **Decisiones de diseño:**

## Análisis Léxico
- **Análisis léxico:** 
  - El analizador lexico identificará tokens clave así como operadores específicos de Sonic Pi. 
- **Ejemplos:**
  - Notas: 
    - C4, G5, D3
  - Keywords:
    - play
    - amp:
    - do:
    - end
    - loop
    - live_loop
    - pan:
    - rate:
    - sleep
  - Operadores & Punctuation:
    - ,
    - ;
    - :
    - _
  
  **Automata**
    ![Automata_Sencillo](/imgs/Prototipo%20de%20Sonic%20Pi.png)
  
  **Tabla de Transiciones**
    ![Transiciones](/imgs/Tabla%20de%20Transiciones.png)

## Análisis Sintáctico
  - El analizador sintactico (parser) se propone hacer un recorrido en base a la metodologia LL(1).
- **Análisis sintáctico:** 
  - ![Codigo Compilado](/imgs/recorrido_parser1.png)
    ![Codigo Compilado](/imgs/recorrido_parser2.png)

- **Ejemplos:** TBD

## Análisis Semántico

- **Análisis semantico:** 
  - TBD

- **Ejemplos:** TBD

## Pruebas y Validación
El programa se busca validar mediante un codigo fuente consistente, el cual esta formado por:

*play :A5*
*sample :guit_e_fifths, amp: 0.5*

- **Metodología de pruebas:** 
  - Hasta el momento presente, se han hecho pruebas por separado utilizando el lexer y parser respectivamente para asegurar una funcionalidad apropiadad de ambos siste.as
- **Resultados obtenidos:** 
  - JFLEX ha ayudado para generar un lexer automatico en base a estructuras de gramaticas definidas despues de varias revisiones.
  - El Parser se ha creado 
- **Casos de prueba específicos:** Por el momento el enfoque ha sido  exclusivo con hacer funcionar nuestros casos bases debido a dificultades en el desarrollo de los componentes lexicos y sintacticos del compilador. 

## Herramientas y Entorno de Desarrollo
- **Lenguajes de programación utilizados:** Java
- **Herramientas de desarrollo:** Visual Studio Code, Sonic Pi, JFlex, IntelliJ
- **Entorno de pruebas y simulación:** IntelliJ IDE Community

## Demostración
- **Ejemplo de código fuente:** 
    ![Codigo Fuente](/imgs/codigo_fuente.png)
- **Proceso de compilación:** 
    ![Proceso de Compilacion de Parser](/imgs/recorrido_baseparse.png)
- **Ejecución del código compilado:** 
    ![Parser Ejecutado](/imgs/parser_run.png)

## Desafíos y Soluciones
- **Problemas técnicos o de diseño:** Definir reglas claras y objetivas para la transformación entre géneros fue un desafío, dado que la música tiene elementos subjetivos.
- **Estrategias adoptadas para superar desafíos:** Revisiones constantes y reevaluaciones de planteamientos al utilizar herramientas como ChatGPT para evaluar nuestros errores. Asimismo, agendar juntas con el profesor para resolver dudas mas especificas a nuestro lenguaje que se acercan mas a nuestros propios retos en comprender el comportamiento de los componentes de un compilador.
- **Lecciones aprendidas:** Tomar con tiempo el desarrollo, y hacer avances graduales para evitar una acumulacion de dudas y avances por entregar hasta ultimo minuto.

## Conclusiones y Trabajo Futuro
- **Resumen de objetivos cumplidos:** TBD
- **Evaluación del desempeño:** TBD
- **Propuestas para mejoras futuras:** TBD

## Preguntas y Discusión
- Espacio para responder preguntas y discusión sobre el proyecto.

## Referencias
- **Fuentes citadas:** Documentacion Sonic Pi