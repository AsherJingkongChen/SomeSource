import java.math.BigDecimal

class Rgb {
    var r: Int = 0
    var g: Int = 0
    var b: Int = 0
    var r_ratio: Double = 0.0
    var g_ratio: Double = 0.0
    var b_ratio: Double = 0.0

    constructor ()

    constructor (_hexCode: String) {

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
            is Int -> {
                r = __r
                r_ratio = __r.toDouble() / maxInteger
            }
            is Float -> {
                r = (__r * maxInteger).toInt()
                r_ratio = __r.toDouble()
            }
            is Double -> {
                r = (__r * maxInteger).toInt()
                r_ratio = __r
            }
        }
        when (__g) {
            is Int -> {
                g = __g
                g_ratio = __g.toDouble() / maxInteger
            }
            is Float -> {
                g = (__g * maxInteger).toInt()
                g_ratio = __g.toDouble()
            }
            is Double -> {
                g = (__g * maxInteger).toInt()
                g_ratio = __g
            }
        }
        when (__b) {
            is Int -> {
                b = __b
                b_ratio = __b.toDouble() / maxInteger
            }
            is Float -> {
                b = (__b * maxInteger).toInt()
                b_ratio = __b.toDouble()
            }
            is Double -> {
                b = (__b * maxInteger).toInt()
                b_ratio = __b
            }
        }
    }

    /**
     * "`Rgb(r, g, b)`"
     *
     * represents in three 8-bits decimal integers
     */
    fun toDecString(): String {
        return "Rgb(${r}, ${g}, ${b})"
    }

    /**
     * "`Rgb(r_ratio, g_ratio, b_ratio)`"
     *
     * represents in three double-precision ratios
     *
     * rounded down n decimal place
     */
    fun toRatioString(n: Int = 4, PERCENTAGE_MODE: Boolean = false): String {
        return if (!PERCENTAGE_MODE)
            "Rgb(" +
            "${r_ratio.toBigDecimal()
                .setScale(n, BigDecimal.ROUND_DOWN).toPlainString()}, " +
            "${g_ratio.toBigDecimal()
                .setScale(n, BigDecimal.ROUND_DOWN).toPlainString()}, " +
            "${b_ratio.toBigDecimal()
                .setScale(n, BigDecimal.ROUND_DOWN).toPlainString()})"
        else
            "Rgb(" +
            "${(r_ratio.toBigDecimal() * BigDecimal(100))
                .setScale(n, BigDecimal.ROUND_DOWN).toPlainString()}%, " +
            "${(g_ratio.toBigDecimal() * BigDecimal(100))
                .setScale(n, BigDecimal.ROUND_DOWN).toPlainString()}%, " +
            "${(b_ratio.toBigDecimal() * BigDecimal(100))
                .setScale(n, BigDecimal.ROUND_DOWN).toPlainString()}%" +
            ")"

    }

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
                "b_ratio: ${b_ratio} " + "\n" +
                "}"
    }

    /**
     * (R, G, B) == (r, g, b)
     */
    override fun equals(other: Any?): Boolean {
        return if (other is Rgb)
            (r == other.r
            && g == other.g
            && b == other.b)
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

    companion object {

        /**
         * Range validation
         *
         * 1. `Int` (0 ~ 255),
         *
         * 2. `Float` (0.0f ~ 1.0f),
         *
         * 3. `Double` (0.0 ~ 1.0),
         *
         * 4. `String` (Auto Convert)
         */
        fun isFit (n: Any?): Boolean {
            when (n) {
                is Int -> return (n in minInteger..maxInteger)
                is Float -> return (minFloat <= n && n <= maxFloat)
                is Double -> return (minDouble <= n && n <= maxDouble)
                else -> return false
            }
        }

        /**
         * auto `String` convertion handler
         *
         * return `null` when failed to convert
         */
        fun autoStringConvertor(str: String): Any? {
            val testDec: Int? = str.toIntOrNull(10)
            val testFixed: Double? = str.toDoubleOrNull()
            val testHex: Int? = str.toIntOrNull(16)
            if( testDec != null ) return testDec
            if( testFixed != null ) return testFixed
            if( testHex != null ) return testHex
            return null
        }

        const val maxInteger: Int = 255
        const val minInteger: Int = 0
        const val maxFloat: Float = 1f
        const val minFloat: Float = 0f
        const val maxDouble: Double = 1.0
        const val minDouble: Double = 0.0
    }
}
fun main() {
    val R = 0.301
    val G = 245
    val B = 1
    val a = Rgb(R,G,B)
    val b = Rgb()
    println(a)
    println(a.toDecString())
    println(a.toRatioString(0))
    println(a.toRatioString(4))
    println(a.toRatioString(5,true))
    println(a==b)
    println(b)
    println(b.toDecString())
    println(b.toRatioString(0))
    println(b.toRatioString(8, true))
}
