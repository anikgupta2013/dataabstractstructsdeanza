import java.io.*;
import java.util.*;

/*
Generics are a facility of generic programming that was added to the Java programming 
language in 2004 as part of J2SE 5.0. They allow "a type or method to operate on objects 
of various types while providing compile-time type safety." A common use of this feature 
is when using a Java Collection that can hold objects of any type, to specify the specific 
type of object stored in it.
 */

public class Node <T>
{
	T data;

	public Node(T t)
	{
		data = t;
	}
	public T get()
	{
		return data;
	}
	public void set(T t)
	{
		data = t;
	}

	public static void main(String[] args)
	{
		Integer inumber = new Integer(123);
		Node<Integer> inode = new Node<Integer>(inumber);
		System.out.println(inode.get());
		
		String astring = "abc";
		Node<String> snode = new Node<String>(astring);
		System.out.println(snode.get());
		
		ArrayList<String> alist = new ArrayList<String>();
		Node<ArrayList<String>> anode = new Node<ArrayList<String>>(alist);
		anode.get().add("ABC");
		anode.get().add("DEF");
		anode.get().add("GHI");
		for (int x=0; x<anode.get().size(); x++)
			System.out.println(anode.get().get(x));
	} 
}
