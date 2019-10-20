# Project

## News
Running.
All the processes already separated.
There are still several functions to implement.

## .C Files
- [ ] MAN_COLAS.C
  - [ ] meter_colas_listos(ID);
  - [ ] sacar_colas_listos(ID_POS);
  - [ ] primero_colas_listos();
- [ ] MAN_CPU.C
  - [ ] cambio_contexto();
    - [ ] push(ID_POS); // From Regs to Stack (_SS & _SP)
    - [ ] *PCL=primero_colas_listos();*
    - [ ] push(PCL); // From Stack to Regs (_SS & _SP)
    - [x] *old_clock();* // Original
- [ ] INIT.C
  - [x] init_sistema();
    - [x] *old_clock();* // Original interrupt
    - [x] getvect();
    - [x] setvect();
  - [ ] activa(funcion, ID);
    - [ ] init_pcb(funcion, ID);
    - [ ] *meter_colas_listos(ID);*
    - [ ] *cambio_contexto();*
  - [ ] elimina();
    - [ ] *sacar_colas_listos(ID_POS);*
    - [ ] *cambio_contexto();*
  - [x] term_sistema();
    - [x] setvect();
- [ ] PROCESO0.C
  - proceso0();
    - [ ] *activa(funcion, ID);* // proc1, 1
    - [ ] *activa(funcion, ID);* // proc2, 2
    - [ ] *activa(funcion, ID);* // proc3, 3
    - [ ] *activa(funcion, ID);* // proc4, 4
    - [ ] *elimina();* // proceso0
- [ ] MAIN.C
  - [x] *init_sistema();*
  - [ ] proceso0();
  - [ ] while(1);
  - [x] *term_sistema();*

## .H Files
- [ ] MAN_COLAS.H
  - [ ] PCL;
- [ ] MAN_CPU.H
  - [ ] PCB;
- [ ] INIT.H
  - [x] old_clock();
  - [ ] ID_POS;
- [ ] MAIN.H
- [ ] DATOS.H // Definitions
