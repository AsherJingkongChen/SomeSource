class BrickList {
    /* property */
    val list: HashSet<Int> = hashSetOf() // ordered
    var count = 0

    /* method */

    fun push (): String {
        /* dequeue then return head or count */
        val it = list.iterator()
        if (it.hasNext()) {
            val head = it.next()
            list.remove(head)
            return head.toString()
        } else {
            count += 1
            return count.toString()
        }
    }

    fun pull (value: Int) {
        /* enqueue */
        list.add(value)
    }
}
