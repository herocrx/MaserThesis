

#include "FindTextureVisitor.h"

namespace MasterThesisProject {
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

}
