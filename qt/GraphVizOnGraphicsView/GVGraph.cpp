#include "GVGraph.h"
#include "GraphViz.h"
#include "graphviz/gvc.h"
#include <math.h>

#define makeChar(QSTR)							\
	const_cast<char*>(QSTR.toLocal8Bit().constData())

namespace {

const qreal Pi = 3.141592;

/// The agopen method for opening a graph
static inline Agraph_t* _agopen(QString name, int kind)
{
	Agraph_t* graph = agopen(makeChar(name), kind);
	 return graph;
 }

 /// Add an alternative value parameter to the method for getting an object's attribute
 static inline QString _agget(void *object,
							  const QString& attributeName,
							  QString defaultValue=QString())
 {
	 QString val = agget((Agraph_t*)object, makeChar(attributeName));

	 if(val==QString())
		 return defaultValue;
	 else
		 return val;
 }

 /// Directly use agsafeset which always works, contrarily to agset
 static inline int _agset(void *object,
						  const QString& attributeName,
						  const QString& value)
 {
	 return agsafeset((Agraph_t*)object,
					  makeChar(attributeName),
					  makeChar(value),
					  makeChar(value));
 }

 // extern Agsym_t *agnodeattr(Agraph_t *, char *, char *);
 static inline Agsym_t* _agnodeattr(void* object,
									const QString& attributeName,
									const QString& defaultValue)
 {
	 return agnodeattr((Agraph_t*)object,
					   makeChar((attributeName)),
					   makeChar((defaultValue)));
 }


 static inline Agsym_t* _agedgeattr(void* object,
									const QString& attributeName,
									const QString& defaultValue)
 {
	 return agnodeattr((Agraph_t*)object,
					   makeChar(attributeName),
					   makeChar(defaultValue));
 }

 static inline Agnode_t* _agnode(void* object,
								 const QString& nodeName)
 {
	 Agnode_t* node = agnode((Agraph_t*)object,
							 makeChar(nodeName));
	 return node;
 }

 // /* Compute a layout using a specified engine */
 // extern int gvLayout(GVC_t *gvc, graph_t *g, const char *engine);
 static inline int _gvLayout(void* gvc, void* graph,
							 const char* engineName)
 {
	 return gvLayout((GVC_t*)gvc, (Agraph_t*)graph,
					 engineName);
 }

 } // namespace

 /*! Dot uses a 72 DPI value for converting it's position coordinates
   from points to pixels while we display at 96 DPI on most operating
   systems. */
 const qreal GVGraph::DotDefaultDPI=72.0;

 GVGraph::GVGraph(QString graphName, QFont font, qreal nodeSizePixel)
	 : _context(0)
	 , _graph(0) // Strict directed graph, see libgraph doc
 {
	 _context = gvContext();
	 Q_ASSERT(_context);

	 // Strict directed graph, see libgraph doc
	 _graph = _agopen(graphName, AGDIGRAPHSTRICT);
	 Q_ASSERT(_graph);
	 if (0)
	 {
		 if (_graph) {
			 _agset(_graph, "overlap", "prism");
			 _agset(_graph, "splines", "true");
			 _agset(_graph, "pad", "0,2");
			 // _agset(_graph, "dpi", "96,0");
			 _agset(_graph, "nodesep", "0,4");

			 //Set default attributes for the future nodes
			 _agnodeattr(_graph, "fixedsize", "true");
			 _agnodeattr(_graph, "label", "");
			 _agnodeattr(_graph, "regular", "true");
			 _agnodeattr(_graph, "arrowsize", "5");

			 //Divide the wanted width by the DPI to get the value in points
			 QString nodePtsWidth =
				 QString::fromLatin1("%1").arg(nodeSizePixel/graphDpi());
			 //GV uses , instead of . for the separator in floats
			 // _agnodeattr(_graph, "width", nodePtsWidth.replace('.', ","));
		 }
	 }
	 setFont(font);
 }

GVGraph::~GVGraph()
{
    gvFreeLayout((GVC_t*)_context, (Agraph_t*)_graph);
    agclose((Agraph_t*)_graph);
    gvFreeContext((GVC_t*)_context);
}

void GVGraph::addNode(const QString& name)
{
    if(_nodes.contains(name))
        removeNode(name);

    _nodes.insert(name, _agnode(_graph, name));
}

void GVGraph::addNodes(const QStringList& names)
{
    for(int i=0; i<names.size(); ++i) {
        addNode(names.at(i));
	}
}

void GVGraph::removeNode(const QString& name)
{
    if(_nodes.contains(name))
    {
        agdelete((Agraph_t*)_graph, _nodes[name]);
        _nodes.remove(name);

        QList< LinkPair > keys = _edges.keys();
        for(int i=0; i<keys.size(); ++i) {
            if(keys.at(i).first==name || keys.at(i).second==name) {
                removeEdge(keys.at(i));
			}
		}
    }
}

void GVGraph::clearNodes()
{
    QList<QString> keys=_nodes.keys();

    for(int i=0; i<keys.size(); ++i) {
        removeNode(keys.at(i));
	}
}

void GVGraph::setRootNode(const QString& name)
{
    if(_nodes.contains(name))
        _agset((Agraph_t*)_graph, "root", name);
}

void GVGraph::addEdge(const QString &source, const QString &target)
{
	String2NodeMap::iterator itSource = _nodes.find(source);
	String2NodeMap::iterator itTarget = _nodes.find(target);
    if(itSource!=_nodes.end() && itTarget!=_nodes.end()) {
        LinkPair key(source, target);
        if(!_edges.contains(key)) {
			Agnode_t* source = (Agnode_t*)itSource.value();
			Agnode_t* target = (Agnode_t*)itTarget.value();
            Agedge_t* edge = agedge((Agraph_t*)_graph,
									source,
									target);
			if (edge) {
				_edges.insert(key, edge);
			}
		}
    }
}

