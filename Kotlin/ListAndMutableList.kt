open class Item(val name: String, val price: Int)

class Noodles : Item("Noodles", 10) 
{
   override fun toString(): String 
   {
       return name
   }
}
class Vegetables1() : Item("Vegetables", 5) 
{
   override fun toString(): String 
   {
       return name
   }
}

class Vegetables2(val topping1: String,
                 val topping2: String, 
                 val topping3: String): Item("Vegetables", 5) 
	{
    	override fun toString(): String 
   		{
       		return name
        }
   	}


class Vegetables3(val toppings: List<String>): Item("Vegetables", 5) 
	{
    	override fun toString(): String 
   		{
       		return name
        }
   	}


fun main() {
    /// List
    val numbers: List<Int> = listOf(1, 2, 3, 4, 5, 6)
    //val numbers = listOf(1, 2, 3, 4, 5, 6)
    println("List: $numbers")
    println("Size: ${numbers.size}")
    println("First element: ${numbers[0]}")
    println("Last element: ${numbers[numbers.size - 1]}")

    println("First: ${numbers.first()}")
    println("Last: ${numbers.last()}")

    println("Contains 4? ${numbers.contains(4)}")
    println("Contains 7? ${numbers.contains(7)}")

    val colors = listOf("green", "orange", "blue")
    //colors.add("purple") /// Error
    //colors[0] = "yellow" /// Error
    println("Reversed list: ${colors.reversed()}")
    println("List: $colors")
	println("Sorted list: ${colors.sorted()}")
    
    val oddNumbers = listOf(5, 3, 7, 1)
    println("List: $oddNumbers")
    println("Sorted list: ${oddNumbers.sorted()}")

    /// Mutable Lists => Java 的 ListArray 
    val entrees = mutableListOf<String>()
    // val entrees: MutableList<String> = mutableListOf()
    println("Entrees: $entrees")
    println("Add noodles: ${entrees.add("noodles")}")
    println("Entrees: $entrees")
    println("Add spaghetti: ${entrees.add("spaghetti")}")
    println("Entrees: $entrees")

    val moreItems = listOf("ravioli", "lasagna", "fettuccine")
    println("Add list: ${entrees.addAll(moreItems)}")
    println("Entrees: $entrees")
    //entrees.add(10)
    println("Remove spaghetti: ${entrees.remove("spaghetti")}")
    println("Entrees: $entrees")
    println("Remove item that doesn't exist: ${entrees.remove("rice")}")
    println("Entrees: $entrees")

    println("Remove first element: ${entrees.removeAt(0)}")
    println("Entrees: $entrees")

    entrees.clear()
    println("Entrees: $entrees")
    println("Empty? ${entrees.isEmpty()}")

    val names = listOf("Jessica", "Henry", "Alicia", "Jose")
    for (name in names) 
    {
        println("$name - Number of characters: ${name.length}")
    }
    /*
    for (item in list) print(item) // Iterate over items in a list
    for (item in 'b'..'g') print(item) // Range of characters in an alphabet
    for (item in 1..5) print(item) // Range of numbers
    for (item in 5 downTo 1) print(item) // Going backward
    for (item in 3..6 step 2) print(item) // Prints: 35
	  */
    
    val noodles = Noodles()
    val vegetables1 = Vegetables1()
    println(noodles)
    println(vegetables1)
    
	  val vegetables2 = Vegetables2("Cabbage", "Sprouts", "Onion")	
    val vegetables3 = Vegetables3(listOf("cabbage", "sprouts", "onion"))
}