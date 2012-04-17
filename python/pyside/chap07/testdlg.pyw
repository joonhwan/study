#!/usr/bin/env python
import sys
from PySide.QtCore import *
from PySide.QtGui import *


class Form(QDialog):
    def __init__(self, parent=None):
        super(Form, self).__init__(parent)
        layout = QVBoxLayout()
        layout.addWidget(QLabel("Hello Joonhwan"))
        self.button = QPushButton("&Close")
        layout.addWidget(self.button)
        self.button.clicked.connect(self.accept)
        self.setLayout(layout)

app = QCoreApplication.instance()
if app is None:
    app = QApplication(sys.argv)
form = Form()
form.show()
form.exec_()
sys.exit(0)
