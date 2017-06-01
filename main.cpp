#include "windshieldImage.cpp"

namespace MasterThesisProject{

	void runAnimation(osg::ref_ptr<osg::Group> root){
        //void runAnimation(osg::ref_ptr<osg::Group> root, windshieldImage *Windshield){
		osgViewer::Viewer viewer;
		viewer.setSceneData(root.get());
		//dodatkowa kamera do patrzenia
		//viewer.setCameraManipulator(new osgGA::TrackballManipulator);
		float delta = 0.001f, bias= 0.0f;
		osg::Vec3 eye(0.5f,-1.0f,5.0f);
		int frame=  0;
		while ( !viewer.done()){
			//std::cout << "bias: " << bias << std::endl;
			if (bias<-1.0f){
				delta = 0.001f;
				std::cout << "bias<-1.0" << std::endl;
			}
			else if ( bias>1.0f){
				delta = -0.001f;
				//std::cout << "bias>1.0" << std::endl;
			}
			bias+=delta;
			//Windshield->getWindshieldCamera()->setViewMatrixAsLookAt(eye,osg::Vec3(0,0,0),osg::Vec3(bias,0.5f,0.5f));
			//.windshield->setViewMatrixAsLookAt(eye,osg::Vec3(0,0,0),osg::Vec3(bias,0.5f,0.5f));
			frame++;
			viewer.frame();
		}
	}


	osg::Node * addAxes(){
	    float scale_parameter = 0.2f;
		osg::ref_ptr<osg::MatrixTransform> axes = new osg::MatrixTransform;
	    axes->setMatrix(osg::Matrix::translate(-6.0f, -3.5f, 0.0f) * osg::Matrix::scale(osg::Vec3d(scale_parameter,scale_parameter,scale_parameter)));
	    axes->addChild(osgDB::readNodeFile("axes.osgt"));
	    return axes.release();
	}

	osg::Node * addWindshield(){
		windshieldImage  *Windshield = new windshieldImage();
		Windshield->loadSubModel();
		Windshield->loadWindshieldObject();
		Windshield->setPositionWindshield();
		Windshield->setTextureFormatAndFilter();
		Windshield->setTextureSize();
		Windshield->EncapsulateBlendTransparencyState();
		Windshield->setProjectionTextureCamera();
		// this can be managable -> here must be found the way to manipualte Eye trackng
		//Windshield->setHeadCamera();
		return Windshield->release() ;
	}


	osg::Camera * setHeadCamera(){
		osg::ref_ptr<osg::Camera> mainCamera = new osg::Camera;
	    mainCamera->setClearColor(osg::Vec4(0.0f,1.0f,1.0f,0.0f));
	    mainCamera->setViewMatrixAsLookAt(osg::Vec3(0.0f,0.0f,-3.0f),osg::Vec3(),osg::Vec3(0.0f,2.0f,0.0f));
	    mainCamera->setRenderTargetImplementation(osg::Camera::FRAME_BUFFER, osg::Camera::FRAME_BUFFER);
	    // Nie mam pojecia co to robi
	    //mainCamera->setReferenceFrame(osg::Camera::ABSOLUTE_RF);
	    mainCamera->setRenderOrder ( osg::Camera::POST_RENDER);
	    return mainCamera.release();
	}

}





int main(int arg, char * argc[]){

    //osg::ref_ptr<osg::Group> root = new osg::Group;
	osg::ref_ptr<osg::Camera> mainCamera = MasterThesisProject::setHeadCamera();

	mainCamera->addChild(MasterThesisProject::addWindshield());
	mainCamera->addChild(MasterThesisProject::addAxes());

    MasterThesisProject::runAnimation(mainCamera);

	return 0;
}
