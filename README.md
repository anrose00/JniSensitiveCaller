Requires Cmake / VS2017+

build with:
```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
mkdir build
cmake --build build
```
run:
```
build\Debug\JniTest.exe
```
result (JDK17):

JVM option: -Djava.class.path=.;D:\java\JniTest.jar
JVM created successfully
baseName=com.apisgroup.languageTools.bundles.graphEditor.Images
Exception in thread "main" java.lang.NullPointerException: Cannot invoke "java.lang.Class.getModule()" because "caller" is null
        at java.base/java.util.ResourceBundle.getDefaultControl(ResourceBundle.java:1508)
        at java.base/java.util.ResourceBundle.getBundle(ResourceBundle.java:1280)
