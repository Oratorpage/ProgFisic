# Top Priorities

- [ ] Fine test, ~boids TU~ e vChange TU
- [ ] Gestione della finestra e degli eventi, bisogna avere tutto nel loop while window is open

# Functional

- [ ] Sistema l'aggiornamento della posizione (la distanza) in modo che faccia wrap-around e veda quelli dall'altro lato, altrimenti non è precisa la modalità toroidale, un po'bruttina
- [ ] Quando sistemi la cosa sopra devi anche sistemare gli inerenti test case(boids toroidal ') in quanto cambia la situazione
- [ ] Guarda la cosa che diceva giacomini della gestione della finestra iowindow e del polling degli eventi
- [ ] ALGOTRITHM THE WORLD, IF NOT THERE YOU CAN THINK OF MAKING YOUR OWN
- [ ] Create different behaviours and make them optional -> this means changing the vChange accordingly, would maybe require an enum for the tyoe of behaviour -> con questo si può anche aggiungere un'opzione per limitare/modificare l'angolo di visuale del singolo boid; questo è inerente a vChange, bisogna modificare il modo di aggiunta dei nearboids (riuscire a modificare solo quello rispetto all'aggiornamento totale secondo me sarebbe pulito, bisogna vedere se in realtà è comodo per l'aggiornamento della posizione, non so se funzioni ugualmente)
- [ ] Resize according to window
- [ ] Add another window that displays stats for the boid flock, ~cm position, average velocity,~ highest, lowest, ~number of boids on screen~, average position between boids
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
- [x] Create the border non toroidal/toroidal option:  toroidal space in tandem with velocity limit
- [x]  ~output statistics~ + ~optional radiuses~ 
- [x] Fix Class invariance with the constexpression, look up theory before

**Assignment**
- [x] Input da file
- [x] Do the initialization by file dude, it's time
- [x] Sistema i nomi delle variabili per migliorare la comprensione
- [x] Put everything into the namespace
- [x] Implement the try catch in general 
- [x] Divide into multiple translation units + file with tests