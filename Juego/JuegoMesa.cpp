// proyecto: Grupal/Juego
// arhivo:   JuegoMesa.cpp
// versión:  1.1  (9-Ene-2023)


#include "juego.h"


namespace juego {


    /*******************************************************************************************
    /*******************************************************************************************
        
    CONFIGURACIÓN DEL JUEGO
    Primera sección - Los recursos

    En esta sección se establecen las carpetas en las que aparecen los recursos usados por el 
    juego, incluyendo las imágenes que aparecen en pantalla y los sonidos que se escuchan. Hay 
    una carpeta separada para los retratos de los personajes y otra para las imágenes de las 
    habilidades.

    Las carpetas están situadas en la carpeta donde están los archivos de código fuente del 
    proyecto.

    En principio no es necesario hacer ningún cambio en esta sección, si los recursos que se 
    cambian se sitúan en las mismas carpetas.

    *******************************************************************************************/
    string JuegoMesa::carpeta_activos_juego  {"./activos/"};
    string JuegoMesa::carpeta_retratos_juego {"./retratos/"};
    string JuegoMesa::carpeta_habilids_juego {"./habilidades/"};
    string JuegoMesa::carpeta_sonidos_juego  {"./sonidos/"};
    /*******************************************************************************************
    /******************************************************************************************/


    const std::wstring JuegoMesa::tituloVentana () const {
        return L"UNIR-2D :: X-Korodan";
    }


