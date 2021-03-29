fun main() 
{
  val numberArrayList = arrayListOf<Int>()
    
  println("list:   ${numberArrayList}")
	
  val numbers = listOf(0, 3, 8, 4, 0, 5, 5, 8, 9, 2)
    
  println("list:   ${numbers}")
  println("list:   ${numbers.sorted()}")
	
  val sets = numbers.toSet()
  println("set:    ${sets}")
  println("contains 7: ${sets.contains(7)}\n")
	
  val set1 = setOf(1,2,3)
	val set2 = mutableSetOf(3,2,1)
  println("set:    ${set1}")
  println("set:    ${set2}")
  println("$set1 == $set2: ${set1 == set2}")
    
  val peopleAges = mutableMapOf<String, Int>(
    "Fred" to 30,
    "Ann" to 23
  )
  peopleAges.put("Barbara", 42)
  peopleAges["Joe"] = 51
  println(peopleAges)
    
  peopleAges["Fred"] = 31
  println(peopleAges)

  peopleAges.forEach { 
    print("${it.key} is ${it.value}, ") 
  }
  println(peopleAges.map {"${it.key} is ${it.value}"}.joinToString(", "))

  val filteredNames = peopleAges.filter{it.key.length < 4}
	println(filteredNames)
    
  /// lambda
  peopleAges.forEach {
    println("${it.key} is ${it.value}") 
  }

  val triple1: (Int) -> Int = { a: Int -> a * 3 }
  println(triple1(5))
  val triple2: (Int) -> Int = { it * 3 }
  println(triple2(5))

  /// Higher-order functions
  println(peopleAges.filter { it.key.length < 4 })

  val peopleNames = listOf("Fred", "Ann", "Barbara", "Joe")
  println(peopleNames.sorted())
  println(peopleNames.sortedWith { str1: String, str2: String -> str1.length - str2.length })
}