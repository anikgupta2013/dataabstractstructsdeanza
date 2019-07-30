class Animal{
	public String name;
	public Animal(String name){
		this.name = name;
	}
	@Override
	public String toString(){
		return name;
	}
}
class Operations<T>{
	void swap(Animal a, Animal b){
		String t = a.name;
		a.name = b.name;
		b.name = t;
	}
}
public class SwapTest {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Animal dog = new Animal("Dog");
		Animal cat = new Animal("Cat");
		
		System.out.println("Before");
		System.out.println("Dog: "+ dog );
		System.out.println("Cat: "+ cat +"\n");
		
		Operations<Animal> operation = new Operations<Animal>();
		operation.swap(dog, cat);
		
		System.out.println("After");
		System.out.println("Dog: "+ dog );
		System.out.println("Cat: "+ cat );

	}

}
