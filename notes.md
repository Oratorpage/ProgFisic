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

    ## Invarianza di classe
    - [ ] Per simulation, dove ho struct come statistics che non posso inizializzare a qualcosa di utile perchè non (in realtà potrei fare una funzione void calculate statistics come per il vettore flock in maniera da inizializzarlo subito e sistemarlo in maniera corretta)

    # Main
    argc e argv sono abbreviazioni, sono parametri (arguments) di input del main, argc sarebbe argument count e argv sarebbe argument vector (array di string? char* argv[] o char** argv, indaghiamo meglio); li uso quando voglio che il main prenda argomenti dalla linea di comando o dalle impostazioni di avvio (uguale, solo che implicito) -> argc è sempre maggiore o uguale a uno poichè il nome del file è sempre il primo parametro/argomento

    ## Cose che ho rimosso su cui può essere utile tornare
    /* No bad values can be introduced for a boid initialization, any value that
    doesn't produce compilation errors is acceptable, if it is far from the
    window or if it has the speed of a photon it's not a problem. --- Well with the
    implementation of the current world it is but it ain't a boid problem

    If it is far (in any direction)(and not in toroidal mode) it will be back
    thanks to the update member function and the velocity update; if it is in
    toroidal mode it will just go back to a border in the next update.

    For the velocity it is regulated by the update member function.

     It may have an initial wrong position for the first few milliseconds but
     considering how the user is not prompted to initialize any singular boids it
    shouldn't be a problem, it wouldn't be even with the manual insertion since the
    only thing the user can decide would be the position (by clicking inside the
    window).

    Qua bisogna chiedere se test e struttura delle TU va fatta in maniera tale che
    funzioni anche stand-alone con un main generico come libreria perchè in quel
    caso devo cambiare effettivamente un po' di cose
*/

// Dovrei includere direttamente BoidProperties nel costruttore di Simulation?
// Anche una prima inizializzazione di stats? Suppongo dipende da quando viene
// chiamato l'oggetto, nel programma mi devo assicurare che quando venga
// chiamato non ritorni cose a caso. Non è necessario no che per una good cpp
// practice ogni oggetto appartenente ad una classe venga completamente
// inizializzato? yesss, perchè l'oggetto della classe dopo sarebbe in parte
// invalido dunque bisogna inizializzare ad un qualche valore di default
// statistics per esempio e poi fare {} in modo che venga usata la costruzione
// di default, poi lo si va a modificare
// Viene inizializzato di defualt con {} o senza nulla con ; perchè dipende
// molto, devo controllare nelle dispende questa cosa