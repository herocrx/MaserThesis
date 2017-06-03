#include "windshieldImage.h"
#include "FindTextureVisitor.cpp"
#include <string>

namespace MasterThesisProject{


	windshieldImage::windshieldImage() : scale_parameter(0.3f), tex_width(0), tex_height(0){
		windshield = new osg::MatrixTransform;
		texture = new osg::Texture2D;
		cameraWindshield = new osg::Camera;
	    windshieldGroup = new osg::Group;
	    windshieldGroup->addChild(cameraWindshield.get());
	    windshieldGroup->addChild(windshield.get());
	}

	bool windshieldImage::setPositionWindshield(){
	    rotateMatrix = osg::Matrix::rotate(float(M_PI), float(-1/4*M_PI), float(1/4*M_PI), 1 );
	    scaleMatrix =  osg::Matrix::translate(0.4f, -0.3f, 0.0f);
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
	    sub_model = osgDB::readNodeFile(subModelName);
	    return;
	}



	void windshieldImage::setProjectionTextureCamera(){
		  cameraWindshield->setViewport(0,0,tex_width,tex_height);
		  cameraWindshield->setClearColor(osg::Vec4(1.0f,1.0f,1.0f,0.0f));
		  cameraWindshield->setClearMask(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		  cameraWindshield->setRenderOrder (osg::Camera::PRE_RENDER);
		  cameraWindshield->setRenderTargetImplementation(osg::Camera::FRAME_BUFFER_OBJECT);
		  cameraWindshield->attach (osg::Camera::COLOR_BUFFER, texture.get());
		   // Rendering on the whole surfacesetProjectionTextureCamera
		  cameraWindshield->setReferenceFrame (osg::Camera::ABSOLUTE_RF);
		  cameraWindshield->addChild (sub_model.get());
	}



	void windshieldImage::setTextureSize(){
		 tex_width = 1024;
		 tex_height = 1024;
		 texture->setTextureSize(tex_width,tex_height);
		 return;
	}


	void windshieldImage::setTextureFormatAndFilter(){
	    texture->setInternalFormat(GL_RGBA);
	    texture->setFilter(osg::Texture2D::MIN_FILTER,osg::Texture2D::LINEAR);
	    texture->setFilter(osg::Texture2D::MAG_FILTER,osg::Texture2D::LINEAR);
		return;
	}

	osg::Camera * windshieldImage::getWindshieldCamera(){
		return cameraWindshield.get();
	}

	osg::Node * windshieldImage::get(){
		return windshieldGroup.get();
	}


	void windshieldImage::attachAnimation(){
	    FindTextureVisitor ftv(texture.get());
	    if (windshield.valid())
	        windshield->accept(ftv);
		return;
	}


}

