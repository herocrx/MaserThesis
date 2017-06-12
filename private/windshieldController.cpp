
#include <osg/Camera>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osg/Geode>
#include <osg/MatrixTransform>
#include "keyboardController.cpp"
#include "windshieldController.hpp"

namespace MasterThesisProject{

	windshieldController::windshieldController(){
			Windshield = new windshieldImage();
			mainCamera = new osg::Camera();
			keyboardControl = new keyboardController();
			background = new Background();
	}

	void windshieldController::setup(){
		addWindshield();
		addHeadCamera();
		addAxes();
		addBackground();
		mainCamera->addChild(Windshield->get());
		mainCamera->addChild(axes);
		mainCamera->addChild(background->backgroundRootMatrix.get());
		viewer.setSceneData(mainCamera.get());
		//setLight();
		return;
	}

	void windshieldController::run(){
		viewer.addEventHandler( keyboardControl.get() );
		viewer.setCameraManipulator(new osgGA::TrackballManipulator);
		float delta = 0.001f, bias= 0.0f;
		while ( !viewer.done()){
			osg::Vec3 eye(-5.5f,-10.0f,5.0f);
			if (bias<-1.0f){
				delta = 0.001f;
			}
			else if ( bias>1.0f){
				delta = -0.001f;
			}
			bias+=delta;
			Windshield->getWindshieldCamera()->setViewMatrixAsLookAt(eye,osg::Vec3(0,0,0),osg::Vec3(bias,0.5f,0.5f));

			viewer.frame();
		}
		return;
	}

	void windshieldController::addBackground(){
		background->pGeo = new osg::Geometry;
		background->backgroundRootMatrix = new osg::MatrixTransform();
		float scale_parameter = 3.0f;
		osg::Matrix rotateMatrix = osg::Matrix::rotate(90, M_PI, 0, 0 );
		background->backgroundRootMatrix->setMatrix(rotateMatrix * osg::Matrix::scale(osg::Vec3d(scale_parameter,scale_parameter,scale_parameter))* osg::Matrix::translate(0.0f, 0.0f, 0.1));
		// add 4 vertices creating a quad
		osg::Vec3Array* pVerts = new osg::Vec3Array;
		pVerts->push_back( osg::Vec3( 0, 0, 0 ) );
		pVerts->push_back( osg::Vec3( 1, 0, 0 ) );
		pVerts->push_back( osg::Vec3( 1, 0, 1 ) );
		pVerts->push_back( osg::Vec3( 0, 0, 1 ) );
		background->pGeo->setVertexArray( pVerts );

		// create a primitive set
		background->pPrimitiveSet = new osg::DrawElementsUInt(
		osg::PrimitiveSet::QUADS, 0 );
		background->pPrimitiveSet->push_back( 3 );
		background->pPrimitiveSet->push_back( 2 );
		background->pPrimitiveSet->push_back( 1 );
		background->pPrimitiveSet->push_back( 0 );
		background->pGeo->addPrimitiveSet( background->pPrimitiveSet );

		// create an arraw for texture coordinates
		background->pTexCoords = new osg::Vec2Array( 4 );
		(*background->pTexCoords)[0].set( 0.0f, 0.0f );
		(*background->pTexCoords)[1].set( 1.0f, 0.0f );
		(*background->pTexCoords)[2].set( 1.0f, 1.0f );
		(*background->pTexCoords)[3].set( 0.0f, 1.0f );
		background->pGeo->setTexCoordArray( 0, background->pTexCoords );

		// create geometry node that will contain all our drawables
		background->pGeode = new osg::Geode;
		osg::StateSet* pStateSet = background->pGeode->getOrCreateStateSet();
		pStateSet->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
		background->pGeode->addDrawable( background->pGeo );

		// load and set texture attribute and mode
		osg::Texture2D* pTex = new osg::Texture2D;
		osg::Image* pImage = osgDB::readImageFile( "resources/background.jpeg" );
		if(!pImage) {
		std::cout << "Error: Couldn't find texture!" << std::endl;
		}
		else
		std::cout << "The texture has been found!" << std::endl;
		pTex->setImage( pImage );
		pStateSet->setTextureAttributeAndModes( 0, pTex,osg::StateAttribute::ON );

		background->pGeo->setStateSet(pStateSet);

		background->backgroundRootMatrix->addChild(background->pGeode);

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
	    axes->setMatrix(osg::Matrix::translate(-4.0f, -2.5f, 0.0f) * osg::Matrix::scale(osg::Vec3d(scale_parameter,scale_parameter,scale_parameter)));
	    if (osgDB::readNodeFile("resources/axes.osgt") == NULL){
	    	std::cout<<"Axes cannot be loaded!" << std::endl;
	    }
	    else
	    	std::cout<<"Axes is loaded!" << std::endl;

	    axes->addChild(osgDB::readNodeFile("resources/axes.osgt"));

	    return;
	}

	void windshieldController::addHeadCamera(){
	    mainCamera->setClearColor(osg::Vec4(0.0f,0.0f,0.0f,0.0f));
	    mainCamera->setViewMatrixAsLookAt(osg::Vec3(0.0f,0.0f,-2.5f),osg::Vec3(),osg::Vec3(0.0f,3.0f,0.0f));
	    mainCamera->setRenderTargetImplementation(osg::Camera::FRAME_BUFFER, osg::Camera::FRAME_BUFFER);
	    // Nie mam pojecia co to robi
	   // mainCamera->setReferenceFrame(osg::Camera::ABSOLUTE_RF);
	    mainCamera->setRenderOrder ( osg::Camera::POST_RENDER);
	    return;
	}

	bool windshieldController::setLight(){
		osg::Light* pLight = new osg::Light();
		pLight->setLightNum (0);
		pLight->setAmbient (osg::Vec4d (1.0, 1.0, 1.0, 1.0));
		pLight->setDiffuse (osg::Vec4d (1.0, 1.0, 1.0, 1.0));
		pLight->setSpecular (osg::Vec4d (1.0, 1.0, 1.0, 1.0));
		osg::LightSource* pLightsource = new osg::LightSource();
		pLightsource->setLight (pLight);
		pLightsource->setStateSetModes (*mainCamera->getOrCreateStateSet(), osg::StateAttribute::ON);
		mainCamera->addChild (pLightsource);
		return true;
	}





}
