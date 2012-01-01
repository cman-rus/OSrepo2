

void print(){
	int add	= 0xB8000;
	for(int i=0; i<80*25;++i)
	{
		*((short int *)add) =  0x0000;
		add+=2;
	}
	return;
}

