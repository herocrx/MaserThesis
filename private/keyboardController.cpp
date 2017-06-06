#include <iostream>
#include "keyboardController.hpp"

namespace MasterThesisProject{

	keyboardController::keyboardController(): windshieldStatus(true){}

	bool keyboardController::handle(const osgGA::GUIEventAdapter & ea, osgGA::GUIActionAdapter & aa){
		switch (ea.getEventType()){
			case osgGA::GUIEventAdapter::KEYDOWN:
				switch ( ea.getKey() ){
					case 't': case 'T':
						std::cout << "Zmiana" << std::endl;
						windshieldStatus = !windshieldStatus;
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}
		return false;
	}


	bool keyboardController::showWindshield(){
		return windshieldStatus;
	}





}
