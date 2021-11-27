


void setupSegment();
void resetDiskSystem();
void printMessage();
void readSecondStage();


void BootEntry() {
	//setupSegments();
	//resetDiskSystem();
	//printMessage();
	//readSecondStage();
	asm
	( 
	".intel_syntax;"
	"hlt;"  
	);
	//hlt;
	//jmp 0x7e00;
}


void setupSegments() {

}


void resetDiskSystem() {

}


void printMessage() {
	char message[] = "Loading OS...\n\x00";

}


void readSecondStage() {


}






