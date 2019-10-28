# Project

## News
Running.
All the processes already separated.
There are still several functions to implement.

## .C Files
- [x] MAN_COLAS.C
  - [x] meter_colas_listos(ID);
  - [x] sacar_colas_listos(ID_POS);
  - [x] primero_colas_listos();
- [ ] MAN_CPU.C
  - [ ] cambio_contexto();
    - [ ] push(ID_POS); // From Regs to Stack (_SS & _SP)
    - [ ] *PCL=primero_colas_listos();*
    - [ ] push(PCL); // From Stack to Regs (_SS & _SP)
    - [x] *old_clock();* // Original
- [x] INIT.C
  - [x] old_clock();
  - [x] init_sistema();
    - [x] *old_clock();* // Original interrupt
    - [x] *getvect();*
    - [x] *setvect();*
  - [x] init_pcb(funcion, ID);
  - [x] activa(funcion, ID);
    - [x] *init_pcb(funcion, ID);*
    - [x] *meter_colas_listos(ID);*
    - [x] *cambio_contexto();*
  - [x] elimina();
    - [x] *sacar_colas_listos(ID_POS);*
    - [x] *cambio_contexto();*
  - [x] term_sistema();
    - [x] *setvect();*
- [x] PROC0.C
  - [x] proc0();
    - [x] *activa(funcion, ID);* // proc1, 1
    - [x] *activa(funcion, ID);* // proc2, 2
    - [x] *activa(funcion, ID);* // proc3, 3
    - [x] *activa(funcion, ID);* // proc4, 4
    - [x] *elimina();* // proceso0
- [x] MAIN.C
  - [x] *init_sistema();*
  - [x] *proceso0();*
  - [x] while (1);
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


## Prueba de escritorio.
main();
```
- main(); // MAIN.C
  - init_system(); // INIT.C
    - **disable();**
    - old_clock = getvect(CLK_INT);
    - setvect(CLK_INT, context_switch);
    - activa(&proc0, 0);
      - **disable();**
      - init_pcb(process, id);
      - meter_cola_listos(id);
      - context_switch();
        - **disable();**
        - push();
        - primero_cola_listos();
        - (*old_clock)();
        - pop();                 // proc0

```
proc0();
```
- proc0();
  - activa(&proc1, 1);
    - **disable();**
    - init_pcb(process, id);
    - meter_cola_listos(id);
    - context_switch();
      - **disable();**
      - push();                // Guarda proc0
      - primero_cola_listos();
      - (*old_clock)();
      - pop();                 // proc1
```
proc1();
```
- proc1();
  - while(1);                // enable()
  - context_switch();        <=
    - **disable();**
    - push();                // Guarda proc1
    - primero_cola_listos();
    - (*old_clock)();
    - pop();                 // proc0
```
proc0();
```
      - **enable();**          // context_switch
    - **enable();**            // activa(&proc1, 1)
  - activa(&proc2, 2);
    - **disable();**
    - init_pcb(process, id);
    - meter_cola_listos(id);
    - context_switch();
      - **disable();**
      - push();                // Guarda proc0
      - primero_cola_listos();
      - (*old_clock)();
      - pop();                 // proc1
```
proc1();
```
  - while(1);                // enable()
  - context_switch();        <=
    - **disable();**
    - push();                // Guarda proc1
    - primero_cola_listos();
    - (*old_clock)();
    - pop();                 // proc2
```
proc2();
```
- proc2();
  - while(1);                // enable()
  - context_switch();        <=
    - **disable();**
    - push();                // Guarda proc2
    - primero_cola_listos();
    - (*old_clock)();
    - pop();                 // proc0
```
proc0;
```
      - **enable();**          // context_switch
    - **enable();**            // activa(&proc2, 2)
  - activa(&proc3, 3);
    - **disable();**
    - init_pcb(process, id);
    - meter_cola_listos(id);
    - context_switch();
      - **disable();**
      - push();                // Guarda proc0
      - primero_cola_listos();
      - (*old_clock)();
      - pop();                 // proc1
```
proc1();
```
  - while(1);                // enable()
  - context_switch();        <=
    - **disable();**
    - push();                // Guarda proc1
    - primero_cola_listos();
    - (*old_clock)();
    - pop();                 // proc2
```
proc2();
```
- proc2();
  - while(1);                // enable()
  - context_switch();        <=
    - **disable();**
    - push();                // Guarda proc2
    - primero_cola_listos();
    - (*old_clock)();
    - pop();                 // proc3
```
proc3();
```
- proc3();
  - while(1);                // enable()
  - context_switch();        <=
    - **disable();**
    - push();                // Guarda proc3
    - primero_cola_listos();
    - (*old_clock)();
    - pop();                 // proc0
```
proc0;
```
      - **enable();**          // context_switch
    - **enable();**            // activa(&proc3, 3)
  - activa(&proc4, 4);
    - **disable();**
    - init_pcb(process, id);
    - meter_cola_listos(id);
    - context_switch();
      - **disable();**
      - push();                // Guarda proc0
      - primero_cola_listos();
      - (*old_clock)();
      - pop();                 // proc1
```
proc1();
```
  - while(1);                // enable()
  - context_switch();        <=
    - **disable();**
    - push();                // Guarda proc1
    - primero_cola_listos();
    - (*old_clock)();
    - pop();                 // proc2
```
proc2();
```
  - while(1);                // enable()
  - context_switch();        <=
    - **disable();**
    - push();                // Guarda proc2
    - primero_cola_listos();
    - (*old_clock)();
    - pop();                 // proc3
```
proc3();
```
  - while(1);                // enable()
  - context_switch();        <=
    - **disable();**
    - push();                // Guarda proc3
    - primero_cola_listos();
    - (*old_clock)();
    - pop();                 // proc4
```
proc4();
```
- proc4();
  - while(1);                // enable()
  - context_switch();        <=
    - **disable();**
    - push();                // Guarda proc4
    - primero_cola_listos();
    - (*old_clock)();
    - pop();                 // proc0
```
proc0();
```
      - **enable();**          // context_switch
    - **enable();**            // activa(&proc4, 4)
  - elimina(0);
    - **disable();**
    - sacar_cola_listos(id);   // f = 0
    - context_switch();
	  - **disable();**
      - push();                // Guarda proc0
      - primero_cola_listos();
      - (*old_clock)();
      - pop();                 // proc1
```
proc1();
```
  - while(1);                // enable()
  - context_switch();        <=
    - **disable();**
    - push();                // Guarda proc1
    - primero_cola_listos();
    - (*old_clock)();
    - pop();                 // proc2
```
proc2();
```
  - while(1);                // enable()
  - context_switch();        <=
    - **disable();**
    - push();                // Guarda proc2
    - primero_cola_listos();
    - (*old_clock)();
    - pop();                 // proc3
```
proc3();
```
  - while(1);                // enable()
  - context_switch();        <=
    - **disable();**
    - push();                // Guarda proc3
    - primero_cola_listos();
    - (*old_clock)();
    - pop();                 // proc4
```
proc4();
```
  - while(1);                // enable()
  - context_switch();        <=
    - **disable();**
    - push();                // Guarda proc4
    - primero_cola_listos();
    - (*old_clock)();
    - pop();                 // proc1
```




```
    - enable();
```