    JuegoMesa::JuegoMesa () {
        //
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Segunda sección - El modo del juego

        En esta sección se configura el modo general del juego, es decir como se suceden las 
        jugadas, los turnos y las rondas. Y como se establece el personaje que realiza cada jugada.  

        La configuración del modo del juego se realiza mediante la elección de alguno de los
        modos preestablecidos. Es la única forma de configurar el modo del juego.

        Hay tres modos de juego preestablecidos:

            1) Modo de juego por pares
            2) Modo de juego por equipos
            3) Modo de juego libre de doble jugada

        Las siguientes definiciones se aplican a todos los modos de juego:

        Jugada:   
            Es una acción realizada con uno de los personajes. Puede ser un desplazamiento o la
            aplicación de una habilidad.

        Turno:
            Es una secuencia de jugadas realizadas por un grupo de personajes, normalmente 
            alternando a los dos equipos. los turnos se inician con la elección de los personajes 
            que van a participar en el turno, aunque en algunos modos de juego estos están 
            preestablecidos.

        Ronda:
            Es una secuencia de turnos en las que intervienen todos los personajes y que se 
            prolongan hasta que los personajes no pueden continuar, por haber perdido sus puntos de 
            acción o por haber perdido su vitalidad. Al inicio de la ronda, se recuperan los puntos 
            de acción de todos los personajes.

        Partida:
            Está formada por una secuencia de rondas. La partida termina cuando todos los personajes 
            de un equipo pierden su vitalidad. El otro equipo es el ganador.


        Modo de juego por pares
        --------------------------
        
        En este modo debe haber el mismo número de personajes en cada equipo.

        los turnos comienzan con los jugadores eligiendo un personaje de cada equipo. El primer 
        personaje en jugar es el que tiene más iniciativa, y en caso de tener la misma, se elige al 
        azar. A continuación se suceden las jugadas, alternando los dos personajes. 

        Cuando un personaje pierde sus puntos de acción o su vitalidad, el turno continua solo con 
        el otro. Y cuando lo pierden los dos, el turno termina.

        En el nuevo turno los jugador elige de nuevo a los dos personajes, evitando a los que han
        perdido sus puntos de acción o vitalidad.

        Cuando todos los personajes han perdido sus puntos de acción o su vitalidad, termina la 
        ronda.


        Modo de juego por equipos
        ----------------------------

        En este modo debe haber el mismo número de personajes en cada equipo.

        Al principio de la partida se establece un orden de juego para los personajes. Se toman los 
        personajes según aparecen en el tablero, de arriba a abajo, alternando los dos equipos. El 
        primero de los personajes será el que tenga más iniciativa de los dos primeros, eligiéndolos 
        al azar si coinciden. 
        
        Un turno consiste en una jugada de cada personaje, tomándolos en el orden de la lista y se 
        prolonga hasta que juega el último de los personajes de la lista. Si un personaje ha perdido 
        sus puntos de acción o su vitalidad, la jugada es nula y se pasa al siguiente personaje de 
        la lista. 
        
        Los turnos se suceden hasta que todos los personajes han perdido sus puntos de acción o su 
        vitalidad, momento en que se inicia el siguiente ronda.


        Modo de juego libre de doble jugada
        --------------------------------------

        En este modo debe haber el mismo número de personajes en cada equipo.

        Al principio de la partida se establece un equipo inicial, tomando el que tiene el personaje 
        con más iniciativa o eligiéndolo al azar si coinciden. A continuación se alternan turnos de 
        uno y otro equipo. 
        
        Al principio de cada turno, el jugador elije un personaje del equipo correspondiente. El 
        turno consiste en dos jugadas seguidas del mismo personaje, tras las cuales se pasa a el 
        siguiente turno, en la que el jugador elige un personaje del otro equipo. Si un personaje 
        ha perdido sus puntos de acción o su vitalidad, no puede ser elegido.

        Cuando todos los personajes de un equipo han perdido sus puntos de acción o vitalidad, 
        termina el turno (a pesar de que el otro equipo si pueda continuar).


        Programación
        ------------

        Para cambiar el modo del juego es suficiente con cambiar los identificadores usados en 
        las dos líneas de código siguientes. Debe aparecer una de estas tres parejas:

            · ModoJuegoPares       SucesosJuegoPares       
            · ModoJuegoEquipo      SucesosJuegoEquipo    
            · ModoJuegoLibreDoble  SucesosJuegoLibreDoble

        *******************************************************************************************/
        ModoJuegoPares    * modo    = new ModoJuegoPares {this};
        SucesosJuegoPares * sucesos = new SucesosJuegoPares {this, modo};
        /*******************************************************************************************
        /******************************************************************************************/
        //
        JuegoMesaBase::configura (sucesos, modo);
    }


    /*******************************************************************************************
    /*******************************************************************************************
        
    CONFIGURACIÓN DEL JUEGO
    Tercera sección - El tablero - Primera parte

    En esta sección se preparan los muros que aparecen en el tablero de juego.

    En el juego aparecen imágenes que muestran muros que ocupan algunas casillas hexagonales
    del tablero. Los jugadores no pueden situar a los personajes sobre los muros, ni 
    atravesarlos. Tampoco pueden realizar ataque a través de los muros (excepto si están 
    marcados como ataques indirectos).  

    Existen muchas posibilidades de diseño para los muros. Es posible que los muros se usen solo
    para delimitar un área del tablero, como ocurre con el ejemplo que aparece a continuación,
    llamado 'grafico_muros_area_central'. Otra posibilidad es diseñar una especie de laberinto
    con pasillos y cámaras, como en el ejemplo: 'grafico_muros_pasillos'. Aunque, lo más 
    aconsejable es crear unos muros que sean simplemente obstáculos para los ataques entre los 
    personajes.

    Especificación de los muros
    ---------------------------

    Para especificar los muros del tablero se debe crear un array similar al que aparece en los 
    ejemplos. Es preferible crear uno nuevo y mantener los ejemplos, en ese caso , la variable 
    debe tener un nombre diferente.

    El array está formado por 51 cadenas de caracteres, cada una de ellas de 145 caracteres de 
    longitud (mas el carácter \0 final, que no es visible). La mayor parte de los caracteres de 
    la cadena son espacios en blanco. En determinadas posiciones, y solo en ellas, puede haber: 
    o bien un guion, o bien la letra O mayúscula. 
        
    Esta disposición está pensada para indicar las posiciones de las celdas de la rejilla del 
    tablero. Al ser celdas hexagonales, no es posible usar una tabla formada por filas y 
    columnas, que, además, no daría una representación visual clara del tablero.

    Si se quiere que en una celda del tablero no aparezca un fragmento del muro, se debe 
    escribir un guion en la posición correspondiente del array. Si, por el contrario, se quiere 
    que si aparezca, se debe escribir la letra o mayúscula.

    El programa es muy sensible a la colocación de los caracteres en el array. Si uno de ellos
    está desplazado (por poco que sea), se producirá una excepción y el programa no se podrá 
    ejecutar.

    Programación
    ------------

    Véase la tercera parte de esta sección.
        
    *******************************************************************************************/
    static ActorTablero::GraficoMuros grafico_muros_vacio { 
//                                      1  1  1  1  1  1  1  1  1  1  2  2  2  2  2  2  2  2  2  2  3  3  3  3  3  3  3  3  3  3  4  4  4  4  4  4  4  4  4  4
//           1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9
//                                                                                                                11111111111111111111111111111111111111111111
//                     111111111122222222223333333333444444444455555555556666666666777777777788888888889999999999000000000011111111112222222222333333333344444  
//           0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",  
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -"};

    static ActorTablero::GraficoMuros grafico_muros_ciudad{
        //                                      1  1  1  1  1  1  1  1  1  1  2  2  2  2  2  2  2  2  2  2  3  3  3  3  3  3  3  3  3  3  4  4  4  4  4  4  4  4  4  4
        //           1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9
        //                                                                                                                11111111111111111111111111111111111111111111
        //                     111111111122222222223333333333444444444455555555556666666666777777777788888888889999999999000000000011111111112222222222333333333344444  
        //           0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234
                    "-     -     -     -     -     -     -     -     -     O     -     -     -     -     -     O     -     -     -     -     -     -     -     -     -",
                    "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
                    "-     -     -     -     -     -     -     -     -     O     -     -     -     -     -     O     -     -     -     -     -     -     -     -     -",
                    "   -     -     -     -     -     -     -     -     -     O     O     -     -     O     O     -     -     -     -     -     -     -     -     -   ",
                    "-     -     -     -     -     -     -     -     -     O     O     O     -     O     O     O     -     -     -     -     -     -     -     -     -",
                    "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
                    "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
                    "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
                    "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
                    "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
                    "-     -     -     -     -     -     -     -     -     -     O     O     O     O     O     -     -     -     -     -     -     -     -     -     -",
                    "   -     -     -     -     -     -     -     -     -     O     O     O     O     O     O     -     -     -     -     -     -     -     -     -   ",
                    "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
                    "   -     -     -     -     -     -     -     -     -     O     -     -     -     -     O     -     -     -     -     -     -     -     -     -   ",
                    "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
                    "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
                    "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
                    "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
                    "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
                    "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
                    "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
                    "   -     -     -     -     -     -     -     -     -     O     -     -     -     -     O     -     -     -     -     -     -     -     -     -   ",
                    "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
                    "   -     -     -     -     -     -     -     -     -     O     O     -     -     O     O     -     -     -     -     -     -     -     -     -   ",
                    "-     -     -     -     -     -     -     -     -     -     O     O     -     O     O     -     -     -     -     -     -     -     -     -     -",
                    "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
                    "-     -     -     -     -     -     -     -     -     -     -     -     O     -     -     -     -     -     -     -     -     -     -     -     -",
                    "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
                    "-     -     -     -     -     -     -     -     -     -     -     -     O     -     -     -     -     -     -     -     -     -     -     -     -",
                    "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
                    "-     -     -     -     -     -     -     -     -     -     -     -     O     -     -     -     -     -     -     -     -     -     -     -     -",
                    "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
                    "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
                    "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
                    "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
                    "   -     -     -     -     -     -     -     -     -     O     -     -     -     -     O     -     -     -     -     -     -     -     -     -   ",
                    "-     -     -     -     -     -     -     -     -     -     -     -     O     -     -     -     -     -     -     -     -     -     -     -     -",
                    "   -     -     -     -     -     -     -     -     -     O     -     -     -     -     O     -     -     -     -     -     -     -     -     -   ",
                    "-     -     -     -     -     -     -     -     O     O     O     O     O     O     O     O     O     -     -     -     -     -     -     -     -",
                    "   -     -     -     -     -     -     -     -     -     O     -     -     -     -     O     -     -     -     -     -     -     -     -     -   ",
                    "-     -     -     -     -     -     -     -     -     -     -     -     O     -     -     -     -     -     -     -     -     -     -     -     -",
                    "   -     -     -     -     -     -     -     -     -     O     -     -     -     -     O     -     -     -     -     -     -     -     -     -   ",
                    "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
                    "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
                    "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
                    "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
                    "-     -     -     -     -     -     -     -     -     -     -     -     O     -     -     -     -     -     -     -     -     -     -     -     -",
                    "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
                    "-     -     -     -     -     -     -     -     -     -     -     -     O     -     -     -     -     -     -     -     -     -     -     -     -",
                    "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
                    "-     -     -     -     -     -     -     -     -     -     -     -     O     -     -     -     -     -     -     -     -     -     -     -     -" };

  
    static ActorTablero::GraficoMuros grafico_muros_area_central { 
//                                      1  1  1  1  1  1  1  1  1  1  2  2  2  2  2  2  2  2  2  2  3  3  3  3  3  3  3  3  3  3  4  4  4  4  4  4  4  4  4  4
//           1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9
//                                                                                                                11111111111111111111111111111111111111111111
//                     111111111122222222223333333333444444444455555555556666666666777777777788888888889999999999000000000011111111112222222222333333333344444  
//           0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234
            "-     -     -     -     -     -     -     -     O     O     O     O     -     O     O     O     O     -     -     -     -     -     -     -     -",  
            "   -     -     -     -     -     -     -     O     O     O     O     -     -     O     O     O     O     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     O     O     O     O     -     -     -     O     O     O     O     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     O     O     O     O     -     -     -     -     O     O     O     O     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     O     O     O     O     -     -     -     -     -     O     O     O     O     -     -     -     -     -     -",
            "   -     -     -     -     -     O     O     O     O     -     -     -     -     -     -     O     O     O     O     -     -     -     -     -   ",
            "-     -     -     -     -     O     O     O     O     -     -     -     -     -     -     -     O     O     O     O     -     -     -     -     -",
            "   -     -     -     -     O     O     O     O     -     -     -     -     -     -     -     -     O     O     O     O     -     -     -     -   ",
            "-     -     -     -     O     O     O     O     -     -     -     -     -     -     -     -     -     O     O     O     O     -     -     -     -",
            "   -     -     -     O     O     O     O     -     -     -     -     -     -     -     -     -     -     O     O     O     O     -     -     -   ",
            "-     -     -     O     O     O     O     -     -     -     -     -     -     -     -     -     -     -     O     O     O     O     -     -     -",
            "   -     -     O     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     O     -     -   ",
            "-     -     O     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     O     -     -",
            "   -     O     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     O     -   ",
            "-     O     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     O     -",
            "   -     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     -   ",
            "-     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     -",
            "   -     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     -   ",
            "-     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     -",
            "   -     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     -   ",
            "-     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     -     -",
            "   -     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     -     -   ",
            "-     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     -     -     -",
            "   -     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     -",
            "   -     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     -   ",
            "-     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     -   ",
            "-     -     -     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     -",
            "   -     -     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     -   ",
            "-     -     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     -",
            "   -     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     -   ",
            "-     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     -",
            "   -     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     -   ",
            "-     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     -",
            "   -     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     -   ",
            "-     O     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     O     -",
            "   -     O     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     O     -   ",
            "-     -     O     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     O     -     -",
            "   -     -     O     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     O     -     -   ",
            "-     -     -     O     O     O     O     -     -     -     -     -     -     -     -     -     -     -     O     O     O     O     -     -     -",
            "   -     -     -     O     O     O     O     -     -     -     -     -     -     -     -     -     -     O     O     O     O     -     -     -   ",
            "-     -     -     -     O     O     O     O     -     -     -     -     -     -     -     -     -     O     O     O     O     -     -     -     -",
            "   -     -     -     -     O     O     O     O     -     -     -     -     -     -     -     -     O     O     O     O     -     -     -     -   ",
            "-     -     -     -     -     O     O     O     O     -     -     -     -     -     -     -     O     O     O     O     -     -     -     -     -",
            "   -     -     -     -     -     O     O     O     O     -     -     -     -     -     -     O     O     O     O     -     -     -     -     -   ",
            "-     -     -     -     -     -     O     O     O     O     -     -     -     -     -     O     O     O     O     -     -     -     -     -     -",
            "   -     -     -     -     -     -     O     O     O     O     -     -     -     -     O     O     O     O     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     O     O     O     O     -     -     -     O     O     O     O     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     O     O     O     O     -     -     O     O     O     O     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     O     O     O     O     -     O     O     O     O     -     -     -     -     -     -     -     -"};


    static ActorTablero::GraficoMuros grafico_muros_pasillos { 
            "-     O     -     -     -     -     -     O     -     -     -     -     -     -     -     -     O     -     -     -     O     -     -     -     -",
            "   O     O     -     -     -     -     O     O     -     -     -     -     -     -     -     O     O     -     -     O     O     -     -     -   ",
            "O     -     O     -     -     -     O     -     O     -     -     -     -     -     -     O     -     O     -     O     -     O     -     -     -",
            "   -     -     O     -     -     O     -     -     O     -     -     -     -     -     O     -     -     O     -     O     -     O     -     -   ",
            "O     -     -     O     -     O     -     O     -     O     -     -     -     -     O     -     O     -     O     -     O     -     O     -     -",
            "   -     -     -     O     O     -     O     O     -     O     -     -     -     O     -     O     O     -     O     -     O     -     O     -   ",
            "O     -     -     -     O     -     O     -     O     -     O     -     -     O     -     O     -     O     -     O     -     O     -     O     -",
            "   -     -     -     -     O     O     O     -     O     -     O     -     O     -     O     -     -     O     -     O     -     O     -     O   ",
            "O     -     -     -     -     -     -     O     -     O     -     O     O     -     O     -     -     -     O     -     O     -     O     -     O",
            "   -     -     -     -     O     O     -     O     -     O     -     O     -     O     -     -     O     -     O     -     O     -     O     O   ",
            "O     -     -     -     -     -     -     O     O     -     O     -     -     O     -     -     O     O     -     O     -     O     -     O     -",
            "   -     -     -     -     O     O     O     -     O     -     O     -     O     -     -     O     -     O     -     O     -     O     -     -   ",
            "O     -     -     -     -     -     O     -     -     O     -     O     -     O     -     O     -     -     O     -     O     -     O     -     -",
            "   -     -     -     -     -     O     -     O     -     O     -     O     -     O     O     -     -     -     O     -     O     -     O     -   ",
            "O     -     -     -     -     -     -     O     O     -     O     -     O     -     O     -     -     -     -     O     -     O     -     O     -",
            "   -     -     -     -     O     O     -     -     O     -     O     -     O     -     -     -     -     -     -     O     -     O     -     -   ",
            "O     -     -     -     -     -     -     O     -     O     -     O     -     O     -     -     -     -     -     -     O     -     O     -     -",
            "   -     -     -     -     O     O     -     O     -     O     -     O     -     O     -     -     -     -     -     -     O     -     O     -   ",
            "O     -     -     -     O     -     O     -     O     -     O     -     O     -     O     -     -     -     -     -     O     O     -     O     -",
            "   O     -     -     O     -     O     O     -     O     -     O     -     O     -     -     -     -     -     -     -     -     O     -     -   ",
            "-     O     -     O     -     O     -     O     -     O     -     O     -     O     -     -     -     -     -     -     O     -     O     O     -",
            "   -     -     O     -     O     -     -     O     -     O     -     O     -     O     -     -     -     -     -     -     O     -     -     -   ",
            "-     O     O     -     O     -     -     -     O     -     O     -     O     -     O     -     -     -     -     -     -     O     O     O     -",
            "   -     O     -     O     -     -     -     -     O     -     O     -     O     -     -     -     -     -     -     -     -     O     -     -   ",
            "-     -     -     O     -     -     -     -     -     -     -     O     -     O     -     -     -     -     -     -     O     -     O     -     -",
            "   -     -     O     -     -     -     -     -     -     -     O     O     O     O     -     -     -     -     -     -     O     -     O     -   ",
            "-     O     O     O     -     -     -     -     -     -     -     -     -     -     O     -     -     -     -     -     -     O     -     O     -",
            "   -     -     -     -     -     -     -     -     -     -     O     O     O     -     -     -     -     -     -     -     -     O     -     -   ",
            "-     O     O     O     -     -     -     -     -     -     -     -     -     -     O     -     -     -     -     -     O     O     O     -     -",
            "   -     -     -     -     -     -     -     -     -     -     O     O     O     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     O     O     O     -     -     -     -     -     -     -     -     -     -     O     -     -     -     -     -     O     O     O     O     -",
            "   -     -     -     -     -     -     -     -     -     -     O     O     O     -     -     -     -     -     -     -     -     -     -     O   ",
            "-     O     O     O     -     -     -     -     -     -     -     -     -     -     O     -     -     -     -     -     O     O     O     O     O",
            "   -     -     O     -     -     -     -     -     -     -     O     O     O     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     O     -     -     -     -     -     -     -     -     -     -     -     -     O     -     -     -     -     -     O     O     O     O     O",
            "   -     O     -     -     -     -     -     -     -     -     O     O     O     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     O     -     -     -     -     -     -     -     -     -     -     -     O     -     -     -     -     -     O     O     O     O     O",
            "   -     -     O     -     -     -     -     -     -     -     O     O     O     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     O     -     O     -     -     -     -     -     -     -     O     -     O     O     -     -     -     -     -     O     O     O     O     O",
            "   -     O     -     O     -     -     -     -     -     -     O     -     -     O     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     O     -     O     -     -     -     -     -     O     -     O     -     O     -     -     -     -     -     O     O     O     O     O",
            "   -     -     O     -     O     -     -     -     -     O     -     O     O     -     O     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     O     -     O     -     -     -     O     -     O     -     O     -     O     -     -     -     -     O     O     O     O     O",
            "   -     -     -     O     -     O     -     -     O     -     O     -     -     O     -     O     -     O     -     O     -     O     -     -   ",
            "-     -     -     -     O     -     O     -     O     -     O     -     O     -     O     -     O     O     O     O     -     -     O     O     O",
            "   -     -     -     -     O     -     O     O     -     O     -     O     O     -     O     -     O     -     O     -     O     -     -     -   ",
            "-     -     -     -     -     O     -     O     -     O     -     O     -     O     -     O     -     -     -     -     O     O     -     O     O",
            "   -     -     -     -     -     O     -     -     -     -     O     -     -     O     -     O     -     O     -     O     -     O     O     -   ",
            "-     -     -     -     -     -     O     -     O     -     O     -     -     -     O     -     O     O     O     O     -     -     O     O     O",
            "   -     -     -     -     -     -     O     O     O     O     -     -     -     -     O     O     O     -     O     -     -     -     -     O   ",
            "-     -     -     -     -     -     -     O     -     O     -     -     -     -     -     O     -     -     -     -     -     -     -     -     -"};
    /*******************************************************************************************
    /******************************************************************************************/


    void JuegoMesa::preparaTablero () {
        agregaTablero (new ActorTablero (this));
        //
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Tercera sección - El tablero - Segunda parte

        En esta sección se configura el fondo del tablero. Para rellenar el fondo del tablero se usa
        un conjunto de imágenes colocadas en una rejilla (en filas y columnas), que ocupan toda la 
        superficie de la ventana.
        
        La imagen usada para rellenar el fondo del tablero no se usa directamente, se divide en 16
        partes, con 4 filas y 4 columnas, y continuación se colocan en el fondo del tablero, 
        seleccionado las partes de manera aleatoria. La razón de este funcionamiento es que se 
        consiguen evitar los patrones visuales que pueden aparecer si se colocan de forma uniforme.

        El tamaño de la imagen usada es de 128x128 px (y cada parte es de 32x32 px). 
        
        Programación
        ------------

        Para cambiar la imagen del fondo es suficiente con situar la imagen nueva en la carpeta de 
        activos del juego y cambiar el nombre en la línea de código siguiente. 
        
        Es conveniente usar un archivo de tipo PNG. Además se deben respetar las medidas indicadas
        previamente.

        *******************************************************************************************/
        //tablero ()->ponArchivoBaldosas (carpeta_activos_juego + "estampas_fondo.png");
        tablero()->ponArchivoBaldosas(carpeta_activos_juego + "tile.png");
        /*******************************************************************************************
        /******************************************************************************************/
        //
        //
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Cuarta sección - Los personajes - Primera parte

        En esta sección se configuran los equipos del juego. 

        Cada equipo tiene un nombre y un escudo que aparece sobre la bandera en la parte superior de
        los paneles laterales del juego. En escudo se superpone a la bandera, sin taparla. El tamaño
        de las dos imágenes es de 40x40 px.
        
        Programación
        ------------

        Para cambiar los nombres de los equipos, se deben cambiar las dos líneas de código 
        siguientes. 
        
        Para cambiar las imágenes de los escudos es suficiente con situar las imágenes nuevas en la 
        carpeta de activos del juego y cambiar los nombres en las líneas de código siguiente. 
        
        Es conveniente usar archivos de tipo PNG que permiten la transparencia. Además se deben 
        respetar las medidas indicadas previamente.

        *******************************************************************************************/
        //tablero ()->equipa (LadoTablero::Izquierda, L"Devils", carpeta_activos_juego + "escudo_devils.png");
        //tablero()->equipa(LadoTablero::Derecha, L"Tusk", carpeta_activos_juego + "escudo_tusk.png");
        tablero()->equipa(LadoTablero::Izquierda, L"Red Squadron", carpeta_activos_juego + "rs.png");
        tablero()->equipa(LadoTablero::Derecha, L"Blue Division", carpeta_activos_juego + "bd.png");
        /*******************************************************************************************
        /******************************************************************************************/
        //
        //
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Tercera sección - El tablero - Tercera parte

        En esta sección se preparan los muros que aparecen en el tablero de juego. En la primera
        parte de la sección se preparan los muros que aparecen en el tablero, en esta tercera parte 
        se establecen los muros que usará el juego.

        Programación
        ------------

        Para cambiar los muros que aparecen en el tablero de juego es suficiente con cambiar el 
        nombre de la variable que contiene el array que los especifica en la línea de código que 
        aparece a continuación.
        
        *******************************************************************************************/
        tablero ()->situaMuros (grafico_muros_ciudad);

        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::preparaPersonajes () {
        //
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Cuarta sección - Los personajes - Tercera parte

        En esta sección se configuran los personajes del juego. En la segunda parte se establecen
        las variables destinadas a almacenar las instancias que definen los personajes. En esta 
        parte se crean las instancias y se configuran.

        Las variable usan un nombre similar al nombre del personaje correspondiente. Las variables 
        son de tipo puntero, la creación de las instancias utiliza la palabra reservada 'new'. 

        Atributos
        ---------

        Se asignan los siguientes atributos a los personajes:

             a) Nombre: Asignado en la creación de la instancia en una cadena de caracteres. Deben 
                ser evitados los nombres compuestos y los nombres largos.

             b) Equipo: Se establece indicando si el personaje aparece en el panel de la izquierda o 
                en el panel de la derecha en el tablero de juego.

             c) Orden en equipo: Debe ser un índice a partir de 0 y consecutivo.

             d) Iniciativa: Establece que personaje actúa en primer lugar en algunas de las 
                circunstancias del juego. Debe ser positivo.

        Imágenes
        --------

        Cada personaje tiene un retrato con el que aparece en la pantalla del juego. El tamaño de la
        imagen usada es de 75x75 px. La imagen puede tener zonas transparentes, en cuyo caso aparece 
        sobre un fondo gris oscuro. El retrato se especifica en la creación de la instancia.

        De la misma forma, cada personaje tiene una imagen para la ficha con la que aparece en el 
        tablero. El tamaño de la imagen usada es de 31x31 px.

        Programación
        ------------

        Se deben modificar las lineas de código que aparecen a continuación.

        Se debe sustituir las listas de creaciones de instancias y las listas de llamadas a los 
        métodos por listas similares, obtenidas a partir de la lista de personajes diseñados para el 
        juego.

        Se deben cambiar los valores de los parámetros según los valores establecidos para cada 
        personaje en el diseño del juego.

        Para cambiar las imágenes de los retratos de los personajes es suficiente con situar las 
        imágenes nuevas en la carpeta de retratos del juego y cambiar los nombres de los archivos en 
        las llamadas al método correspondientes. Lo mismo ocurre con las imágenes de las fichas.
        
        Es conveniente usar archivos de tipo PNG que permiten la transparencia. Además se deben 
        respetar las medidas indicadas previamente.

        *******************************************************************************************/
        
        Brute57 = new ActorPersonaje{ this, LadoTablero::Izquierda, 0, L"Brute57" };
		Brute57->flipped = true; // Volteamos el retrato para que se vea bien en el tablero
        Glory_F1st = new ActorPersonaje{ this, LadoTablero::Izquierda, 1, L"Glory_F1st" };
		Glory_F1st->flipped = true; // Volteamos el retrato para que se vea bien en el tablero
        MPSYKO = new ActorPersonaje{ this, LadoTablero::Izquierda, 2, L"M-PSY-KO" };
		MPSYKO->flipped = true; // Volteamos el retrato para que se vea bien en el tablero  
        MASA01 = new ActorPersonaje{ this, LadoTablero::Derecha, 0, L"MASA-01" };
        NeoNet = new ActorPersonaje{ this, LadoTablero::Derecha, 1, L"NeoNet" };
        Titan800 = new ActorPersonaje{ this, LadoTablero::Derecha, 2, L"TITAN-800" };

		Brute57->ponArchivoRetrato(carpeta_retratos_juego + "Brute57.png");
		Glory_F1st->ponArchivoRetrato(carpeta_retratos_juego + "Glory_F1st.png");
		MPSYKO->ponArchivoRetrato(carpeta_retratos_juego + "M-PSY-KO.png");
		MASA01->ponArchivoRetrato(carpeta_retratos_juego + "MASA-01.png");
		NeoNet->ponArchivoRetrato(carpeta_retratos_juego + "NeoNet.png");
		Titan800->ponArchivoRetrato(carpeta_retratos_juego + "TITAN-800.png");
		
        
        Brute57->ponArchivoFicha(carpeta_retratos_juego + "Brute57_ficha.png");
        Glory_F1st->ponArchivoFicha(carpeta_retratos_juego + "Glory_F1st_ficha.png");
        MPSYKO->ponArchivoFicha(carpeta_retratos_juego + "M-PSY-KO_ficha.png");
        MASA01->ponArchivoFicha(carpeta_retratos_juego + "MASA-01_ficha.png");
        NeoNet->ponArchivoFicha(carpeta_retratos_juego + "NeoNet_ficha.png");
        Titan800->ponArchivoFicha(carpeta_retratos_juego + "TITAN-800_ficha.png");

        Brute57->ponIniciativa(20);
		Glory_F1st->ponIniciativa(19);
		MPSYKO->ponIniciativa(18);
		MASA01->ponIniciativa(20);
		NeoNet->ponIniciativa(19);
		Titan800->ponIniciativa(18);

		agregaPersonaje(Brute57);
		agregaPersonaje(Glory_F1st);
		agregaPersonaje(MPSYKO);
		agregaPersonaje(MASA01);
		agregaPersonaje(NeoNet);
		agregaPersonaje(Titan800);
        
        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::preparaHabilidades () {
        //
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Quinta sección - Las habilidades - Segunda parte

        En esta sección se configuran las habilidades compartidas por los personajes del juego. En 
        la primera parte se establecen las variables destinadas a almacenar las instancias que 
        definen las habilidades. En esta segunda parte se crean las instancias y se configuran.

        Las variable usan un nombre similar al nombre de la habilidad correspondiente. Las variables 
        son de tipo puntero, la creación de las instancias utiliza la palabra reservada 'new'. 

        Atributos
        ---------

        Se asignan los siguientes atributos a las habilidades:

             a) Nombre: Asignado en la creación de la instancia en una cadena de caracteres. 

             b) Enfoque: Indica a que esta enfocada la habilidad. Puede ser a un personaje, a un 
                área formada por varias celdas del tablero o hacia el mismo personaje que usa la 
                habilidad. 

             c) Acceso: Indica si el efecto de la habilidad puede atravesar muros. Puede ser directo,
                indirecto o ninguno.

             d) Antagonista: Indica a que grupo de personajes se dirige la habilidad. Puede ser a un
                oponente, a un aliado o a sí mismo.

             e) Descripción: Es un texto largo que describe la habilidad.

        Imágenes
        --------

        Cada habilidad tiene una imagen con el que aparece en la pantalla del juego. El tamaño de la
        imagen usada es de 50x50 px. La imagen puede tener zonas transparentes, en cuyo caso aparece 
        sobre una imagen de fondo, que puede ser distinta para cada habilidad o la misma para todas. 
        Las dos imágenes de cada habilidad se especifican la misma llamada a un método.

        Sonidos
        -------

        Cada habilidad tiene un sonido que suena cuando el personaje la usa. El sonido se carga de 
        un archivo de tipo 'wav', 'ogg' o 'flac', pero no 'mp3'. El tiempo de emisión del sonido
        debe ser corto (escasos segundos).

        Programación
        ------------

        Se deben modificar las lineas de código que aparecen a continuación.

        Se debe sustituir las listas de creaciones de instancias y las listas de llamadas a los 
        métodos por listas similares, obtenidas a partir de la lista de habilidades diseñadas para 
        el juego.

        Se deben cambiar los valores de los parámetros según los valores establecidos para cada 
        habilidad en el diseño del juego.

        Para cambiar las imágenes de las habilidad es suficiente con situar las imágenes nuevas en 
        la carpeta de habilidades del juego y cambiar los nombres en las llamadas al método 
        correspondiente. 
        
        Para cambiar los sonidos de las habilidad es suficiente con situar los sonidos nuevos en 
        la carpeta de sonidos del juego y cambiar los nombres en las llamadas al método 
        correspondiente. 
        
        Es conveniente usar archivos de tipo PNG que permiten la transparencia. Además se deben 
        respetar las medidas indicadas previamente.

        *******************************************************************************************/
        //
		golpeMele = new Habilidad{
			L"Ataque cuerpo a cuerpo normal",
			EnfoqueHabilidad::personaje, AccesoHabilidad::directo, Antagonista::oponente};
        golpeMele->ponDescripcion(
            L"El personaje golpea a un enemigo que se encuentra en una casilla próxima.");
        golpeMele->ponArchivosImagenes(
            carpeta_habilids_juego + "Hab_1 Blue Squad.png", carpeta_habilids_juego + "fondo_5.png");
        golpeMele->ponArchivoSonido(carpeta_sonidos_juego + "Mecha Missiles.ogg");
        agregaHabilidad(golpeMele);

        salvaMisiles = new Habilidad{
             L"Ataque a distancia de área explosiva",
                EnfoqueHabilidad::area, AccesoHabilidad::directo,   Antagonista::oponente };
        salvaMisiles->ponDescripcion(
            L"Disparo a distancia con misiles explosivos");
        salvaMisiles->ponArchivosImagenes(
            carpeta_habilids_juego + "salvaMisiles.png", carpeta_habilids_juego + "fondo_5.png");
        salvaMisiles->ponArchivoSonido(carpeta_sonidos_juego + "Mecha Missiles.ogg");
        agregaHabilidad(salvaMisiles);

        tipoDuro = new Habilidad{
             L"Sube defensas",
                EnfoqueHabilidad::si_mismo,  AccesoHabilidad::ninguno,   Antagonista::si_mismo };
        tipoDuro->ponDescripcion(
            L"Aguanta todo tipo de ataques");
        tipoDuro->ponArchivosImagenes(
            carpeta_habilids_juego + "Hab_7 Blue Squad.png", carpeta_habilids_juego + "fondo_5.png");
        tipoDuro->ponArchivoSonido(carpeta_sonidos_juego + "Mecha Missiles.ogg");
        agregaHabilidad(tipoDuro);

        punoHidraulico = new Habilidad{
            L"Ataque cuerpo a cuerpo cinético",
            EnfoqueHabilidad::personaje, AccesoHabilidad::directo, Antagonista::oponente };
        punoHidraulico->ponDescripcion(
            L"El personaje golpea cuerpo a cuerpo con daño cinético en vez de físico");
        punoHidraulico->ponArchivosImagenes(
            carpeta_habilids_juego + "Hab Red Squad (4).png", carpeta_habilids_juego + "fondo_5.png");
        punoHidraulico->ponArchivoSonido(carpeta_sonidos_juego + "Mecha Missiles.ogg");
        agregaHabilidad(punoHidraulico);

        canonIones = new Habilidad{
             L"Ataque a distancia de daño eléctrico",
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente };
        canonIones->ponDescripcion(
            L"Disparo a distancia con daño eléctrico");
        canonIones->ponArchivosImagenes(
            carpeta_habilids_juego + "Hab Red Squad (3).png", carpeta_habilids_juego + "fondo_5.png");
        canonIones->ponArchivoSonido(carpeta_sonidos_juego + "Mecha Missiles.ogg");
        agregaHabilidad(canonIones);

        canon20mm = new Habilidad{
             L"Ataque a distancia de daño cinético",
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente };
        canon20mm->ponDescripcion(
            L"Disparo a distancia con daño cinético");
        canon20mm->ponArchivosImagenes(
            carpeta_habilids_juego + "misc_canon_riel.png", carpeta_habilids_juego + "fondo_5.png");
        canon20mm->ponArchivoSonido(carpeta_sonidos_juego + "Mecha Missiles.ogg");
        agregaHabilidad(canon20mm);

        laserPesado = new Habilidad{
             L"Ataque a distancia de daño energético",
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente };
        laserPesado->ponDescripcion(
            L"Disparo a distancia con daño energético");
        laserPesado->ponArchivosImagenes(
            carpeta_habilids_juego + "Hab Red Squad (5).png", carpeta_habilids_juego + "fondo_5.png");
        laserPesado->ponArchivoSonido(carpeta_sonidos_juego + "Mecha Missiles.ogg");
        agregaHabilidad(laserPesado);

        canonPlasma = new Habilidad{
             L"Ataque de área de daño energético",
                EnfoqueHabilidad::area, AccesoHabilidad::directo,   Antagonista::oponente };
        canonPlasma->ponDescripcion(
            L"Disparo a distancia con daño energético de área");
        canonPlasma->ponArchivosImagenes(
            carpeta_habilids_juego + "Hab Red Squad (5).png", carpeta_habilids_juego + "fondo_5.png");
        canonPlasma->ponArchivoSonido(carpeta_sonidos_juego + "Mecha Missiles.ogg");
        agregaHabilidad(canonPlasma);

        reparar = new Habilidad{
             L"Repara vitalidad",
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::aliado };
        reparar->ponDescripcion(
            L"Repara vitalidad");
        reparar->ponArchivosImagenes(
            carpeta_habilids_juego + "Hab_3 Blue Squad.png", carpeta_habilids_juego + "fondo_5.png");
        reparar->ponArchivoSonido(carpeta_sonidos_juego + "Mecha Missiles.ogg");
        agregaHabilidad(reparar);

        piezasRepuesto = new Habilidad{
             L"Piezas respuesto",
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::aliado };
        piezasRepuesto->ponDescripcion(
            L"Recupera la vitalidad propia");
        piezasRepuesto->ponArchivosImagenes(
            carpeta_habilids_juego + "misc_piezas_repuesto.png", carpeta_habilids_juego + "fondo_5.png");
        piezasRepuesto->ponArchivoSonido(carpeta_sonidos_juego + "Mecha Missiles.ogg");
        agregaHabilidad(piezasRepuesto);

        /*
        ataqueEspadaNormal   = new Habilidad {
                L"Ataque cuerpo a cuerpo normal", 
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente};
        ataqueArco           = new Habilidad {
                L"Ataque a distancia normal",     
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente};
        ataqueEspadaPoderoso = new Habilidad {
                L"Ataque poderoso",               
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente};
        defensaFerrea        = new Habilidad {
                L"Defensa férrea",                
                EnfoqueHabilidad::si_mismo,  AccesoHabilidad::ninguno,   Antagonista::si_mismo};
        curacionSimple       = new Habilidad {
                L"Curación",                      
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::aliado};
        curacionGrupo        = new Habilidad {
                L"Curación en grupo",             
                EnfoqueHabilidad::area,      AccesoHabilidad::directo,   Antagonista::aliado};
        proyectilMagico      = new Habilidad {
                L"Proyectil mágico",              
                EnfoqueHabilidad::personaje, AccesoHabilidad::indirecto, Antagonista::oponente};
        bolaFuego            = new Habilidad {
                L"Bola de fuego",                 
                EnfoqueHabilidad::area,      AccesoHabilidad::directo,   Antagonista::oponente};
        //
      
        ataqueEspadaNormal  ->ponDescripcion (
                L"El personaje usa su espada para atacar a un enemigo que se encuentra en una casilla próxima.");
        ataqueArco          ->ponDescripcion (
                L"El personaje usa su arco para atacar a un enemigo que se encuentra en una casilla próxima.");
        ataqueEspadaPoderoso->ponDescripcion (
                L"El personaje blande su espada con fuerza para atacar a un enemigo que se encuentra en una casilla próxima.");
        defensaFerrea       ->ponDescripcion (
                L"El personaje aumenta su defensa hasta su próximo ronda.");
        curacionSimple      ->ponDescripcion (
                L"El personaje canaliza poder divino para sanar a un aliado.");
        curacionGrupo      ->ponDescripcion (
                L"El personaje canaliza poder divino para sanar a todos los personajes en un área.");
        proyectilMagico     ->ponDescripcion (
                L"El personaje acumula energía mágica y la lanza contra un enemigo.");
        bolaFuego           ->ponDescripcion (
                L"El personaje acumula energía mágica y la lanza contra un grupo de enemigos.");
        //
        ataqueEspadaNormal  ->ponArchivosImagenes (
                carpeta_habilids_juego + "espada.png",          carpeta_habilids_juego + "fondo_5.png");
        ataqueArco          ->ponArchivosImagenes (
                carpeta_habilids_juego + "arco_flecha.png",     carpeta_habilids_juego + "fondo_5.png");
        ataqueEspadaPoderoso->ponArchivosImagenes (
                carpeta_habilids_juego + "espada_poderosa.png", carpeta_habilids_juego + "fondo_5.png");
        defensaFerrea       ->ponArchivosImagenes (
                carpeta_habilids_juego + "escudo.png",          carpeta_habilids_juego + "fondo_5.png");
        curacionSimple      ->ponArchivosImagenes (
                carpeta_habilids_juego + "vela.png",            carpeta_habilids_juego + "fondo_5.png");
        curacionGrupo       ->ponArchivosImagenes (
                carpeta_habilids_juego + "vela_triple.png",     carpeta_habilids_juego + "fondo_5.png");
        proyectilMagico     ->ponArchivosImagenes (
                carpeta_habilids_juego + "cristales.png",       carpeta_habilids_juego + "fondo_5.png");
        bolaFuego           ->ponArchivosImagenes (
                carpeta_habilids_juego + "bola_fuego.png",      carpeta_habilids_juego + "fondo_5.png");
        //
        ataqueEspadaNormal  ->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");
        ataqueArco          ->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");
        ataqueEspadaPoderoso->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");
        defensaFerrea       ->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");
        curacionSimple      ->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");
        curacionGrupo       ->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");
        proyectilMagico     ->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");
        bolaFuego           ->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");
        //
        agregaHabilidad (ataqueEspadaNormal);
        agregaHabilidad (ataqueArco);
        agregaHabilidad (ataqueEspadaPoderoso);
        agregaHabilidad (defensaFerrea );
        agregaHabilidad (curacionSimple);
        agregaHabilidad (curacionGrupo );
        agregaHabilidad (proyectilMagico );
        agregaHabilidad (bolaFuego );
        */
        //
        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::preparaTiposEstadisticas () {
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Sexta sección - Los tipos de ataque, defensa y daño (estadísticas) - Segunda parte

        En esta sección se configuran los tipos de ataque, defensa y daño del juego. Estos tipos  
        son usados para establecer las estadisticas del juego en los personajes y en las habilidades. 
        En la primera parte se establecen las variables destinadas a almacenar las instancias que 
        definen los tipos de ataque, defensa y daño. En esta parte se crean las instancias y se 
        configuran.

        Las variable usan un nombre similar al nombre de los tipos correspondiente. Las variables 
        son de tipo puntero, la creación de las instancias utiliza la palabra reservada 'new'. 

        Atributos
        ---------

        Se asignan los siguientes atributos a los tipos:

             a) Descripción: Asignado en la creación de la instancia en una cadena de caracteres. 
                Deben ser cortos y deben comenzar con la palabra 'Ataque', 'Defensa' o 'Daño'.

        Programación
        ------------

        Se deben modificar las líneas de código que aparecen a continuación.

        Se debe sustituir las listas de creaciones de instancias por listas similares, obtenidas a 
        partir de la lista de tipos diseñados para el juego. El nombre de la clase (por ejemplo 
        'TipoAtaque' para los ataques) establece si es un tipo de ataque, de defensa o de daño.

        Se deben cambiar los valores de los parámetros según los valores establecidos para cada 
        tipo en el diseño del juego.

        *******************************************************************************************/
        //
        
        ataqueMele  = new TipoAtaque  {L"Ataque Melé"};
        ataqueDisparo  = new TipoAtaque  {L"Ataque de Disparo"};
		ataqueArtilleria = new TipoAtaque  {L"Ataque de Artilleria"};
		ataquePulso = new TipoAtaque {L"Ataque de Pulso"};
		ataqueHackeo  = new TipoAtaque {L"Ataque de Hackeo"};

        defensaMele  = new TipoDefensa  {L"Defensa Melé"};
        defensaDisparo  = new TipoDefensa  {L"Defensa de Disparo"};
        defensaArtilleria = new TipoDefensa  {L"Defensa de Artilleria"};
        defensaPulso  = new TipoDefensa {L"Defensa de Pulso"};
        defensaHackeo  = new TipoDefensa {L"Defensa Hackeo"};

        danoFisico = new TipoDano {L"Daño Físico"};
        danoCinetico = new TipoDano {L"Daño Cinético"};
        danoExplosivo = new TipoDano {L"Daño Explosivo"};
        danoEnergetico = new TipoDano {L"Daño Energético"};
        danoElectrico = new TipoDano {L"Daño Eléctrico"};

		agregaAtaque(ataqueMele);
		agregaAtaque(ataqueDisparo);
		agregaAtaque(ataqueArtilleria);
		agregaAtaque(ataquePulso);
		agregaAtaque(ataqueHackeo);
		agregaDefensa(defensaMele);
		agregaDefensa(defensaDisparo);
		agregaDefensa(defensaArtilleria);
		agregaDefensa(defensaPulso);
		agregaDefensa(defensaHackeo);
		agregaDano(danoFisico);
		agregaDano(danoCinetico);
		agregaDano(danoExplosivo);
		agregaDano(danoEnergetico);
		agregaDano(danoElectrico);

        /*
        agregaAtaque  (ataqueCuerpoACuerpo );
        agregaAtaque  (ataqueADistancia);
        agregaAtaque  (ataqueMagico);
        agregaDefensa (defensaCuerpoACuerpo);
        agregaDefensa (defensaADistancia );
        agregaDefensa (defensaMagica );
        agregaDano    (danoFisico);
        agregaDano    (danoMagico);
        */
        
        //
        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::agregaHabilidadesPersonajes () {
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Octava sección - Las habilidades de los personajes

        En esta sección se establecen que habilidades que tiene cada personajes del juego.

        Cada personaje debe tener entre 1 y 10 habilidades.

        Programación
        ------------

        Se deben modificar las líneas de código que aparecen a continuación.

        Se deben sustituir las listas de habilidades de cada personaje por listas similares, 
        obtenidas a partir del diseño del juego.

        Brute57
        Glory_F1st
        MPSYKO
        MASA01
        NeoNet
        Titan800
        *******************************************************************************************/
        //
		Brute57->agregaHabilidad(golpeMele);
        Brute57->agregaHabilidad(salvaMisiles);
        Brute57->agregaHabilidad(tipoDuro);

		Glory_F1st->agregaHabilidad(golpeMele);
		Glory_F1st->agregaHabilidad(punoHidraulico);
		Glory_F1st->agregaHabilidad(piezasRepuesto);

		MPSYKO->agregaHabilidad(golpeMele);
		MPSYKO->agregaHabilidad(canonIones);
		MPSYKO->agregaHabilidad(reparar);

		MASA01->agregaHabilidad(golpeMele);
		MASA01->agregaHabilidad(canon20mm);
		MASA01->agregaHabilidad(piezasRepuesto);

		NeoNet->agregaHabilidad(golpeMele);
		NeoNet->agregaHabilidad(laserPesado);
		NeoNet->agregaHabilidad(reparar);

		Titan800->agregaHabilidad(golpeMele);
		Titan800->agregaHabilidad(canonPlasma);
		Titan800->agregaHabilidad(piezasRepuesto);

        /*
        Brute57->agregaHabilidad (ataqueEspadaNormal);
        Brute57->agregaHabilidad (ataqueArco);
        Brute57->agregaHabilidad (ataqueEspadaPoderoso);
        Brute57->agregaHabilidad (defensaFerrea);
        //
        Glory_F1st->agregaHabilidad (ataqueEspadaNormal);
        Glory_F1st->agregaHabilidad (curacionSimple);
        Glory_F1st->agregaHabilidad (curacionGrupo);
        Glory_F1st->agregaHabilidad (proyectilMagico);
        //
        MPSYKO->agregaHabilidad (ataqueEspadaNormal);
        MPSYKO->agregaHabilidad (proyectilMagico);
        MPSYKO->agregaHabilidad (bolaFuego);
        //
        //Pirate->agregaHabilidad (ataqueEspadaNormal);
        //Pirate->agregaHabilidad (ataqueArco);
        //Pirate->agregaHabilidad (ataqueEspadaPoderoso);
        //
        MASA01->agregaHabilidad (ataqueEspadaNormal);
        MASA01->agregaHabilidad (ataqueArco);
        MASA01->agregaHabilidad (ataqueEspadaPoderoso);
        MASA01->agregaHabilidad (defensaFerrea);
        //
        NeoNet->agregaHabilidad (ataqueEspadaNormal);
        NeoNet->agregaHabilidad (curacionSimple);
        NeoNet->agregaHabilidad (curacionGrupo);
        NeoNet->agregaHabilidad (proyectilMagico);
        //
        Titan800->agregaHabilidad (ataqueEspadaNormal);
        Titan800->agregaHabilidad (proyectilMagico);
        Titan800->agregaHabilidad (bolaFuego);
        //
        //Thief ->agregaHabilidad (ataqueEspadaNormal);
        //Thief ->agregaHabilidad (ataqueArco);
        //Thief ->agregaHabilidad (ataqueEspadaPoderoso);
        //
        */
        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::agregaEstadisticasHabilidades () {
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Novena sección - Las estadísticas de las habilidades

        En esta sección se establecen diversos atributos y valores para las habilidades del juego,
        incluyendo las estadisticas del juego.

        Estadísticas
        ------------

        Las habilidades se clasifican en habilidades de ataque, de curación y auto-aplicada. Esta 
        clasificación se establece mediante el atributo 'Antagonista' de la habilidad. 

            - Si 'Antagonista' es 'oponente' la habilidad es de ataque. El ataque puede afectar a un 
              personaje o a los personajes de un área del tablero.
            - Si 'Antagonista' es 'aliado' la habilidad es de curación. La curación puede afectar a 
              un personaje o a los personajes de un área del tablero.
            - Si 'Antagonista' es 'si_mismo' la habilidad es auto-aplicada.

        Los valores que se establecen para las habilidades son:

             a) Coste: Es el número de puntos de acción que se gastan al usar la habilidad.

             b) Alcance: En las habilidades de ataque y curación debe estar establecido el alcance 
                de la habilidad. La habilidad solo se puede usar si el alcance lo permite. Es un 
                valor que indica un número de casillas del tablero y debe ser positivo.

             c) Radio de ara de alcance: En las habilidades de ataque y curación que afectan a un 
                área del tablero, debe estar establecido el radio del área. Es un valor que indica 
                un número de casillas del tablero y debe ser positivo. 

             d) Tipo de ataque: Cuando una habilidad es de ataque, debe tener establecido un tipo de 
                ataque. El tipo de ataque se usa en el personaje atacante.

             e) Tipo de defensa: Cuando una habilidad es de ataque, debe tener establecido un tipo 
                de defensa. El tipo de defensa se usa en el personaje atacado.

             f) Tipo de daño: Cuando una habilidad es de ataque, debe tener establecido un tipo de 
                daño. El tipo de daño se usa en el personaje atacado.

             g) Valor del daño: Cuando una habilidad es de ataque, debe tener establecido un valor 
                para el daño en puntos de vitalidad. El valor del daño se usa con el personaje 
                atacado.

             h) Curación: Cuando una habilidad es de curación, debe tener establecido un valor de 
                curación en puntos.

             i) Efecto en ataque: Cuando una habilidad es auto-aplicada, puede tener establecido uno 
                o más tipos de ataque, asignado como tipo de efecto en ataque. Alternativamente 
                (y excluyentemente) puede tener establecido un efecto en defensa (véase k).

             j) Valor del efecto en ataque: Cuando una habilidad es auto-aplicada, para cada tipo de 
                efecto en ataque establecido (véase i), debe tener establecido un valor del efecto
                en ataque en puntos de vitalidad.

             k) Efecto en defensa: Cuando una habilidad es auto-aplicada, puede tener establecido 
                uno o más tipos de defensa, asignado como tipo de efecto en defensa. Alternativamente 
                (excluyentemente) puede tener establecido un efecto en ataque (véase i).

             l) Valor del efecto en defensa: Cuando una habilidad es auto-aplicada, para cada tipo de 
                efecto en defensa establecido (véase k), debe tener establecido un valor del efecto
                en defensa en puntos de vitalidad.


        Programación
        ------------

        Se deben modificar las líneas de código que aparecen a continuación.

        Se deben sustituir las asignaciones de valores por asignaciones similares, obtenidas a 
        partir del diseño del juego.

        Los métodos usados en las líneas de código siguientes establecen si se debe usar un tipo de 
        ataque, de defensa o de daño. Por ejemplo, el método 'asignaAtaque' debe ser llamado con un 
        parámetro del tipo (puntero) 'TipoAtaque'.  

        *******************************************************************************************/
        //
        golpeMele->ponCoste(3);
        golpeMele->ponAlcance(1);
        golpeMele->asignaAtaque(ataqueMele);
        golpeMele->asignaDefensa(defensaMele);
        golpeMele->asignaDano(danoFisico, 30);

        salvaMisiles->ponCoste(9);
        salvaMisiles->ponAlcance(10);
        salvaMisiles->ponRadioAlcance(3);
        salvaMisiles->asignaAtaque(ataqueArtilleria);
        salvaMisiles->asignaDefensa(defensaArtilleria);
        salvaMisiles->asignaDano(danoExplosivo, 50);

        tipoDuro->ponCoste(4);
		tipoDuro->agregaEfectoDefensa(defensaMele, 30);
        tipoDuro->agregaEfectoDefensa(defensaDisparo, 30);

        punoHidraulico->ponCoste(5);
        punoHidraulico->ponAlcance(1);
        punoHidraulico->asignaAtaque(ataqueMele);
        punoHidraulico->asignaDefensa(defensaMele);
        punoHidraulico->asignaDano(danoCinetico, 60);

		canonIones->ponCoste(6);
        canonIones->ponAlcance(15);
        canonIones->asignaAtaque(ataqueHackeo);
        canonIones->asignaDefensa(defensaHackeo);
        canonIones->asignaDano(danoElectrico, 25);

		canon20mm->ponCoste(5);
        canon20mm->ponAlcance(12);
        canon20mm->asignaAtaque(ataqueDisparo);
        canon20mm->asignaDefensa(defensaDisparo);
        canon20mm->asignaDano(danoCinetico, 20);

        laserPesado->ponCoste(10);
        laserPesado->ponAlcance(18);
        laserPesado->asignaAtaque(ataqueDisparo);
        laserPesado->asignaDefensa(defensaDisparo);
        laserPesado->asignaDano(danoEnergetico, 50);

        canonPlasma->ponCoste(8);
        canonPlasma->ponAlcance(12);
        canonPlasma->ponRadioAlcance(2);
        canonPlasma->asignaAtaque(ataqueDisparo);
        canonPlasma->asignaDefensa(defensaDisparo);
        canonPlasma->asignaDano(danoEnergetico, 40);

        reparar->ponCoste(10);
        reparar->ponAlcance(3);
        reparar->asignaCuracion(30);

        piezasRepuesto->ponCoste(20);
        piezasRepuesto->ponAlcance(1);
        piezasRepuesto->asignaCuracion(40);
        
        /*
        ataqueEspadaNormal->ponCoste (3);                                       
        ataqueEspadaNormal->ponAlcance (1);
        ataqueEspadaNormal->asignaAtaque  (ataqueCuerpoACuerpo); 
        ataqueEspadaNormal->asignaDefensa (defensaCuerpoACuerpo); 
        ataqueEspadaNormal->asignaDano    (danoFisico, 20); 
        //
        ataqueArco->ponCoste (5);
        ataqueArco->ponAlcance (15);
        ataqueArco->asignaAtaque  (ataqueADistancia);
        ataqueArco->asignaDefensa (defensaADistancia);
        ataqueArco->asignaDano    (danoFisico, 20);
        //
        ataqueEspadaPoderoso->ponCoste (5);
        ataqueEspadaPoderoso->ponAlcance (1);
        ataqueEspadaPoderoso->asignaAtaque  (ataqueCuerpoACuerpo);
        ataqueEspadaPoderoso->asignaDefensa (defensaCuerpoACuerpo);
        ataqueEspadaPoderoso->asignaDano    (danoFisico, 50);
        //
        defensaFerrea->ponCoste (3);
        defensaFerrea->agregaEfectoDefensa (defensaCuerpoACuerpo, 30);
        defensaFerrea->agregaEfectoDefensa (defensaADistancia,    30);
        //
        curacionSimple->ponCoste (5);
        curacionSimple->ponAlcance (3);  
        curacionSimple->asignaCuracion (40);
        //
        curacionGrupo->ponCoste (10);
        curacionGrupo->ponAlcance (3);  
        curacionGrupo->ponRadioAlcance (3);
        curacionGrupo->asignaCuracion (40);
        //
        proyectilMagico->ponCoste (7);
        proyectilMagico->ponAlcance (15);                                            
        proyectilMagico->asignaAtaque  (ataqueMagico);
        proyectilMagico->asignaDefensa (defensaMagica);
        proyectilMagico->asignaDano    (danoMagico, 30);
        //
        bolaFuego->ponCoste (10);
        bolaFuego->ponAlcance (8);
        bolaFuego->ponRadioAlcance (3);
        bolaFuego->asignaAtaque  (ataqueMagico);
        bolaFuego->asignaDefensa (defensaMagica);
        bolaFuego->asignaDano    (danoMagico, 50);
        //
        */
        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::agregaEstadisticasPersonajes () {
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Décima sección - Los tipos de ataque, defensa y reducción de daño de los personajes

        En esta sección se establecen que tipos de ataque, defensa y reducción de daño tiene cada 
        personajes del juego, junto con la correspondiente puntuación.

        Configuración
        -------------

        La configuración de los tipos se debe realizar de la siguiente forma:

             a) Si un personaje tiene una habilidad y esta habilidad tiene un tipo de ataque, el 
                personaje debe tener ese tipo de ataque.

             b) Cada personaje debe tener todos los tipos de defensa.

             c) Cada personaje debe tener todos los tipos de daño, en forma de reducción de daño.

             d) Si un personaje tiene una habilidad y esta habilidad tiene un efecto en ataque,
                que está definido usando un tipo de ataque, el personaje debe tener dicho tipo de 
                ataque.

             e) Si un personaje tiene una habilidad y esta habilidad tiene un efecto en defensa,
                que está definido usando un tipo de defensa, el personaje debe tener dicho tipo de 
                defensa. Esta propiedad está establecida previamente mediante el punto (b)

             f) Cada tipo de ataque, defensa y reducción de daño del personaje debe tener una 
                puntuación. La puntuación no puede ser negativa.        

        Programación
        ------------

        Se deben modificar las líneas de código que aparecen a continuación.

        Se deben sustituir las listas de tipos de ataque, defensa y reducción de daño de cada 
        personaje por listas similares, obtenidas a partir del diseño del juego.

        Los métodos usados en las líneas de código siguientes establecen si el tipo es ataque, 
        defensa o daño. Por ejemplo, el método 'agregaReduceDano' debe ser llamado con un parámetro 
        del tipo (puntero) 'TipoDano'.  

        

        *******************************************************************************************/
        //
        Brute57->agregaAtaque(ataqueMele,               70);
        Brute57->agregaAtaque(ataqueDisparo,            50);
		Brute57->agregaAtaque(ataqueArtilleria,         50);
		Brute57->agregaAtaque(ataquePulso,              50);
		Brute57->agregaAtaque(ataqueHackeo,             20);
		Brute57->agregaDefensa(defensaMele,             70);
		Brute57->agregaDefensa(defensaDisparo,          70);
		Brute57->agregaDefensa(defensaArtilleria,       70);
		Brute57->agregaDefensa(defensaPulso,            70);
		Brute57->agregaDefensa(defensaHackeo,           20);
        
        Brute57->agregaReduceDano(danoFisico,            5);
		Brute57->agregaReduceDano(danoCinetico,         10);
		Brute57->agregaReduceDano(danoExplosivo,         5);
		Brute57->agregaReduceDano(danoEnergetico,       10);
		Brute57->agregaReduceDano(danoElectrico,         5);
        

        Glory_F1st->agregaAtaque(ataqueMele,            70);
        Glory_F1st->agregaAtaque(ataqueDisparo,         50);
        Glory_F1st->agregaAtaque(ataqueArtilleria,      50);
        Glory_F1st->agregaAtaque(ataquePulso,           50);
        Glory_F1st->agregaAtaque(ataqueHackeo,          20);
        Glory_F1st->agregaDefensa(defensaMele,          70);
        Glory_F1st->agregaDefensa(defensaDisparo,       70);
        Glory_F1st->agregaDefensa(defensaArtilleria,    70);
        Glory_F1st->agregaDefensa(defensaPulso,         70);
        Glory_F1st->agregaDefensa(defensaHackeo,        20);
        
        Glory_F1st->agregaReduceDano(danoFisico, 5);
        Glory_F1st->agregaReduceDano(danoCinetico,      10);
        Glory_F1st->agregaReduceDano(danoExplosivo,      5);
        Glory_F1st->agregaReduceDano(danoEnergetico,    10);
        Glory_F1st->agregaReduceDano(danoElectrico,      5);
       

        MPSYKO->agregaAtaque(ataqueMele,                70);
        MPSYKO->agregaAtaque(ataqueDisparo,             50);
        MPSYKO->agregaAtaque(ataqueArtilleria,          50);
        MPSYKO->agregaAtaque(ataquePulso,               50);
        MPSYKO->agregaAtaque(ataqueHackeo,              20);
        MPSYKO->agregaDefensa(defensaMele,              70);
        MPSYKO->agregaDefensa(defensaDisparo,           70);
        MPSYKO->agregaDefensa(defensaArtilleria,        70);
        MPSYKO->agregaDefensa(defensaPulso,             70);
        MPSYKO->agregaDefensa(defensaHackeo,            20);
        
        MPSYKO->agregaReduceDano(danoFisico,            5);
        MPSYKO->agregaReduceDano(danoCinetico,          10);
        MPSYKO->agregaReduceDano(danoExplosivo,         5);
        MPSYKO->agregaReduceDano(danoEnergetico,        10);
        MPSYKO->agregaReduceDano(danoElectrico,         5);
        

        MASA01->agregaAtaque(ataqueMele,                70);
        MASA01->agregaAtaque(ataqueDisparo,             50);
        MASA01->agregaAtaque(ataqueArtilleria,          50);
        MASA01->agregaAtaque(ataquePulso,               50);
        MASA01->agregaAtaque(ataqueHackeo,              20);
        MASA01->agregaDefensa(defensaMele,              70);
        MASA01->agregaDefensa(defensaDisparo,           70);
        MASA01->agregaDefensa(defensaArtilleria,        70);
        MASA01->agregaDefensa(defensaPulso,             70);
        MASA01->agregaDefensa(defensaHackeo,            20);
        
        MASA01->agregaReduceDano(danoFisico,            5);
        MASA01->agregaReduceDano(danoCinetico,          10);
        MASA01->agregaReduceDano(danoExplosivo,         5);
        MASA01->agregaReduceDano(danoEnergetico,        10);
        MASA01->agregaReduceDano(danoElectrico,         5);
        

        
		NeoNet->agregaAtaque(ataqueMele,                70);
		NeoNet->agregaAtaque(ataqueDisparo,             50);
		NeoNet->agregaAtaque(ataqueArtilleria,          50);
		NeoNet->agregaAtaque(ataquePulso,               50);
		NeoNet->agregaAtaque(ataqueHackeo,              20);
		NeoNet->agregaDefensa(defensaMele,              70);
		NeoNet->agregaDefensa(defensaDisparo,           70);
		NeoNet->agregaDefensa(defensaArtilleria,        70);
		NeoNet->agregaDefensa(defensaPulso,             70);
		NeoNet->agregaDefensa(defensaHackeo,            20);
        
        NeoNet->agregaReduceDano(danoFisico,            5);
		NeoNet->agregaReduceDano(danoCinetico,          10);
		NeoNet->agregaReduceDano(danoExplosivo,         5);
		NeoNet->agregaReduceDano(danoEnergetico,        10);
		NeoNet->agregaReduceDano(danoElectrico,         5);
        

		Titan800->agregaAtaque(ataqueMele,              70);
		Titan800->agregaAtaque(ataqueDisparo,           50);
		Titan800->agregaAtaque(ataqueArtilleria,        50);
		Titan800->agregaAtaque(ataquePulso,             50);
		Titan800->agregaAtaque(ataqueHackeo,            20);
		Titan800->agregaDefensa(defensaMele,            70);
		Titan800->agregaDefensa(defensaDisparo,         70);
		Titan800->agregaDefensa(defensaArtilleria,      70);
		Titan800->agregaDefensa(defensaPulso,           70);
		Titan800->agregaDefensa(defensaHackeo,          20);
        
		Titan800->agregaReduceDano(danoFisico,          5);
		Titan800->agregaReduceDano(danoCinetico,        10);
		Titan800->agregaReduceDano(danoExplosivo,       5);
		Titan800->agregaReduceDano(danoEnergetico,      10);
		Titan800->agregaReduceDano(danoElectrico,       5);
        

        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::preparaSistemaAtaque () {
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Séptima sección - Los grados de efectividad - Segunda parte

        En esta sección se configuran los grados de efectividad de los ataques del juego. En la 
        primera parte se establecen las variables destinadas a almacenar las instancias que definen 
        los grados de efectividad. En esta parte se crean las instancias y se configuran.

        Las variable usan un nombre similar al nombre de los tipos correspondiente. Las variables 
        son de tipo puntero, la creación de las instancias utiliza la palabra reservada 'new'. 

        Atributos
        ---------

        Se asignan los siguientes atributos a los tipos:

             a) Descripción: Asignado en la creación de la instancia en una cadena de caracteres. 
                Deben ser cortos.

             b) Intervalo de puntos: Es el intervalo de puntos al que se aplica la efectividad. 
                Se establece con un valor mínimo y uno máximo. En el primer intervalo el valor 
                mínimo es el número entero mínimo y en el último intervalo, el valor máximo es 
                el número entero máximo.

             c) Efectividad: Es un porcentaje que se aplica a una puntuación para modificar su 
                valor cuando dicha puntuación esta en el intervalo definido por el intervalo
                correspondiente. 
            
        Programación
        ------------

        Se deben modificar las líneas de código que aparecen a continuación.

        Se debe sustituir las listas de creaciones de instancias por listas similares, obtenidas a 
        partir de la lista de grados de efectividad diseñados para el juego. 

        Se deben cambiar los valores de los parámetros según los valores establecidos para cada 
        grados de efectividad en el diseño del juego.

        *******************************************************************************************/
        //
        GradoEfectividad * fallo   = new GradoEfectividad {L"Fallo"};
        GradoEfectividad * roce    = new GradoEfectividad {L"Roce"};
        GradoEfectividad * impacto = new GradoEfectividad {L"Impacto"};
        GradoEfectividad * critico = new GradoEfectividad {L"Impacto crítico"};
        //
        fallo  ->estableceRango (INT_MIN,       9,    0);
        roce   ->estableceRango (     10,      49,   50);
        impacto->estableceRango (     50,      89,  100);
        critico->estableceRango (     90, INT_MAX,  150);
        //
        agregaEfectividad (fallo);
        agregaEfectividad (roce);
        agregaEfectividad (impacto);
        agregaEfectividad (critico);
        //
        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::configuraJuego () {
        agregaMusica (new ActorMusica {this});
        //
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Undécima sección - Configuración miscelánea del juego.

        En esta sección se establecen varios valores de configuración que no tienen sitio en otras 
        secciones.

        Configuración
        -------------

        La configuración tiene los siguientes aspectos:

                 a) Se establece el consumo de puntos de acción de los desplazamientos de los 
                    personajes. Para ello se indica el número píxeles de desplazamiento que 
                    originan el consumo de un punto de acción.

                 b) Se establece la posición inicial de las fichas de los personajes en el tablero 
                    de juego.
         
                 c) Se establecen los archivos de sonido, que se escuchan en momentos concretos del
                    juego. Se deben especificar los sonidos:

                      - Sonido de una pulsación con el ratón (clic)
                      - Sonido de desplazamiento de una ficha.

                 d) Se establece la música que se escucha con el juego. En un fragmento musical que 
                    se repite en bucle.

                 e) Se almacenan los nombres de los alumnos diseñadores del juego. Estos nombres
                    aparecen en la ayuda del juego.

                 f) Se almacena el curso académico durante el que los alumnos han elaborado el 
                    diseño del juego.

        Sonidos y música
        ----------------

        Los sonidos se cargan de archivos de tipo 'wav', 'ogg' o 'flac', pero no 'mp3'. El tiempo de
        emisión del sonido debe ser corto (escasos segundos).
        
        Los sonidos y la música se han tomado de:
                https://opengameart.org/content/metal-click
                https://opengameart.org/content/walking-on-snow-sound
        La licencia aparece en esas mismas páginas.

        La música que suena en momentos determinados del juego también se carga de un archivo. Sin 
        embargo, no es necesario que sea corta, por que se atenúa a los pocos segundos.

        La música se han tomado de:
                https://opengameart.org/content/unused-music
        La licencia aparece en esa misma página.

        Programación
        ------------

        Se deben modificar las líneas de código que aparecen a continuación.

        Se deben sustituir las listas de personajes por listas similares, obtenidas a partir del 
        diseño del juego.

        
        *******************************************************************************************/
        //
        modo ()->configuraDesplaza (RejillaTablero::distanciaCeldas);
        //
        Brute57->ponSitioFicha (Coord {23, 15});
        Glory_F1st->ponSitioFicha (Coord {17, 15});
        MPSYKO->ponSitioFicha (Coord {29, 15});
        //Pirate->ponSitioFicha (Coord {35, 15});
        MASA01->ponSitioFicha (Coord {23, 35});
        NeoNet->ponSitioFicha (Coord {17, 35});
        Titan800->ponSitioFicha (Coord {29, 35});
        //Thief ->ponSitioFicha (Coord {35, 35});
        //
        //tablero()->asignaSonidoEstablece(carpeta_sonidos_juego + "Metal Click.wav", 100);
        tablero ()->asignaSonidoEstablece (carpeta_sonidos_juego + "MechaClick.wav", 40);
        //tablero ()->asignaSonidoDesplaza  (carpeta_sonidos_juego + "SnowWalk.ogg",    100);
        tablero()->asignaSonidoDesplaza(carpeta_sonidos_juego + "FootSteps.ogg", 100);
        //musica  ()->asignaMusica          (carpeta_sonidos_juego + "Track_1.ogg",     100);
        musica  ()->asignaMusica          (carpeta_sonidos_juego + "Musica_Battala_01-002.wav",     100);
        //
        agregaNombreAlumno (L"Juan Manuel Carrillo");
        agregaNombreAlumno (L"Francisco Manuel Medina García");
        agregaNombreAlumno (L"Sara Pérez Armenteros");
        agregaNombreAlumno(L"Thiago Hachikyan Fernández");
        agregaNombreAlumno(L"Iván López Baeza");
        indicaCursoAcademico (L"2024 - 2025");
        //
        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::termina () {
        //
        JuegoMesaBase::termina ();
        //
        
            
            
            
            
        // Personajes    
        Brute57 = nullptr;
        Glory_F1st = nullptr;
        MPSYKO = nullptr;
        MASA01 = nullptr;
        NeoNet = nullptr;
        Titan800 = nullptr;
        //Habilidades
		golpeMele = nullptr;
		salvaMisiles = nullptr;
		tipoDuro = nullptr;
		punoHidraulico = nullptr;
		canonIones = nullptr;
		canon20mm = nullptr;
		laserPesado = nullptr;
		canonPlasma = nullptr;
		reparar = nullptr;
		piezasRepuesto = nullptr;

    
        //Estadisticas
		ataqueMele = nullptr;
		ataqueDisparo = nullptr;
		ataqueArtilleria = nullptr;
		ataquePulso = nullptr;
		ataqueHackeo = nullptr;
		defensaMele = nullptr;
		defensaDisparo = nullptr;
		defensaArtilleria = nullptr;
		defensaPulso = nullptr;
		defensaHackeo = nullptr;
        danoFisico = nullptr;
		danoCinetico = nullptr;
		danoExplosivo = nullptr;
		danoEnergetico = nullptr;
		danoElectrico = nullptr;

    }


}