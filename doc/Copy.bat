set src=E:\Project\trunk\web\bin
set dest=E:\Project\vking-engine-web\Source\assets\webcore\wasm-es6

xcopy "%src%\VK-WebCore.js" "%dest%\VK-WebCore.es6.js"  /Y
xcopy "%src%\VK-WebCore.wasm" "%dest%\VK-WebCore.wasm"  /Y
@cmd.exe