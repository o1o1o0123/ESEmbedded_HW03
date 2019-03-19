HW03
===
This is the hw03 sample. Please follow the steps below.

# Build the Sample Program

1. Fork this repo to your own github account.

2. Clone the repo that you just forked.

3. Under the hw03 dir, use:

	* `make` to build.

	* `make clean` to clean the ouput files.

4. Extract `gnu-mcu-eclipse-qemu.zip` into hw03 dir. Under the path of hw03, start emulation with `make qemu`.

	See [Lecture 02 ─ Emulation with QEMU] for more details.

5. The sample is a minimal program for ARM Cortex-M4 devices, which enters `while(1);` after reset. Use gdb to get more details.

	See [ESEmbedded_HW02_Example] for knowing how to do the observation and how to use markdown for taking notes.

# Build Your Own Program

1. Edit main.c.

2. Make and run like the steps above.

3. Please avoid using hardware dependent C Standard library functions like `printf`, `malloc`, etc.

# HW03 Requirements

1. How do C functions pass and return parameters? Please describe the related standard used by the Application Binary Interface (ABI) for the ARM architecture.

2. Modify main.c to observe what you found.

3. You have to state how you designed the observation (code), and how you performed it.

	Just like how you did in HW02.

3. If there are any official data that define the rules, you can also use them as references.

4. Push your repo to your github. (Use .gitignore to exclude the output files like object files or executable files and the qemu bin folder)

[Lecture 02 ─ Emulation with QEMU]: http://www.nc.es.ncku.edu.tw/course/embedded/02/#Emulation-with-QEMU
[ESEmbedded_HW02_Example]: https://github.com/vwxyzjimmy/ESEmbedded_HW02_Example

--------------------

 **If you volunteer to give the presentation next week, check this.**

