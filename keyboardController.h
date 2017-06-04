#include <osgGA/GUIEventHandler>

namespace MasterThesisProject{
	class keyboardController: public osgGA::GUIEventHandler{
		public:
			keyboardController();
			virtual bool handle ( const osgGA::GUIEventAdapter & ea, osgGA::GUIActionAdapter & aa);
			bool showWindshield();
		private:
			bool windshieldStatus;
	};

}