void GVGraph::removeEdge(const QString &source, const QString &target)
{
    removeEdge(LinkPair(source, target));
}

void GVGraph::removeEdge(const LinkPair& key)
{
	LinkPair2EdgeMap::iterator it = _edges.find(key);
    if (it!=_edges.end()) {
        agdelete((Agraph_t*)_graph, (Agedge_t*)it.value());
        _edges.remove(key);
    }
}

void GVGraph::setFont(QFont font)
{
    _font=font;

	if (_graph) {
		_agset(_graph, "fontname", font.family());
		_agset(_graph, "fontsize", QString("%1").arg(font.pointSizeF()));

		_agnodeattr(_graph, "fontname", font.family());
		_agnodeattr(_graph, "fontsize", QString("%1").arg(font.pointSizeF()));

		_agedgeattr(_graph, "fontname", font.family());
		_agedgeattr(_graph, "fontsize", QString("%1").arg(font.pointSizeF()));
	}
}

void GVGraph::applyLayout()
{
    gvFreeLayout((GVC_t*)_context, (Agraph_t*)_graph);
    // _gvLayout(_context, _graph, "dot");
	// FILE* h = fopen("c:/temp/gvgraph.png", "wb");
	// gvRender((GVC_t*)_context, (Agraph_t*)_graph, "png", h);
	_gvLayout(_context, _graph, "dot");
	gvRender((GVC_t*)_context, (Agraph_t*)_graph, "dot", 0);
}

QRectF GVGraph::boundingRect() const
{
    qreal dpi=graphDpi();
	Agraph_t* graph = (Agraph_t*)_graph;
	boxf& boundBox = graph->u.bb;
	qreal scale = dpi/DotDefaultDPI;
    return QRectF(boundBox.LL.x*scale, boundBox.LL.y*scale,
                  boundBox.UR.x*scale, boundBox.UR.y*scale);
}

qreal GVGraph::graphDpi() const
{
	return _agget(_graph, "dpi", "96.0").toDouble();
}

QList<GVNode> GVGraph::nodes() const
{
	GVNodeList nodeList;
	qreal dpi=graphDpi();
	Agraph_t* graph = (Agraph_t*)_graph;

	String2NodeMap::const_iterator it = _nodes.begin();
	String2NodeMap::const_iterator itEnd = _nodes.end();
    for(; it!=itEnd; ++it)
    {
        Agnode_t *node = (Agnode_t*)it.value();
        GVNode nodeObject;

        //Set the name of the node
        nodeObject.name  = QString::fromLatin1(node->name);

        //Fetch the X coordinate, apply the DPI conversion rate
        //(actual DPI / 72, used by dot)
        qreal x = node->u.coord.x*(dpi/DotDefaultDPI);

        //Translate the Y coordinate from bottom-left to top-left corner
        qreal y = (graph->u.bb.UR.y - node->u.coord.y)*(dpi/DotDefaultDPI);
        nodeObject.centerPos = QPoint(x, y);
        //Transform the width and height from inches to pixels
		nodeObject.size = QSize(node->u.width*dpi,
								node->u.height*dpi);

        nodeList << nodeObject;
    }

    return nodeList;
}

GVEdgeList GVGraph::edges() const
{
	GVEdgeList list;
	qreal dpi = graphDpi();

	Agraph_t * graph = (Agraph_t*)_graph;

    for(LinkPair2EdgeMap::const_iterator it=_edges.begin();
        it!=_edges.end();++it)
    {
        Agedge_t* edge = (Agedge_t*)it.value();
        GVEdge object;

        //Fill the source and target node names
        object.source=edge->tail->name;
        object.target=edge->head->name;

		QPainterPath& path = object.path;

		qreal top = graph->u.bb.UR.y; // actually bottom y of boundbox(GraphViz coord
									   // is LL coordinate. while Qt UL coordinate)
		splines* splines = edge->u.spl;
		bezier* curve = edge->u.spl->list;
		qreal scale = (dpi/DotDefaultDPI);

		//Fill the source and target node names
        object.source=edge->tail->name;
        object.target=edge->head->name;

        //Calculate the path from the spline (only one spline, as the graph is strict. If it
        //wasn't, we would have to iterate over the first list too)
        //Calculate the path from the spline (only one as the graph is strict)
        if((curve!=0) && (curve->size%3 == 1))
        {
            //If there is a starting point, draw a line from it to the first curve point
            if(curve->sflag) {
				// NOTE the direction
				object.sourceArrowLine.setLine(
						curve->list[0].x*scale, (top - curve->list[0].y)*scale,
						curve->sp.x*scale, (top - curve->sp.y)*scale
					);
            } else {
				object.path.moveTo(curve->list[0].x*scale,
								   (top - curve->list[0].y)*scale);
			}

            //Loop over the curve points
			QPointF lastPoint;
            for(int i=1; i<curve->size; i+=3) {
				lastPoint = QPointF(curve->list[i+2].x*scale,
									(top - curve->list[i+2].y)*scale);
                object.path.cubicTo(curve->list[i].x*scale,
									(top - curve->list[i].y)*scale,
									curve->list[i+1].x*scale,
									(top - curve->list[i+1].y)*scale,
									lastPoint.x(),
									lastPoint.y());
			}

            // If there is an ending point,
            if(curve->eflag) {
				QPointF endPoint(curve->ep.x*scale,
								 (top - curve->ep.y)*scale);
				object.targetArrowLine.setPoints(lastPoint, endPoint);
			}
        }

        list << object;
    }

    return list;
}
