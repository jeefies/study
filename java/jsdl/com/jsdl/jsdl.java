package com.jsdl;

public class jsdl {
	static {
		System.loadLibrary("jsdl");
	}
	public static native void Init(int flags);
	public static native void CreateWindow(String title, int w, int h);
	public static native void Delay(int ms);
	public static native void Quit();

	public static final int INIT = 0x000000431;

	public static void main(String[] args) {
		Init(INIT);

		CreateWindow("SDL in JAVA", 450, 600);

		Delay(2000);

		Quit();
	}
}
