#include <jni.h>
#include "com_java_base_native1_HelloWorld.h"
#include <stdio.h>

JNIEXPORT void JNICALL Java_com_java_base_native1_HelloWorld_hello
  (JNIEnv *, jclass, jstring){
	  printf("Hello world!\n");
	  return;
}
int main(){
	return 0;
}
