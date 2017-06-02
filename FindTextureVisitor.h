
namespace MasterThesisProject {

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

}
