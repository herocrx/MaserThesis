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
			bool setLight();
			void addBackground();
			windshieldImage  *Windshield;
			osg::ref_ptr<osg::MatrixTransform> axes;
			osg::ref_ptr<osg::Camera> mainCamera;
			osgViewer::Viewer viewer;
			osg::ref_ptr<keyboardController> keyboardControl;
			struct Background{
				osg::Geometry* pGeo;
				osg::Vec3Array* pVerts;
				osg::DrawElementsUInt* pPrimitiveSet;
				osg::Vec2Array* pTexCoords;
				osg::Geode* pGeode;
				osg::ref_ptr<osg::MatrixTransform> backgroundRootMatrix;
			};
			Background * background;


	};







}

