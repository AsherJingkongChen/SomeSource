package com.example.kotlin_prac.classes

import com.example.kotlin_prac.interfaces.ColorSet
import java.math.BigDecimal

/* class Rgb implements Interface ColorSet */
class Rgb : ColorSet {
    /* properties */

    override var r: Int = 0
    override var g: Int = 0
    override var b: Int = 0
    override var r_ratio: Double = 0.0
    override var g_ratio: Double = 0.0
    override var b_ratio: Double = 0.0
    override var hex_code: String = "#000000"

    /* constructors */

    /**
     * default constructor
     *
     * all  properties are set to 0
     */
    constructor ()

    /**
     * put `#RrGgBb here
     *
     * to construct an Rgb instance
     */
    constructor (_hexColorCode: String) {
        val untagged_hexColorCode = _hexColorCode.slice(1..6)
        var tmp_decColorCode = untagged_hexColorCode.toInt(16)

        hex_code = _hexColorCode

        b = tmp_decColorCode % 256
        tmp_decColorCode /= 256
        g = tmp_decColorCode % 256
        tmp_decColorCode /= 256
        r = tmp_decColorCode % 256
        tmp_decColorCode /= 256

        r_ratio = r.toDouble() / maxInteger
        g_ratio = g.toDouble() / maxInteger
        b_ratio = b.toDouble() / maxInteger
    }

    /**
     * _r, _g, _b can be different types
     *
     * Parameter types allowed are:
     *
     * 1. `Int` (0 ~ 255),
     *
     * 2. `Float` (0.0f ~ 1.0f),
     *
     * 3. `Double` (0.0 ~ 1.0),
     *
     * 4. `String` (Auto Convert)
     */
    constructor (_r: Any, _g: Any, _b: Any) {
        val __r: Any? = if (_r is String) autoStringConvertor(_r) else _r
        val __g: Any? = if (_g is String) autoStringConvertor(_g) else _g
        val __b: Any? = if (_b is String) autoStringConvertor(_b) else _b

        if ( !(isFit(__r) && isFit(__g) && isFit(__b)) ) {
            throw Error("Invalid input")
        }

        when (__r) {
            is Int -> { r = __r }
            is Float -> { r = (__r * maxInteger).toInt() }
            is Double -> { r = (__r * maxInteger).toInt() }
        }
        when (__g) {
            is Int -> { g = __g }
            is Float -> { g = (__g * maxInteger).toInt() }
            is Double -> { g = (__g * maxInteger).toInt() }
        }
        when (__b) {
            is Int -> { b = __b }
            is Float -> { b = (__b * maxInteger).toInt() }
            is Double -> { b = (__b * maxInteger).toInt() }
        }

        r_ratio = r.toDouble() / maxInteger
        g_ratio = g.toDouble() / maxInteger
        b_ratio = b.toDouble() / maxInteger

        hex_code = "#%02X%02X%02X".format(r, g, b)
    }

    /* public methods */

    /**
     * "`Rgb(r, g, b)`"
     *
     * represents in three 8-bits decimal integers
     */
    override fun toDecString(): String {
        return "Rgb(${r}, ${g}, ${b})"
    }

    /**
     * "`#RrGgBb`"
     *
     * represents in hexadecimal color code
     *
     *
     */
    override fun toHexString(UPPERCASE_MODE: Boolean): String {
        return if (UPPERCASE_MODE)
            "#%02X%02X%02X".format(r, g, b)
        else
            "#%02x%02x%02x".format(r, g, b)
    }

    /**
     * "`Rgb(r_ratio, g_ratio, b_ratio)`"
     *
     * represents in three double-precision ratios
     *
     * rounded down n decimal place
     */
    override fun toRatioString(n: Int, PERCENTAGE_MODE: Boolean): String {
        return if (!PERCENTAGE_MODE)
            "Rgb(" +
                    r_ratio.toBigDecimal()
                        .setScale(n, BigDecimal.ROUND_DOWN).toPlainString() + ", " +
                    g_ratio.toBigDecimal()
                        .setScale(n, BigDecimal.ROUND_DOWN).toPlainString() + ", " +
                    b_ratio.toBigDecimal()
                        .setScale(n, BigDecimal.ROUND_DOWN).toPlainString() + ")"
        else
            "Rgb(" +
                    (r_ratio.toBigDecimal() * BigDecimal(100))
                        .setScale(n, BigDecimal.ROUND_DOWN).toPlainString() + "%, " +
                    (g_ratio.toBigDecimal() * BigDecimal(100))
                        .setScale(n, BigDecimal.ROUND_DOWN).toPlainString() + "%, " +
                    (b_ratio.toBigDecimal() * BigDecimal(100))
                        .setScale(n, BigDecimal.ROUND_DOWN).toPlainString() + "%)"

    }

    /* private methods */

    /**
     * Range validation
     *
     * 1. `Int` (0 ~ 255),
     *
     * 2. `Float` (0.0f ~ 1.0f),
     *
     * 3. `Double` (0.0 ~ 1.0)
     */
    protected fun isFit (n: Any?): Boolean {
        when (n) {
            is Int -> return (n in minInteger..maxInteger)
            is Float -> return (minFloat <= n && n <= maxFloat)
            is Double -> return (minDouble <= n && n <= maxDouble)
        }
        return false
    }

    /**
     * auto `String` conversion handler
     *
     * return `null` when failed to convert
     */
    protected fun autoStringConvertor(str: String): Any? {
        val testDec: Int? = str.toIntOrNull(10)
        val testFixed: Double? = str.toDoubleOrNull()
        val testHex: Int? = str.toIntOrNull(16)
        if( testDec != null ) return testDec
        if( testFixed != null ) return testFixed
        if( testHex != null ) return testHex
        return null
    }

    /* arguments */

    override val maxInteger: Int = 255
    override val minInteger: Int = 0
    override val maxFloat: Float = 1f
    override val minFloat: Float = 0f
    override val maxDouble: Double = 1.0
    override val minDouble: Double = 0.0

    /* Common operation methods */

    /**
     * Rgb { r, g, b, r_ratio, g_ratio, b_ratio }
     */
    override fun toString(): String {
        return "Rgb {" + "\n\t" +
                "r: ${r}, " + "\n\t" +
                "g: ${g}, " + "\n\t" +
                "b: ${b}, " + "\n\t" +
                "r_ratio: ${r_ratio}, " + "\n\t" +
                "g_ratio: ${g_ratio}, " + "\n\t" +
                "b_ratio: ${b_ratio}, " + "\n\t" +
                "hex_code: ${hex_code} " + "\n" +
                "}"
    }

    /**
     * (R, G, B) == (r, g, b)
     */
    override fun equals(other: Any?): Boolean {
        return if (other is Rgb)
            hex_code == other.hex_code
        else false
    }

    /**
     * `Integer` in the format "RRRGGGBBB"
     */
    override fun hashCode(): Int {
        var result: Int = r
        result = 1000 * result + g
        result = 1000 * result + b
        return result
    }

    /* static methods and members */

    companion object {
    }
}