class BrickList {
    /* property */
    val list: HashSet<Int> = hashSetOf() // ordered
    var count = 1

    /* method */
    
    fun push (): Int {
        /* dequeue then return head or count */
        val it = list.iterator()
        if (it.hasNext()) {
            val head = it.next()
            list.remove(head)
            return head
        } else {
            return count++
        }
    }

    fun pull (value: Int) {
        /* enqueue */
        list.add(value)
    }
}
