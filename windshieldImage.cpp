#include "windshieldImage.h"
#include "FindTextureVisitor.cpp"
#include <string>

namespace MasterThesisProject{
	windshieldImage::windshieldImage() : scale_parameter(1.0f), tex_width(0), tex_height(0){
		windshield = new osg::MatrixTransform;
		texture = new osg::Texture2D;
		cameraWindshield = new osg::Camera;
		mainCamera = new osg::Camera;
	}



	bool  windshieldImage::attachWindshieldAsTexture(){
		std::cout <<"Hubi to mistrz" << std::endl;
		std::cout << "Hero" << std::endl;

	}



	bool windshieldImage::setPositionWindshield(){
	    rotateMatrix = osg::Matrix::rotate(M_PI, 0, 0, 1 );
	    scaleMatrix =  osg::Matrix::translate(3.0f, 0.0f, 0.0f);
	    scale_parameter = 1.0f;
	    osg::Matrix translateMatrix = osg::Matrix::scale(osg::Vec3d(scale_parameter,scale_parameter,scale_parameter));
	    windshield->setMatrix(translateMatrix*rotateMatrix*scaleMatrix );
	    return true;
	}

	void windshieldImage::EncapsulateBlendTransparencyState(){
		 osg::BlendFunc *fuct = new osg::BlendFunc();
		 fuct->setFunction(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		 windshield->getOrCreateStateSet()->setAttributeAndModes(fuct);
		 windshield->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
		 return;
	}


	void windshieldImage::loadWindshieldObject(std::string WindshieldName = "Windshield.osg"){
	    std::cout << "Used windshield model: " << WindshieldName << std::endl;
		windshield->addChild(osgDB::readNodeFile(WindshieldName));
	    return;
	}

	void windshieldImage::loadSubModel(std::string subModelName = "glider.osg"){
	    osg::ref_ptr<osg::Node> sub_model = osgDB::readNodeFile(subModelName);
	    return;
	}



	bool windshieldImage::setLight(){
		osg::Light* pLight = new osg::Light();
		pLight->setLightNum (0);
		pLight->setAmbient (osg::Vec4d (0.0, 0.0, 0.0, 1.0));
		pLight->setDiffuse (osg::Vec4d (0.0, 0.0, 0.0, 1.0));
		pLight->setSpecular (osg::Vec4d (0.0, 0.0, 0.0, 1.0));
		osg::LightSource* pLightsource = new osg::LightSource();
		pLightsource->setLight (pLight);
		pLightsource->setStateSetModes (*cameraWindshield->getOrCreateStateSet(), osg::StateAttribute::ON);
		cameraWindshield->addChild (pLightsource);
	}



	osg::Node * windshieldImage::getNode(){





	}

	void windshieldImage::setCamera(){
	    mainCamera->addChild(windshieldGroup.get());
	    mainCamera->setClearColor(osg::Vec4(0.0f,1.0f,1.0f,0.0f));
	    mainCamera->setViewMatrixAsLookAt(osg::Vec3(0.0f,0.0f,-15.0f),osg::Vec3(),osg::Vec3(0.0f,2.0f,0.0f));
	    mainCamera->setRenderTargetImplementation(osg::Camera::FRAME_BUFFER, osg::Camera::FRAME_BUFFER);
	    // Nie mam pojecia co to robi
	    //mainCamera->setReferenceFrame(osg::Camera::ABSOLUTE_RF);
	    mainCamera->setRenderOrder ( osg::Camera::POST_RENDER);
	}

	void windshieldImage::setTextureSize(){
		 tex_width = 1024;
		 tex_height = 1024;
		 texture->setTextureSize(tex_width,tex_height);

	}


	void windshieldImage::setTextureFormatAndFilter(){
	    texture->setInternalFormat(GL_RGBA);
	    texture->setFilter(osg::Texture2D::MIN_FILTER,osg::Texture2D::LINEAR);
	    texture->setFilter(osg::Texture2D::MAG_FILTER,osg::Texture2D::LINEAR);
		return;
	}

	osg::Node * windshieldImage::getWindshieldCamera(){
		return cameraWindshield.release();
	}

	void windshieldImage::attachAnimation(){
	    FindTextureVisitor ftv(texture.get());
	    if (windshield.valid())
	        windshield->accept(ftv);
		return;
	}


	osg::Node * windshieldImage::release(){
		return mainCamera.release();
	}


}

