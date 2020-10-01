Skimo Meeting Recorder <https://skimo.tv/SkimoMeetingRecorder>
==============================================================

What is Skimo Meeting Recorder?
-------------------------------

  Skimo Meeting Recorder is software designed for recording, bookmarking, annotating,importing videos (bookmarks and annotations), using the Skimo REST API and viewing the Skimo using Skimo Newton, efficiently.

  It's distributed under the GNU General Public License v2 (or any later
  version) - see the accompanying COPYING file for more details.


How to Install
==============

1. run ~/.bashrc 
2. brew install dylibbundler
3. brew install qt (5.15.1)
4. git clone --recursive https://github.com/skimotv/SkimoMeetingRecorder.git 
5. cd SkimoMeetingRecorder
6. rm -Rf build 
7. mkdir build
8. cd build
9. cmake -DCMAKE_OSX_DEPLOYMENT_TARGET=10.13 -DDISABLE_PYTHON=ON .. 
10. make 

.bashrc 
=======
QTDIR=/usr/local/Cellar
export QTDIR
CMAKE_MODULE_PATH=/usr/local/Cellar/qt/5.15.1/lib/cmake
export CMAKE_MODULE_PATH
Qt5_DIR=$CMAKE_MODULE_PATH/Qt5
export Qt5_DIR
Qt5Core_DIR=$CMAKE_MODULE_PATH/Qt5Core
export Qt5Core_DIR
Qt5Gui_DIR=$CMAKE_MODULE_PATH/Qt5Gui
export Qt5Gui_DIR
Qt5Widgets_DIR=$CMAKE_MODULE_PATH/Qt5Widgets
export Qt5Widgets_DIR
Qt5MacExtras_DIR=$CMAKE_MODULE_PATH/Qt5MacExtras
export Qt5MacExtras_DIR
Qt5WebEngine_DIR=$CMAKE_MODULE_PATH/Qt5WebEngine
export Qt5WebEngine_DIR
Qt5WebEngineWidgets_DIR=$CMAKE_MODULE_PATH/Qt5WebEngineWidgets
export Qt5WebEngineWidgets_DIR
Qt5NetworkAuth_DIR=$CMAKE_MODULE_PATH/Qt5NetworkAuth
export Qt5NetworkAuth_DIR
Qt5Svg_DIR=$CMAKE_MODULE_PATH/Qt5Svg
export Qt5Svg_DIR
Qt5Xml_DIR=$CMAKE_MODULE_PATH/Qt5Xml
export Qt5Xml_DIR
