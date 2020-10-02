#!/usr/bin/env bash

# Exit if something fails
set -e

cd ./build

mv ./rundir/RelWithDebInfo/data/obs-scripting/obslua.so ./rundir/RelWithDebInfo/bin/
mv ./rundir/RelWithDebInfo/data/obs-scripting/_obspython.so ./rundir/RelWithDebInfo/bin/
mv ./rundir/RelWithDebInfo/data/obs-scripting/obspython.py ./rundir/RelWithDebInfo/bin/

../CI/scripts/macos/packageApp.sh

# fix obs outputs plugin it doesn't play nicely with dylibBundler at the moment
chmod +w ./Skimo.app/Contents/Frameworks/*.dylib
install_name_tool -change libmbedtls.12.dylib @executable_path/../Frameworks/libmbedtls.12.dylib ./Skimo.app/Contents/Plugins/obs-outputs.so
install_name_tool -change libmbedcrypto.3.dylib @executable_path/../Frameworks/libmbedcrypto.3.dylib ./Skimo.app/Contents/Plugins/obs-outputs.so
install_name_tool -change libmbedx509.0.dylib @executable_path/../Frameworks/libmbedx509.0.dylib ./Skimo.app/Contents/Plugins/obs-outputs.so
install_name_tool -change /usr/local/opt/curl/lib/libcurl.4.dylib @executable_path/../Frameworks/libcurl.4.dylib ./Skimo.app/Contents/Plugins/obs-outputs.so
install_name_tool -change @rpath/libobs.0.dylib @executable_path/../Frameworks/libobs.0.dylib ./Skimo.app/Contents/Plugins/obs-outputs.so
install_name_tool -change /tmp/obsdeps/bin/libjansson.4.dylib @executable_path/../Frameworks/libjansson.4.dylib ./Skimo.app/Contents/Plugins/obs-outputs.so

cp -R ${GITHUB_WORKSPACE}/cmbuild/sparkle/Sparkle.framework ./Skimo.app/Contents/Frameworks/
install_name_tool -change @rpath/Sparkle.framework/Versions/A/Sparkle @executable_path/../Frameworks/Sparkle.framework/Versions/A/Sparkle ./Skimo.app/Contents/MacOS/obs

sudo mkdir -p ./Skimo.app/Contents/Frameworks
sudo cp -R ${GITHUB_WORKSPACE}/cmbuild/cef_binary_${CEF_BUILD_VERSION}_macosx64/Release/Chromium\ Embedded\ Framework.framework ./Skimo.app/Contents/Frameworks/
install_name_tool -change /usr/local/opt/qt/lib/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui.framework/Versions/5/QtGui ./Skimo.app/Contents/Plugins/obs-browser.so
install_name_tool -change /usr/local/opt/qt/lib/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/5/QtCore ./Skimo.app/Contents/Plugins/obs-browser.so
install_name_tool -change /usr/local/opt/qt/lib/QtWidgets.framework/Versions/5/QtWidgets @executable_path/../Frameworks/QtWidgets.framework/Versions/5/QtWidgets ./Skimo.app/Contents/Plugins/obs-browser.so

cp ../CI/scripts/macos/app/OBSPublicDSAKey.pem ./Skimo.app/Contents/Resources

plutil -insert CFBundleVersion -string $(basename ${GITHUB_REF}) ./Skimo.app/Contents/Info.plist
plutil -insert CFBundleShortVersionString -string $(basename ${GITHUB_REF}) ./Skimo.app/Contents/Info.plist
plutil -insert OBSFeedsURL -string https://obsproject.com/osx_update/feeds.xml ./Skimo.app/Contents/Info.plist
plutil -insert SUFeedURL -string https://obsproject.com/osx_update/stable/updates.xml ./Skimo.app/Contents/Info.plist
plutil -insert SUPublicDSAKeyFile -string OBSPublicDSAKey.pem ./Skimo.app/Contents/Info.plist

mv ./Skimo.app ../Skimo.app
cd -
