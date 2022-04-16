package com.example.kotlin_prac.interfaces

interface ColorSet {
    var r: Int
    var g: Int
    var b: Int
    var r_ratio: Double
    var g_ratio: Double
    var b_ratio: Double
    var hex_code: String

    fun toDecString(): String
    fun toHexString(UPPERCASE_MODE: Boolean = true): String
    fun toRatioString(n: Int = 4, PERCENTAGE_MODE: Boolean = false): String

    val maxInteger: Int
    val minInteger: Int
    val maxFloat: Float
    val minFloat: Float
    val maxDouble: Double
    val minDouble: Double
}