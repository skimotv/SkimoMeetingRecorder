Skimo Meeting Recorder <https://skimo.tv/SkimoMeetingRecorder>
==============================================================

What is Skimo Meeting Recorder?
-------------------------------

  Skimo Meeting Recorder is software designed for recording, bookmarking, annotating,importing videos (bookmarks and annotations), using the Skimo REST API and viewing the Skimo using Skimo Newton, efficiently.

  It's distributed under the GNU General Public License v2 (or any later
  version) - see the accompanying COPYING file for more details.


How to Install
==============

1. run source ~/.bashrc
2. brew install dylibbundler
3. brew install qt (5.15.1)
4. git clone --recursive https://github.com/skimotv/SkimoMeetingRecorder.git
5. cd SkimoMeetingRecorder
6. rm -Rf build
7. mkdir build
8. cd build
9. cmake -DCMAKE_OSX_DEPLOYMENT_TARGET=10.13 -DDISABLE_PYTHON=ON ..
10. make

How to run
===========
1. To build Skimo Smart Smart Meeting Recorder as-is with full browser-source support,
simply run ./CI/full-build-macos.sh from the checkout directory
(The script will take care of downloading all necessary dependencies).
2. To create an app-bundle after building Skimo Smart Meeting Recorder,
run the script with the -b flag: ./CI/full-build-macos.sh -b
3. To create a disk image after building Skimo Smart Meeting Recorder,
run the script with the -p flag: ./CI/full-build-macos.sh -b -p
4. To notarize an app bundle after building and bundling OBS,
run the script with the -n flag: ./CI/full-build-macos.sh -b -n
5. To create an app-bundle without building Skimo Smart Meeting Recorder again,
run the script with the -s flag: ./CI/full-build-macos.sh -s -b

.bashrc
=======
QTDIR=/usr/local/Cellar <br/>
export QTDIR <br/>
CMAKE_MODULE_PATH=/usr/local/Cellar/qt/5.15.1/lib/cmake <br/>
export CMAKE_MODULE_PATH <br/>
Qt5_DIR=$CMAKE_MODULE_PATH/Qt5 <br/>
export Qt5_DIR <br/>
Qt5Core_DIR=$CMAKE_MODULE_PATH/Qt5Core <br/>
export Qt5Core_DIR <br/>
Qt5Gui_DIR=$CMAKE_MODULE_PATH/Qt5Gui <br/>
export Qt5Gui_DIR <br/>
Qt5Widgets_DIR=$CMAKE_MODULE_PATH/Qt5Widgets <br/>
export Qt5Widgets_DIR <br/>
Qt5MacExtras_DIR=$CMAKE_MODULE_PATH/Qt5MacExtras <br/>
export Qt5MacExtras_DIR <br/>
Qt5WebEngine_DIR=$CMAKE_MODULE_PATH/Qt5WebEngine <br/>
export Qt5WebEngine_DIR <br/>
Qt5WebEngineWidgets_DIR=$CMAKE_MODULE_PATH/Qt5WebEngineWidgets <br/>
export Qt5WebEngineWidgets_DIR <br/>
Qt5NetworkAuth_DIR=$CMAKE_MODULE_PATH/Qt5NetworkAuth <br/>
export Qt5NetworkAuth_DIR <br/>
Qt5Svg_DIR=$CMAKE_MODULE_PATH/Qt5Svg <br/>
export Qt5Svg_DIR <br/>
Qt5Xml_DIR=$CMAKE_MODULE_PATH/Qt5Xml <br/>
export Qt5Xml_DIR <br/>
Qt5WebSockets_DIR=$CMAKE_MODULE_PATH/Qt5WebSockets <br/>
export Qt5WebSockets_DIR <br/>

Reference
=========
Use the following as reference: https://github.com/obsproject/obs-studio/wiki/Install-Instructions#macos-install-directions
