#include "windshieldController.cpp"



int main(int arg, char * argc[]){
    MasterThesisProject::windshieldController *Controller = new MasterThesisProject::windshieldController();
    Controller->setup();
    Controller->run();

	return 0;
}
