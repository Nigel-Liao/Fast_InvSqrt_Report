---
lang: zh-tw
title: Fast InvSqrt
description: Report on Inverse Square Root Fast Algorithm
image: https://i0.wp.com/blogs.embarcadero.com/wp-content/uploads/2021/01/Delphi-Fast-Inverse-Square-Root-Quake-3-Arena-6465040.jpg?resize=1140%2C675&ssl=1
type: slide
robots: noindex, nofollow
transition: 'slide'

---

## Fast Inverse Square Root
  
#### 16 程朗 17 黃品睿 20 廖奶茶

---

## 簡述

Fast Inverse Square Root，  
或是 Fast InvSqrt()  
是計算一個數的根號分之一的快速算法

$$
f(x) = \frac{1}{\sqrt{x}}
$$

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

## 程式碼

----

Carmack在Quake III中的原始碼  

```c
#if !idppc
/*
** float q_rsqrt( float number )
*/
float Q_rsqrt( float number )
{
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y  = number;
    i  = * ( long * ) &y;    // evil floating point bit level hacking
    i  = 0x5f3759df - ( i >> 1 );    // what the fuck?
    y  = * ( float * ) &i;
    y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

#ifndef Q3_VM
#ifdef __linux__
    assert( !isnan(y) ); // bk010122 - FPE?
#endif
#endif
    return y;
}

float Q_fabs( float f ) {
    int tmp = * ( int * ) &f;
    tmp &= 0x7FFFFFFF;
    return * ( float * ) &tmp;
}
#endif
```
##### <span>註：halfs 應拼為 halves<!-- .element: class="fragment" data-fragment-index="3" --></span>

---

## IEEE 754

#### 儲存浮點數的方法

