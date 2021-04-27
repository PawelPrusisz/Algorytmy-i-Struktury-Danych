import java.util.ArrayList;
import java.util.Scanner;

public class zadanie1{
	static long compares = 0;
	static long swaps = 0;
	static long startTime = 0;
	static long endTime = 0;
	static String sortType = "";
	static String order = "";
	
	public static void InsertionSort(ArrayList<Integer> tab, String comp) throws Exception
	{
		long startTime = System.nanoTime();
		long compares = 0;
		long swaps = 0;
		if(comp.equals("<="))
		{
			for(int i = 1; i < tab.size(); i++)
			{
				int key = tab.get(i);
				int j = i-1;
				compares++;
				while( (j >= 0) && (tab.get(j) >= key) )
				{
					System.err.println("comp " + key + " " + tab.get(j));
					compares++;
					tab.set(j+1, tab.get(j));
					swaps++;
					System.err.println("swap "  + tab.get(j+1) + " " + tab.get(j));
					j--;
				}
				tab.set(j+1, key);
				swaps++;
			}
			long endTime = System.nanoTime();
			long diff = endTime - startTime;
			double sec = diff/1000000;
			System.err.println("comps: " + compares + " swaps: " + swaps + " time: " + sec + "ms");
			boolean check = true;
			for(int i = 1; i < tab.size(); i++)
			{
				if(tab.get(i-1) > tab.get(i))
				{
					check = false;
					System.out.println(i-1 + " " + tab.get(i-1));
					System.out.println(i + " " + tab.get(i));
					break;
				}
			}
			if(check)
			{
				System.out.println(tab.size());
				for(int i = 0; i < tab.size(); i++)
				{
					System.out.print(tab.get(i) + " ");
				}
			}
			else
			{
				System.out.println("Nie posortowano :(");
				for(int i = 0; i < tab.size(); i++)
				{
					System.out.print(tab.get(i) + " ");
				}
			}
		}
		else if(comp.equals(">="))
		{
			for(int i = 1; i < tab.size(); i++)
			{
				int key = tab.get(i);
				int j = i-1;
				compares++;
				while( (j >= 0) && (tab.get(j) <= key) )
				{
					System.err.println("comp " + key + " " + tab.get(j));
					compares++;
					tab.set(j+1, tab.get(j));
					swaps++;
					System.err.println("swap "  + tab.get(j+1) + " " + tab.get(j));
					j--;
				}
				tab.set(j+1, key);
				swaps++;
			}
			long endTime = System.nanoTime();
			long diff = endTime - startTime;
			double sec = diff/1000000;
			System.err.println("comps: " + compares + " swaps: " + swaps + " time: " + sec + "ms");
			boolean check = true;
			for(int i = 1; i < tab.size(); i++)
			{
				if(tab.get(i-1) < tab.get(i))
				{
					check = false;
					System.out.println(i-1 + " " + tab.get(i-1));
					System.out.println(i + " " + tab.get(i));
					break;
				}
			}
			if(check)
			{
				System.out.println(tab.size());
				for(int i = 0; i < tab.size(); i++)
				{
					System.out.print(tab.get(i) + " ");
				}
			}
			else
			{
				System.out.println("Nie posortowano :(");
				for(int i = 0; i < tab.size(); i++)
				{
					System.out.print(tab.get(i) + " ");
				}
			}
		}
		else 
		{
			throw new Exception();
		}
	}
	
