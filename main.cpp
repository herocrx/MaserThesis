#include "windshieldImage.cpp"

namespace MasterThesisProject{

	void runAnimation(osg::ref_ptr<osg::Group> root){
//void runAnimation(osg::ref_ptr<osg::Group> root, windshieldImage *Windshield){
		osgViewer::Viewer viewer;
		viewer.setSceneData(root.get());
		viewer.setCameraManipulator(new osgGA::TrackballManipulator);
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
			Windshield->getWindshieldCamera()->setViewMatrixAsLookAt(eye,osg::Vec3(0,0,0),osg::Vec3(bias,0.5f,0.5f));
			//.windshield->setViewMatrixAsLookAt(eye,osg::Vec3(0,0,0),osg::Vec3(bias,0.5f,0.5f));
			frame++;
			viewer.frame();
		}
	}


	osg::Node * addAxes(){
	    float scale_parameter = 1.0f;
		osg::ref_ptr<osg::MatrixTransform> axes = new osg::MatrixTransform;
	    axes->setMatrix(osg::Matrix::translate(-5.0f, -3.0f, 0.0f) * osg::Matrix::scale(osg::Vec3d(scale_parameter,scale_parameter,scale_parameter)));
	    axes->addChild(osgDB::readNodeFile("axes.osgt"));
	    return axes.release() ;
	}

	osg::Node * addWindshield(){
		windshieldImage  *Windshield = new windshieldImage();
		Windshield->loadSubModel();
		Windshield->loadWindshieldObject();
		Windshield->setPositionWindshield();
		Windshield->setTextureFormatAndFilter();
		Windshield->EncapsulateBlendTransparencyState();
		//ddWindshiel
		return Windshield->release() ;
	}



}


int main(int arg, char * argc[]){

    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild(MasterThesisProject::addWindshield());
    root->addChild(MasterThesisProject::addAxes());
    MasterThesisProject::runAnimation(root);

	return 0;
}
