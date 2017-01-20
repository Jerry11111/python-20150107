/**
 * 将变量及常量压入操作数栈中
 * @ClassName PushVariable
 * @author Administrator
 * @date 2014-12-28
 */
public class PushVariable {
	
	
	
	/**const指令<p>
	 * 概念:
	 * 该系列命令主要负责把简单的数值类型送到栈顶。该系列命令不带参数。注意只把简单的数值类型送到栈顶时，才使用如下的命令。
	 * int类型只能把-1,0,1,2,3,4,5送到栈顶
	 * （分别采用iconst_m1,iconst_0, iconst_1, iconst_2, iconst_3, iconst_4, iconst_5）
	 * 对于int型，其他的数值请使用push系列命令（比如bipush）
	 * 
	 * long类型只把0,1送到栈顶,对应的指令为：lconst_0,lconst_1
	 * 
	 * float类型只把0,1,2送到栈顶,对于的指令为：fconst_0,fconst_1,fconst_2
	 * 
	 * double类型只把0,1送到栈顶,对应的指令为:dconst_0,dconst_1
	 * 
	 * 
	 * 
	 * bipush指令<p>
	 * 概念:将单字节的常量值(-128~127)推送至栈顶
	 * 用法:
	 * 
	 * sipush指令<p>
	 * 概念:将一个短整型常量值(-32768~32767)推送至栈顶
	 * 用法:sipush  255
	 * 
	 * 
	 */
	@SuppressWarnings("unused")
	public void constInstruct(){
		//int 类型
		int i_2=-2;
		int i_1=-1;
		int i0=0;
		int i1=1;
		int i2=2;
		int i3=3;
		int i4=4;
		int i5=5;
		int i6=6;
		int i255=255;
		float f233 = 23.3f;
		long l = 152;
		/**
		   0:   bipush  -2
		   2:   istore_1
		   3:   iconst_m1
		   4:   istore_2
		   5:   iconst_0
		   6:   istore_3
		   7:   iconst_1
		   8:   istore  4
		   10:  iconst_2
		   11:  istore  5
		   13:  iconst_3
		   14:  istore  6
		   16:  iconst_4
		   17:  istore  7
		   19:  iconst_5
		   20:  istore  8
		   22:  bipush  6
		   24:  istore  9
		   26:  sipush  255
		   29:  istore  10
		   31:  return
		 */
	
	}
	
	/**
	 * idc指令<p>
	 * 用法:将int float long double 和String等常量从常量池中压入操作数栈中
	 * 实例:ldc     #93
	 * 注意:
	 * string中+默认使用StringBuilder添加
	 */
	public void ldcInstruct(){
		String str="字符串";
		String str2=str+"添加";
		/**
		 * Stack=3, Locals=3, Args_size=1
		   0:   ldc     #93; //String 字符串
		   2:   astore_1
		   3:   new     #54; //class java/lang/StringBuilder
		   6:   dup
		   7:   aload_1
		   8:   invokestatic    #95; //Method java/lang/String.valueOf:(Ljava/lang/Object;)Ljava/lang/String;
		   11:  invokespecial   #58; //Method java/lang/StringBuilder."<init>":(Ljava/lang/String;)V
		   14:  ldc     #100; //String 添加
		   16:  invokevirtual   #60; //Method java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
		   19:  invokevirtual   #64; //Method java/lang/StringBuilder.toString:()Ljava/lang/String;
		   22:  astore_2
		   23:  return
		 */
	}
	
	/**
	 * 哪些变量应该放在常量池中：
	 * 1.数值常量和字符串常量,例如：final static int id=23;String str="字符串常量"
	 * 2.对于const系列命令和push系列命令操作范围之外的数值类型常量
	 * int类型：short类型之外的数
	 * float类型：0,1,2之外的数字
	 * long类型:0,1之外的数字
	 * double类型:0,1之外的数字
	 * 
	 * @return:void
	 */
	public static void ldcInstruct2(){
		int i32767=32767;//short范围内
		int i32769=32769;//
		
		float f1=1;
		float f3=3;
		long l1=1;
		long l3=3;
		double d1=1;
		double d3=3;
		
		/**
		   0:   sipush  32767
		   3:   istore_0
		   4:   ldc     #54; //int 32769
		   6:   istore_1
		   7:   fconst_1
		   8:   fstore_2
		   9:   ldc     #55; //float 3.0f
		   11:  fstore_3
		   12:  lconst_1
		   13:  lstore  4
		   15:  ldc2_w  #56; //long 3l
		   18:  lstore  6
		   20:  dconst_1
		   21:  dstore  8
		   23:  ldc2_w  #58; //double 3.0d
		   26:  dstore  10
		   28:  return
		 */
		
		
	}
	
