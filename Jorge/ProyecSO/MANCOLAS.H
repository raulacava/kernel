
void Insertcola(int n);
void Eliminarcola();
int Primerocola();
void Terminarproces();

int Primerocola()
{
return cola[front];
}

void Insertcola(int n)
{
if((end+1)%tam == front)
return;
else if(front == -1 && end == -1)
{
front = 0;
end = 0;
}
else
end = (end+1)%tam;

cola[end] = n;
}


void Eliminarcola()
{

if(front == -1 && end == -1)
return;
else if(front == end)
{
front = -1;
end = -1;
}
else
{
front = (front+1)%tam;
}

}

void Terminarproces()
{
PCB[Primerocola()].status = 0;
}



