import java.io.File
import kotlin.math.roundToLong
import kotlin.streams.toList

fun part1(template: String, patterns: Map<String, String>) {
    fun step(
        from: String, patterns: Map<String, String>
    ): String {
        val pairs = from.zipWithNext().mapIndexed { index, pair ->
            val key = pair.first.toString() + pair.second
            index + 1 to (patterns[key] ?: "")
        }.filter { it.second.isNotEmpty() }

        val to = StringBuilder(from)
        for ((idx, pair) in pairs.withIndex()) {
            to.insert(idx + pair.first, pair.second)
        }

        return to.toString()
    }

    var res = template
    for (i in 0 until 10) {
        res = step(res, patterns)
    }

    val counts = res.toCharArray().distinct().map {
        res.filter { c -> it == c }.length
    }.sorted()

    println(counts.last() - counts.first())
}

fun part2(template: String, patterns: Map<String, String>) {
    fun step(pairsMap: Map<String, ULong>, patterns: Map<String, String>): Map<String, ULong> {
        val newMap = mutableMapOf<String, ULong>()

        for ((p, v) in pairsMap) {
            val p1 = p[0].toString() + patterns[p]!!
            val p2 = patterns[p]!!.toString() + p[1]
            newMap[p1] = newMap.getOrDefault(p1, 0u) + v
            newMap[p2] = newMap.getOrDefault(p2, 0u) + v
        }

        return newMap
    }

    val pairs = template.zipWithNext().map {
        it.first.toString() + it.second
    }
    var pairsMap = pairs.associateWith {
        pairs.filter { p -> p == it }.size.toULong()
    }

    for (i in 0 until 40) {
        pairsMap = step(pairsMap, patterns)
    }

    val res = mutableMapOf<Char, ULong>()
    pairsMap.forEach {
        it.key.toCharArray().forEach { c ->
            res[c] = res.getOrDefault(c, 0u) + it.value
        }
    }

    val counts = res.map { (it.value.toDouble() / 2).roundToLong() }.sorted()
    println(counts.last() - counts.first())
}

fun main() {
    val br = File("d14input").bufferedReader()
    val template = br.readLine()
    br.readLine()
    val patterns = br.lines().map {
        val (k, v) = it.split(" -> ")
        k to v
    }.toList().toMap()

    part1(template, patterns)
    part2(template, patterns)
}