	public static void Merge(ArrayList<Integer> tab, int start, int mid, int end, String comp) throws Exception
	{
		if(comp.equals("<="))
		{
			int newStart = mid + 1;
			compares ++;
			System.err.println("comp " + tab.get(mid) + " " + tab.get(newStart));
			if(tab.get(mid) <= tab.get(newStart) )return;
			
			while(start <= mid && newStart <= end)
			{	
				compares ++;
				System.err.println("comp " + tab.get(start) + " " + tab.get(newStart));
				if(tab.get(start) <= tab.get(newStart))
				{
					start++;
				}
				else
				{
					int val = tab.get(newStart);
					int index = newStart;
					
					while(index != start)
					{
						swaps++;
						System.err.println("swap " + tab.get(index) + " " + tab.get(index -1));
						tab.set(index, tab.get(index -1));
						index --;
					}
					swaps++;
					System.err.println("swap " + tab.get(start) + " " + val);
					tab.set(start, val);
					start++;
					mid++;
					newStart++;
				}
			}
		}
		else if (comp.equals(">="))
		{
			int newStart = mid+1;
			compares ++;
			System.err.println("comp " + tab.get(mid) + " " + tab.get(newStart));
			if(tab.get(mid) >= tab.get(newStart) )return;
			
			while(start <= mid && newStart <= end)
			{	
				compares ++;
				System.err.println("comp " + tab.get(start) + " " + tab.get(newStart));
				if(tab.get(start) >= tab.get(newStart))
				{
					start++;
				}
				else
				{
					int val = tab.get(newStart);
					int index = newStart;
					
					while(index!= start)
					{
						swaps++;
						System.err.println("swap " + tab.get(index) + " " + tab.get(index -1));
						tab.set(index, tab.get(index -1));
						index --;
					}
					swaps++;
					System.err.println("swap " + tab.get(start) + " " + val);
					tab.set(start, val);
					start++;
					mid++;
					newStart++;
				}
			}
		}
		else
		{
			throw new Exception();
		}
		
	}
	
	public static void MergeSort(ArrayList<Integer> tab, int left, int right, String comp) throws Exception
	{
		if(left < right)
		{
			int mid = (left + right) / 2;
			MergeSort(tab, left, mid, comp);
			MergeSort(tab, mid+1, right, comp);
			Merge(tab, left, mid, right, comp);
		}
	}
	
	public static void MegreInit(ArrayList<Integer> tab, String comp) throws Exception
	{
		startTime = System.nanoTime();
		compares = 0;
		swaps = 0;
		int left = 0;
		int right = tab.size()-1;
		MergeSort(tab, left, right, comp);
		endTime = System.nanoTime();
		long diff = endTime - startTime;
		double time = diff/1000000;
		System.err.println("comps: " + compares + " swaps: " + swaps + " time: " + time + "ms");
		boolean check = true;
		if(comp.equals("<="))
		{
			for(int i = 1; i < tab.size(); i++)
			{
				if(tab.get(i-1) > tab.get(i))
				{
					check = false;
					System.out.println(i-1 + " " + tab.get(i-1));
					System.out.println(i + " " + tab.get(i));
					break;
				}
			}
		}
		else if(comp.equals(">="))
		{
			for(int i = 1; i < tab.size(); i++)
			{
				if(tab.get(i-1) < tab.get(i))
				{
					check = false;
					System.out.println(i-1 + " " + tab.get(i-1));
					System.out.println(i + " " + tab.get(i));
					break;
				}
			}
		}
		else
		{
			throw new Exception();
		}
		if(check)
		{
			System.out.println(tab.size());
			for(int i = 0; i < tab.size(); i++)
			{
				System.out.print(tab.get(i) + " ");
			}
		}
		else
		{
			System.out.println("Nie posortowano :(");
			for(int i = 0; i < tab.size(); i++)
			{
				System.out.print(tab.get(i) + " ");
			}
		}
		
	}
	
