set src=D:\Project\VS2015\branche\BuildAndroid
set dest=D:\Project\Android\VkingAndroid\app\src\main\jniLibs\armeabi-v7a

xcopy "%src%\libs\armeabi-v7a\libVking-Engine-Core.so" "%dest%\libVking-Engine-Core.so"  /Y
xcopy "%src%\libs\armeabi-v7a\libc++_shared.so" "%dest%\libc++_shared.so"  /Y
xcopy "%src%\Source\GIS\libGIS.so" "%dest%\libGIS.so"  /Y
xcopy "%src%\Source\Vking-Engine-V8.0-JNI\libVking-Engine-V8.0-JNI.so" "%dest%\libVking-Engine-V8.0-JNI.so"  /Y
xcopy "%src%\Source\Vking-Gis-V8.0-JNI\libVking-Gis-V8.0-JNI.so" "%dest%\libVking-Gis-V8.0-JNI.so"  /Y
@cmd.exe