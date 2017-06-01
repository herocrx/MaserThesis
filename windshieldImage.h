#include <osg/Camera>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>
#include <osgViewer/Viewer>
#include <osg/MatrixTransform>
#include <osg/BlendFunc>
#include <osg/LightSource>

namespace MasterThesisProject {


	class windshieldImage{
		public:
			windshieldImage();
			bool attachWindshieldAsTexture();
			void setTextureSize();
			bool setPositionWindshield();
			bool setLight();
			osg::Node * getNode();
			osg::Node * getWindshieldCamera();
			void setTextureFormatAndFilter();
			void loadWindshieldObject(std::string);
			void loadSubModel(std::string);
			void attachAnimation();
			void setProjectionTextureCamera();
			void setHeadCamera();
			void EncapsulateBlendTransparencyState();
			osg::Node * release();
		private:

			 int tex_width;
			 int tex_height;
			 osg::ref_ptr<osg::Texture2D> texture;
			 osg::ref_ptr<osg::Camera> cameraWindshield;
			 osg::ref_ptr<osg::Group> windshieldGroup;
			 osg::ref_ptr<osg::Camera> mainCamera;
			 osg::ref_ptr<osg::Node> sub_model;
			 osg::ref_ptr<osg::MatrixTransform> windshield;


			 osg::Matrix rotateMatrix;
			 osg::Matrix scaleMatrix;
			 float scale_parameter;
			 osg::Matrix translateMatrix;
	};


}
