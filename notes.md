## Things that I forget that I need to remember for the oral exam

# Classes
- Private objects of the classes are known as fields and public functions pertaining to the class are called methods
- The constructor of a class should should initialize all data members, in order to establish the class invariant; this is why those constructors I made for render and simulation seemed wonky to me, still would it be good to have such a large constructor in favor of class invariance or would it be better to define class invariance gradually?
- Mi rifiuto di usare lo standard cpp iso dell'ordine del tipo di membri per le classi; a me piace private: -> protected: -> public:; Io il mio codice lo scrivo così (anche perchè di protected I'l n'ya un caz in quanto non ci sono classi derivate, pappappero)
- C.40 è interessante e non l'avevo considerato, piuttosto che delegare l'invarianza di classe all'input del programma, farlo effettivamente fare come sarebbe giusto dal costruttore; la mia domanda rimane, per classi grandi come render, è meglio avere un costruttore di tante righe o separarlo e sacrificare un po' di invarianza di classe?
- Allora, view di sfml ha un costruttore che setta la posizione nello schermo e la dimensione della view, dato che andando a vedere nell'hpp view ha anche altri membri che non verrebbero inizializzati usando quel costruttore mi chiedo, è solo perchè sfml non segue iso cpp o perchè effettivamente in alcune situazioni è necessario avere dei costruttori che non ti inizializzano tutto?



    // La suddivisione sarà così, nel main voglio solo load di simulation_params
    // e render_params, poi faccio un conductor.run() e quello fa sì che render
    // si occupi della gestione della finestra (renderstart) e simulation
    // (simulationstart) faccia sì che behaviour(ex vChange) si occupi del
    // calcolo delle velocità e degli spostamenti, tutto sfruttando i metodi di
    // boid, in questa maniera ogni TU contiene correttamente tutte le parti
    // dedicate ad un singolo scopo e non ad un argomento. Devo arrivare a
    // gestire meglio il vettore di boids che chiamerò flock perchè altrimenti
    // com'è ora viene gestito in parte da main e da renderFrame di render, la
    // domanda è, come lo chiamo?
    // sviluppare una TU per statistics

    // Un pelo meglio la divisione in layer:
    // input layer: input e i due config file
    // base/math layer: v2D e rand
    // Simulation_lower:boid
    // Simulation: simulation
    // Render: render
    // Application: conductor

    //  Questo anche lo dovrei aggiungere nel render, relegarlo a quello



    Bruh

    # Main
    argc e argv sono abbreviazioni, sono parametri (arguments) di input del main, argc sarebbe argument count e argv sarebbe argument vector (array di string? char* argv[] o char** argv, indaghiamo meglio); li uso quando voglio che il main prenda argomenti dalla linea di comando o dalle impostazioni di avvio (uguale, solo che implicito) -> argc è sempre maggiore o uguale a uno poichè il nome del file è sempre il primo parametro/argomento