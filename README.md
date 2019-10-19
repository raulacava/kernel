# Project

## News
Running.
Init and the other four processes already separated.
There are still some to be separated.

## .C Files
- MAN_COLAS.C
  - meter_colas_listos(ID);
  - sacar_colas_listos(ID_POS);
  - primero_colas_listos();
- MAN_CPU.C
  - cambio_contexto();
    - push(ID_POS); // From Regs to Stack (_SS & _SP)
    - *PCL=primero_colas_listos();*
    - push(PCL); // From Stack to Regs (_SS & _SP)
    - *interrupt_8();* // Original
- INIT.C
  - init_sistema();
    - *interrupt_8();* // Original
    - getvect();
    - setvect();
  - activa(funcion, ID);
    - init_pcb(funcion, ID);
    - *meter_colas_listos(ID);*
    - *cambio_contexto();*
  - elimina();
    - *sacar_colas_listos(ID_POS);*
    - *cambio_contexto();*
  - salida();
- PROCESO0.C
  - proceso0();
    - *activa(funcion, ID);* // proc1, 1
    - *activa(funcion, ID);* // proc2, 2
    - *activa(funcion, ID);* // proc3, 3
    - *activa(funcion, ID);* // proc4, 4
    - *elimina();* // proceso0
- MAIN.C
  - *init_sistema();*
  - proceso0();
  - while(1);
  - *salida();*

## .H Files
- MAN_COLAS.H
  - PCL;
- MAN_CPU.H
  - PCB;
  - PCL;
- INIT.H
  - ID_POS;
- MAIN.H
- DATOS.H // Definitions
