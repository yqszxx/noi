<script src='//cdn.bootcss.com/mathjax/2.7.1/MathJax.js?config=TeX-AMS-MML_HTMLorMML'></script>

# 第三周

## 组合

《组合数学》第3章看完，后面有答案的习题做完。

如果有时间/之前已经做完了，就继续看到第5章`二项式系数的单峰性`前。

## splay

splay呢其实没什么好讲的，数据结构本身，旋转、splay的那套理论大家也都懂，复杂度大家也多多少少能脑补（严格的证明反正也不需要）。最多是打标记相关大家可能不是很熟悉。

懂了理论之后，建议找几个优秀的模板，把自己的写法固定一下（就是写一个自己的模板）。

推荐：www.hzwer.com

至于代码的熟练程度，大家可以自己搞个默写的形式，每天起床默一遍，睡前默一遍，在terminal下diff，到**稳定**不出错（或即使有错也能快速纠正）感觉就差不多了。

习题推荐：http://www.cnblogs.com/wangyurzee7/p/5129642.html （这篇博客中提到的所有题包括这题本身，按顺序写一遍，有问题可以看代码）。

## 字符串

### 字符串hash（rk-hash）

写法：
```
struct Hash{
	int base,P;
	int bin[N],hash[N];
	void prepare(int _base,int _P,char *s){
		base=_base;
		P=_P;
		int n=strlen(s+1);
		bin[0]=1;hash[0]=0;
		for (int i=1;i<=n;++i){
			hash[i]=((ll)hash[i-1]*base%P+s[i])%P;
			bin[i]=(ll)bin[i-1]*base%P;
		}
	}
	int get_hash(int l,int r){
		return (hash[r]-(ll)hash[l-1]*bin[r-l+1]%P+P)%P;
	}
} h0;
```

可以做的事：

1. 快速求一个前缀的hash值（$O(1)$）

2. 快速求一个子段的hash值（$O(1)$）

3. 快速求两个后缀（或子串）的lcp（$O(\log n)$）

4. 快速比较两个子串的字典序（$O(\log n)$）

有趣的是，这个hash规则满足区间可加性，于是我们可以用线段树/平衡树来维护字符串，并支持更多的操作。

bzoj：`1692`,`1014`

另外的习题：NOI2016优秀的拆分95分算法（可在UOJ上交）

### AC自动机与fail树

AC自动机：在Trie树上BFS即可建出AC自动机。

fail树：由fail指针组成的树。由于其性质奥妙重重，可能会很有用

经典例题&习题：阿狸的打字机

bzoj：`1535`

### 后缀数组

详见：https://wenku.baidu.com/view/228caa45b307e87101f696a8.html?from=search

本周后缀数组的题，可以做里面的例题，本周不强求。

### 关于后缀自动机

后缀自动机抽象难懂，而且NOI不会考只能用SAM做的题，个人不是特别建议大家学。

但SAM非常好用，而且代码更短。一旦学会，可以起飞（基本能全面覆盖SA能做的事）。

所以大家可以自行决定是否要学。

如果要学，可以看clj的营员交流ppt（见附件）。

如果不学，请务必熟练背诵建SA的代码。

## 分治

我有一个课件，见附件。

### 补充

二分答案的常用场合：

1. 最大的最小值、最小的最大值

2. 中位数最大（小）、平均值最大（小）

3. 分数规划的形式：求$$max(\frac{\sum A}{\sum B})$$

## 动态规划

### 习题

下面是这次的习题：

`556-500`

`558-275`

`562-250`

`562-1000`

`563-500`

`565-250`

`566-500`

停课同学要求：2000；非停课同学要求：1500

搞TC客户端的教程在这里：http://blog.csdn.net/u011639256/article/details/38167823

网页版TC在这里：http://arena.topcoder.com
