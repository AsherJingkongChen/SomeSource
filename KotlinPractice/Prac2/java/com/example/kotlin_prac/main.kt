package com.example.kotlin_prac

import com.example.kotlin_prac.classes.Rgb

fun main() {
    val Rn = 0.301f
    val Gn = 245
    val Bn = 1
    val a = Rgb(Rn, Gn, Bn)
    val b = Rgb(a.toHexString())

    /* general test */
    println(a)
    println(a.toDecString())
    println(a.toRatioString())
    println(a.toRatioString(2,true))
    println(a.toHexString())
    println()
    println(b)
    println(b.toDecString())
    println(b.toRatioString(5))
    println(b.toRatioString(2,true))
    println(b.toHexString(false))
    /* general test end */
}