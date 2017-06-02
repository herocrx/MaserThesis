#include "windshieldImage.cpp"


namespace MasterThesisProject{

	class windshieldController{
		public:
			windshieldController();
			void setup();
			void run();
		private:
			void addWindshield();
			void addAxes();
			void addHeadCamera();
			windshieldImage  *Windshield;
			osg::ref_ptr<osg::MatrixTransform> axes;
			osg::ref_ptr<osg::Camera> mainCamera;
			osgViewer::Viewer viewer;
	};







}

