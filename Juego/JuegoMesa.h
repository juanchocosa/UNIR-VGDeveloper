// proyecto: Grupal/Juego
// arhivo:   JuegoMesa.h
// versión:  1.1  (9-Ene-2023)


#pragma once


namespace juego {


    class JuegoMesa : public JuegoMesaBase {
    public:

        JuegoMesa ();

    private:

        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Cuarta sección - Los personajes - Segunda parte

        En esta sección se configuran los personajes del juego. 
        
        Consiste en declarar las variables que están destinadas a almacenar las instancias que 
        definen a los personajes. 

        El nombre de cada variable es similar al nombre del personaje correspondiente. Las variables 
        son de tipo puntero. 

        Programación
        ------------

        Se debe sustituir la lista de declaraciones de variables por una lista similar obtenida de
        la lista de personajes diseñados para el juego.

        *******************************************************************************************/
        ActorPersonaje* Brute57{};
		ActorPersonaje* Glory_F1st{};
		ActorPersonaje* MPSYKO{};
        ActorPersonaje* MASA01{};
        ActorPersonaje* NeoNet{};
		ActorPersonaje* Titan800{};
  
        /*******************************************************************************************
        /******************************************************************************************/
 

        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Quinta sección - Las habilidades - Primera parte

        En esta sección se configuran las habilidades compartidas por los personajes del juego. 
        
        Consiste en declarar las variables que están destinadas a almacenar las instancias que 
        definen a las habilidades. 

        El nombre de cada variable es similar al de la habilidad correspondiente. Las variables son 
        de tipo puntero. 

        Programación
        ------------

        Se debe sustituir la lista de declaraciones de variables por una lista similar obtenida de
        la lista de habilidades diseñadas para el juego.

        *******************************************************************************************/
        // Habilidad de ataque genérica para todos los personajes
        Habilidad* golpeMele{};
        Habilidad* piezasRepuesto{};
		//Red squad
        //**********************
        //Brute-57
		Habilidad* salvaMisiles{}; // Ataque a distancia con misiles de tipo danoExplosivo
        Habilidad* tipoDuro{}; // Sube defensas
		//Glory-F1st
		Habilidad* punoHidraulico{}; // Ataque cc con tipo de daño cinético
		Habilidad* ataquesDevastadores{}; // Sube ataque melé
		//MPSYKO
		Habilidad* canonIones{}; // Ataque a distancia con tipo de daño eléctrico
		Habilidad* reparar{}; // Repara vitalidad

        //Blue division
        //**********************
		//Masa-01
		Habilidad* canon20mm{}; // Ataque a distancia con tipo de daño cinético
		//Habilidad* rajar{}; // Ataque cc con tipo de daño energético
		//NeoNet
		Habilidad* laserPesado{}; // Ataque a distancia con tipo de daño energético
		//Habilidad* depurarSistema{}; // Sube defensa de hackeo y repara vitalidad
		//Titan-800
		Habilidad* canonPlasma{}; // Ataque a distancia con tipo de daño energético
		//Habilidad* aleacionSobrenatural{}; // Sube defensas ,menos hackeo

        /*******************************************************************************************
        /******************************************************************************************/


        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Sexta sección - Los tipos de ataque, defensa y daño (estadísticas) - Primera parte

        En esta sección se configuran los tipos de ataque, defensa y daño del juego, que son usados
        por los personajes y las habilidades del juego. 
        
        Consiste en declarar las variables que están destinadas a almacenar las instancias que 
        definen los tipos de ataque, defensa y daño. 

        El nombre de cada variable identifica el tipo correspondiente. Las variables son de 
        tipo puntero. El nombre de la clase (por ejemplo 'TipoAtaque' para los ataques) 
        establece si es un tipo de ataque, de defensa o de daño.

        Programación
        ------------

        Se debe sustituir la lista de declaraciones de variables por una lista similar obtenida de
        la lista de tipos de ataque, defensa y daño diseñados para el juego.

        *******************************************************************************************/

        TipoAtaque * ataqueMele{};
        TipoAtaque * ataqueDisparo{};
        TipoAtaque * ataqueArtilleria{};
        TipoAtaque * ataquePulso{};
        TipoAtaque * ataqueHackeo{};

        TipoDefensa * defensaMele{};
        TipoDefensa * defensaDisparo{};
        TipoDefensa * defensaArtilleria{};
        TipoDefensa * defensaPulso{};
        TipoDefensa * defensaHackeo{};

        TipoDano* danoFisico{};
        TipoDano* danoCinetico{};
        TipoDano* danoExplosivo{};
        TipoDano* danoEnergetico{};
        TipoDano* danoElectrico{};
        /*******************************************************************************************
        /******************************************************************************************/


        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Séptima sección - Los grados de efectividad - Primera parte

        En esta sección se configuran los grados de efectividad de los ataques del juego. 
        
        Consiste en declarar las variables que están destinadas a almacenar las instancias que 
        definen los grados de efectividad de los ataques. 

        Cada variable tiene un nombre similar al nombre del grados de efectividad correspondiente. 
        Las variables son de tipo puntero. 

        Programación
        ------------

        Se debe sustituir la lista de declaraciones de variables por una lista similar obtenida de
        la lista de grados de efectividad diseñados para el juego.

        *******************************************************************************************/
        GradoEfectividad * fallo {};
        GradoEfectividad * roce {};
        GradoEfectividad * impacto {};
        GradoEfectividad * critico {};
        /*******************************************************************************************
        /******************************************************************************************/

    private:

        static string carpeta_activos_juego;
        static string carpeta_retratos_juego;
        static string carpeta_habilids_juego;
        static string carpeta_sonidos_juego;


        const std::wstring tituloVentana () const override;

        void preparaTablero () override;
        void preparaPersonajes () override;
        void preparaHabilidades () override;
        void preparaTiposEstadisticas () override;
        void agregaHabilidadesPersonajes () override;
        void agregaEstadisticasHabilidades () override;
        void agregaEstadisticasPersonajes () override;
        void preparaSistemaAtaque () override;
        void configuraJuego () override;
        void termina () override;

    };


}


