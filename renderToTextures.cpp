#include <osg/Camera>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>
#include <osgViewer/Viewer>
#include <osg/MatrixTransform>
#include <osg/BlendFunc>
#include <osg/LightSource>
class FindTextureVisitor : public osg::NodeVisitor {
    public:
        FindTextureVisitor (osg::Texture*tex): _texture(tex){
             setTraversalMode(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN);
    }
    virtual void apply( osg::Node& node);
    virtual void apply( osg::Geode& geode);
    void replaceTexture(osg::StateSet * ss);

    protected:
        osg::ref_ptr<osg::Texture> _texture;
};


void FindTextureVisitor::apply(osg::Node & node){
    replaceTexture( node.getStateSet());
    traverse(node);
}

void FindTextureVisitor::apply(osg::Geode& geode){
    replaceTexture(geode.getStateSet() );
    for ( unsigned int i=0; i<geode.getNumDrawables(); ++i){
        replaceTexture(geode.getDrawable(i)->getStateSet());
    }
    // Must be. We cannot forget about traverse() at the end of each method body to continue going through the scene graph
    traverse(geode);
}

void FindTextureVisitor::replaceTexture( osg::StateSet* ss){
    if ( ss){
        osg::Texture* oldTexture = dynamic_cast<osg::Texture*>(ss->getTextureAttribute(0,osg::StateAttribute::TEXTURE));
        if ( oldTexture)
            ss->setTextureAttribute(0,_texture.get());
    }
}



/*
osg::ref_ptr<osg::Group> CreateLight(osg::ref_ptr<osg::Node> node) { 
    osg::ref_ptr<osg::Group> lightRoot=new osg::Group(); 
    lightRoot->addChild(node); 
    osg::ref_ptr<osg::StateSet> stateset=new osg::StateSet; 
    stateset=lightRoot->getOrCreateStateSet (); 
    stateset->setMode(GL_LIGHTING, osg::StateAttribute:ShockedN); 
    stateset->setMode(GL_LIGHT0, osg::StateAttribute:ShockedN); 
    stateset->setMode(GL_NORMALIZE, osg::StateAttribute:ShockedN); 

    osg::BoundingSphere bs; 
    node->computeBound(); 
    bs=node->getBound(); 

    osg::ref_ptr<osg:ight> light=new osg:light; 
    light->setLightNum(0); 

    light->setDirection(osg::Vec3(0.0f, 0.0f, 1.0f)); 
    light->setPosition(osg::Vec4(bs.center().x(), bs.center().y(), 
                bs.center().z()-bs.radius(), 1.0f)); 


    light->setAmbient(osg::Vec4(1.0f,1.0f,1.0f,1.0f)); 
    light->setDiffuse(osg::Vec4(1.0f,1.0f,1.0f,1.0f)); 
    light->setSpecular(osg::Vec4(1.0f,1.0f,1.0f,1.0f)); 

    osg::ref_ptr<osg:ightSource> lightSource=new osg:ightSource; 
    lightSource->setLight(light.get()); 
    lightRoot->addChild(lightSource); 
    return lightRoot.get(); 

} 
*/








