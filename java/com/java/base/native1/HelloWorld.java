package com.java.base.native1;

public class HelloWorld {
	
	static { 
		//System.setProperty("java.library.path", ".");
        System.loadLibrary("hello");
    }
	public static native void hello(String msg);
	public static void test(){
		hello("hello world!");
	}

	public static void main(String[] args) {
		test();
		//System.out.println(System.getProperty("java.library.path"));
	}

}

