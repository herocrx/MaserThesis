
#include <osgGA/TrackballManipulator>
#include <osgViewer/Viewer>
#include <osg/BlendFunc>
#include <osg/LightSource>

namespace MasterThesisProject {


	class windshieldImage{
		public:
			windshieldImage();
			void setTextureSize();
			bool setPositionWindshield();
			bool setLight();
			osg::Camera * getWindshieldCamera();
			void setTextureFormatAndFilter();
			void loadWindshieldObject(std::string);
			void loadSubModel(std::string);
			void attachAnimation();
			void setProjectionTextureCamera();
			void EncapsulateBlendTransparencyState();
			osg::Node * get();
		private:
			int tex_width;
			int tex_height;
			float scale_parameter;
			osg::ref_ptr<osg::Texture2D> texture;
			osg::ref_ptr<osg::Camera> cameraWindshield;
			osg::ref_ptr<osg::Group> windshieldGroup;
			osg::ref_ptr<osg::Camera> mainCamera;
			osg::ref_ptr<osg::Node> sub_model;
		    osg::ref_ptr<osg::MatrixTransform> windshield;
			osg::Matrix rotateMatrix;
			osg::Matrix scaleMatrix;
			osg::Matrix translateMatrix;
	};


}
