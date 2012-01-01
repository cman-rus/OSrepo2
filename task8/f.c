
void print(){
	*(short*)0xB8000=0x0731;
	main();
	return;
}
