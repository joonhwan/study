#pragma once

#include <QFont>
#include <QList>
#include <QMap>
#include <QPainterPath>
#include <QPair>
#include <QRectF>
#include <QSizeF>
#include <QString>
#include <QStringList>
#include <QtGlobal>

/// A struct containing the information for a GVGraph's node
struct GVNode
{
	/// The unique identifier of the node in the graph
	QString name;

	/// The position of the center point of the node from the top-left corner
	QPointF centerPos;

	/// The size of the node in pixels
	QSizeF size;

	QRectF boundBox() const {
		QPointF topLeft(centerPos.x() - size.width()/2,
						centerPos.y() - size.height()/2);
		return QRectF(topLeft, size);
	}
};
typedef QList<GVNode> GVNodeList;

/// A struct containing the information for a GVGraph's edge
struct GVEdge
{
	/// The source and target nodes of the edge
	QString source;
	QString target;

	/// Path of the edge's line
	QLineF sourceArrowLine;
	QLineF targetArrowLine;
	QPainterPath path;
};
typedef QList<GVEdge> GVEdgeList;


/// An object containing a libgraph graph and its associated nodes and edges
class GVGraph
{
	typedef QMap<QString, void*> String2NodeMap; // void* = Agnode_t*
	typedef QPair<QString, QString> LinkPair;
	typedef QMap<LinkPair, void*> LinkPair2EdgeMap;// void* = Agedge_t*
public:
    GVGraph(QString graphName, QFont font=QFont(), qreal nodeSizePixel=50);
    virtual ~GVGraph();

    void addNode(const QString& name);
    void addNodes(const QStringList& names);
    void removeNode(const QString& name);
    void clearNodes();
	void setRootNode(const QString& name);
    void addEdge(const QString& source, const QString& target);
    void removeEdge(const QString& source, const QString& target);
    void setFont(QFont font);
	void applyLayout();
	QRectF boundingRect() const;

	qreal graphDpi() const;
	GVNodeList nodes() const;
	GVEdgeList edges() const;
protected:
	void removeEdge(const LinkPair& key);

	/// Default DPI value used by dot (which uses points instead of
    /// pixels for coordinates)
    static const qreal DotDefaultDPI;
private:
    void* _context; // GVC_t *_context;
    void* _graph; // Agraph_t *_graph;
    QFont _font;
	String2NodeMap _nodes;
    LinkPair2EdgeMap _edges;
};
