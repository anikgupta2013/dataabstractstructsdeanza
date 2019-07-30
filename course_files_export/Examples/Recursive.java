
public class RecursiveAdd 
{

	public int sum = 0;
	int limit = 100;
	int Add(int value)
	{
		if (value <= limit)
		{
			sum += value;
			Add(++value);
		}
		return sum;
	}
	public static void main(String[] s)
	{
		RecursiveAdd radd = new RecursiveAdd();
		radd.Add(radd.sum);
		System.out.println(radd.sum);
	}
}