	/**
	 * load指令<p>
	 * 
	 * 概念：
	 * 负责把本地变量的送到栈顶,这里的本地变量不仅可以是数值类型，还可以是引用类型
	 * 
	 * 注意:
	 * 1.对于前四个本地变量可以采用iload_0,iload_1,iload_2,iload_3(它们分别表示第0,1,2,3个整形变量)这种不到参数的简化命令形式
	 * 2.对于第4以上的本地变量将使用iload命令这种形式，在它后面给一参数，以表示是对第几个(从0开始)本类型的本地变量进行操作。
	 * 3.对本地变量所进行的编号，是对所有类型的本地变量进行的（并不按照类型分类）
	 * 4.对于long和double占用两个变量位置
	 * 5.对于非静态函数，第一变量是this,即其对于的操作是aload_0.
	 * 6.还有函数传入参数也算本地变量，在进行编号时，它是先于函数体的本地变量的
	 * 
	 * 各种类型：
	 * int类型：iload_0,iload_1,iload_2,iload_3
	 * float类型：fload_0,fload_1,fload_2,fload_3
	 * long类型：lload_0,lload_1,lload_2,lload_3
	 * double类型：dload_0,dload_1,dload_2,dload_3
	 * 引用类型：aload_0,aload_1,aload_2,aload_3
	 */
	public static void loadInstruct(int i,float f,long l,double d,String str){
		int it=i;
		
		float ft=f;
		
		long lt=l;
		
		double dt=d;
		
		String strt=str;
		
		/**
		   0:   iload_0
		   1:   istore  7
		   3:   fload_1
		   4:   fstore  8
		   6:   lload_2
		   7:   lstore  9
		   9:   dload   4
		   11:  dstore  11
		   13:  aload   6
		   15:  astore  13
		   17:  return
		   
		  LocalVariableTable:
		  Start  Length  Slot  Name   Signature
		  0      18      0    i       I
		  0      18      1    f       F
		  0      18      2    l       J
		  0      18      4    d       D
		  0      18      6    str       Ljava/lang/String;
		  3      15      7    it       I
		  6      12      8    ft       F
		  9      9      9    lt       J
		  13      5      11    dt       D
		  17      1      13    strt       Ljava/lang/String;
		 */
	}
	
	/**
	 * 数组的load指令
	 * 概念：把数组的某项送到栈顶
	 * 
	 * 各种类型数组元素：
	 * iaload   将int型数组指定索引的值推送至栈顶
	 * laload   将long型数组指定索引的值推送至栈顶
	 * faload   将float型数组指定索引的值推送至栈顶
	 * daload   将double型数组指定索引的值推送至栈顶
	 * aaload   将引用型数组指定索引的值推送至栈顶
	 * baload   将boolean或byte型数组指定索引的值推送至栈顶
	 * caload   将char型数组指定索引的值推送至栈顶
	 * saload   将short型数组指定索引的值推送至栈顶

	 * 
	 * @return:void
	 */
	public static void loadInstruct2(){
		String[]array=new String[]{"a","b","c"};
		String a0=array[0];
		
		/**
		   0:   iconst_3
		   1:   anewarray       #32; //class java/lang/String
		   4:   dup
		   5:   iconst_0
		   6:   ldc     #83; //String a
		   8:   aastore
		   9:   dup
		   10:  iconst_1
		   11:  ldc     #85; //String b
		   13:  aastore
		   14:  dup
		   15:  iconst_2
		   16:  ldc     #87; //String c
		   18:  aastore
		   19:  astore_0
		   20:  aload_0
		   21:  iconst_0
		   22:  aaload
		   23:  astore_1
		   24:  return
		 */
		
	}

	/** 
	 * @param args
	 * @return:void
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

}

