#!/usr/bin/env bash

# Exit if something fails
set -e

rm -rf ./Skimo.app

mkdir Skimo.app
mkdir Skimo.app/Contents
mkdir Skimo.app/Contents/MacOS
mkdir Skimo.app/Contents/PlugIns
mkdir Skimo.app/Contents/Resources

cp -R rundir/RelWithDebInfo/bin/ ./Skimo.app/Contents/MacOS
cp -R rundir/RelWithDebInfo/data ./Skimo.app/Contents/Resources
cp ../CI/scripts/macos/app/skimo.icns ./Skimo.app/Contents/Resources
cp -R rundir/RelWithDebInfo/obs-plugins/ ./Skimo.app/Contents/PlugIns
cp ../CI/scripts/macos/app/Info.plist ./Skimo.app/Contents

../CI/scripts/macos/package/dylibBundler -b -cd -d ./Skimo.app/Contents/Frameworks -p @executable_path/../Frameworks/ \
-s ./Skimo.app/Contents/MacOS \
-x ./Skimo.app/Contents/PlugIns/coreaudio-encoder.so \
-x ./Skimo.app/Contents/PlugIns/decklink-ouput-ui.so \
-x ./Skimo.app/Contents/PlugIns/frontend-tools.so \
-x ./Skimo.app/Contents/PlugIns/image-source.so \
-x ./Skimo.app/Contents/PlugIns/linux-jack.so \
-x ./Skimo.app/Contents/PlugIns/mac-avcapture.so \
-x ./Skimo.app/Contents/PlugIns/mac-capture.so \
-x ./Skimo.app/Contents/PlugIns/mac-decklink.so \
-x ./Skimo.app/Contents/PlugIns/mac-syphon.so \
-x ./Skimo.app/Contents/PlugIns/mac-vth264.so \
-x ./Skimo.app/Contents/PlugIns/obs-browser.so \
-x ./Skimo.app/Contents/PlugIns/obs-browser-page \
-x ./Skimo.app/Contents/PlugIns/obs-ffmpeg.so \
-x ./Skimo.app/Contents/PlugIns/obs-filters.so \
-x ./Skimo.app/Contents/PlugIns/obs-transitions.so \
-x ./Skimo.app/Contents/PlugIns/obs-vst.so \
-x ./Skimo.app/Contents/PlugIns/rtmp-services.so \
-x ./Skimo.app/Contents/MacOS/obs \
-x ./Skimo.app/Contents/MacOS/obs-ffmpeg-mux \
-x ./Skimo.app/Contents/MacOS/obslua.so \
-x ./Skimo.app/Contents/PlugIns/obs-x264.so \
-x ./Skimo.app/Contents/PlugIns/text-freetype2.so \
-x ./Skimo.app/Contents/PlugIns/obs-libfdk.so
# -x ./Skimo.app/Contents/MacOS/_obspython.so \
# -x ./Skimo.app/Contents/PlugIns/obs-outputs.so \

/usr/local/Cellar/qt/${QT_VERSION}/bin/macdeployqt ./Skimo.app

mv ./Skimo.app/Contents/MacOS/libobs-opengl.so ./Skimo.app/Contents/Frameworks

rm -f -r ./Skimo.app/Contents/Frameworks/QtNetwork.framework

# put qt network in here becasuse streamdeck uses it
cp -R /usr/local/opt/qt/lib/QtNetwork.framework ./Skimo.app/Contents/Frameworks
chmod -R +w ./Skimo.app/Contents/Frameworks/QtNetwork.framework
rm -r ./Skimo.app/Contents/Frameworks/QtNetwork.framework/Headers
rm -r ./Skimo.app/Contents/Frameworks/QtNetwork.framework/Versions/5/Headers/
chmod 644 ./Skimo.app/Contents/Frameworks/QtNetwork.framework/Versions/5/Resources/Info.plist
install_name_tool -id @executable_path/../Frameworks/QtNetwork.framework/Versions/5/QtNetwork ./Skimo.app/Contents/Frameworks/QtNetwork.framework/Versions/5/QtNetwork
install_name_tool -change /usr/local/Cellar/qt/${QT_VERSION}/lib/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/5/QtCore ./Skimo.app/Contents/Frameworks/QtNetwork.framework/Versions/5/QtNetwork


# decklink ui qt
install_name_tool -change /usr/local/opt/qt/lib/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui.framework/Versions/5/QtGui ./Skimo.app/Contents/PlugIns/decklink-ouput-ui.so
install_name_tool -change /usr/local/opt/qt/lib/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/5/QtCore ./Skimo.app/Contents/PlugIns/decklink-ouput-ui.so
install_name_tool -change /usr/local/opt/qt/lib/QtWidgets.framework/Versions/5/QtWidgets @executable_path/../Frameworks/QtWidgets.framework/Versions/5/QtWidgets ./Skimo.app/Contents/PlugIns/decklink-ouput-ui.so

# frontend tools qt
install_name_tool -change /usr/local/opt/qt/lib/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui.framework/Versions/5/QtGui ./Skimo.app/Contents/PlugIns/frontend-tools.so
install_name_tool -change /usr/local/opt/qt/lib/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/5/QtCore ./Skimo.app/Contents/PlugIns/frontend-tools.so
install_name_tool -change /usr/local/opt/qt/lib/QtWidgets.framework/Versions/5/QtWidgets @executable_path/../Frameworks/QtWidgets.framework/Versions/5/QtWidgets ./Skimo.app/Contents/PlugIns/frontend-tools.so

# vst qt
install_name_tool -change /usr/local/opt/qt/lib/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui.framework/Versions/5/QtGui ./Skimo.app/Contents/PlugIns/obs-vst.so
install_name_tool -change /usr/local/opt/qt/lib/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/5/QtCore ./Skimo.app/Contents/PlugIns/obs-vst.so
install_name_tool -change /usr/local/opt/qt/lib/QtWidgets.framework/Versions/5/QtWidgets @executable_path/../Frameworks/QtWidgets.framework/Versions/5/QtWidgets ./Skimo.app/Contents/PlugIns/obs-vst.so
install_name_tool -change /usr/local/opt/qt/lib/QtMacExtras.framework/Versions/5/QtMacExtras @executable_path/../Frameworks/QtMacExtras.framework/Versions/5/QtMacExtras ./Skimo.app/Contents/PlugIns/obs-vst.so