--------------------
HW02 
===
## 1. 實驗題目
改寫main.c並觀察Return指令如何運行。
## 2. 實驗內容
ARM有固定的架構ARM ( Architecture Procedure Call Standard ）,下圖附上ARMv7-M Architecture Reference Manual之介紹:
![](https://github.com/o1o1o0123/ESEmbedded_HW03/blob/master/img_folder_2/Procedure%20Call%20Standard%20for%20the%20ARM%20Architecture.jpg)
![](https://github.com/o1o1o0123/ESEmbedded_HW03/blob/master/img_folder_2/Procedure%20Call%20Standard%20for%20the%20ARM%20Architecture2.jpg)
如協議所示，每個記憶體讀取皆有固定之格式進行堆放記憶體。

## 3. 實驗步驟
設計測試程式 main.c ，從 _rest_handler) 開始後依序執行(a)引入一個引數並回傳一個值(b)引入五個引數並回傳一個值(c)引入五個指標引數，併使用指標回傳複數個值。

main.c:
```
int function_add(int a,int b, int c, int d, int e) //callee 
{
	int x[5] = {a,b,c,d,e};
	int ans=(x[0]+x[1])*x[2]-x[3]-x[4];
	return ans;
}
int caller_1(void)   //callee  ARG
{
	const int x[5] = {1,2,3,4,5};
	int ans=function_add( x[4], x[3], x[2], x[1], x[0]);
	return ans;
}
int a=0;
int b=1;
int c=2;
int d=3;
int e=4;
const int f=5;
const int g=6;
const int h=7;
const int i=8;
const int j=9;
void reset_handler(void)
{	
		int k=10;
		int l=11;
		int m=12;
		int n=13;
		int o=14;
		const int p=15;
		const int q=16;
		const int r=17;
		const int s=18;
		const int t=19;
		int ans_1=function_add(k, l, m, n, o);   //caller
		int ans_0=caller_1();               //callermake
	while (1)
	{
	}
}
```

將 main.c 編譯,反組譯之後如下所示：  
```
Disassembly of section .mytext:

00000000 <function_add-0x8>:
   0:	20000100 	andcs	r0, r0, r0, lsl #2
   4:	00000075 	andeq	r0, r0, r5, ror r0

00000008 <function_add>:
   8:	b480      	push	{r7}
   a:	b08b      	sub	sp, #44	; 0x2c
   c:	af00      	add	r7, sp, #0
   e:	60f8      	str	r0, [r7, #12]
  10:	60b9      	str	r1, [r7, #8]
  12:	607a      	str	r2, [r7, #4]
  14:	603b      	str	r3, [r7, #0]
  16:	68fb      	ldr	r3, [r7, #12]
  18:	613b      	str	r3, [r7, #16]
  1a:	68bb      	ldr	r3, [r7, #8]
  1c:	617b      	str	r3, [r7, #20]
  1e:	687b      	ldr	r3, [r7, #4]
  20:	61bb      	str	r3, [r7, #24]
  22:	683b      	ldr	r3, [r7, #0]
  24:	61fb      	str	r3, [r7, #28]
  26:	6b3b      	ldr	r3, [r7, #48]	; 0x30
  28:	623b      	str	r3, [r7, #32]
  2a:	693a      	ldr	r2, [r7, #16]
  2c:	697b      	ldr	r3, [r7, #20]
  2e:	4413      	add	r3, r2
  30:	69ba      	ldr	r2, [r7, #24]
  32:	fb02 f203 	mul.w	r2, r2, r3
  36:	69fb      	ldr	r3, [r7, #28]
  38:	1ad2      	subs	r2, r2, r3
  3a:	6a3b      	ldr	r3, [r7, #32]
  3c:	1ad3      	subs	r3, r2, r3
  3e:	627b      	str	r3, [r7, #36]	; 0x24
  40:	6a7b      	ldr	r3, [r7, #36]	; 0x24
  42:	4618      	mov	r0, r3
  44:	372c      	adds	r7, #44	; 0x2c
  46:	46bd      	mov	sp, r7
  48:	f85d 7b04 	ldr.w	r7, [sp], #4
  4c:	4770      	bx	lr
  4e:	bf00      	nop

00000050 <caller_1>:
  50:	b590      	push	{r4, r7, lr}
  52:	b085      	sub	sp, #20
  54:	af02      	add	r7, sp, #8
  56:	2005      	movs	r0, #5
  58:	2104      	movs	r1, #4
  5a:	2203      	movs	r2, #3
  5c:	2402      	movs	r4, #2
  5e:	2301      	movs	r3, #1
  60:	9300      	str	r3, [sp, #0]
  62:	4623      	mov	r3, r4
  64:	f7ff ffd0 	bl	8 <function_add>
  68:	6078      	str	r0, [r7, #4]
  6a:	687b      	ldr	r3, [r7, #4]
  6c:	4618      	mov	r0, r3
  6e:	370c      	adds	r7, #12
  70:	46bd      	mov	sp, r7
  72:	bd90      	pop	{r4, r7, pc}

00000074 <reset_handler>:
  74:	b580      	push	{r7, lr}
  76:	b08e      	sub	sp, #56	; 0x38
  78:	af02      	add	r7, sp, #8
  7a:	230a      	movs	r3, #10
  7c:	62fb      	str	r3, [r7, #44]	; 0x2c
  7e:	230b      	movs	r3, #11
  80:	62bb      	str	r3, [r7, #40]	; 0x28
  82:	230c      	movs	r3, #12
  84:	627b      	str	r3, [r7, #36]	; 0x24
  86:	230d      	movs	r3, #13
  88:	623b      	str	r3, [r7, #32]
  8a:	230e      	movs	r3, #14
  8c:	61fb      	str	r3, [r7, #28]
  8e:	230f      	movs	r3, #15
  90:	61bb      	str	r3, [r7, #24]
  92:	2310      	movs	r3, #16
  94:	617b      	str	r3, [r7, #20]
  96:	2311      	movs	r3, #17
  98:	613b      	str	r3, [r7, #16]
  9a:	2312      	movs	r3, #18
  9c:	60fb      	str	r3, [r7, #12]
  9e:	2313      	movs	r3, #19
  a0:	60bb      	str	r3, [r7, #8]
  a2:	69fb      	ldr	r3, [r7, #28]
  a4:	9300      	str	r3, [sp, #0]
  a6:	6af8      	ldr	r0, [r7, #44]	; 0x2c
  a8:	6ab9      	ldr	r1, [r7, #40]	; 0x28
  aa:	6a7a      	ldr	r2, [r7, #36]	; 0x24
  ac:	6a3b      	ldr	r3, [r7, #32]
  ae:	f7ff ffab 	bl	8 <function_add>
  b2:	6078      	str	r0, [r7, #4]
  b4:	f7ff ffcc 	bl	50 <caller_1>
  b8:	6038      	str	r0, [r7, #0]
  ba:	e7fe      	b.n	ba <reset_handler+0x46>

Disassembly of section .rodata:

000000bc <f>:
  bc:	00000005 	andeq	r0, r0, r5

000000c0 <g>:
  c0:	00000006 	andeq	r0, r0, r6

000000c4 <h>:
  c4:	00000007 	andeq	r0, r0, r7

000000c8 <i>:
  c8:	00000008 	andeq	r0, r0, r8

000000cc <j>:
  cc:	00000009 	andeq	r0, r0, r9

000000d0 <x.3956>:
  d0:	00000001 	andeq	r0, r0, r1
  d4:	00000002 	andeq	r0, r0, r2
  d8:	00000003 	andeq	r0, r0, r3
  dc:	00000004 	andeq	r0, r0, r4
  e0:	00000005 	andeq	r0, r0, r5

Disassembly of section .data:

000000e4 <b>:
  e4:	00000001 	andeq	r0, r0, r1

000000e8 <c>:
  e8:	00000002 	andeq	r0, r0, r2

000000ec <d>:
  ec:	00000003 	andeq	r0, r0, r3

000000f0 <e>:
  f0:	00000004 	andeq	r0, r0, r4

Disassembly of section .bss:

000000f4 <a>:
  f4:	00000000 	andeq	r0, r0, r0

Disassembly of section .comment:

00000000 <.comment>:
   0:	3a434347 	bcc	10d0d24 <a+0x10d0c30>
   4:	35312820 	ldrcc	r2, [r1, #-2080]!	; 0xfffff7e0
   8:	392e343a 	stmdbcc	lr!, {r1, r3, r4, r5, sl, ip, sp}
   c:	732b332e 			; <UNDEFINED> instruction: 0x732b332e
  10:	33326e76 	teqcc	r2, #1888	; 0x760
  14:	37373131 			; <UNDEFINED> instruction: 0x37373131
  18:	2029312d 	eorcs	r3, r9, sp, lsr #2
  1c:	2e392e34 	mrccs	14, 1, r2, cr9, cr4, {1}
  20:	30322033 	eorscc	r2, r2, r3, lsr r0
  24:	35303531 	ldrcc	r3, [r0, #-1329]!	; 0xfffffacf
  28:	28203932 	stmdacs	r0!, {r1, r4, r5, r8, fp, ip, sp}
  2c:	72657270 	rsbvc	r7, r5, #112, 4
  30:	61656c65 	cmnvs	r5, r5, ror #24
  34:	00296573 	eoreq	r6, r9, r3, ror r5

Disassembly of section .ARM.attributes:

00000000 <.ARM.attributes>:
   0:	00003041 	andeq	r3, r0, r1, asr #32
   4:	61656100 	cmnvs	r5, r0, lsl #2
   8:	01006962 	tsteq	r0, r2, ror #18
   c:	00000026 	andeq	r0, r0, r6, lsr #32
  10:	726f4305 	rsbvc	r4, pc, #335544320	; 0x14000000
  14:	2d786574 	cfldr64cs	mvdx6, [r8, #-464]!	; 0xfffffe30
  18:	0600344d 	streq	r3, [r0], -sp, asr #8
  1c:	094d070d 	stmdbeq	sp, {r0, r2, r3, r8, r9, sl}^
  20:	14041202 	strne	r1, [r4], #-514	; 0xfffffdfe
  24:	17011501 	strne	r1, [r1, -r1, lsl #10]
  28:	1a011803 	bne	4603c <a+0x45f48>
  2c:	22061e01 	andcs	r1, r6, #1, 28
  30:	Address 0x0000000000000030 is out of bounds.
```
起初會從0X00000000開始，接著定義SP在0X20000100，再接著定義程式從0X00000074開始。
```
00000000 <function_add-0x8>:
   0:	20000100 	andcs	r0, r0, r0, lsl #2
   4:	00000075 	andeq	r0, r0, r5, ror r0  
```
由下面可以得知6件事情

1.SP會預先推疊56給主程式使用。

2.r7會是SP加8之後的記憶體位置，使得記憶體中空出32bit，用於暫存器。

3.如果要將值給副程式使用時，會先將數值放入暫存器中，如：r0、r1、r2、r3依序放入。如果暫存的值多餘4個以後，會先將最後一個值依序放入記憶體中空餘的地址，直到最後4個值，在依序放入r0、r1、r2、r3中。

4.暫存的值會優先放入r3中。

5.回傳的值會優先放入r0中。

6.進行副程式時，會將lr記紀錄離開的的點，如：lr等於主程式回來的記憶體位置加一的值。
```
00000074 <reset_handler>:
  74:	b580      	push	{r7, lr}                    <---將r7和lr的值放置到堆疊記憶體中
  76:	b08e      	sub	sp, #56	; 0x38              <---SP下向推出56個空白記憶體位置，用於存放記憶體
  78:	af02      	add	r7, sp, #8                  <---將SP的值加8放入r7中
  7a:	230a      	movs	r3, #10                     <---將10放入r3                  (1)
  7c:	62fb      	str	r3, [r7, #44]	; 0x2c      <---將r3放入r7+44的記憶體位置    (2) 
  7e:	230b      	movs	r3, #11                     <---同(1)步驟
  80:	62bb      	str	r3, [r7, #40]	; 0x28      <---同(2)步驟
  82:	230c      	movs	r3, #12                     <---同(1)步驟
  84:	627b      	str	r3, [r7, #36]	; 0x24      <---同(2)步驟
  86:	230d      	movs	r3, #13                     <---同(1)步驟
  88:	623b      	str	r3, [r7, #32]               <---同(2)步驟
  8a:	230e      	movs	r3, #14                     <---同(1)步驟
  8c:	61fb      	str	r3, [r7, #28]               <---同(2)步驟
  8e:	230f      	movs	r3, #15                     <---同(1)步驟
  90:	61bb      	str	r3, [r7, #24]               <---同(2)步驟
  92:	2310      	movs	r3, #16                     <---同(1)步驟
  94:	617b      	str	r3, [r7, #20]               <---同(2)步驟
  96:	2311      	movs	r3, #17                     <---同(1)步驟
  98:	613b      	str	r3, [r7, #16]               <---同(2)步驟
  9a:	2312      	movs	r3, #18                     <---同(1)步驟
  9c:	60fb      	str	r3, [r7, #12]               <---同(2)步驟
  9e:	2313      	movs	r3, #19                     <---同(1)步驟
  a0:	60bb      	str	r3, [r7, #8]                <---同(2)步驟
  a2:	69fb      	ldr	r3, [r7, #28]               <---將r7+28的記憶體位置的值 放入r3
  a4:	9300      	str	r3, [sp, #0]                <---將r3放入SP的記憶體位置
  a6:	6af8      	ldr	r0, [r7, #44]	; 0x2c      <---將r7+44的記憶體位置的值 放入r0
  a8:	6ab9      	ldr	r1, [r7, #40]	; 0x28      <---將r7+44的記憶體位置的值 放入r1
  aa:	6a7a      	ldr	r2, [r7, #36]	; 0x24      <---將r7+44的記憶體位置的值 放入r2
  ac:	6a3b      	ldr	r3, [r7, #32]               <---將r7+44的記憶體位置的值 放入r3
  ae:	f7ff ffab 	bl	8 <function_add>            <---跳到0X00000008的記憶體位置，進行副程式。
								同時會將lr紀錄跳開的記憶體位置，lr等於下一步記憶體位置加一的結果。
  b2:	6078      	str	r0, [r7, #4]                <---將r7+4的記憶體位置的值 回傳的值放到r0
  b4:	f7ff ffcc 	bl	50 <caller_1>               <---跳到0X00000050的記憶體位置，進行副程式
  b8:	6038      	str	r0, [r7, #0]                <---將r7的記憶體位置的值 回傳的值放到r0
  ba:	e7fe      	b.n	ba <reset_handler+0x46>
```
執行完ae會將執行過程跳致副程式中開始執行0X00000008。

由下面可以得知6件事情

1.計算的結果會優先放入r3，接著r2，輪流放置。

2.回傳的值會優先放入r0
```
00000008 <function_add>:
   8:	b480      	push	{r7}
   a:	b08b      	sub	sp, #44	; 0x2c              <---SP下向推出56個空白記憶體位置，用於存放記憶體
   c:	af00      	add	r7, sp, #0
   e:	60f8      	str	r0, [r7, #12]               <---將r0放入r7+12的記憶體位置
  10:	60b9      	str	r1, [r7, #8]                <---將r1放入r7+8的記憶體位置
  12:	607a      	str	r2, [r7, #4]                <---將r2放入r7+4的記憶體位置
  14:	603b      	str	r3, [r7, #0]                <---將r3放入r7+0的記憶體位置。 一共有4個值記錄到記憶體位置裡面
                                                                將值放入矩陣過程
  16:	68fb      	ldr	r3, [r7, #12]               <---將r7+12的記憶體位置的值 放入r3                      (4)
  18:	613b      	str	r3, [r7, #16]               <---將r3放入r7+16的記憶體位置              第1個值      (5)
  1a:	68bb      	ldr	r3, [r7, #8]                <---同(4)步驟
  1c:	617b      	str	r3, [r7, #20]               <---同(5)步驟                             第2個值
  1e:	687b      	ldr	r3, [r7, #4]                <---同(4)步驟
  20:	61bb      	str	r3, [r7, #24]               <---同(5)步驟                             第3個值
  22:	683b      	ldr	r3, [r7, #0]                <---同(4)步驟
  24:	61fb      	str	r3, [r7, #28]               <---同(5)步驟                             第4個值
  26:	6b3b      	ldr	r3, [r7, #48]	; 0x30      <---此值為a4暫存記憶體位置，紀錄第5個值
  28:	623b      	str	r3, [r7, #32]               <---將r3放入r7+32的記憶體位置              第5個值
------------------------將兩個值相加---------------------------
  2a:	693a      	ldr	r2, [r7, #16]
  2c:	697b      	ldr	r3, [r7, #20]               <---將兩個值取出到r2、r3
  2e:	4413      	add	r3, r2                      <---將r3+r2的結果放到r3
------------------------將兩個值相乘---------------------------
  30:	69ba      	ldr	r2, [r7, #24]               <---將值取出到r2
  32:	fb02 f203 	mul.w	r2, r2, r3                  <---將r2*r3的結果放到r2
------------------------將兩個值相減---------------------------
  36:	69fb      	ldr	r3, [r7, #28]
  38:	1ad2      	subs	r2, r2, r3
  3a:	6a3b      	ldr	r3, [r7, #32]
  3c:	1ad3      	subs	r3, r2, r3
------------------------將兩個值相減---------------------------
  3e:	627b      	str	r3, [r7, #36]	; 0x24      <---最後將計算的值放入r7+36的地址
  40:	6a7b      	ldr	r3, [r7, #36]	; 0x24      <---將r7+36地址的值取出放到r3
  42:	4618      	mov	r0, r3                      <---將r3的值放入r0，用於回傳
  44:	372c      	adds	r7, #44	; 0x2c              <---將SP+44放入r7，目的使r7的值歸回原本副程式剛開始的值
  46:	46bd      	mov	sp, r7                      <---令sp等於r7
  48:	f85d 7b04 	ldr.w	r7, [sp], #4                <---令sp等於SP+4之結果，r7等於sp+8之結果結果
  4c:	4770      	bx	lr                          <---命定下一點起始點等於lr之值
  4e:	bf00      	nop
```

```
00000050 <caller_1>:
  50:	b590      	push	{r4, r7, lr}
  52:	b085      	sub	sp, #20
  54:	af02      	add	r7, sp, #8
  56:	2005      	movs	r0, #5
  58:	2104      	movs	r1, #4
  5a:	2203      	movs	r2, #3
  5c:	2402      	movs	r4, #2
  5e:	2301      	movs	r3, #1
  60:	9300      	str	r3, [sp, #0]
  62:	4623      	mov	r3, r4
  64:	f7ff ffd0 	bl	8 <function_add>
  68:	6078      	str	r0, [r7, #4]
  6a:	687b      	ldr	r3, [r7, #4]
  6c:	4618      	mov	r0, r3
  6e:	370c      	adds	r7, #12
  70:	46bd      	mov	sp, r7
  72:	bd90      	pop	{r4, r7, pc}
```
## 3. 結果與討論
1.傳遞值的過程值中，優先順位為r0、r1、r2、r3。

2.當傳遞的值超過4個以上，會將多餘的值放到堆疊中。

3.r3會被優先當作計算的放置位置，接著r2輪流交換。
