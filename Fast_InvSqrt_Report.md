# Fast Inverse Square Root 
## 反平方根快速演算法

### 16 程朗 17 黃品睿 20 廖乃頡

---

## 簡述

Fast Inverse Square Root，反平方根快速演算法，又稱為Fast InvSqrt()，
反平方根快速演算法，最早開發是為了遊戲物理引擎及電腦圖學領域，
若要求取照明和投影的波動角度與反射效果，就常需計算平方根倒數。

---

![Vector](https://miro.medium.com/max/1400/1*7C6G7vRCqcJDZRB5lBEWpA.png)

像是在計算Vector(a,b,c)就常會用到反平方根。
一方面減少運算的資源消耗，另一方面也可減少運算時間過長導致的光學錯誤。

---

## 歷史

---

### id Software的共同創辦人-John D.Carmack II
![co-founder](https://pic2.zhimg.com/v2-364afc9d34fbe5bbd4d350f49fd17abf_r.jpg?source=172ae18b)

雖然在他之前就有許多類似發展，但普遍認為這演算法的發明者是約翰·卡馬克(John D. Carmack II)
而他所作的遊戲引擎，也作為戰慄時空(永遠不出三代:0 )、毀滅戰士等知名神作的物理引擎。

![HF](https://thumbor.4gamers.com.tw/YtX0Pa1r5XY9-NrFUYJeg47Iig8=/800x0/filters:extract_cover():no_upscale():quality(80)/https%3A%2F%2Fimg.4gamers.com.tw%2Fckfinder%2Fimages%2FWhy%2520Lee%2F579998eb9c7aa.jpg)
Valve知名ip-戰慄時空

---

### 發展
1999年，Carmack在 雷神之鎚III競技場(Quake III Arena)中初次發明並使用此演算法。

![quake3](https://raidofgame.com/uploads/posts/2019-12/1575285955_screenshot-3-quake-3-arena.jpg)
Quake III Arena

比起平常的square算法，Fast InvSqrt()有約4倍的速度，故被越來越多圖形與遊戲程式採用。

---

## 目的 與 原理

