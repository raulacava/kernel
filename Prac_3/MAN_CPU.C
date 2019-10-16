//#include <DATOS.H>

void interrupt context_switch() {
	disable();

	pcbs[PtrRun->Este].ss = _SS;
	pcbs[PtrRun->Este].sp = _SP;

	g_bFirstRun = 0;

	if (++g_iTicks >= 18) {
		g_iTicks = 0;
		g_iSeconds++;
	}

	InsertaListos(PtrRun);
	PtrRun = PrimeraTarea();

	_SS = pcbs[PtrRun->Este].ss;
	_SP = pcbs[PtrRun->Este].sp;
	gotoxy(g_iLastX,g_iLastY);
	old_clock();
	enable();
}
