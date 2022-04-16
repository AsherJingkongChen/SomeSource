/**
 * Practice for Kotlin OOP
 */
// open v.s. final (default)
open class Shape {
    // properties
    open protected var shape: String = "Shape"
    
    // use default properties
    constructor ()
    
    // put parameters and construct properties
    constructor (_shape: String) {
        shape = _shape
    }
    
    // other members
    open protected var filled: Boolean = false
    open protected var clear_time: Int = 0 
    
    // other methods
    open fun draw() { 
        if (filled) {
            println("${shape} : already drew")
        }
        else {
            println("${shape} : draw") 
        	filled = true
        }
    }
    open fun clear(): Int { 
        if (filled) {
            println("${shape} : cleared")
            filled = false
            return ++clear_time
        }
        else {
            println("${shape} : already cleared")
            return clear_time
        }
    }
}

class Circle() : Shape("Circle") // Simple inheritance

fun main() {
    val a = Circle() // or try to use Shape()
    a.draw()
    a.draw() // already
    println(a.clear()) // 1
    println(a.clear()) // 1 already
    a.draw()
    println(a.clear()) // 2
    //a.shape = "Broken_wheel" // protected from outter classes, try it
}
