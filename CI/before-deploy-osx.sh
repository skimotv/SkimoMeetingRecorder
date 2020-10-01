hr() {
  echo "───────────────────────────────────────────────────"
  echo $1
  echo "───────────────────────────────────────────────────"
}

# Exit if something fails
set -e

# Generate file name variables
export GIT_TAG=$(git describe --abbrev=0)
export GIT_HASH=$(git rev-parse --short HEAD)
export FILE_DATE=$(date +%Y-%m-%d.%H-%M-%S)
export FILENAME=$FILE_DATE-$GIT_HASH-$TRAVIS_BRANCH-osx.dmg

echo "git tag: $GIT_TAG"

cd ./build

# Move obslua
hr "Moving OBS LUA"
mv ./rundir/RelWithDebInfo/data/obs-scripting/obslua.so ./rundir/RelWithDebInfo/bin/

# Move obspython
hr "Moving OBS Python"
# mv ./rundir/RelWithDebInfo/data/obs-scripting/_obspython.so ./rundir/RelWithDebInfo/bin/
# mv ./rundir/RelWithDebInfo/data/obs-scripting/obspython.py ./rundir/RelWithDebInfo/bin/

# Package everything into a nice .app
hr "Packaging .app"
STABLE=false
if [ -n "${TRAVIS_TAG}" ]; then
  STABLE=true
fi

#sudo python ../CI/install/osx/build_app.py --public-key ../CI/install/osx/OBSPublicDSAKey.pem --sparkle-framework ../../sparkle/Sparkle.framework --stable=$STABLE

../CI/install/osx/packageApp.sh

