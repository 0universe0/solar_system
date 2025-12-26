# Solar System

## geocentrism rocks!

Final project for the "Computing Techniques for Physics" course in the Bachelor's Degree in Physics at the University of Turin.
The goal is to simulate the solar system in C++, implementing a graphical motor with openGL to visualize the orbits of the planets in 3 dimensions. Coincidentally we also verify the validity of the second and third Kepler's laws.

### Luca Tempesta, Paolo Rocchietti March, Alessandro Romanini

## Struttura

Il progetto è suddiviso in directories:
    * src: contiene i file source (.cpp)
    * include: contiene i file header (.h, .cc)
Inoltre utilizzeremo Make come strumento per gestire in modo automatizzato la compilazione.
Se il progetto dovesse crescere in modo tale da rendere disturbante l'utilizzo stesso di Make,
utilizzeremo CMake, rendendo così automatizzata la generazione di file Make utilizzati per buildare gli eseguibili (.o)
