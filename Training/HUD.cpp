#include <osg/Camera>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>



int main(int arg, char * argc []){
    // Read The files
    osg::ref_ptr<osg::Node> model = osgDB::readNodeFile("lz.osg");
    //osg::ref_ptr<osg::Node> hud_model = osgDB::readNodeFile("cessna.osg");
    osg::ref_ptr<osg::MatrixTransform> cessna1 = new osg::MatrixTransform;
    float parameter = 0.01f;
    osg::Vec3d scaleFactor(parameter,parameter,parameter);
    cessna1->setMatrix(osg::Matrix::scale(scaleFactor) * osg::Matrix::translate(0.2f, 0.1f, -0.25f)* osg::Matrix::rotate( -M_PI*0.5, M_PI*0.2, 0, 1 ));
    cessna1->addChild(osgDB::readNodeFile("cessna.osg"));

    
    osg::ref_ptr<osg::MatrixTransform> cessna2 = new osg::MatrixTransform;
    cessna2->setMatrix( osg::Matrix::scale(osg::Vec3d(0.5,0.5,0.5)) *  osg::Matrix::rotate( -M_PI*0.5, 0, 0, 1 ) *  osg::Matrix::translate(0.0f, -0.5f, -0.9f));
    //cessna2->setMatrix(osg::Matrix::translate(0.2f, -0.5f, -0.25f) *  osg::Matrix::rotate( -M_PI*0.5, 0, 0, 1 ) *  osg::Matrix::scale(osg::Vec3d(0.5,0.5,0.5)) );
    cessna2->addChild(osgDB::readNodeFile("Windshield.osg"));


    osg::ref_ptr<osg::MatrixTransform> cessna3 = new osg::MatrixTransform;
   // osg::Matrix mat1 = osg::Matrix::scale(1.0,1.0,1.0);
    float x = -0.4;
    float y = 0.0;
    float z = -0.1;
   // osg::Matrix mat2 = osg::Matrix::translate(x,y,z);
   // cessna3->setMatrix(mat1*mat2);// * osg::Matrix::rotate( -M_PI*0.5, -M_PI*0.2, 0, 1 ) * osg::Matrix::scale(scaleFactor));
    cessna3->addChild(osgDB::readNodeFile("Windshield.osg"));




    osg::ref_ptr<osg::Camera> camera = new osg::Camera;
    camera->setClearMask(GL_DEPTH_BUFFER_BIT);
    camera->setRenderOrder ( osg::Camera::POST_RENDER);

    camera->setReferenceFrame ( osg::Camera::ABSOLUTE_RF);
    camera->setViewMatrixAsLookAt( osg::Vec3(0.0f,-500.0,2.0f),osg::Vec3(), osg::Vec3(0.0f,15.0f,1.0f));
    

    camera->addChild(cessna1.get());
    camera->addChild(cessna2.get());
    camera->addChild(cessna3.get());
    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild(model.get());
    root->addChild(camera.get());
    //root->addCh XE "render-to-textures technique:ild( camera.get() );
    osgViewer::Viewer viewer;
    viewer.setSceneData ( root.get());
    return viewer.run();


    

}
