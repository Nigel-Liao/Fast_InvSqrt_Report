---
lang: zh-tw
title: Fast InvSqrt
description: Report on Inverse Square Root Fast Algorithm
image: https://i0.wp.com/blogs.embarcadero.com/wp-content/uploads/2021/01/Delphi-Fast-Inverse-Square-Root-Quake-3-Arena-6465040.jpg?resize=1140%2C675&ssl=1
type: slide
robots: noindex, nofollow
---

## Fast Inverse Square Root
  
#### 16 程朗 17 黃品睿 20 廖奶茶

---

## 簡述

Fast Inverse Square Root，  
或是 Fast InvSqrt()  

----

### 用途
最早開發是為了遊戲物理引擎及電腦圖學領域，  
若要求取照明和投影的波動角度與反射效果，  
就經常會是使用到計算平方根倒數的函式。  

----

![Vector](https://miro.medium.com/max/1400/1*7C6G7vRCqcJDZRB5lBEWpA.png)

像是在計算Vector(a,b,c)就常會用到反平方根。  

---

## 歷史

是誰發明的？  
又為何發明？  

----

### 爭議
在他之前就有許多類似程式，  
但普遍認為這演算法的發明者是Carmack  

----

### id Software的共同創辦人-John D.Carmack II
![co-founder](https://pic2.zhimg.com/v2-364afc9d34fbe5bbd4d350f49fd17abf_r.jpg?source=172ae18b)

----

#### 成就
成為戰慄時空、毀滅戰士等知名ip的遊戲引擎。  

![HF](https://thumbor.4gamers.com.tw/YtX0Pa1r5XY9-NrFUYJeg47Iig8=/800x0/filters:extract_cover():no_upscale():quality(80)/https%3A%2F%2Fimg.4gamers.com.tw%2Fckfinder%2Fimages%2FWhy%2520Lee%2F579998eb9c7aa.jpg)

----

### 亮相
1999年，Carmack在 雷神之鎚III競技場(Quake III Arena)中初次發明並使用此演算法。  


![quake3](https://raidofgame.com/uploads/posts/2019-12/1575285955_screenshot-3-quake-3-arena.jpg)
Quake III Arena

----

### 發展
比起一般算法，Fast InvSqrt()有約4倍的速度，  
因而被越來越多圖形與遊戲程式採用。  

---

## 目的 與 原理

----

### 法向量計算

法線的運算，涉及到向量範數的計算。  
其中有大量的反平方根計算，  
錯誤將導致光學路徑的偏移。  

----

### 電腦圖形 光學原理

![image1](https://upload.wikimedia.org/wikipedia/commons/thumb/f/f7/Toru_and_utah_teapot.png/150px-Toru_and_utah_teapot.png) ![image2](https://upload.wikimedia.org/wikipedia/commons/thumb/1/1b/Per_fragment_lighting_example.png/150px-Per_fragment_lighting_example.png)

>左圖為多邊形近似，右圖是將多邊形內部透過頂點法向量進行內插  

----

### 頂點法向量

![vector](https://upload.wikimedia.org/wikipedia/commons/thumb/7/7f/Vertex_tangent%2C_bitangent_and_normal_vector.svg/220px-Vertex_tangent%2C_bitangent_and_normal_vector.svg.png)

頂點的T、B、N一個表面坐標系  

##### 註: T為切向量，B為餘切向量，而N為法向量

---

## 運作機制

----

Carmack在Quake III中的原始碼  
```
float Q_rsqrt( float number )
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;                       // evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck? 
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

	return y;
}
```

---

## 浮點數表示法

----

### 小數表示法 

$$
significand \times base^{exponent}
$$

$$
eg. 1.2345 = 12345 \times 10^{-4}
$$

----

### 記憶體
對一個n bits的浮點數x而言:  
![float-pointing](https://miro.medium.com/max/1400/1*tu8UHXww5mM6ndUVNA_dAg.png)

----

x表示為:


$$
x=(-1)^{s}(1+m_x)2^{e_x}
$$

>$s$ = sign = 0  
$m_x$ = matissa  
$e_x$ = exponent  
平方根內為正數，所以$s$為0  

----

$$
log_2(x) = log_2((1+m_x)2^{e_x}) \\
= log_2(1+{m_x})+{e_x}
$$

$$
I_x = E_xL + M_x \\
e_x = E_x - B \\
$$

----

### IEEE754 表示浮點數的方法

假設今天我們想要把3.1415這個數放在一個float裡
電腦會怎麼樣儲存它呢？
並不是直接把他換成二進制
11.00100100001110
存起來喔