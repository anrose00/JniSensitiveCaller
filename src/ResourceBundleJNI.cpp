/*
 * resourcebundle.cpp
 *
 *  Created on: 28.01.2022
 *      Author: anrose00
 */

#include <stdlib.h>
#include <stdint.h>
#include <jni.h>

JavaVM *jvm;       /* denotes a Java VM */
JNIEnv *env;       /* pointer to native method interface */


int main(int argc, char * argv[]) {
   char * vmOptions = "-Djava.class.path=.;D:\\java\\JniTest.jar";

   JavaVMInitArgs vm_args; 
   JavaVMOption options;
   jint res;
    
   options.optionString = vmOptions;
   vm_args.version = JNI_VERSION_1_8;
   vm_args.nOptions = 1;
   vm_args.options = &options;
   vm_args.ignoreUnrecognized = JNI_FALSE;
   /* load and initialize a Java VM, return a JNI interface
     * pointer in env */

   printf("JVM option: %s\n", options.optionString);

   res = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
   if (!res){
       printf("JVM created successfully\n");
   } else {
       printf("res = %i",res);
       exit(1);
   }

   // get system class loader
   jclass ClassLoader = env->FindClass("java/lang/ClassLoader");
   if(env->ExceptionCheck()) { env->ExceptionDescribe(); env->ExceptionClear(); exit(1); }   

   jmethodID getClassLoaderMethID = env->GetStaticMethodID( ClassLoader, "getSystemClassLoader","()Ljava/lang/ClassLoader;");
   if(env->ExceptionCheck()) { env->ExceptionDescribe(); env->ExceptionClear(); exit(1); }   

   jobject systemClassLoader = env->CallStaticObjectMethod(ClassLoader, getClassLoaderMethID);
   if(env->ExceptionCheck()) { env->ExceptionDescribe(); env->ExceptionClear(); exit(1); }   
 
   // setup base name
   jstring baseName = env->NewStringUTF("com.apisgroup.languageTools.bundles.graphEditor.Images");
   printf("baseName=%s\n", env->GetStringUTFChars(baseName, NULL));

   // setup locale
   jclass Locale = env->FindClass("java/util/Locale");
   if(env->ExceptionCheck()) { env->ExceptionDescribe(); env->ExceptionClear(); exit(1); }   

   jmethodID localeConstructor = env->GetMethodID(Locale, "<init>", "(Ljava/lang/String;)V");
   if(env->ExceptionCheck()) { env->ExceptionDescribe(); env->ExceptionClear(); exit(1); }   

   jstring langJString  = env->NewStringUTF("en");
   jobject locale = env->NewObject(Locale, localeConstructor, langJString);
   if(env->ExceptionCheck()) { env->ExceptionDescribe(); env->ExceptionClear(); exit(1); }   
    
   // get resource bundle
   jclass ResourceBundle = env->FindClass("java/util/ResourceBundle");
   if(env->ExceptionCheck()) { env->ExceptionDescribe(); env->ExceptionClear(); exit(1); }   

   jmethodID getBundleMethID = env->GetStaticMethodID( ResourceBundle, "getBundle","(Ljava/lang/String;Ljava/util/Locale;Ljava/lang/ClassLoader;)Ljava/util/ResourceBundle;");
   if(env->ExceptionCheck()) { env->ExceptionDescribe(); env->ExceptionClear(); exit(1); }   

   // this call crashes when called from JNI and JAVA > 8 - caller sensitive call
   jobject resourceBundle = env->CallStaticObjectMethod(ResourceBundle, getBundleMethID, baseName, locale,systemClassLoader);
   if(env->ExceptionCheck()) { env->ExceptionDescribe(); env->ExceptionClear(); exit(1); }   

   jmethodID toString = env->GetMethodID(ResourceBundle, "toString", "()Ljava/lang/String;");
   jstring resourceBundleJString = static_cast<jstring> (env->CallObjectMethod(resourceBundle, toString));
   if(env->ExceptionCheck()) { env->ExceptionDescribe(); env->ExceptionClear(); exit(1); }   
   
   printf("resource bundle = %s\n", env->GetStringUTFChars(resourceBundleJString,NULL));
   
}