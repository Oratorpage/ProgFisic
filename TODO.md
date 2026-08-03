# Big things
- [ ] Finishing the cooperation between simulation and behaviour, ~between render, simulation and conductor~
- [ ] Fixing the input (redirecting logic)
- [ ] Making the shell prompt argv argc thingamabob

# DUDE
- [ ] Guarda quando si può e quando non fare il default per le classi; per esempio, per i boid ha senso poter fare il default, crei un boid e poi ti modifichi come lo vuoi e non c'è problema in quanto è sensato e realistico; per una cosa come la simulazione, dove ho oggetti membro(fields) che sono classi a loro volta diventa complicato e probabilmente poco utile in quanto un oggetto simulazione che viene definito in un main futuro per essere usato, devo sapere qual'è uno stato accettabile iniziale in cui lo trovo; in questo senso immagino ci sia il metodo o inizializzi tutto in modo da poter fare un default o non inizializzi nulla e sei tranquillo
- [ ] Gestione inizializzazione costruttore, parziale o totale, simulazione, render, world, tutte le classi
- [ ] Verifica come funzionano le funzioni private e la correttezza d'uso
- [ ] Verifica il ritorno del membro vettore di boids (flock) Simulation::currentFlock()
- [ ] Fai effettivamente la funzione tick di simulation
- [ ] Dai un'altro occhio a render che mi pare strano funzioni incredibilmente tutto bene, ci sarà qualcosa che non va; inoltre fai un controllo addizzionale su quel costruttore, sono 17 righe non contando gli spazi
- [ ] Va senza dubbio fatto altro con World, non mi ricordo cos'altro mi fossi segnato, vai a guardare sul quaderno
- [ ] Tutto behaviour va riguardato e sistemato, non dovrebbe essere terribile, bisogna reindirizzare la logica che segue e fare in modo che segua il nuovo flusso
- [ ] Input va rifatto ex-novo considerando tutta la nuova struttura dati, anche lì probabilmente sarà solo un redirezionamento di input, la logica effettiva non varia troppo solo I/O
- [ ] Il main va fatto anche quello da capo e lì inoltre bisogna implementare una cosa che permetta di leggere i comandi da terminale come ci aveva fatto vedere giacomini all'epoca, sarebbe effettivamente molto figo e professionale
- [ ] Sarebbe il caso di renderle template funzioni e classi? Per ora opero con un tipo, per le simulazioni fisiche i double sono lo standard per cui bho
- [ ] Bisognerebbe iniziare a fare una mappa del programma, trova un sito/programma che permetta di farlo, magari uno di quelli tipo per gli homelab, così impari anche ad usarlo; poi domani se riesco guardo anche il router che ho trovato e provo a far funzionare il vecchio computer e farlo comunicare via wi-fi con junker


# Controlli
- [ ] Metodi che non vanno a modificare i membri di una classe (fields) devono essere dichiarati const
- [ ] Passaggio by reference e by value, soprattutto negli operatori e funzioni membro
- [ ] Valuta se chiamarli getter-setters o se lasciarli con i tuoi nomi attuali
- [ ] Elimina funzioni membro o libere inutili (se pensi utili nel futuro commentale)
- [ ] Sistema i costruttori in maniera da renderli deleganti (penso sia possibile solo per boid)
- [ ] Come scritto a slide 150 non inizializzare i membri con {} vuote, delle due inserisci dei valori (penso che per il caso di simulation per esempio, con World ed altre struct e classi membro, passi attraverso con {} e vada alla sua inizializzazione di default quindi lì forse non c'è bisogno di togliere le graffe, vedi la documentazione)
- [ ] Se in un costruttore inizializzo un membro che è solo value const, allora delle due è meglio inizializzarlo nella classe e lasciare che il compilatore crei un default constructor
- [ ] Forse è il caso di definire un'invariante di classe meglio per i boid? per dire un assert sul fatto che la velocità debba essere minore o uguale o bho
- [ ] Definire correttamente i throw in base al tipo e assicurarsi che siano caught "catch" per const&
- [ ] Effettivamente definire dei throw nei costruttori per meglio stabilire l'invarianza di classe?
- [ ] Guarda se si può fare la somma del cm con un algoritmo per la variazione di velocità comportamentale
- [ ] Indaga sulla slide 228 ("the type has to be complete", referring to definitin) Non significa che bisogna anche sviluppare tutti gli operatori ed i modi per manipolarlo vero? Come al solito penso sia riferito alle cose effettivamente utili
- [ ] Fai un check sulle funzioni non metodo definite negli header, ce ne sono alcune non metodo? Vanno definite inline allora

- Fatto fino a slide 243, il resto è gestione delle risorse, valori sull'heap e cose del genere, non lo farò certamente ora in quanto non serve, quando servirà  ci tornerò

- [ ] Il fatto che io non dia la possibilità di riprodurre lo stesso stato è un problema? Non è seed based, è  completamente randomico effettivamente


# Top Priorities

- [ ] Fine gestione angolo, fine gestione inseguimento dei predatori e allontanamento delle prede, devi fare i calcoli lì
- [ ] Fine test, ~boids TU~ e vChange TU
- [work_in_progress] Trimma le funzioni per seguire la regola una funzione una cosa, in particolare vChange e render

# Functional

- [ ] Sistema l'aggiornamento della posizione (la distanza) in modo che faccia wrap-around e veda quelli dall'altro lato, altrimenti non è precisa la modalità toroidale, un po'bruttina
- [ ] Quando sistemi la cosa sopra devi anche sistemare gli inerenti test case(boids toroidal ') in quanto cambia la situazione
- [ ] ALGOTRITHM THE WORLD, IF NOT THERE YOU CAN THINK OF MAKING YOUR OWN
- [ ] Create different behaviours and make them optional -> this means changing the vChange accordingly, would maybe require an enum for the tyoe of behaviour -> con questo si può anche aggiungere un'opzione per limitare/modificare l'angolo di visuale del singolo boid; questo è inerente a vChange, bisogna modificare il modo di aggiunta dei nearboids (riuscire a modificare solo quello rispetto all'aggiornamento totale secondo me sarebbe pulito, bisogna vedere se in realtà è comodo per l'aggiornamento della posizione, non so se funzioni ugualmente)
- [ ] MIRROR MIRROR OF MY WILL ARE YOU READY TO BE PARALLELIZED
- [ ] Maybe add an initialization function that allows you to create boids where you click with the mouse?
- [ ] Maybe a trail for the boids would be kind of nice graphically?
- [ ] Istogramma sulla statistica della simulazione, volendo metterlo anche direttamente all'interno della finestra della simulazione


---

# Assignment

- [ ] Check performance and usability of algorithms

---

# DONE
**Func:**
- [x] Add another window that displays stats for the boid flock, ~cm position, average velocity,~ highest, lowest, ~number of boids on screen~, average position between boids(Not gonna do highest lowest, dumb, will try to look into root statistics)
- [kinda] Resize according to window
- [x] Guarda la cosa che diceva giacomini della gestione della finestra iowindow e del polling degli eventi
- [x] Create the border non toroidal/toroidal option:  toroidal space in tandem with velocity limit
- [x]  ~output statistics~ + ~optional radiuses~ 
- [x] Fix Class invariance with the constexpression, look up theory before

**Assignment**
- [x] Gestione della finestra e degli eventi, bisogna avere tutto nel loop while window is open
- [x] Input da file
- [x] Do the initialization by file dude, it's time
- [x] Sistema i nomi delle variabili per migliorare la comprensione
- [x] Put everything into the namespace
- [x] Implement the try catch in general 
- [x] Divide into multiple translation units + file with tests