int main(int arg, char * argc[]){

    osg::ref_ptr<osg::Node> sub_model = osgDB::readNodeFile("glider.osg");

    osg::ref_ptr<osg::MatrixTransform> windshield = new osg::MatrixTransform;
    osg::Matrix rotateMatrix = osg::Matrix::rotate(M_PI, 0, 0, 1 );     
    osg::Matrix scaleMatrix =  osg::Matrix::translate(3.0f, 0.0f, 0.0f);
    float scale_parameter = 1.0f;
    osg::Matrix translateMatrix = osg::Matrix::scale(osg::Vec3d(scale_parameter,scale_parameter,scale_parameter)); 
    osg::BlendFunc *fuct = new osg::BlendFunc(); 
    fuct->setFunction(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    windshield->getOrCreateStateSet()->setAttributeAndModes(fuct); 
    windshield->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);    


    windshield->addChild(osgDB::readNodeFile("Windshield.osg"));
    windshield->setMatrix(translateMatrix*rotateMatrix*scaleMatrix );


             

    osg::ref_ptr<osg::MatrixTransform> axes = new osg::MatrixTransform;
    axes->setMatrix(osg::Matrix::translate(-5.0f, -3.0f, 0.0f) * osg::Matrix::scale(osg::Vec3d(scale_parameter,scale_parameter,scale_parameter)));
    axes->addChild(osgDB::readNodeFile("axes.osgt"));



    int tex_width = 1024, tex_height = 1024;
    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
    texture->setTextureSize(tex_width,tex_height);
    texture->setInternalFormat(GL_RGBA);
    texture->setFilter(osg::Texture2D::MIN_FILTER,osg::Texture2D::LINEAR);
    texture->setFilter(osg::Texture2D::MAG_FILTER,osg::Texture2D::LINEAR);

    FindTextureVisitor ftv(texture.get());
    if (windshield.valid()) 
        windshield->accept(ftv);

    osg::ref_ptr<osg::Camera> cameraWindshield = new osg::Camera;
    cameraWindshield->setViewport(0,0,tex_width,tex_height);
    cameraWindshield->setClearColor(osg::Vec4(1.0f,1.0f,1.0f,0.0f));
    cameraWindshield->setClearMask(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    cameraWindshield->setRenderOrder (osg::Camera::PRE_RENDER);
    cameraWindshield->setRenderTargetImplementation(osg::Camera::FRAME_BUFFER_OBJECT);
   cameraWindshield->attach (osg::Camera::COLOR_BUFFER, texture.get());
   // Rendering on the whole surface
    cameraWindshield->setReferenceFrame (osg::Camera::ABSOLUTE_RF);
    cameraWindshield->addChild (sub_model.get());

    osg::ref_ptr<osg::Group> windshieldGroup = new osg::Group;
    windshieldGroup->addChild(cameraWindshield.get());
    windshieldGroup->addChild(windshield.get());
/*
    osg::Light* pLight = new osg::Light(); 
    pLight->setLightNum (0); 
    pLight->setAmbient (osg::Vec4d (0.0, 0.0, 0.0, 1.0)); 
    pLight->setDiffuse (osg::Vec4d (0.0, 0.0, 0.0, 1.0)); 
    pLight->setSpecular (osg::Vec4d (0.0, 0.0, 0.0, 1.0)); 
    osg::LightSource* pLightsource = new osg::LightSource(); 
    pLightsource->setLight (pLight); 
    pLightsource->setStateSetModes (*cameraWindshield->getOrCreateStateSet(), osg::StateAttribute::ON); 
    cameraWindshield->addChild (pLightsource); 
*/

    osg::ref_ptr<osg::Camera> mainCamera = new osg::Camera;
    mainCamera->addChild(windshieldGroup.get());
    mainCamera->addChild(axes.get());
    mainCamera->setClearColor(osg::Vec4(0.0f,1.0f,1.0f,0.0f));
    mainCamera->setViewMatrixAsLookAt(osg::Vec3(0.0f,0.0f,-15.0f),osg::Vec3(),osg::Vec3(0.0f,2.0f,0.0f));
    mainCamera->setRenderTargetImplementation(osg::Camera::FRAME_BUFFER, osg::Camera::FRAME_BUFFER);
    // Nie mam pojecia co to robi
    //mainCamera->setReferenceFrame(osg::Camera::ABSOLUTE_RF);
    mainCamera->setRenderOrder ( osg::Camera::POST_RENDER);


    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild(mainCamera);
    root->addChild(axes);
    
    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    viewer.setCameraManipulator(new osgGA::TrackballManipulator);

    float delta = 0.001f, bias= 0.0f;
    osg::Vec3 eye(0.5f,-1.0f,5.0f);
    int frame=  0;
    while ( !viewer.done()){
        std::cout << "bias: " << bias << std::endl;
        if (bias<-1.0f){ 
            delta = 0.001f;
            std::cout << "bias<-1.0" << std::endl;
        }
        else if ( bias>1.0f){
            delta = -0.001f;
            std::cout << "bias>1.0" << std::endl;
        }
        bias+=delta;
        cameraWindshield->setViewMatrixAsLookAt(eye,osg::Vec3(0,0,0),osg::Vec3(bias,0.5f,0.5f));
        frame++;
        viewer.frame();
    }
    return 0;
}





