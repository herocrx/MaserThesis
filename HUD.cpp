#include <osg/Camera>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>


int main(int arg, char * argc []){
    // Read The files
    osg::ref_ptr<osg::Node> model = osgDB::readNodeFile("lz.osg");
    osg::ref_ptr<osg::Node> hud_model = osgDB::readNodeFile("cessna.osg");
    if ( hud_model == NULL ) 
        std::cout << "The file does not exist" << std::endl;


    osg::ref_ptr<osg::Camera> camera = new osg::Camera;
    camera->setClearMask(GL_DEPTH_BUFFER_BIT);
    camera->setRenderOrder ( osg::Camera::POST_RENDER);

    camera->setReferenceFrame ( osg::Camera::ABSOLUTE_RF);
    camera->setViewMatrixAsLookAt( osg::Vec3(0.0f,-500.0,5.0f),osg::Vec3(), osg::Vec3(0.0f,30.0f,1.0f));
    
    camera->addChild(hud_model.get());

    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild(model.get());
    root->addChild(camera.get());
    //root->addCh XE "render-to-textures technique:ild( camera.get() );
    osgViewer::Viewer viewer;
    viewer.setSceneData ( root.get());
    return viewer.run();


    

}