![qr](https://i.imgur.com/9MRN4Kg.png =300x300)  
https://www.h-schmidt.net/FloatConverter/IEEE754.html
<!-- 給同學玩一玩 IEEE754 儲存浮點數的方法 -->

----

#### float

![float](https://i.imgur.com/z5hmqIl.png)

fraction = mantissa = $M$
exponent = $E$
sign = $S$ (= 0)

$$
x = (-1)^S(1+\frac{M}{2^{23}}) \times 2^{E-127}
$$

---

### 原理

$$
\begin{align*}
\log_2 x &= \log_2((1+\frac{M}{2^{23}}) \times 2^{E-127}) \\
&= \log_2(1+\frac{M}{2^{23}}) + E - 127
\end{align*}
$$

----

![graph](https://i.imgur.com/RcSv4UC.png =594x550)

$$
\log_2(1+x) \approx x + 0.0430 \quad \textrm{for } x \in [0, 1]
$$

----

$$
\begin{align*}
&\mspace{25mu}\log_2(1+\frac{M}{2^{23}}) + E - 127 \\
&\approx \frac{M}{2^{23}} + 0.0430 + E - 127 \\
&= 2^{-23}(\color{pink} {E \times 2^{23} + M}) - 126.957
\end{align*}
$$

----

$\color{pink} {2^{23}E + M}$ 就是……
![img](https://i.imgur.com/4tAwPzO.png)
把此浮點數當成一個整數 `long` 來看的值！！

在計算$\tfrac{1}{\sqrt{x}}$時，我們可以利用這個技巧，  
將我們的 $x$ 換成他的 $\log$ 值，  
這樣拿來作運算會方便的多！

$$
\color{lime} {\small \log_2((1+\frac{M}{2^{23}}) \times 2^{E-127}) \approx 2^{-23}(E \times 2^{23} + M) - 126.957}
$$

---

### 逐步分析

----

```c
float Q_rsqrt(float number) {
    long i;
    float x2, y;
    const float threehalfs = 1.5F;
    x2 = number * 0.5F;
    y  = number;
```

----

```c
    i  = * ( long * ) &y;    // evil floating point bit level hacking
```

把y這個float裡的資料直接塞進i這個long裡面

![floating point bit hack](https://i.imgur.com/uUQ798d.jpg)



----

```c
    i  = 0x5f3759df - ( i >> 1 );      // what the fuck?
```

----

設算出來的 $\tfrac{1}{\sqrt{x}}$ 為 $a = (1+\tfrac{M_a}{2^{23}}) \times 2^{E_a - 127}$，  
及欲求反平方根之數為 $b = (1+\tfrac{M_b}{2^{23}}) \times 2^{E_b - 127}$，  
浮點數整數化整理可得:

----

$$
(1+\frac{M_a}{2^{23}}) \times 2^{E_a-127} = ((1+\frac{M_b}{2^{23}}) \times 2^{E_b - 127})^{-\tfrac{1}{2}} \\
\scriptsize \log_2((1+\frac{M_a}{2^{23}}) \times 2^{E_a-127}) = \log_2(((1+\frac{M_b}{2^{23}}) \times 2^{E_b - 127})^{-\tfrac{1}{2}})\\
2^{-23}(E_a \times 2^{23} + M_a) - 126.957 \\
= -\tfrac{1}{2}(2^{-23}(E_b \times 2^{23} + M_b) - 126.957) \\
E_a \times 2^{23} + M_a \approx \color{pink} {1.597 \times 10^9} - \frac{1}{2}(E_b \times 2^{23} + M_b)
$$

----

$$
E_a \times 2^{23} + M_a \approx \color{pink} {1.597 \times 10^9} - \frac{1}{2}(E_b \times 2^{23} + M_b) \\
(1.597 \times 10^9)_{10} = \textrm{5f3759df}_{16}
$$

----

```c
    y  = * ( float * ) &i;
```
把i這個long記憶體區塊裡面放的資料  
硬塞進y這個float記憶體區塊中  

----

```c
    y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
    // y  = y * ( threehalfs - ( x2 * y * y ) );
    // 2nd iteration, this can be removed
    return y;
}
```

Newton's method!!  
使用牛頓法來使我們大概  
算出來的反平方根值更準確

----

![newton's method](https://tutorial.math.lamar.edu/classes/calci/NewtonsMethod_Files/image001.png =630x360)

$$
x_1 = x_0 - \frac{f(x_0)}{f'(x_0)}
$$

----

如果我們製造一形如

$$
f(y) = \frac{1}{y^2} - \textrm{number}
$$

的函數的話，那麼 $f(y)$ 應該要等於 $0$

所以呢，我們可以運用牛頓法，得到更準確的 $y$

----

$$
f(y) = \frac{1}{y^2} - n \\
f'(y) = -\frac{2}{y^3} \\
$$

----

$$
\begin{align*}
y_1 &= y_0 - \frac{f(y_0)}{f'(y_0)} \\
    &= y_0 - \frac{\frac{1}{y_0^2} - n}{\frac{-2}{y_0^3}} \\
    &= y_0 + \frac{y_0}{2} - \frac{ny_0^3}{2} \\
    &= y_0(1.5 - \frac{n}{2}y_0^2)
\end{align*}
$$

```c
    y = y (threehalfs - x2 * y * y);  // (x2 = n/2)
```

---

### 結語  

---

Fast InvSqrt()，比尋常方法快約三到四倍。  
縱使代價為精準度下降1%，  
但仍是2000年左右遊戲常用到的光學演算方式。

----

#### 現在呢？

在 Quake 3 發布幾年後，  
英特爾發布了x86 SSE指令集，  
其中包括硬件中的SQRT功能！  

----

#### SQRT

現在，如果寫 <code> x**(-1/2) </code> 不會調用牛頓例程  
(Newton routine)，而只是調用RSQRTSS指令。

更快，也更簡單。

----

雖然在硬體更新後，這方法已不必繼續使用。  
但靠軟體勝過硬體限制，或許不會有Quake III  
不會促使SSE誕生，也不會有現金蓬勃的遊戲市場  

----

最後，  
向這些電腦駭客，  
獻上最大的敬意。  

----

![faster](http://i.imgur.com/WHMBN.gif)
##### John D.Carmack II: 快，還要更快!

---

### Q&A

----

##### **P.S. 我有這款遊戲，可以來試玩看看。**

----

參考資料:

> https://www.youtube.com/watch?v=p8u_k2LIZyo&t=745s
> https://levelup.gitconnected.com/death-of-quake-3s-inverse-square-root-hack-32fd2eadd7b7
> https://matthewarcus.wordpress.com/2012/11/19/134/
> https://stackoverflow.com/questions/47946741/what-does-i-long-y-do
> https://213style.blogspot.com/2014/07/john-carmack.html
> https://en.wikipedia.org/wiki/Fast_inverse_square_root
> https://github.com/id-Software/Quake-III-Arena/blob/dbe4ddb10315479fc00086f08e25d968b4b43c49/code/game/q_math.c
> https://www.felixcloutier.com/x86/sqrtss
> https://www.felixcloutier.com/x86/rsqrtss
> https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html
> https://gcc.gnu.org
> http://www.matrix67.com/data/InvSqrt.pdf

---

### 報告到此結束

謝謝大家