# fix obs outputs plugin it doesn't play nicely with dylibBundler at the moment
if [ -f /usr/local/opt/mbedtls/lib/libmbedtls.12.dylib ]; then
    cp /usr/local/opt/mbedtls/lib/libmbedtls.12.dylib ./Skimo.app/Contents/Frameworks/
    cp /usr/local/opt/mbedtls/lib/libmbedcrypto.3.dylib ./Skimo.app/Contents/Frameworks/
    cp /usr/local/opt/mbedtls/lib/libmbedx509.0.dylib ./Skimo.app/Contents/Frameworks/
    chmod +w ./Skimo.app/Contents/Frameworks/*.dylib
    install_name_tool -id @executable_path/../Frameworks/libmbedtls.12.dylib ./Skimo.app/Contents/Frameworks/libmbedtls.12.dylib
    install_name_tool -id @executable_path/../Frameworks/libmbedcrypto.3.dylib ./Skimo.app/Contents/Frameworks/libmbedcrypto.3.dylib
    install_name_tool -id @executable_path/../Frameworks/libmbedx509.0.dylib ./Skimo.app/Contents/Frameworks/libmbedx509.0.dylib
    install_name_tool -change libmbedtls.12.dylib @executable_path/../Frameworks/libmbedtls.12.dylib ./Skimo.app/Contents/Plugins/obs-outputs.so
    install_name_tool -change libmbedcrypto.3.dylib @executable_path/../Frameworks/libmbedcrypto.3.dylib ./Skimo.app/Contents/Plugins/obs-outputs.so
    install_name_tool -change libmbedx509.0.dylib @executable_path/../Frameworks/libmbedx509.0.dylib ./Skimo.app/Contents/Plugins/obs-outputs.so
elif [ -f /usr/local/opt/mbedtls/lib/libmbedtls.13.dylib ]; then
    cp /usr/local/opt/mbedtls/lib/libmbedtls.13.dylib ./Skimo.app/Contents/Frameworks/
    cp /usr/local/opt/mbedtls/lib/libmbedcrypto.5.dylib ./Skimo.app/Contents/Frameworks/
    cp /usr/local/opt/mbedtls/lib/libmbedx509.1.dylib ./Skimo.app/Contents/Frameworks/
    chmod +w ./Skimo.app/Contents/Frameworks/*.dylib
    install_name_tool -id @executable_path/../Frameworks/libmbedtls.13.dylib ./Skimo.app/Contents/Frameworks/libmbedtls.13.dylib
    install_name_tool -id @executable_path/../Frameworks/libmbedcrypto.5.dylib ./Skimo.app/Contents/Frameworks/libmbedcrypto.5.dylib
    install_name_tool -id @executable_path/../Frameworks/libmbedx509.1.dylib ./Skimo.app/Contents/Frameworks/libmbedx509.1.dylib
    install_name_tool -change libmbedtls.13.dylib @executable_path/../Frameworks/libmbedtls.13.dylib ./Skimo.app/Contents/Plugins/obs-outputs.so
    install_name_tool -change libmbedcrypto.5.dylib @executable_path/../Frameworks/libmbedcrypto.5.dylib ./Skimo.app/Contents/Plugins/obs-outputs.so
    install_name_tool -change libmbedx509.1.dylib @executable_path/../Frameworks/libmbedx509.1.dylib ./Skimo.app/Contents/Plugins/obs-outputs.so
fi

install_name_tool -change /usr/local/opt/curl/lib/libcurl.4.dylib @executable_path/../Frameworks/libcurl.4.dylib ./Skimo.app/Contents/Plugins/obs-outputs.so
install_name_tool -change @rpath/libobs.0.dylib @executable_path/../Frameworks/libobs.0.dylib ./Skimo.app/Contents/Plugins/obs-outputs.so
install_name_tool -change /tmp/obsdeps/bin/libjansson.4.dylib @executable_path/../Frameworks/libjansson.4.dylib ./Skimo.app/Contents/Plugins/obs-outputs.so

# copy sparkle into the app
hr "Copying Sparkle.framework"
cp -R ../../sparkle/Sparkle.framework ./Skimo.app/Contents/Frameworks/
install_name_tool -change @rpath/Sparkle.framework/Versions/A/Sparkle @executable_path/../Frameworks/Sparkle.framework/Versions/A/Sparkle ./Skimo.app/Contents/MacOS/obs

# Copy Chromium embedded framework to app Frameworks directory
hr "Copying Chromium Embedded Framework.framework"
sudo mkdir -p Skimo.app/Contents/Frameworks
sudo cp -R ../../cef_binary_${CEF_BUILD_VERSION}_macosx64/Release/Chromium\ Embedded\ Framework.framework Skimo.app/Contents/Frameworks/

install_name_tool -change /usr/local/opt/qt/lib/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui.framework/Versions/5/QtGui ./Skimo.app/Contents/Plugins/obs-browser.so
install_name_tool -change /usr/local/opt/qt/lib/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/5/QtCore ./Skimo.app/Contents/Plugins/obs-browser.so
install_name_tool -change /usr/local/opt/qt/lib/QtWidgets.framework/Versions/5/QtWidgets @executable_path/../Frameworks/QtWidgets.framework/Versions/5/QtWidgets ./Skimo.app/Contents/Plugins/obs-browser.so

cp ../CI/install/osx/OBSPublicDSAKey.pem Skimo.app/Contents/Resources

# edit plist
plutil -insert CFBundleVersion -string $GIT_TAG ./Skimo.app/Contents/Info.plist
plutil -insert CFBundleShortVersionString -string $GIT_TAG ./Skimo.app/Contents/Info.plist
plutil -insert OBSFeedsURL -string https://obsproject.com/osx_update/feeds.xml ./Skimo.app/Contents/Info.plist
plutil -insert SUFeedURL -string https://obsproject.com/osx_update/stable/updates.xml ./Skimo.app/Contents/Info.plist
plutil -insert SUPublicDSAKeyFile -string OBSPublicDSAKey.pem ./Skimo.app/Contents/Info.plist

dmgbuild -s ../CI/install/osx/settings.json "Skimo" Skimo.dmg

if [ -v "$TRAVIS" ]; then
	# Signing stuff
	hr "Decrypting Cert"
	openssl aes-256-cbc -K $encrypted_dd3c7f5e9db9_key -iv $encrypted_dd3c7f5e9db9_iv -in ../CI/osxcert/Certificates.p12.enc -out Certificates.p12 -d
	hr "Creating Keychain"
	security create-keychain -p mysecretpassword build.keychain
	security default-keychain -s build.keychain
	security unlock-keychain -p mysecretpassword build.keychain
	security set-keychain-settings -t 3600 -u build.keychain
	hr "Importing certs into keychain"
	security import ./Certificates.p12 -k build.keychain -T /usr/bin/productsign -P ""
	# macOS 10.12+
	security set-key-partition-list -S apple-tool:,apple: -s -k mysecretpassword build.keychain
fi

cp ./Skimo.dmg ./$FILENAME

# Move to the folder that travis uses to upload artifacts from
hr "Moving package to nightly folder for distribution"
mkdir ../nightly
sudo mv ./$FILENAME ../nightly
