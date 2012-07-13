#include "GVGraph.h"
#include "WGraphicsArrowItem.h"
#include "graphviz/types.h"
#include "graphviz/graph.h"
#include "graphviz/gvc.h"
#include <QDir>
#include <QtGui/QApplication>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPathItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsSimpleTextItem>
#include <stdio.h>

void doTest()
{
	Agraph_t* g;
	Agnode_t* n;
	Agnode_t* m;
	Agedge_t* e;
	// Agsym_t* a;
	GVC_t* gvc;

	// set up a graphviz context
	gvc = gvContext();
	// // parse command line args - minimally argv[0] sets layout engine
	// gvParseArgs(gvc, argc, argv);
	// Create a simple digraph
	g = agopen("g", AGDIGRAPH);
	n = agnode(g, "n");
	m = agnode(g, "m");
	e = agedge(g, n, m);
	// Set an attribute - in this case one that affects the visible rendering
	agsafeset(n, "color", "red", "");

	gvLayout(gvc, g, "dot");
	gvRender(gvc, g, "plain", 0);
	gvFreeLayout(gvc, g);
	agclose(g);
	gvFreeContext(gvc);
	// // Compute a layout using layout engine from command line args
	// gvLayoutJobs(gvc, g);
	// // Write the graph according to -T and -o options
	// gvRenderJobs(gvc, g);
	// // Free layout data
	// gvFreeLayout(gvc, g);
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	// agseterr(AGPREV);
	// doTest();
	// return 0;

	GVGraph graph("SIS", QApplication::font());
	graph.addNodes(QStringList()
				   << "IPC1"
				   << "CAMERA1"
				   << "IPC2"
				   << "CAMERA2"
				   << "MPC"
				   << "VEC"
		);
	graph.addEdge("IPC1", "CAMERA1");
	graph.addEdge("IPC1", "MPC");
	graph.addEdge("IPC2", "CAMERA2");
	graph.addEdge("IPC2", "MPC");
	graph.addEdge("MPC", "VEC");
	graph.addEdge("VEC", "MPC");
	graph.applyLayout();

	QGraphicsScene scene;
	scene.setSceneRect(graph.boundingRect());
	QGraphicsView view;
	view.setScene(&scene);
	view.setRenderHint(QPainter::Antialiasing);

	WGraphicsArrowItem* arrow = new WGraphicsArrowItem(QPointF(0,0),
													   QPointF(10,30));
	scene.addItem(arrow);

	QPen pathPen(Qt::black, 1.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	if (1) {
		foreach(const GVNode& node, graph.nodes()) {
			QRectF box = node.boundBox();
			QGraphicsEllipseItem* item = new QGraphicsEllipseItem(box);
			scene.addItem(item);

			QLinearGradient myGradient;
			QPen myPen;
			QFont myFont;

			QPainterPath myPath;
			myPath.addText(QPointF(0,0), QApplication::font(), node.name);

			QRectF textBox = myPath.boundingRect();
			myPath.translate(box.center().x() - textBox.center().x() ,
							 box.center().y() - textBox.center().y());
			textBox = myPath.boundingRect();
			QGraphicsPathItem* text = new QGraphicsPathItem();
			text->setPath(myPath);
			text->setBrush(myGradient);
			text->setPen(QPen(Qt::black));
			scene.addItem(text);
		}
		foreach(const GVEdge& edge, graph.edges()) {
			QGraphicsPathItem* item = new QGraphicsPathItem;
			item->setPath(edge.path);
			item->setPen(pathPen);
			scene.addItem(item);

			if (!edge.sourceArrowLine.isNull()) {
				WGraphicsArrowItem* arrow = new WGraphicsArrowItem(edge.sourceArrowLine);
				arrow->setPen(pathPen);
				scene.addItem(arrow);
			}
			if (!edge.targetArrowLine.isNull()) {
				WGraphicsArrowItem* arrow = new WGraphicsArrowItem(edge.targetArrowLine);
				arrow->setPen(pathPen);
				scene.addItem(arrow);
			}

			// QGraphicsSimpleTextItem* text = new QGraphicsSimpleTextItem(item);
			// text->setText(node.name);
			// text->setPos(QPoint(0,0));
			// scene.addItem(text);
		}
	}

	view.show();

	return a.exec();
}
