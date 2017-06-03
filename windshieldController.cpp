#include <osg/Camera>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osg/MatrixTransform>
#include "windshieldController.h"

namespace MasterThesisProject{

	windshieldController::windshieldController(){
			Windshield = new windshieldImage();
			mainCamera = new osg::Camera();
	}

	void windshieldController::setup(){
		addWindshield();
		addHeadCamera();
		addAxes();
		mainCamera->addChild(Windshield->get());
		mainCamera->addChild(axes);
		viewer.setSceneData(mainCamera.get());
		return;
	}

	void windshieldController::run(){
		//viewer.setCameraManipulator(new osgGA::TrackballManipulator);
		float delta = 0.001f, bias= 0.0f;
		osg::Vec3 eye(0.5f,-1.0f,5.0f);
		int frame=  0;
		while ( !viewer.done()){
			//std::cout << "bias: " << bias << std::endl;
			if (bias<-1.0f){
				delta = 0.001f;
				//std::cout << "bias<-1.0" << std::endl;
			}
			else if ( bias>1.0f){
				delta = -0.001f;
				//std::cout << "bias>1.0" << std::endl;
			}
			bias+=delta;
			Windshield->getWindshieldCamera()->setViewMatrixAsLookAt(eye,osg::Vec3(0,0,0),osg::Vec3(bias,0.5f,0.5f));
			frame++;
			viewer.frame();
		}
		return;
	}


	void windshieldController::addWindshield(){
		Windshield->loadSubModel();
		Windshield->loadWindshieldObject();
		Windshield->setPositionWindshield();
		Windshield->setTextureSize();
		Windshield->setTextureFormatAndFilter();
		Windshield->EncapsulateBlendTransparencyState();
		Windshield->attachAnimation();
		Windshield->setProjectionTextureCamera();
		return;
	}

	void windshieldController::addAxes(){
	    float scale_parameter = 0.2f;
		axes = new osg::MatrixTransform;
	    axes->setMatrix(osg::Matrix::translate(-6.0f, -3.5f, 0.0f) * osg::Matrix::scale(osg::Vec3d(scale_parameter,scale_parameter,scale_parameter)));
	    axes->addChild(osgDB::readNodeFile("axes.osgt"));
	    return;
	}

	void windshieldController::addHeadCamera(){
	    mainCamera->setClearColor(osg::Vec4(0.0f,1.0f,1.0f,0.0f));
	    mainCamera->setViewMatrixAsLookAt(osg::Vec3(0.0f,0.0f,-3.0f),osg::Vec3(),osg::Vec3(0.0f,2.0f,0.0f));
	    mainCamera->setRenderTargetImplementation(osg::Camera::FRAME_BUFFER, osg::Camera::FRAME_BUFFER);
	    // Nie mam pojecia co to robi
	    //mainCamera->setReferenceFrame(osg::Camera::ABSOLUTE_RF);
	    mainCamera->setRenderOrder ( osg::Camera::POST_RENDER);
	    return;
	}



}
