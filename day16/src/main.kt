import java.io.File
import kotlin.collections.ArrayDeque
import kotlin.math.max
import kotlin.math.min
import kotlin.math.pow

val hexToBinary = hashMapOf(
    '0' to "0000",
    '1' to "0001",
    '2' to "0010",
    '3' to "0011",
    '4' to "0100",
    '5' to "0101",
    '6' to "0110",
    '7' to "0111",
    '8' to "1000",
    '9' to "1001",
    'A' to "1010",
    'B' to "1011",
    'C' to "1100",
    'D' to "1101",
    'E' to "1110",
    'F' to "1111"
)

open class Packet(val version: Int, val id: Int)
class LiteralValue(version: Int, id: Int, val value: ULong) : Packet(version, id)
class Operator(version: Int, id: Int, val children: List<Packet>) : Packet(version, id)

fun binaryToDecimal(s: String): ULong {
    tailrec fun helper(s: String, i: ULong): ULong = when {
        s.isEmpty() -> i
        s.first() == '1' -> helper(s.drop(1), i + 2.0.pow(s.lastIndex).toULong())
        else -> helper(s.drop(1), i)
    }

    return helper(s, 0.toULong())
}

fun parseN(input: ArrayDeque<Char>, N: Int): String? {
    var s = ""
    for (i in 1..N) s += input.removeFirstOrNull() ?: return null

    return s
}

fun parsePackets(input: ArrayDeque<Char>, pred: (ArrayDeque<Char>, MutableList<Packet>) -> Boolean): List<Packet> {
    val packets = mutableListOf<Packet>()

    while (pred(input, packets)) {
        val version = binaryToDecimal(parseN(input, 3) ?: break).toInt()
        val typeID = binaryToDecimal(parseN(input, 3) ?: break).toInt()

        when (typeID) {
            4 -> { // literal value
                var s: String
                val num = mutableListOf<Char>()
                do {
                    s = parseN(input, 5) ?: break
                    num.addAll(s.drop(1).toList())
                } while (s.first() != '0')

                packets.add(LiteralValue(version, typeID, binaryToDecimal(num.joinToString(""))))
            }
            else -> { // operator
                val lengthTypeID = parseN(input, 1) ?: break
                when (lengthTypeID.first()) {
                    '0' -> {
                        val numBitsInSubpacket = binaryToDecimal(parseN(input, 15) ?: break).toInt()
                        val subpackets = parsePackets(
                            ArrayDeque(
                                (parseN(input, numBitsInSubpacket) ?: break).toList()
                            )
                        ) { q, _ -> q.isNotEmpty() }
                        if (typeID == 6 && subpackets.size != 2) println(subpackets)
                        packets.add(Operator(version, typeID, subpackets))
                    }
                    else -> {
                        val numSubpackets = binaryToDecimal(parseN(input, 11) ?: break).toInt()
                        val subpackets = parsePackets(input) { _, packets -> packets.size < numSubpackets }
                        packets.add(Operator(version, typeID, subpackets))
                    }
                }
            }
        }
    }

    return packets
}

fun sumVersions(packets: List<Packet>): Int = packets.fold(0) { acc, packet ->
    when (packet) {
        is Operator -> acc + packet.version + sumVersions(packet.children)
        else -> acc + packet.version
    }
}

fun part1(packets: List<Packet>) {
    println(sumVersions(packets))
}

fun evaluatePacket(packet: Packet): ULong = when (packet) {
    is Operator -> {
        when (packet.id) {
            0 -> packet.children.fold(0.toULong()) { acc, packet -> acc + evaluatePacket(packet) }
            1 -> packet.children.fold(1.toULong()) { acc, packet -> acc * evaluatePacket(packet) }
            2 -> packet.children.fold(ULong.MAX_VALUE) { acc, packet -> min(acc, evaluatePacket(packet)) }
            3 -> packet.children.fold(ULong.MIN_VALUE) { acc, packet -> max(acc, evaluatePacket(packet)) }
            5 -> if (evaluatePacket(packet.children[0]) > evaluatePacket(packet.children[1])) 1.toULong() else 0.toULong()
            6 -> if (evaluatePacket(packet.children[0]) < evaluatePacket(packet.children[1])) 1.toULong() else 0.toULong()
            7 -> if (evaluatePacket(packet.children[0]) == evaluatePacket(packet.children[1])) 1.toULong() else 0.toULong()
            else -> throw IllegalArgumentException("invalid id for operator")
        }
    }
    else -> (packet as LiteralValue).value
}

fun part2(packets: List<Packet>) {
    println(evaluatePacket(packets.first()))
}

fun main() {
    val input = ArrayDeque(File("d16input").bufferedReader().readLine().flatMap { hexToBinary[it]!!.toList() })
    val packets = parsePackets(input) { input, _ -> input.isNotEmpty() }

    part1(packets)
    part2(packets)
}