	public static int Partition(ArrayList<Integer> tab, int left, int right, String comp) throws Exception
	{
		int pivot = tab.get(right);
		int i = left - 1;
		
		if(comp.equals("<="))
		{
			for(int j = left; j < right; j++)
			{
				compares++;
				System.err.println("comp " + tab.get(j) + " " + pivot);
				if(tab.get(j) <= pivot)
				{
					i++;
					int swp = tab.get(i);
					swaps++;
					System.err.println("swap " + tab.get(i) + " " + tab.get(j));
					tab.set(i, tab.get(j));
					tab.set(j, swp);
				}
			}
			
			int swp = tab.get(i+1);
			swaps++;
			System.err.println("swap " + swp + " " + tab.get(right));
			tab.set(i+1, tab.get(right));
			tab.set(right, swp);
		}
		else if (comp.equals(">="))
		{
			for(int j = left; j < right; j++)
			{
				compares++;
				System.err.println("comp " + tab.get(j) + " " + pivot);
				if(tab.get(j) >= pivot)
				{
					i++;
					int swp = tab.get(i);
					swaps++;
					System.err.println("swap " + tab.get(i) + " " + tab.get(j));
					tab.set(i, tab.get(j));
					tab.set(j, swp);
				}
			}
			
			int swp = tab.get(i+1);
			swaps++;
			System.err.println("swap " + swp + " " + tab.get(right));
			tab.set(i+1, tab.get(right));
			tab.set(right, swp);
		}
		else
		{
			throw new Exception();
		}
		return i+1;
	}
	
	public static void QuickSort(ArrayList<Integer> tab, int left, int right, String comp) throws Exception
	{
		if(left < right)
		{
			int pivot = Partition(tab, left, right, comp);
			
			QuickSort(tab, left, pivot -1, comp);
			QuickSort(tab, pivot + 1, right, comp);
		}
	}
	
	public static void QuickInit(ArrayList<Integer> tab, String comp) throws Exception
	{
		compares = 0;
		swaps = 0;
		startTime = System.nanoTime();
		int left =0;
		int right = tab.size()-1;
		QuickSort(tab, left, right, comp);
		endTime = System.nanoTime();
		long diff = endTime - startTime;
		double time = diff/1000000;
		System.err.println("comps: " + compares + " swaps: " + swaps + " time: " + time + "ms");
		boolean check = true;
		if(comp.equals("<="))
		{
			for(int i = 1; i < tab.size(); i++)
			{
				if(tab.get(i-1) > tab.get(i))
				{
					check = false;
					System.out.println(i-1 + " " + tab.get(i-1));
					System.out.println(i + " " + tab.get(i));
					break;
				}
			}
		}
		else if(comp.equals(">="))
		{
			for(int i = 1; i < tab.size(); i++)
			{
				if(tab.get(i-1) < tab.get(i))
				{
					check = false;
					System.out.println(i-1 + " " + tab.get(i-1));
					System.out.println(i + " " + tab.get(i));
					break;
				}
			}
		}
		else
		{
			throw new Exception();
		}
		if(check)
		{
			System.out.println(tab.size());
			for(int i = 0; i < tab.size(); i++)
			{
				System.out.print(tab.get(i) + " ");
			}
		}
		else
		{
			System.out.println("Nie posortowano :(");
			for(int i = 0; i < tab.size(); i++)
			{
				System.out.print(tab.get(i) + " ");
			}
		}
	}
	
	public static void main(String[] args) throws Exception {
		
		//for(int i = 0; i< args.length; i++)System.out.println(args[i]);
		
		for(int i = 0; i < args.length; i++)
		{
			if(args[i].equals("type"))
			{
				i++;
				sortType = args[i];
			}
			else if(args[i].equals("comp"))
			{
				i++;
				order = args[i];
			}
		}
		
		int n = 0;
		
		Scanner scanner = new Scanner(System.in);
		
		n = scanner.nextInt();
		ArrayList<Integer> tab = new ArrayList<Integer>();
		
		for(int i = 0; i <  n; i++)
		{
			int tmp = scanner.nextInt();
			tab.add(tmp);
		}
		
		if(sortType.equals("quick"))
		{
			System.out.println("\n QuickSort");
			QuickInit(tab, order);
		}
		else if(sortType.equals("merge"))
		{
			System.out.println("\n MergeSort");
			MegreInit(tab, order);
		}
		else if(sortType.equals("insert"))
		{
			System.out.println("\n Sort");
			InsertionSort(tab, order);
		}
		scanner.close();
	}
}
