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
			osg::ref_ptr<osg::Node> getNode();
			osg::ref_ptr<osg::Camera> getWindshieldCamera();
			void setCamera();

		private:

			 int tex_width;
			 int tex_height;
			 osg::ref_ptr<osg::Texture2D> texture;
			 osg::ref_ptr<osg::Camera> cameraWindshield;
			 osg::ref_ptr<osg::Group> windshieldGroup;
			 osg::ref_ptr<osg::Node> sub_model;
			 osg::ref_ptr<osg::MatrixTransform> windshield;






	};


}
