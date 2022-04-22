## [DEPRECATED] No-Clip Audio mix algorithm (Simple, Swift/C/C++ way)

[origin article](https://atastypixel.com/how-to-mix-audio-samples-properly-on-ios/)

origin author: Micheal Tyson

## en-US highlights

#### 1.Objective

digital mixing actually requires a little thought in order to avoid overflowing these bounds and clipping.

(PCM signed int 16-bits)

#
#### 2.Method

- If both samples are positive,

we mix them so that the output value is somewhere between the maximum value of the two samples, 
and the maximum possible value.

- If both samples are negative, 

we mix them so that the output value is somewhere between the minimum value of the two samples, 
and the minimum possible value.

- If one sample is positive, and one is negative, 

we want them to cancel out somewhat.

#
#### 3.Implementation

!['1-1'](https://atastypixel.com/wp-content/uploads/2011/02/Eqn.png)

```swift
/* origin codes, swift */
inline SInt16 TPMixSamples(SInt16 a, SInt16 b) {
    return  
            // If both samples are negative, mixed signal must have an amplitude between the lesser of A and B, and the minimum permissible negative amplitude
            a < 0 && b < 0 ?
                ((int)a + (int)b) - (((int)a * (int)b)/INT16_MIN) :
 
            // If both samples are positive, mixed signal must have an amplitude between the greater of A and B, and the maximum permissible positive amplitude
            ( a > 0 && b > 0 ?
                ((int)a + (int)b) - (((int)a * (int)b)/INT16_MAX)
 
            // If samples are on opposite sides of the 0-crossing, mixed signal should reflect that samples cancel each other out somewhat
            :
                a + b);
}

/* my edited pure code, C/C++ */
inline int16_t NoClipAudioMixTwoSample_I16(int16_t this_, int16_t other_) {
    return
        (this_ < 0 && other_ < 0) ?
            ((int32_t)this_ + (int32_t)other_) - (((int32_t)this_ * (int32_t)other_) / INT16_MIN) :
            
            (this_ > 0 && other_ > 0) ?
                ((int32_t)this_ + (int32_t)other_) - (((int32_t)this_ * (int32_t)other_) / INT16_MAX) :
                
                this_ + other_;
}
```

## zh-TW 摘要

#### 1.目標

PCM音訊混音或是多音軌播放, 把兩個數字加在一起, 但是要迴避 __溢出 (overflow)__

#
#### 2.方法

兩樣本都正的，相加減一減很大的數字

兩個都負的，相加加一加很大的數字

一正一負，不會溢出

#
#### 3.實做

其實code貼過去就好了

`inline` 內聯函數, 傳入兩個short, 展開三種決定, 轉大避免溢出, 再轉回來 __(signed int 16-bits [-1<<16, 1<<16-1])__

其實這算法很老了._.
